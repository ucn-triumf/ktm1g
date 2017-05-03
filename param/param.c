// test griffin parameter read/write:  param r|w par chan val
//    gcc -g -o param param.c

#include <stdio.h>
#include <netinet/in.h> /* sockaddr_in, IPPROTO_TCP, INADDR_ANY */
#include <netdb.h>      /* gethostbyname */
#include <stdlib.h>     /* exit() */
#include <string.h>     /* memset() */
#include <errno.h>      /* errno */
#include <unistd.h>     /* usleep */
#include <time.h>       /* select */

#define SERVER_HOSTNAME "grifip10" // grif16
//#define SERVER_HOSTNAME "grifip09" // grifc
#define DATA_PORT 8800
#define CMD_PORT  8808

#define WRITE 1 // parameter encoding
#define READ  0

#define MAX_PKT_SIZE 1500

#define NUM_PAR        89
#define PARNAMELEN     32
#define COMPARE_LEN     6
#define MAX_LISTSIZE 1024

static int addr_len = sizeof(struct sockaddr);
static struct sockaddr_in cmd_addr, data_addr;
static int data_socket, cmd_socket;
static char    msgbuf[256];
static unsigned char replybuf[MAX_PKT_SIZE];
static int chanlist[MAX_LISTSIZE];

typedef struct parname_struct {
   int param_id; char param_name[PARNAMELEN];
} Parname;
Parname param_names[NUM_PAR]={
   { 1,  "threshold"},{ 2, "pulserctrl"},{ 3,   "polarity"},{ 4,  "diffconst"},
   { 5, "integconst"},{ 6, "decimation"},{ 7, "numpretrig"},{ 8, "numsamples"},
   { 9,   "polecorn"},{10,   "hitinteg"},{11,    "hitdiff"},{12, "integdelay"},
   {13,"wavebufmode"},{14,  "trigdtime"},{15,  "enableadc"},{16,    "dettype"},
   {17,   "synclive"},{18,   "syncdead"},{19,   "cfddelay"},{20,    "cfdfrac"},
   {21,   "exthiten"},{22,  "exthitreq"},{23,  "chandelay"},{24,   "blrspeed"},
   {25,  "phtrigdly"},{26, "cfdtrigdly"},{27,    "cfddiff"},{28,     "cfdint"},
                                                            {31,  "timestamp"},
   {32,  "eventrate"},{33, "evraterand"},{34,   "baseline"},{35,   "risetime"},
   {36,    "blrauto"},{37, "blinedrift"},{38,      "noise"},
                                         {63,        "csr"},{64,   "chanmask"},
   {65, "trigoutdly"},{66, "trigoutwid"},{67,"exttrigcond"},
   {96,     "debug1"},{97,     "debug2"},
   {128,   "filter1"},{129,   "filter2"},{130,   "filter3"},{131,   "filter4"},
   {132,   "filter5"},{133,   "filter6"},{134,   "filter7"},{135,   "filter8"},
   {136,   "filter9"},{137,  "filter10"},{138,  "filter11"},{139,  "filter12"},
   {140,  "filter13"},{141,  "filter14"},{142,  "filter15"},{143,  "filter16"},
   {144,   "pscale1"},{145,   "pscale2"},{146,   "pscale3"},{147,   "pscale4"},
   {148,  "coincwin"},
   {256,   "scaler1"},{257,   "scaler2"},{258,   "scaler3"},{259,   "scaler4"},
   {260,   "scaler5"},{261,   "scaler6"},{262,   "scaler7"},{263,   "scaler8"},
   {264,   "scaler9"},{265,  "scaler10"},{266,  "scaler11"},{267,  "scaler12"},
   {268,  "scaler13"},{269,  "scaler14"},{270,  "scaler15"},{271,  "scaler16"},
   {272,  "scaler17"},{273,  "scaler18"},{274,  "scaler19"},{275,  "scaler20"},
   {276,  "scaler21"},{277,  "scaler22"},{278,  "scaler23"},{279,  "scaler24"},
   {-1,    "invalid"}
};

int comseplist_to_array(char *string, int *entries, int maxentry);
void param_encode(char *buf, int par, int write, int chan, int val);
int  param_decode(unsigned char *buf, int *par, int *chan, int *val);
int open_udp_socket(int port, char *hostname, struct sockaddr_in *addr);
int sndmsg(int fd, struct sockaddr_in *addr, char *msg, int len);
int testmsg(int socket, int timeout);
int readmsg(int socket);

