/// Program for writing the KTM waveforms to a file, to place on webpage...
//
// T. Lindner

#include <stdio.h>
#include <iostream>
#include <time.h>

#include "TRootanaEventLoop.hxx"
#include "TAnaManager.hxx"

#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>

class Analyzer: public TRootanaEventLoop {




public:

  // Last time we opened file.
  int lastOpenFileDay; 
  int lastOpenFileHour;

  // output file
  std::fstream outfile;


  // An analysis manager.  Define and fill histograms in 
  // analysis manager.
  TAnaManager *anaManager;
  
  Analyzer() {
    //DisableAutoMainWindow();
    DisableRootOutput(true);
    UseBatchMode();
    SetOnlineName("file_writer");
    anaManager = 0;
    
  };

  virtual ~Analyzer() {};

  void Initialize(){

    lastOpenFileDay = -2; 
    lastOpenFileHour = -2;

  }

  void OpenFileForWriting(struct tm * timeinfo){

    // If file is already open, close it.
    if(outfile.is_open()){
      outfile.close();
      std::cout << "Closed old file " <<  std::endl;
    }

    // Check if directory exists for this hour; if it doesn't create it.
    //    time_t ts = time;
    //struct tm * timeinfo;
    //timeinfo = localtime (&ts);

    char rootdirectory[500];
    sprintf(rootdirectory,"/home/ucn/online/data");

    struct stat info;
    char pathname[100];
    sprintf(pathname,"%s/%04i/%02i/%02i",rootdirectory,timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday);    

    if( stat( pathname, &info ) != 0 ){
      printf( "cannot access directory %s; creating.\n", pathname );

      char tempname[100];
      sprintf(tempname,"%s/%04i",rootdirectory,timeinfo->tm_year+1900);    
      if(stat( tempname, &info ) != 0 ){
	
	int dir_err = mkdir(tempname, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (-1 == dir_err){ 
	  printf("Error creating directory %s!n",tempname);exit(1); 
	}else{
	  printf("Created directory %s\n",tempname);
	}
      }      

      sprintf(tempname,"%s/%04i/%02i",rootdirectory,timeinfo->tm_year+1900,timeinfo->tm_mon+1);    
      if(stat( tempname, &info ) != 0 ){
	
	int dir_err = mkdir(tempname, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (-1 == dir_err){ 
	  printf("Error creating directory %s!n",tempname);exit(1); 
	}else{
	  printf("Created directory %s\n",tempname);
	}
      }      

      sprintf(tempname,"%s/%04i/%02i/%02i",rootdirectory,timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday);    
      if(stat( tempname, &info ) != 0 ){
	
	int dir_err = mkdir(tempname, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (-1 == dir_err){ 
	  printf("Error creating directory %s!n",tempname);exit(1); 
	}else{
	  printf("Created directory %s\n",tempname);
	}
      }      

    }else if(!( info.st_mode & S_IFDIR)){  // S_ISDIR() doesn't exist on my windows 
      printf( "%s is no directory\n", pathname );
      exit(0);
    }

    // Open a file for writing...
    char filename[100];
    sprintf(filename,"%s/ktm_data_hour%02i00.dat",pathname,timeinfo->tm_hour);        

    outfile.open (filename, std::fstream::in | std::fstream::out | std::fstream::app);
    if(!outfile.is_open()){
      std::cout << "Failed to open outfile: " << filename << std::endl;
      exit(0);
    }else{
      std::cout << "Successfully opened file " << filename << std::endl;
    }

    lastOpenFileDay = timeinfo->tm_mday;
    lastOpenFileHour = timeinfo->tm_hour;

  }


  void InitManager(){
    
    if(anaManager)
      delete anaManager;
    anaManager = new TAnaManager();

  }
  
  
  void BeginRun(int transition,int run,int time){
    
  }


  bool ProcessMidasEvent(TDataContainer& dataContainer){

    if(!anaManager) InitManager();

    // Check if the output file is not opened or if the hour has changed.  Otherwise open it.
    int time = dataContainer.GetMidasData().GetTimeStamp();
    time_t ts = time;
    struct tm * timeinfo;
    timeinfo = localtime (&ts);
    if(!outfile.is_open() || 
       (lastOpenFileDay != timeinfo->tm_mday || lastOpenFileHour != timeinfo->tm_hour)){
      OpenFileForWriting(timeinfo);
    }
    
    anaManager->ProcessMidasEvent(dataContainer);
    TH1D *waveform = anaManager->GetRawWaveform();

    // Add timestamp to the event
    outfile << dataContainer.GetMidasData().GetTimeStamp() << " " ;
    
    // Add all data to event
    for(int i = 0; i < waveform->GetNbinsX(); i++){
      outfile << waveform->GetBinContent(i+1) << " ";
    }
    outfile << std::endl;
    


    return true;
  }


}; 


int main(int argc, char *argv[])
{

  Analyzer::CreateSingleton<Analyzer>();
  return Analyzer::Get().ExecuteLoop(argc, argv);

}