void usage(char *prog)
{
   int i;
   fprintf(stderr,"%s: r|w par chan[0-15,255] [val] [host]\n", prog);
   fprintf(stderr,"   parameters ...\n");
   for(i=0; i<NUM_PAR-1; i++){
      if( param_names[i].param_id == -1 ){ break; }
      fprintf(stderr,"  %3d: %-11s", param_names[i].param_id,
                                   param_names[i].param_name );
      if( ((i+1) % 4) == 0 ){ fprintf(stderr,"\n"); }
   }
   if( (i % 4) != 0 ){ fprintf(stderr,"\n"); }
}

char *parname(int num)
{
   int i;
   for(i=0; i<NUM_PAR-1; i++){
      if(param_names[i].param_id == num||param_names[i].param_id == -1){break;}
   }
   return( param_names[i].param_name );
}

int read_paramnum(char *arg, int *parnum)
{
   char name[32];
   int i, p, len;

   if( sscanf(arg, "%d", parnum ) > 0 ){ return(0); } // was just number
   p=0;
   for(i=0; i<32; i++){// convert to lower case, [letters/digits only]
      if( arg[i] == '\0' ){ name[p] = '\0'; break; }          // end of string
      if( arg[i] >= 65 && arg[i] <=  90 ){ name[p++] = arg[i] + 32; }// upr2lwr
      if( arg[i] >= 97 && arg[i] <= 122 ){ name[p++] = arg[i]; }     // lower
      if( arg[i] >= 48 && arg[i] <=  57 ){ name[p++] = arg[i]; }     // digit
   }
   //len = ( strlen(name) < COMPARE_LEN ) ? strlen(name) : COMPARE_LEN;
   len = strlen(name);
   for(i=0; i<NUM_PAR; i++){            // look for name in list of parameters
      if( param_names[i].param_id == -1 ){ break; } // end of list
      p = strlen(param_names[i].param_name);
      if( p < len ){ continue; }
      if( strncmp(name, param_names[i].param_name, ( p<len ? p : len) ) == 0){
         *parnum = param_names[i].param_id; return(0);
      }
   }
   // didn't find it
   fprintf(stderr,"couldn't read param in %s [->%s]\n", arg, name);
   return( -1 );
}

int read_channum(char *arg)
{
   if( sscanf(arg, "chan%d", &chanlist[0] ) <= 0 ){
      fprintf(stderr,"couldn't read chan in %s\n", arg ); return(-1);
   }
   if( sscanf(arg, "chan0x%x", &chanlist[0] ) > 0 ){
     return(1); /* also allow single hex value */
   }
   return( comseplist_to_array(&arg[4], chanlist, MAX_LISTSIZE) );
}

int read_paramval(char *arg, int *val)
{
   if( sscanf(arg, "0x%x", val ) > 0 ){ return(0); }
   if( sscanf(arg, "%d",   val ) > 0 ){ return(0); }
   fprintf(stderr,"couldn't read value in %s\n", arg );
   return( -1 );
}

void printreply(int bytes)
{
   int i;
   printf("  ");
   for(i=0; i<bytes; i++){
      printf("%02x", replybuf[i]);
      if( !((i+1)%2) ){ printf(" "); }
   }
   printf("::");
   for(i=0; i<bytes; i++){
      if( replybuf[i] > 20 && replybuf[i] < 127 ){
         printf("%c", replybuf[i]);
      } else {
         printf(".", replybuf[i]);
      }
   }
   printf("\n");
}

int write_param(int par, int chan, int val)
{
   int bytes;
   printf("Writing %d [0x%08x] into %s[par%d] on chan%d[%2d,%2d,%3d]\n",
	  val, val, parname(par), par, chan, chan>>12, (chan>>8)&0xF, chan&0xFF);
   param_encode(msgbuf, par, WRITE, chan, val);
   sndmsg(cmd_socket, &cmd_addr, msgbuf, 12);
   bytes = readmsg(cmd_socket);
   printf("   reply      :%d bytes ...", bytes);
   printreply(bytes);
   return(0);
}

#define FWTBUFSIZ 64
static char tstampbuf[FWTBUFSIZ];
struct tm *tptr;

int read_param(int par, int chan)
{
   int bytes, val;
   time_t ts;
   printf("Reading %s[par%d] on chan%d[%2d,%2d,%3d]\n",
      parname(par), par, chan, chan>>12, (chan>>8)&0xF, chan&0xFF);
   param_encode(msgbuf, par, READ, chan, 0);
   sndmsg(cmd_socket, &cmd_addr, msgbuf, 12);
   bytes = readmsg(cmd_socket);
   printf("   reply      :%d bytes ... ", bytes);
   printreply(bytes);
   bytes = readmsg(cmd_socket);
   printf("   read-return:%d bytes ... ", bytes);
   printreply(bytes);
   if( param_decode(replybuf, &par, &chan, &val) == 0 ){
     if( par == 31 ){
       ts = val;
       tptr = gmtime(&ts);
       strftime(tstampbuf, FWTBUFSIZ, "%d%b%g_%H:%M", tptr);
       printf("%10s[par%2d] on chan%5d[%2d,%2d,%3d] is %s [0x%08x]\n",
       parname(par),par,chan,chan>>12,(chan>>8)&0xF,chan&0xFF,tstampbuf,val);
     } else {
       printf("%10s[par%2d] on chan%5d[%2d,%2d,%3d] is %10u [0x%08x]\n",
       parname(par), par, chan, chan>>12, (chan>>8)&0xF, chan&0xFF, val, val);
     }
   }
   return(0);
}

int main(int argc, char *argv[])
{
   int i, bytes, read=0, write=0, nchan, par, val;
   char *hostname = SERVER_HOSTNAME;

   memset(chanlist,-1,(sizeof(int)*MAX_LISTSIZE));

   if( argc > 5 ){ hostname = argv[5]; }
   if( argc < 4 ){ usage(argv[0]); exit(-1); }
   if(        strncmp(argv[1],"r",1) == 0 ){ read  = 1;
   } else if( strncmp(argv[1],"w",1) == 0 ){ write = 1;
      if( argc < 5 ){ usage(argv[0]); exit(-1); }
      if( read_paramval(argv[4], &val) ){ usage(argv[0]); exit(-1); }
   } else { usage(argv[0]); exit(-1); }
   if( read_paramnum(argv[2], &par )       ){ usage(argv[0]); exit(-1); }
   if( (nchan=read_channum (argv[3])) <= 0 ){ usage(argv[0]); exit(-1); }

   if( (data_socket = open_udp_socket(DATA_PORT,hostname,&data_addr)) < 0 ){;}
   if( (cmd_socket  = open_udp_socket(CMD_PORT, hostname,&cmd_addr )) < 0 ){;}

   for(i=0; i<nchan; i++){
      if( write ){ write_param(par, chanlist[i], val); }
      else {       read_param (par, chanlist[i]);      }
   }
   exit(0);
}

// initial test ...
//   p,a, r,m,   2,0, 0,0,   83,3, 0,0    len=12
//   data sent to chan starts with rm, ends with 83,3
//   memcpy(msgbuf, "PARM", 4);
//   *(unsigned short *)(&msgbuf[4]) =   2; // parnum = 2       [0x0002]
//   *(unsigned short *)(&msgbuf[6]) =   0; // op=write, chan=0 [0x0000]
//   *(unsigned int   *)(&msgbuf[8]) = 899; // value = 899 [0x0000 0383]
void param_encode(char *buf, int par, int write, int chan, int val)
{
   memcpy(buf, "PARM", 4);
   buf [4] = (par & 0x3f00)     >>  8; buf[ 5] = (par & 0x00ff);
   buf[ 6] = (chan& 0xFf00)     >>  8; buf[ 7] = (chan& 0x00ff);
   buf[ 8] = (val & 0xff000000) >> 24; buf[ 9] = (val & 0x00ff0000) >> 16;
   buf[10] = (val & 0x0000ff00) >>  8; buf[11] = (val & 0x000000ff);
   if( ! write ){ buf[4] |= 0x40; }
}

int param_decode(unsigned char *buf, int *par, int *chan, int *val)
{
   if( strncmp(buf, "RDBK", 4) != 0 ){ return(-1); } // wrong header
   if( ! (buf[4] & 0x40) ){ return(-1); } // readbit not set
   *par  = ((buf[4] & 0x3f ) << 8) | buf[5];
   *chan = ((buf[6] & 0xff ) << 8) | buf[7];
   *val  = (buf[8]<<24) | (buf[9]<<16) | (buf[10]<<8) | buf[11];
   return(0);
}

/* convert string containing comma-separated list (e.g 1,2-3,5,6-9) to array of values */
int comseplist_to_array(char *string, int *entries, int maxentry)
{
   int i, nentry=0, n=0, val, low, high, range=0;
   char *ptr = string;

   for(i=strlen(ptr)-1; i>=0; i--){ /* remove any trailing whitespace */
      if( ptr[i] != ' ' && ptr[i] != '\n' && ptr[i] != '\t'){ break; }
      ptr[i] = '\0';
   }
   while( strlen(ptr) ){    // an empty string, will just return(0)
      // decode first item [should be digit]
      if( sscanf(ptr,"%d%n", &val, &n) < 1 || n < 1 ){
         fprintf(stderr,"unexpected non-digit in String [%s]...\n", string);
         return(0);
      }
      ptr += n;
      // next item can be either dash or comma (or end of string)
      if( *ptr == '-' ){
         if( range ){
            fprintf(stderr,"excess '-' in [%s]...\n",string);
            return(0);
	 }
         if( *(ptr+1) == '\0' ){
            fprintf(stderr,"string [%s] ends after '-' ...\n", string);
            return(0);
	 }
         low = val; range = 1; ++ptr;
      } else if( *ptr ==  ',' || *ptr == '\0' ){
         if( range ){ high = val; range = 0;
	 } else { low = high = val; }
         if( *ptr ==  ',' ){ ++ptr; }
      } else {
         fprintf(stderr,"unexpected separator in String [%s]...\n", string);
         return(0);
      }
      // range flag is set while decoding range, and cleared when decoding complete
      if( ! range ){
	 if( high < low ){ i = low; low = high; high = i; }
         for(i=low; i<=high; i++){
            entries[nentry++] = i;
            if( nentry >= maxentry ){
               fprintf(stderr,"too many entries [max%d] in String [%s]...\n",
                 maxentry, string);
               return(0);
	    }
         }
      }
   }
   return(nentry);
}

///////////////////////////////////////////////////////////////////////////
//////////////////////      network data link      ////////////////////////

int sndmsg(int sock_fd, struct sockaddr_in *addr, char *message, int msglen)
{
   struct sockaddr_in client_addr;
   int bytes, flags=0;

   if( (bytes = sendto(sock_fd, message, msglen, flags,
        (struct sockaddr *)addr, addr_len) ) < 0 ){
      fprintf(stderr,"sndmsg: sendto failed\n");
      return(-1);
   }
   return(bytes);
}

// select: -ve=>error, zero=>no-data +ve=>data-avail
int testmsg(int socket, int timeout)
{
   int num_fd; fd_set read_fds;
   struct timeval tv;

   tv.tv_sec = 0; tv.tv_usec = timeout;
   num_fd = socket+1; FD_ZERO(&read_fds); FD_SET(socket, &read_fds);
   return( select(num_fd, &read_fds, NULL, NULL, &tv) );
}

// reply pkts have 16bit dword count, then #count dwords
int readmsg(int socket)
{
   struct sockaddr_in client_addr;
   int bytes, flags=0;

   if( testmsg(socket, 10000) < 0 ){ return(-2); } // wait 10ms for msg
   if( (bytes = recvfrom(socket, replybuf, MAX_PKT_SIZE, flags,
        (struct sockaddr *) &client_addr, (socklen_t *)&addr_len) ) == -1 ){
       return -1;
   }
   return( bytes );
}

int open_udp_socket(int server_port, char *hostname, struct sockaddr_in *addr)
{
   struct sockaddr_in local_addr;
   struct hostent *hp;
   int sock_fd;

   int mxbufsiz = 0x00800000; /* 8 Mbytes ? */
   int sockopt=1; // Re-use the socket
   if( (sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ){
      fprintf(stderr,"udptest: ERROR opening socket\n");
      return(-1);
   }
   setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof(int));
   if(setsockopt(sock_fd, SOL_SOCKET,SO_RCVBUF, &mxbufsiz, sizeof(int)) == -1){
      fprintf(stderr,"udptest: setsockopt for buff size\n");
      return(-1);
   }
   memset(&local_addr, 0, sizeof(local_addr));
   local_addr.sin_family = AF_INET;
   local_addr.sin_port = htons(0);          // 0 => use any available port
   local_addr.sin_addr.s_addr = INADDR_ANY; // listen to all local addresses
   if( bind(sock_fd, (struct sockaddr *)&local_addr, sizeof(local_addr) )<0) {
      fprintf(stderr,"udptest: ERROR on binding\n");
      return(-1);
   }
   // now fill in structure of server addr/port to send to ...
   bzero((char *) addr, addr_len );
   if( (hp=gethostbyname(hostname)) == NULL ){
      fprintf(stderr,"udptest: can't get host address for %s\n", hostname);
      return(-1);
   }
   memcpy(&addr->sin_addr, hp->h_addr_list[0], hp->h_length);
   addr->sin_family = AF_INET;
   addr->sin_port = htons(server_port);

   return(sock_fd);
}

///////////////////////////////////////////////////////////////////////////
////////////////////      comma-separated list       //////////////////////

