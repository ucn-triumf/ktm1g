/********************************************************************\

  Name:         experim.h
  Created by:   ODBedit program

  Contents:     This file contains C structures for the "Experiment"
                tree in the ODB and the "/Analyzer/Parameters" tree.

                Additionally, it contains the "Settings" subtree for
                all items listed under "/Equipment" as well as their
                event definition.

                It can be used by the frontend and analyzer to work
                with these information.

                All C structures are accompanied with a string represen-
                tation which can be used in the db_create_record function
                to setup an ODB structure which matches the C structure.

  Created on:   Tue Apr 14 13:24:19 2015

\********************************************************************/

#define EXP_PARAM_DEFINED

typedef struct {
  char      comment[128];
} EXP_PARAM;

#define EXP_PARAM_STR(_name) const char *_name[] = {\
"[.]",\
"comment = STRING : [128] testing temperature dependence",\
"",\
NULL }

#define EXP_EDIT_DEFINED

typedef struct {
  char      comment[128];
  BOOL      write_data;
} EXP_EDIT;

#define EXP_EDIT_STR(_name) const char *_name[] = {\
"[.]",\
"Comment = LINK : [35] /Experiment/Run parameters/comment",\
"Write Data = LINK : [19] /Logger/Write Data",\
"",\
NULL }

#ifndef EXCL_TRIGGER

#define TRIGGER_COMMON_DEFINED

typedef struct {
  WORD      event_id;
  WORD      trigger_mask;
  char      buffer[32];
  INT       type;
  INT       source;
  char      format[8];
  BOOL      enabled;
  INT       read_on;
  INT       period;
  double    event_limit;
  DWORD     num_subevents;
  INT       log_history;
  char      frontend_host[32];
  char      frontend_name[32];
  char      frontend_file_name[256];
  char      status[256];
  char      status_color[32];
  BOOL      hidden;
} TRIGGER_COMMON;

#define TRIGGER_COMMON_STR(_name) const char *_name[] = {\
"[.]",\
"Event ID = WORD : 1",\
"Trigger mask = WORD : 0",\
"Buffer = STRING : [32] SYSTEM",\
"Type = INT : 2",\
"Source = INT : 0",\
"Format = STRING : [8] MIDAS",\
"Enabled = BOOL : y",\
"Read on = INT : 1",\
"Period = INT : 50",\
"Event limit = DOUBLE : 0",\
"Num subevents = DWORD : 0",\
"Log history = INT : 0",\
"Frontend host = STRING : [32] grsmid00.triumf.ca",\
"Frontend name = STRING : [32] fegrifip09",\
"Frontend file name = STRING : [256] fegrifdev.c",\
"Status = STRING : [256] fegrifip09@grsmid00.triumf.ca",\
"Status color = STRING : [32] #00FF00",\
"Hidden = BOOL : n",\
"",\
NULL }

#endif

#ifndef EXCL_SCALAR

#define SCALAR_COMMON_DEFINED

typedef struct {
  WORD      event_id;
  WORD      trigger_mask;
  char      buffer[32];
  INT       type;
  INT       source;
  char      format[8];
  BOOL      enabled;
  INT       read_on;
  INT       period;
  double    event_limit;
  DWORD     num_subevents;
  INT       log_history;
  char      frontend_host[32];
  char      frontend_name[32];
  char      frontend_file_name[256];
  char      status[256];
  char      status_color[32];
  BOOL      hidden;
} SCALAR_COMMON;

#define SCALAR_COMMON_STR(_name) const char *_name[] = {\
"[.]",\
"Event ID = WORD : 2",\
"Trigger mask = WORD : 0",\
"Buffer = STRING : [32] SYSTEM",\
"Type = INT : 1",\
"Source = INT : 0",\
"Format = STRING : [8] MIDAS",\
"Enabled = BOOL : n",\
"Read on = INT : 511",\
"Period = INT : 800",\
"Event limit = DOUBLE : 0",\
"Num subevents = DWORD : 0",\
"Log history = INT : 0",\
"Frontend host = STRING : [32] grsmid00.triumf.ca",\
"Frontend name = STRING : [32] fegrifip09",\
"Frontend file name = STRING : [256] fegrifdev.c",\
"Status = STRING : [256] fegrifip09@grsmid00.triumf.ca",\
"Status color = STRING : [32] #00FF00",\
"Hidden = BOOL : n",\
"",\
NULL }

#endif

#ifndef EXCL_HV_0

#define HV_0_COMMON_DEFINED

typedef struct {
  WORD      event_id;
  WORD      trigger_mask;
  char      buffer[32];
  INT       type;
  INT       source;
  char      format[8];
  BOOL      enabled;
  INT       read_on;
  INT       period;
  double    event_limit;
  DWORD     num_subevents;
  INT       log_history;
  char      frontend_host[32];
  char      frontend_name[32];
  char      frontend_file_name[256];
  char      status[256];
  char      status_color[32];
  BOOL      hidden;
} HV_0_COMMON;

#define HV_0_COMMON_STR(_name) const char *_name[] = {\
"[.]",\
"Event ID = WORD : 30",\
"Trigger mask = WORD : 0",\
"Buffer = STRING : [32] SYSTEM",\
"Type = INT : 16",\
"Source = INT : 0",\
"Format = STRING : [8] MIDAS",\
"Enabled = BOOL : y",\
"Read on = INT : 255",\
"Period = INT : 3000",\
"Event limit = DOUBLE : 0",\
"Num subevents = DWORD : 0",\
"Log history = INT : 1",\
"Frontend host = STRING : [32] grsmid00.triumf.ca",\
"Frontend name = STRING : [32] FeSy2527-0",\
"Frontend file name = STRING : [256] fesy2527.c",\
"Status = STRING : [256] Ok",\
"Status color = STRING : [32] #00FF00",\
"Hidden = BOOL : n",\
"",\
NULL }

#define HV_0_SETTINGS_DEFINED

typedef struct {
  struct {
    struct {
      struct {
        char      system_name[32];
        char      ip[32];
        INT       linktype;
        INT       first_slot;
        INT       cratemap;
      } dd;
      struct {
        char      description[128];
        char      name[128];
        char      model[15];
        WORD      channels;
      } slot_0;
      struct {
        char      description[128];
        char      name[128];
        char      model[15];
        WORD      channels;
      } slot_2;
      struct {
        char      description[128];
        char      name[128];
        char      model[15];
        WORD      channels;
      } slot_6;
      struct {
        char      description[128];
        char      name[128];
        char      model[15];
        WORD      channels;
      } slot_7;
      struct {
        char      description[128];
        char      name[128];
        char      model[15];
        WORD      channels;
      } slot_9;
      struct {
        char      description[128];
        char      name[128];
        char      model[15];
        WORD      channels;
      } slot_14;
    } sy2527;
  } devices;
  char      names[72][32];
  float     update_threshold_measured[72];
  float     update_threshold_current[72];
  float     zero_threshold[72];
  float     voltage_limit[72];
  float     current_limit[72];
  float     trip_time[72];
  float     ramp_up_speed[72];
  float     ramp_down_speed[72];
  DWORD     chstate[72];
} HV_0_SETTINGS;

#define HV_0_SETTINGS_STR(_name) const char *_name[] = {\
"[Devices/sy2527/DD]",\
"System Name = STRING : [32] sy2527",\
"IP = STRING : [32] 142.90.119.252",\
"LinkType = INT : 0",\
"First Slot = INT : 0",\
"crateMap = INT : 1141182468",\
"",\
"[Devices/sy2527/Slot 0]",\
"Description = STRING : [128] 12 Ch Pos 6KV 200uA Ind En",\
"Name = STRING : [128] sy2527",\
"Model = STRING : [15] A1832E",\
"Channels = WORD : 12",\
"",\
"[Devices/sy2527/Slot 2]",\
"Description = STRING : [128] 12 Ch Pos 6KV 200uA Ind En",\
"Name = STRING : [128] sy2527",\
"Model = STRING : [15] A1832E",\
"Channels = WORD : 12",\
"",\
"[Devices/sy2527/Slot 6]",\
"Description = STRING : [128] 12 Ch Pos 6KV 200uA Ind En",\
"Name = STRING : [128] sy2527",\
"Model = STRING : [15] A1832E",\
"Channels = WORD : 12",\
"",\
"[Devices/sy2527/Slot 7]",\
"Description = STRING : [128] 12 Ch Pos 6KV 200uA Ind En",\
"Name = STRING : [128] sy2527",\
"Model = STRING : [15] A1832E",\
"Channels = WORD : 12",\
"",\
"[Devices/sy2527/Slot 9]",\
"Description = STRING : [128] 12 Ch Pos 6KV 200uA Ind En",\
"Name = STRING : [128] sy2527",\
"Model = STRING : [15] A1832E",\
"Channels = WORD : 12",\
"",\
"[Devices/sy2527/Slot 14]",\
"Description = STRING : [128] 12 Ch Pos 6KV 200uA Ind En",\
"Name = STRING : [128] sy2527",\
"Model = STRING : [15] A1832E",\
"Channels = WORD : 12",\
"",\
"[.]",\
"Names = STRING[72] :",\
"[32] GRG16BN00X",\
"[32] GRG16GN00X",\
"[32] GRG16RN00X",\
"[32] GRG16WN00X",\
"[32] EMPTY",\
"[32] GRG14GN00X",\
"[32] EMPTY",\
"[32] EMPTY",\
"[32] EMPTY",\
"[32] EMPTY",\
"[32] EMPTY",\
"[32] EMPTY",\
"[32] GRG13BN00X",\
"[32] GRG13GN00X",\
"[32] GRG13RN00X",\
"[32] GRG13WN00X",\
"[32] GRG14BN00X",\
"[32] BadChan",\
"[32] GRG14RN00X",\
"[32] GRG14WN00X",\
"[32] GRG15BN00X",\
"[32] GRG15GN00X",\
"[32] GRG15RN00X",\
"[32] GRG15WN00X",\
"[32] GRG10BN00X",\
"[32] GRG10GN00X",\
"[32] GRG10RN00X",\
"[32] GRG10WN00X",\
"[32] GRG11BN00X",\
"[32] GRG11GN00X",\
"[32] GRG11RN00X",\
"[32] GRG11WN00X",\
"[32] GRG12BN00X",\
"[32] GRG12GN00X",\
"[32] GRG12RN00X",\
"[32] GRG12WN00X",\
"[32] GRG07BN00X",\
"[32] GRG07GN00X",\
"[32] GRG07RN00X",\
"[32] GRG07WN00X",\
"[32] GRG08BN00X",\
"[32] GRG08GN00X",\
"[32] GRG08RN00X",\
"[32] GRG08WN00X",\
"[32] GRG09BN00X",\
"[32] GRG09GN00X",\
"[32] GRG09RN00X",\
"[32] GRG09WN00X",\
"[32] GRG04BN00X",\
"[32] GRG04GN00X",\
"[32] GRG04RN00X",\
"[32] GRG04WN00X",\
"[32] GRG05BN00X",\
"[32] GRG05GN00X",\
"[32] GRG05RN00X",\
"[32] GRG05WN00X",\
"[32] GRG06BN00X",\
"[32] GRG06GN00X",\
"[32] GRG06RN00X",\
"[32] GRG06WN00X",\
"[32] GRG01BN00X",\
"[32] GRG01GN00X",\
"[32] GRG01RN00X",\
"[32] GRG01WN00X",\
"[32] GRG02BN00X",\
"[32] GRG02GN00X",\
"[32] GRG02RN00X",\
"[32] GRG02WN00X",\
"[32] GRG03BN00X",\
"[32] GRG03GN00X",\
"[32] GRG03RN00X",\
"[32] GRG03WN00X",\
"Update Threshold Measured = FLOAT[72] :",\
"[0] 0.5",\
"[1] 0.5",\
"[2] 0.5",\
"[3] 0.5",\
"[4] 0.5",\
"[5] 0.5",\
"[6] 0.5",\
"[7] 0.5",\
"[8] 0.5",\
"[9] 0.5",\
"[10] 0.5",\
"[11] 0.5",\
"[12] 0.5",\
"[13] 0.5",\
"[14] 0.5",\
"[15] 0.5",\
"[16] 0.5",\
"[17] 0.5",\
"[18] 0.5",\
"[19] 0.5",\
"[20] 0.5",\
"[21] 0.5",\
"[22] 0.5",\
"[23] 0.5",\
"[24] 0.5",\
"[25] 0.5",\
"[26] 0.5",\
"[27] 0.5",\
"[28] 0.5",\
"[29] 0.5",\
"[30] 0.5",\
"[31] 0.5",\
"[32] 0.5",\
"[33] 0.5",\
"[34] 0.5",\
"[35] 0.5",\
"[36] 0.5",\
"[37] 0.5",\
"[38] 0.5",\
"[39] 0.5",\
"[40] 0.5",\
"[41] 0.5",\
"[42] 0.5",\
"[43] 0.5",\
"[44] 0.5",\
"[45] 0.5",\
"[46] 0.5",\
"[47] 0.5",\
"[48] 0.5",\
"[49] 0.5",\
"[50] 0.5",\
"[51] 0.5",\
"[52] 0.5",\
"[53] 0.5",\
"[54] 0.5",\
"[55] 0.5",\
"[56] 0.5",\
"[57] 0.5",\
"[58] 0.5",\
"[59] 0.5",\
"[60] 0.5",\
"[61] 0.5",\
"[62] 0.5",\
"[63] 0.5",\
"[64] 0.5",\
"[65] 0.5",\
"[66] 0.5",\
"[67] 0.5",\
"[68] 0.5",\
"[69] 0.5",\
"[70] 0.5",\
"[71] 0.5",\
"Update Threshold Current = FLOAT[72] :",\
"[0] 1",\
"[1] 1",\
"[2] 1",\
"[3] 1",\
"[4] 1",\
"[5] 1",\
"[6] 1",\
"[7] 1",\
"[8] 1",\
"[9] 1",\
"[10] 1",\
"[11] 1",\
"[12] 1",\
"[13] 1",\
"[14] 1",\
"[15] 1",\
"[16] 1",\
"[17] 1",\
"[18] 1",\
"[19] 1",\
"[20] 1",\
"[21] 1",\
"[22] 1",\
"[23] 1",\
"[24] 1",\
"[25] 1",\
"[26] 1",\
"[27] 1",\
"[28] 1",\
"[29] 1",\
"[30] 1",\
"[31] 1",\
"[32] 1",\
"[33] 1",\
"[34] 1",\
"[35] 1",\
"[36] 1",\
"[37] 1",\
"[38] 1",\
"[39] 1",\
"[40] 1",\
"[41] 1",\
"[42] 1",\
"[43] 1",\
"[44] 1",\
"[45] 1",\
"[46] 1",\
"[47] 1",\
"[48] 1",\
"[49] 1",\
"[50] 1",\
"[51] 1",\
"[52] 1",\
"[53] 1",\
"[54] 1",\
"[55] 1",\
"[56] 1",\
"[57] 1",\
"[58] 1",\
"[59] 1",\
"[60] 1",\
"[61] 1",\
"[62] 1",\
"[63] 1",\
"[64] 1",\
"[65] 1",\
"[66] 1",\
"[67] 1",\
"[68] 1",\
"[69] 1",\
"[70] 1",\
"[71] 1",\
"Zero Threshold = FLOAT[72] :",\
"[0] 20",\
"[1] 20",\
"[2] 20",\
"[3] 20",\
"[4] 20",\
"[5] 20",\
"[6] 20",\
"[7] 20",\
"[8] 20",\
"[9] 20",\
"[10] 20",\
"[11] 20",\
"[12] 20",\
"[13] 20",\
"[14] 20",\
"[15] 20",\
"[16] 20",\
"[17] 20",\
"[18] 20",\
"[19] 20",\
"[20] 20",\
"[21] 20",\
"[22] 20",\
"[23] 20",\
"[24] 20",\
"[25] 20",\
"[26] 20",\
"[27] 20",\
"[28] 20",\
"[29] 20",\
"[30] 20",\
"[31] 20",\
"[32] 20",\
"[33] 20",\
"[34] 20",\
"[35] 20",\
"[36] 20",\
"[37] 20",\
"[38] 20",\
"[39] 20",\
"[40] 20",\
"[41] 20",\
"[42] 20",\
"[43] 20",\
"[44] 20",\
"[45] 20",\
"[46] 20",\
"[47] 20",\
"[48] 20",\
"[49] 20",\
"[50] 20",\
"[51] 20",\
"[52] 20",\
"[53] 20",\
"[54] 20",\
"[55] 20",\
"[56] 20",\
"[57] 20",\
"[58] 20",\
"[59] 20",\
"[60] 20",\
"[61] 20",\
"[62] 20",\
"[63] 20",\
"[64] 20",\
"[65] 20",\
"[66] 20",\
"[67] 20",\
"[68] 20",\
"[69] 20",\
"[70] 20",\
"[71] 20",\
"Voltage Limit = FLOAT[72] :",\
"[0] 3600",\
"[1] 3600",\
"[2] 3600",\
"[3] 3600",\
"[4] 3600",\
"[5] 3600",\
"[6] 3600",\
"[7] 3600",\
"[8] 3600",\
"[9] 3600",\
"[10] 3600",\
"[11] 3600",\
"[12] 3599",\
"[13] 3599",\
"[14] 3599",\
"[15] 3599",\
"[16] 4500",\
"[17] 3599",\
"[18] 4500",\
"[19] 4500",\
"[20] 4500",\
"[21] 4500",\
"[22] 4500",\
"[23] 4500",\
"[24] 3600",\
"[25] 4100",\
"[26] 3600",\
"[27] 3600",\
"[28] 3600",\
"[29] 3600",\
"[30] 4100",\
"[31] 3600",\
"[32] 3600",\
"[33] 3600",\
"[34] 3600",\
"[35] 3600",\
"[36] 3600",\
"[37] 3600",\
"[38] 3600",\
"[39] 3600",\
"[40] 3600",\
"[41] 3600",\
"[42] 3600",\
"[43] 3600",\
"[44] 3600",\
"[45] 3600",\
"[46] 3600",\
"[47] 3600",\
"[48] 3600",\
"[49] 3600",\
"[50] 3600",\
"[51] 3600",\
"[52] 3600",\
"[53] 3600",\
"[54] 3600",\
"[55] 3600",\
"[56] 3600",\
"[57] 3600",\
"[58] 3600",\
"[59] 3600",\
"[60] 3600",\
"[61] 3600",\
"[62] 4100",\
"[63] 3600",\
"[64] 3600",\
"[65] 3600",\
"[66] 3600",\
"[67] 3600",\
"[68] 3600",\
"[69] 3600",\
"[70] 3600",\
"[71] 3600",\
"Current Limit = FLOAT[72] :",\
"[0] 20",\
"[1] 20",\
"[2] 20",\
"[3] 20",\
"[4] 20",\
"[5] 20",\
"[6] 20",\
"[7] 20",\
"[8] 20",\
"[9] 20",\
"[10] 20",\
"[11] 20",\
"[12] 0.2",\
"[13] 0.2",\
"[14] 0.2",\
"[15] 0.2",\
"[16] 0.4",\
"[17] 0.4",\
"[18] 0.2",\
"[19] 0.4",\
"[20] 0.4",\
"[21] 0.4",\
"[22] 0.4",\
"[23] 0.4",\
"[24] 1",\
"[25] 1",\
"[26] 1",\
"[27] 1",\
"[28] 1",\
"[29] 1",\
"[30] 1",\
"[31] 1",\
"[32] 1",\
"[33] 1",\
"[34] 1",\
"[35] 1",\
"[36] 20",\
"[37] 20",\
"[38] 20",\
"[39] 20",\
"[40] 20",\
"[41] 20",\
"[42] 20",\
"[43] 20",\
"[44] 20",\
"[45] 20",\
"[46] 20",\
"[47] 20",\
"[48] 20",\
"[49] 20",\
"[50] 20",\
"[51] 20",\
"[52] 20",\
"[53] 20",\
"[54] 20",\
"[55] 20",\
"[56] 20",\
"[57] 20",\
"[58] 20",\
"[59] 20",\
"[60] 20",\
"[61] 20",\
"[62] 20",\
"[63] 20",\
"[64] 20",\
"[65] 20",\
"[66] 20",\
"[67] 20",\
"[68] 20",\
"[69] 20",\
"[70] 20",\
"[71] 20",\
"Trip Time = FLOAT[72] :",\
"[0] 10",\
"[1] 10",\
"[2] 10",\
"[3] 10",\
"[4] 10",\
"[5] 10",\
"[6] 10",\
"[7] 10",\
"[8] 10",\
"[9] 10",\
"[10] 10",\
"[11] 10",\
"[12] 10",\
"[13] 10",\
"[14] 10",\
"[15] 10",\
"[16] 10",\
"[17] 10",\
"[18] 10",\
"[19] 10",\
"[20] 10",\
"[21] 10",\
"[22] 10",\
"[23] 10",\
"[24] 10",\
"[25] 10",\
"[26] 10",\
"[27] 10",\
"[28] 10",\
"[29] 10",\
"[30] 10",\
"[31] 10",\
"[32] 10",\
"[33] 10",\
"[34] 10",\
"[35] 10",\
"[36] 10",\
"[37] 10",\
"[38] 10",\
"[39] 10",\
"[40] 10",\
"[41] 10",\
"[42] 10",\
"[43] 10",\
"[44] 10",\
"[45] 10",\
"[46] 10",\
"[47] 10",\
"[48] 10",\
"[49] 10",\
"[50] 10",\
"[51] 10",\
"[52] 10",\
"[53] 10",\
"[54] 10",\
"[55] 10",\
"[56] 10",\
"[57] 10",\
"[58] 10",\
"[59] 10",\
"[60] 10",\
"[61] 10",\
"[62] 10",\
"[63] 10",\
"[64] 10",\
"[65] 10",\
"[66] 10",\
"[67] 10",\
"[68] 10",\
"[69] 10",\
"[70] 10",\
"[71] 10",\
"Ramp Up Speed = FLOAT[72] :",\
"[0] 2",\
"[1] 2",\
"[2] 2",\
"[3] 2",\
"[4] 2",\
"[5] 2",\
"[6] 2",\
"[7] 2",\
"[8] 2",\
"[9] 2",\
"[10] 2",\
"[11] 2",\
"[12] 2",\
"[13] 2",\
"[14] 2",\
"[15] 2",\
"[16] 2",\
"[17] 2",\
"[18] 2",\
"[19] 2",\
"[20] 2",\
"[21] 2",\
"[22] 2",\
"[23] 2",\
"[24] 2",\
"[25] 2",\
"[26] 2",\
"[27] 2",\
"[28] 2",\
"[29] 2",\
"[30] 2",\
"[31] 2",\
"[32] 2",\
"[33] 2",\
"[34] 2",\
"[35] 2",\
"[36] 2",\
"[37] 2",\
"[38] 2",\
"[39] 2",\
"[40] 2",\
"[41] 2",\
"[42] 2",\
"[43] 2",\
"[44] 2",\
"[45] 2",\
"[46] 2",\
"[47] 2",\
"[48] 2",\
"[49] 2",\
"[50] 2",\
"[51] 2",\
"[52] 2",\
"[53] 2",\
"[54] 2",\
"[55] 2",\
"[56] 2",\
"[57] 2",\
"[58] 2",\
"[59] 2",\
"[60] 2",\
"[61] 2",\
"[62] 2",\
"[63] 2",\
"[64] 2",\
"[65] 2",\
"[66] 2",\
"[67] 2",\
"[68] 2",\
"[69] 2",\
"[70] 2",\
"[71] 2",\
"Ramp Down Speed = FLOAT[72] :",\
"[0] 500",\
"[1] 500",\
"[2] 500",\
"[3] 500",\
"[4] 500",\
"[5] 500",\
"[6] 500",\
"[7] 500",\
"[8] 500",\
"[9] 500",\
"[10] 500",\
"[11] 500",\
"[12] 500",\
"[13] 500",\
"[14] 500",\
"[15] 500",\
"[16] 500",\
"[17] 50",\
"[18] 500",\
"[19] 500",\
"[20] 500",\
"[21] 500",\
"[22] 500",\
"[23] 500",\
"[24] 500",\
"[25] 500",\
"[26] 500",\
"[27] 500",\
"[28] 500",\
"[29] 500",\
"[30] 500",\
"[31] 500",\
"[32] 500",\
"[33] 500",\
"[34] 500",\
"[35] 500",\
"[36] 500",\
"[37] 500",\
"[38] 500",\
"[39] 500",\
"[40] 500",\
"[41] 500",\
"[42] 500",\
"[43] 500",\
"[44] 500",\
"[45] 500",\
"[46] 500",\
"[47] 500",\
"[48] 500",\
"[49] 500",\
"[50] 500",\
"[51] 500",\
"[52] 500",\
"[53] 500",\
"[54] 500",\
"[55] 500",\
"[56] 500",\
"[57] 500",\
"[58] 500",\
"[59] 500",\
"[60] 500",\
"[61] 500",\
"[62] 500",\
"[63] 500",\
"[64] 500",\
"[65] 500",\
"[66] 500",\
"[67] 500",\
"[68] 500",\
"[69] 500",\
"[70] 500",\
"[71] 500",\
"ChState = DWORD[72] :",\
"[0] 0",\
"[1] 0",\
"[2] 0",\
"[3] 0",\
"[4] 0",\
"[5] 0",\
"[6] 0",\
"[7] 0",\
"[8] 0",\
"[9] 0",\
"[10] 0",\
"[11] 0",\
"[12] 0",\
"[13] 0",\
"[14] 0",\
"[15] 0",\
"[16] 0",\
"[17] 0",\
"[18] 0",\
"[19] 0",\
"[20] 0",\
"[21] 0",\
"[22] 0",\
"[23] 0",\
"[24] 0",\
"[25] 0",\
"[26] 0",\
"[27] 0",\
"[28] 0",\
"[29] 0",\
"[30] 0",\
"[31] 0",\
"[32] 0",\
"[33] 0",\
"[34] 0",\
"[35] 0",\
"[36] 1",\
"[37] 0",\
"[38] 0",\
"[39] 0",\
"[40] 0",\
"[41] 0",\
"[42] 0",\
"[43] 0",\
"[44] 0",\
"[45] 0",\
"[46] 0",\
"[47] 0",\
"[48] 0",\
"[49] 0",\
"[50] 0",\
"[51] 0",\
"[52] 0",\
"[53] 0",\
"[54] 0",\
"[55] 0",\
"[56] 0",\
"[57] 0",\
"[58] 0",\
"[59] 0",\
"[60] 0",\
"[61] 0",\
"[62] 0",\
"[63] 0",\
"[64] 0",\
"[65] 0",\
"[66] 0",\
"[67] 0",\
"[68] 0",\
"[69] 0",\
"[70] 0",\
"[71] 0",\
"",\
NULL }

#endif

#ifndef EXCL_HV_1

#define HV_1_COMMON_DEFINED

typedef struct {
  WORD      event_id;
  WORD      trigger_mask;
  char      buffer[32];
  INT       type;
  INT       source;
  char      format[8];
  BOOL      enabled;
  INT       read_on;
  INT       period;
  double    event_limit;
  DWORD     num_subevents;
  INT       log_history;
  char      frontend_host[32];
  char      frontend_name[32];
  char      frontend_file_name[256];
  char      status[256];
  char      status_color[32];
  BOOL      hidden;
} HV_1_COMMON;

#define HV_1_COMMON_STR(_name) const char *_name[] = {\
"[.]",\
"Event ID = WORD : 30",\
"Trigger mask = WORD : 0",\
"Buffer = STRING : [32] SYSTEM",\
"Type = INT : 16",\
"Source = INT : 0",\
"Format = STRING : [8] MIDAS",\
"Enabled = BOOL : y",\
"Read on = INT : 255",\
"Period = INT : 3000",\
"Event limit = DOUBLE : 0",\
"Num subevents = DWORD : 0",\
"Log history = INT : 1",\
"Frontend host = STRING : [32] grsmid00.triumf.ca",\
"Frontend name = STRING : [32] FeSy2527-1",\
"Frontend file name = STRING : [256] fesy2527.c",\
"Status = STRING : [256] Ok",\
"Status color = STRING : [32] #00FF00",\
"Hidden = BOOL : n",\
"",\
NULL }

#define HV_1_SETTINGS_DEFINED

typedef struct {
  struct {
    struct {
      struct {
        char      system_name[32];
        char      ip[32];
        INT       linktype;
        INT       first_slot;
        INT       cratemap;
      } dd;
      struct {
        char      description[128];
        char      name[128];
        char      model[15];
        WORD      channels;
      } slot_0;
      struct {
        char      description[128];
        char      name[128];
        char      model[15];
        WORD      channels;
      } slot_2;
      struct {
        char      description[128];
        char      name[128];
        char      model[15];
        WORD      channels;
      } slot_4;
    } sy2527;
  } devices;
  char      names[36][32];
  float     update_threshold_measured[36];
  float     update_threshold_current[36];
  float     zero_threshold[36];
  float     voltage_limit[36];
  float     current_limit[36];
  float     trip_time[36];
  float     ramp_up_speed[36];
  float     ramp_down_speed[36];
  DWORD     chstate[36];
} HV_1_SETTINGS;

#define HV_1_SETTINGS_STR(_name) const char *_name[] = {\
"[Devices/sy2527/DD]",\
"System Name = STRING : [32] sy2527",\
"IP = STRING : [32] 142.90.127.157",\
"LinkType = INT : 0",\
"First Slot = INT : 0",\
"crateMap = INT : 1145044994",\
"",\
"[Devices/sy2527/Slot 0]",\
"Description = STRING : [128] 12 Ch Neg. 4KV 2mA  ",\
"Name = STRING : [128] sy2527",\
"Model = STRING : [15] A1733",\
"Channels = WORD : 12",\
"",\
"[Devices/sy2527/Slot 2]",\
"Description = STRING : [128] 12 Ch Neg. 4KV 2mA  ",\
"Name = STRING : [128] sy2527",\
"Model = STRING : [15] A1733",\
"Channels = WORD : 12",\
"",\
"[Devices/sy2527/Slot 4]",\
"Description = STRING : [128] 12 Ch Neg. 4KV 2mA  ",\
"Name = STRING : [128] sy2527",\
"Model = STRING : [15] A1733",\
"Channels = WORD : 12",\
"",\
"[.]",\
"Names = STRING[36] :",\
"[32] SEP00XN00x",\
"[32] SEP01XN00x",\
"[32] SEP02XN00x",\
"[32] SEP03XN00x",\
"[32] SEP04XN00x",\
"[32] SEP05XN00x",\
"[32] SEP06XN00x",\
"[32] SEP07XN00x",\
"[32] SEP08XN00x",\
"[32] SEP09XN00x",\
"[32] SPARE",\
"[32] SPARE",\
"[32] SEP10XN00x",\
"[32] SEP11XN00x",\
"[32] SEP12XN00x",\
"[32] SEP13XN00x",\
"[32] SEP14XN00x",\
"[32] SEP15XN00x",\
"[32] SEP16XN00x",\
"[32] SEP17XN00x",\
"[32] SEP18XN00x",\
"[32] SEP19XN00x",\
"[32] SPARE10",\
"[32] SPARE11",\
"[32] CHANNEL00",\
"[32] CHANNEL01",\
"[32] CHANNEL02",\
"[32] CHANNEL03",\
"[32] CHANNEL04",\
"[32] CHANNEL05",\
"[32] CHANNEL06",\
"[32] CHANNEL07",\
"[32] CHANNEL08",\
"[32] CHANNEL09",\
"[32] CHANNEL10",\
"[32] CHANNEL11",\
"Update Threshold Measured = FLOAT[36] :",\
"[0] 0.5",\
"[1] 0.5",\
"[2] 0.5",\
"[3] 0.5",\
"[4] 0.5",\
"[5] 0.5",\
"[6] 0.5",\
"[7] 0.5",\
"[8] 0.5",\
"[9] 0.5",\
"[10] 0.5",\
"[11] 0.5",\
"[12] 0.5",\
"[13] 0.5",\
"[14] 0.5",\
"[15] 0.5",\
"[16] 0.5",\
"[17] 0.5",\
"[18] 0.5",\
"[19] 0.5",\
"[20] 0.5",\
"[21] 0.5",\
"[22] 0.5",\
"[23] 0.5",\
"[24] 0.5",\
"[25] 0.5",\
"[26] 0.5",\
"[27] 0.5",\
"[28] 0.5",\
"[29] 0.5",\
"[30] 0.5",\
"[31] 0.5",\
"[32] 0.5",\
"[33] 0.5",\
"[34] 0.5",\
"[35] 0.5",\
"Update Threshold Current = FLOAT[36] :",\
"[0] 1",\
"[1] 1",\
"[2] 1",\
"[3] 1",\
"[4] 1",\
"[5] 1",\
"[6] 1",\
"[7] 1",\
"[8] 1",\
"[9] 1",\
"[10] 1",\
"[11] 1",\
"[12] 1",\
"[13] 1",\
"[14] 1",\
"[15] 1",\
"[16] 1",\
"[17] 1",\
"[18] 1",\
"[19] 1",\
"[20] 1",\
"[21] 1",\
"[22] 1",\
"[23] 1",\
"[24] 1",\
"[25] 1",\
"[26] 1",\
"[27] 1",\
"[28] 1",\
"[29] 1",\
"[30] 1",\
"[31] 1",\
"[32] 1",\
"[33] 1",\
"[34] 1",\
"[35] 1",\
"Zero Threshold = FLOAT[36] :",\
"[0] 20",\
"[1] 20",\
"[2] 20",\
"[3] 20",\
"[4] 20",\
"[5] 20",\
"[6] 20",\
"[7] 20",\
"[8] 20",\
"[9] 20",\
"[10] 20",\
"[11] 20",\
"[12] 20",\
"[13] 20",\
"[14] 20",\
"[15] 20",\
"[16] 20",\
"[17] 20",\
"[18] 20",\
"[19] 20",\
"[20] 20",\
"[21] 20",\
"[22] 20",\
"[23] 20",\
"[24] 20",\
"[25] 20",\
"[26] 20",\
"[27] 20",\
"[28] 20",\
"[29] 20",\
"[30] 20",\
"[31] 20",\
"[32] 20",\
"[33] 20",\
"[34] 20",\
"[35] 20",\
"Voltage Limit = FLOAT[36] :",\
"[0] 4000",\
"[1] 4000",\
"[2] 4000",\
"[3] 4000",\
"[4] 4000",\
"[5] 4000",\
"[6] 4000",\
"[7] 4000",\
"[8] 4000",\
"[9] 4000",\
"[10] 4000",\
"[11] 4000",\
"[12] 4000",\
"[13] 4000",\
"[14] 4000",\
"[15] 4000",\
"[16] 4000",\
"[17] 4000",\
"[18] 4000",\
"[19] 4000",\
"[20] 4000",\
"[21] 4000",\
"[22] 4000",\
"[23] 4000",\
"[24] 4000",\
"[25] 4000",\
"[26] 4000",\
"[27] 4000",\
"[28] 4000",\
"[29] 4000",\
"[30] 4000",\
"[31] 4000",\
"[32] 4000",\
"[33] 4000",\
"[34] 4000",\
"[35] 4000",\
"Current Limit = FLOAT[36] :",\
"[0] 450",\
"[1] 450",\
"[2] 450",\
"[3] 450",\
"[4] 450",\
"[5] 450",\
"[6] 450",\
"[7] 450",\
"[8] 450",\
"[9] 450",\
"[10] 500",\
"[11] 500",\
"[12] 450",\
"[13] 450",\
"[14] 450",\
"[15] 450",\
"[16] 450",\
"[17] 450",\
"[18] 450",\
"[19] 450",\
"[20] 450",\
"[21] 450",\
"[22] 200",\
"[23] 200",\
"[24] 450",\
"[25] 450",\
"[26] 450",\
"[27] 450",\
"[28] 450",\
"[29] 450",\
"[30] 450",\
"[31] 450",\
"[32] 200",\
"[33] 200",\
"[34] 200",\
"[35] 200",\
"Trip Time = FLOAT[36] :",\
"[0] 10",\
"[1] 10",\
"[2] 10",\
"[3] 10",\
"[4] 10",\
"[5] 10",\
"[6] 10",\
"[7] 10",\
"[8] 10",\
"[9] 10",\
"[10] 10",\
"[11] 10",\
"[12] 10",\
"[13] 10",\
"[14] 10",\
"[15] 10",\
"[16] 10",\
"[17] 10",\
"[18] 10",\
"[19] 10",\
"[20] 10",\
"[21] 10",\
"[22] 10",\
"[23] 10",\
"[24] 10",\
"[25] 10",\
"[26] 10",\
"[27] 10",\
"[28] 10",\
"[29] 10",\
"[30] 10",\
"[31] 10",\
"[32] 10",\
"[33] 10",\
"[34] 10",\
"[35] 10",\
"Ramp Up Speed = FLOAT[36] :",\
"[0] 50",\
"[1] 50",\
"[2] 50",\
"[3] 50",\
"[4] 50",\
"[5] 50",\
"[6] 50",\
"[7] 50",\
"[8] 50",\
"[9] 50",\
"[10] 50",\
"[11] 50",\
"[12] 50",\
"[13] 50",\
"[14] 50",\
"[15] 50",\
"[16] 50",\
"[17] 50",\
"[18] 50",\
"[19] 50",\
"[20] 50",\
"[21] 50",\
"[22] 50",\
"[23] 50",\
"[24] 50",\
"[25] 50",\
"[26] 50",\
"[27] 50",\
"[28] 50",\
"[29] 50",\
"[30] 50",\
"[31] 50",\
"[32] 50",\
"[33] 50",\
"[34] 50",\
"[35] 50",\
"Ramp Down Speed = FLOAT[36] :",\
"[0] 200",\
"[1] 200",\
"[2] 200",\
"[3] 200",\
"[4] 200",\
"[5] 200",\
"[6] 200",\
"[7] 200",\
"[8] 200",\
"[9] 200",\
"[10] 200",\
"[11] 200",\
"[12] 200",\
"[13] 200",\
"[14] 200",\
"[15] 200",\
"[16] 200",\
"[17] 200",\
"[18] 200",\
"[19] 200",\
"[20] 200",\
"[21] 200",\
"[22] 50",\
"[23] 50",\
"[24] 200",\
"[25] 200",\
"[26] 200",\
"[27] 200",\
"[28] 200",\
"[29] 200",\
"[30] 200",\
"[31] 200",\
"[32] 50",\
"[33] 50",\
"[34] 50",\
"[35] 50",\
"ChState = DWORD[36] :",\
"[0] 0",\
"[1] 0",\
"[2] 0",\
"[3] 0",\
"[4] 0",\
"[5] 0",\
"[6] 0",\
"[7] 0",\
"[8] 0",\
"[9] 0",\
"[10] 0",\
"[11] 0",\
"[12] 0",\
"[13] 0",\
"[14] 0",\
"[15] 0",\
"[16] 0",\
"[17] 0",\
"[18] 0",\
"[19] 0",\
"[20] 0",\
"[21] 0",\
"[22] 0",\
"[23] 0",\
"[24] 0",\
"[25] 0",\
"[26] 0",\
"[27] 0",\
"[28] 0",\
"[29] 0",\
"[30] 0",\
"[31] 0",\
"[32] 0",\
"[33] 0",\
"[34] 0",\
"[35] 0",\
"",\
NULL }

#endif

#ifndef EXCL_GRIF_CLK0

#define GRIF_CLK0_COMMON_DEFINED

typedef struct {
  WORD      event_id;
  WORD      trigger_mask;
  char      buffer[32];
  INT       type;
  INT       source;
  char      format[8];
  BOOL      enabled;
  INT       read_on;
  INT       period;
  double    event_limit;
  DWORD     num_subevents;
  INT       log_history;
  char      frontend_host[32];
  char      frontend_name[32];
  char      frontend_file_name[256];
  char      status[256];
  char      status_color[32];
  BOOL      hidden;
} GRIF_CLK0_COMMON;

#define GRIF_CLK0_COMMON_STR(_name) const char *_name[] = {\
"[.]",\
"Event ID = WORD : 10",\
"Trigger mask = WORD : 0",\
"Buffer = STRING : [32] SYSTEM",\
"Type = INT : 16",\
"Source = INT : 0",\
"Format = STRING : [8] MIDAS",\
"Enabled = BOOL : y",\
"Read on = INT : 255",\
"Period = INT : 60000",\
"Event limit = DOUBLE : 10000",\
"Num subevents = DWORD : 0",\
"Log history = INT : 60",\
"Frontend host = STRING : [32] grsmid00.triumf.ca",\
"Frontend name = STRING : [32] GRIF-Clk0 Frontend",\
"Frontend file name = STRING : [256] mscb_fe.c",\
"Status = STRING : [256] Ok",\
"Status color = STRING : [32] #00FF00",\
"Hidden = BOOL : n",\
"",\
NULL }

#define GRIF_CLK0_SETTINGS_DEFINED

typedef struct {
  struct {
    struct {
      char      device[256];
      char      pwd[32];
      INT       mscb_address[54];
      BYTE      mscb_index[54];
      BOOL      debug;
      INT       retries;
    } scs2001;
  } devices;
  float     update_threshold[54];
  char      names_input[54][32];
  float     output_offset[54];
  float     output_factor[54];
  char      names_output[54][32];
} GRIF_CLK0_SETTINGS;

#define GRIF_CLK0_SETTINGS_STR(_name) const char *_name[] = {\
"[Devices/SCS2001]",\
"Device = STRING : [256] mscb570.triumf.ca",\
"Pwd = STRING : [32] meg",\
"MSCB Address = INT[54] :",\
"[0] 1",\
"[1] 1",\
"[2] 1",\
"[3] 1",\
"[4] 1",\
"[5] 1",\
"[6] 1",\
"[7] 1",\
"[8] 1",\
"[9] 1",\
"[10] 1",\
"[11] 1",\
"[12] 1",\
"[13] 1",\
"[14] 1",\
"[15] 1",\
"[16] 1",\
"[17] 1",\
"[18] 1",\
"[19] 1",\
"[20] 1",\
"[21] 1",\
"[22] 1",\
"[23] 1",\
"[24] 1",\
"[25] 1",\
"[26] 1",\
"[27] 1",\
"[28] 1",\
"[29] 1",\
"[30] 1",\
"[31] 1",\
"[32] 1",\
"[33] 1",\
"[34] 1",\
"[35] 1",\
"[36] 1",\
"[37] 1",\
"[38] 1",\
"[39] 1",\
"[40] 1",\
"[41] 1",\
"[42] 1",\
"[43] 1",\
"[44] 1",\
"[45] 1",\
"[46] 1",\
"[47] 1",\
"[48] 1",\
"[49] 1",\
"[50] 1",\
"[51] 1",\
"[52] 1",\
"[53] 1",\
"MSCB Index = BYTE[54] :",\
"[0] 0",\
"[1] 1",\
"[2] 2",\
"[3] 3",\
"[4] 4",\
"[5] 5",\
"[6] 6",\
"[7] 7",\
"[8] 8",\
"[9] 9",\
"[10] 10",\
"[11] 11",\
"[12] 12",\
"[13] 13",\
"[14] 14",\
"[15] 15",\
"[16] 16",\
"[17] 17",\
"[18] 18",\
"[19] 19",\
"[20] 20",\
"[21] 21",\
"[22] 22",\
"[23] 23",\
"[24] 24",\
"[25] 25",\
"[26] 26",\
"[27] 27",\
"[28] 28",\
"[29] 29",\
"[30] 30",\
"[31] 31",\
"[32] 32",\
"[33] 33",\
"[34] 34",\
"[35] 35",\
"[36] 36",\
"[37] 37",\
"[38] 38",\
"[39] 39",\
"[40] 40",\
"[41] 41",\
"[42] 42",\
"[43] 43",\
"[44] 44",\
"[45] 45",\
"[46] 46",\
"[47] 47",\
"[48] 48",\
"[49] 49",\
"[50] 50",\
"[51] 51",\
"[52] 52",\
"[53] 53",\
"Debug = BOOL : n",\
"Retries = INT : 10",\
"",\
"[.]",\
"Update Threshold = FLOAT[54] :",\
"[0] 0.1",\
"[1] 0.1",\
"[2] 0.1",\
"[3] 0.1",\
"[4] 0.1",\
"[5] 0.1",\
"[6] 0.1",\
"[7] 0.1",\
"[8] 0.1",\
"[9] 0.1",\
"[10] 0.1",\
"[11] 0.1",\
"[12] 0.1",\
"[13] 0.1",\
"[14] 0.1",\
"[15] 0.1",\
"[16] 0.1",\
"[17] 0.1",\
"[18] 0.1",\
"[19] 0.1",\
"[20] 0.1",\
"[21] 0.1",\
"[22] 0.1",\
"[23] 0.1",\
"[24] 0.1",\
"[25] 0.1",\
"[26] 0.1",\
"[27] 0.1",\
"[28] 0.1",\
"[29] 0.1",\
"[30] 0.1",\
"[31] 0.1",\
"[32] 0.1",\
"[33] 0.1",\
"[34] 0.1",\
"[35] 0.1",\
"[36] 0.1",\
"[37] 0.1",\
"[38] 0.1",\
"[39] 0.1",\
"[40] 0.1",\
"[41] 0.1",\
"[42] 0.1",\
"[43] 0.1",\
"[44] 0.1",\
"[45] 0.1",\
"[46] 0.1",\
"[47] 0.1",\
"[48] 0.1",\
"[49] 0.1",\
"[50] 0.1",\
"[51] 0.1",\
"[52] 0.1",\
"[53] 0.1",\
"Names Input = STRING[54] :",\
"[32] ClockEnB",\
"[32] Master",\
"[32] SyncSel",\
"[32] FanSel",\
"[32] RefSel",\
"[32] ExtClk",\
"[32] ExtSync",\
"[32] SATAClk",\
"[32] SATASync",\
"[32] SyncTmeS",\
"[32] SyncTmeE",\
"[32] ch0_high",\
"[32] ch0_low",\
"[32] ch0_byp",\
"[32] ch0_ph",\
"[32] ch1_high",\
"[32] ch1_low",\
"[32] ch1_byp",\
"[32] ch1_ph",\
"[32] ch2_high",\
"[32] ch2_low",\
"[32] ch2_byp",\
"[32] ch2_ph",\
"[32] ch3_high",\
"[32] ch3_low",\
"[32] ch3_byp",\
"[32] ch3_ph",\
"[32] ch4_high",\
"[32] ch4_low",\
"[32] ch4_byp",\
"[32] ch4_ph",\
"[32] ch5_high",\
"[32] ch5_low",\
"[32] ch5_byp",\
"[32] ch5_ph",\
"[32] ch6_high",\
"[32] ch6_low",\
"[32] ch6_byp",\
"[32] ch6_ph",\
"[32] ch7_high",\
"[32] ch7_low",\
"[32] ch7_byp",\
"[32] ch7_ph",\
"[32] CSAC_ena",\
"[32] CSAC_sta",\
"[32] CSAC_mod",\
"[32] CSAC_air",\
"[32] CSAC_pwr",\
"[32] CSAC_tcx",\
"[32] CSAC_lsr",\
"[32] CSAC_htr",\
"[32] CSAC_tmp",\
"[32] CSAC_sn",\
"[32] CSAC_ver",\
"Output Offset = FLOAT[54] :",\
"[0] 0",\
"[1] 0",\
"[2] 0",\
"[3] 0",\
"[4] 0",\
"[5] 0",\
"[6] 0",\
"[7] 0",\
"[8] 0",\
"[9] 0",\
"[10] 0",\
"[11] 0",\
"[12] 0",\
"[13] 0",\
"[14] 0",\
"[15] 0",\
"[16] 0",\
"[17] 0",\
"[18] 0",\
"[19] 0",\
"[20] 0",\
"[21] 0",\
"[22] 0",\
"[23] 0",\
"[24] 0",\
"[25] 0",\
"[26] 0",\
"[27] 0",\
"[28] 0",\
"[29] 0",\
"[30] 0",\
"[31] 0",\
"[32] 0",\
"[33] 0",\
"[34] 0",\
"[35] 0",\
"[36] 0",\
"[37] 0",\
"[38] 0",\
"[39] 0",\
"[40] 0",\
"[41] 0",\
"[42] 0",\
"[43] 0",\
"[44] 0",\
"[45] 0",\
"[46] 0",\
"[47] 0",\
"[48] 0",\
"[49] 0",\
"[50] 0",\
"[51] 0",\
"[52] 0",\
"[53] 0",\
"Output Factor = FLOAT[54] :",\
"[0] 1",\
"[1] 1",\
"[2] 1",\
"[3] 1",\
"[4] 1",\
"[5] 1",\
"[6] 1",\
"[7] 1",\
"[8] 1",\
"[9] 1",\
"[10] 1",\
"[11] 1",\
"[12] 1",\
"[13] 1",\
"[14] 1",\
"[15] 1",\
"[16] 1",\
"[17] 1",\
"[18] 1",\
"[19] 1",\
"[20] 1",\
"[21] 1",\
"[22] 1",\
"[23] 1",\
"[24] 1",\
"[25] 1",\
"[26] 1",\
"[27] 1",\
"[28] 1",\
"[29] 1",\
"[30] 1",\
"[31] 1",\
"[32] 1",\
"[33] 1",\
"[34] 1",\
"[35] 1",\
"[36] 1",\
"[37] 1",\
"[38] 1",\
"[39] 1",\
"[40] 1",\
"[41] 1",\
"[42] 1",\
"[43] 1",\
"[44] 1",\
"[45] 1",\
"[46] 1",\
"[47] 1",\
"[48] 1",\
"[49] 1",\
"[50] 1",\
"[51] 1",\
"[52] 1",\
"[53] 1",\
"Names Output = STRING[54] :",\
"[32] ClockENb",\
"[32] Master",\
"[32] SyncSel",\
"[32] FanSel",\
"[32] RefSel",\
"[32] ExtClk",\
"[32] ExtSync",\
"[32] SATAClk",\
"[32] SATASync",\
"[32] SyncTmeS",\
"[32] SyncTmeE",\
"[32] ch0_high",\
"[32] ch0_low",\
"[32] ch0_byp",\
"[32] ch0_ph",\
"[32] ch1_high",\
"[32] ch1_low",\
"[32] ch1_byp",\
"[32] ch1_ph",\
"[32] ch2_high",\
"[32] ch2_low",\
"[32] ch2_byp",\
"[32] ch2_ph",\
"[32] ch3_high",\
"[32] ch3_low",\
"[32] ch3_byp",\
"[32] ch3_ph",\
"[32] ch4_high",\
"[32] ch4_low",\
"[32] ch4_byp",\
"[32] ch4_ph",\
"[32] ch5_high",\
"[32] ch5_low",\
"[32] ch5_byp",\
"[32] ch5_ph",\
"[32] ch6_high",\
"[32] ch6_low",\
"[32] ch6_byp",\
"[32] ch6_ph",\
"[32] ch7_high",\
"[32] ch7_low",\
"[32] ch7_byp",\
"[32] ch7_ph",\
"[32] CSAC_ena",\
"[32] CSAC_sta",\
"[32] CSAC_mod",\
"[32] CSAC_alr",\
"[32] CSAC_pwr",\
"[32] CSAC_tcx",\
"[32] CSAC_lsr",\
"[32] CSAC_htr",\
"[32] CSAC_tmp",\
"[32] CSAC_sn",\
"[32] CSAC_ver",\
"",\
NULL }

#endif

#ifndef EXCL_GRIF_CLK1

#define GRIF_CLK1_COMMON_DEFINED

typedef struct {
  WORD      event_id;
  WORD      trigger_mask;
  char      buffer[32];
  INT       type;
  INT       source;
  char      format[8];
  BOOL      enabled;
  INT       read_on;
  INT       period;
  double    event_limit;
  DWORD     num_subevents;
  INT       log_history;
  char      frontend_host[32];
  char      frontend_name[32];
  char      frontend_file_name[256];
  char      status[256];
  char      status_color[32];
  BOOL      hidden;
} GRIF_CLK1_COMMON;

#define GRIF_CLK1_COMMON_STR(_name) const char *_name[] = {\
"[.]",\
"Event ID = WORD : 10",\
"Trigger mask = WORD : 0",\
"Buffer = STRING : [32] SYSTEM",\
"Type = INT : 16",\
"Source = INT : 0",\
"Format = STRING : [8] MIDAS",\
"Enabled = BOOL : y",\
"Read on = INT : 255",\
"Period = INT : 60000",\
"Event limit = DOUBLE : 10000",\
"Num subevents = DWORD : 0",\
"Log history = INT : 60",\
"Frontend host = STRING : [32] grsmid00.triumf.ca",\
"Frontend name = STRING : [32] GRIF-Clk1 Frontend",\
"Frontend file name = STRING : [256] mscb_fe.c",\
"Status = STRING : [256] Hardware error",\
"Status color = STRING : [32] #FF0000",\
"Hidden = BOOL : n",\
"",\
NULL }

#define GRIF_CLK1_SETTINGS_DEFINED

typedef struct {
  struct {
    struct {
      char      device[32];
      char      pwd[32];
      INT       mscb_address[54];
      BYTE      mscb_index[54];
      BOOL      debug;
      INT       retries;
    } scs2001;
  } devices;
  float     update_threshold[54];
  char      names_input[54][32];
  float     output_offset[54];
  float     output_factor[54];
  char      names_output[54][32];
} GRIF_CLK1_SETTINGS;

#define GRIF_CLK1_SETTINGS_STR(_name) const char *_name[] = {\
"[Devices/SCS2001]",\
"Device = STRING : [32] mscb571.triumf.ca",\
"Pwd = STRING : [32] meg",\
"MSCB Address = INT[54] :",\
"[0] 1",\
"[1] 1",\
"[2] 1",\
"[3] 1",\
"[4] 1",\
"[5] 1",\
"[6] 1",\
"[7] 1",\
"[8] 1",\
"[9] 1",\
"[10] 1",\
"[11] 1",\
"[12] 1",\
"[13] 1",\
"[14] 1",\
"[15] 1",\
"[16] 1",\
"[17] 1",\
"[18] 1",\
"[19] 1",\
"[20] 1",\
"[21] 1",\
"[22] 1",\
"[23] 1",\
"[24] 1",\
"[25] 1",\
"[26] 1",\
"[27] 1",\
"[28] 1",\
"[29] 1",\
"[30] 1",\
"[31] 1",\
"[32] 1",\
"[33] 1",\
"[34] 1",\
"[35] 1",\
"[36] 1",\
"[37] 1",\
"[38] 1",\
"[39] 1",\
"[40] 1",\
"[41] 1",\
"[42] 1",\
"[43] 1",\
"[44] 1",\
"[45] 1",\
"[46] 1",\
"[47] 1",\
"[48] 1",\
"[49] 1",\
"[50] 1",\
"[51] 1",\
"[52] 1",\
"[53] 1",\
"MSCB Index = BYTE[54] :",\
"[0] 0",\
"[1] 1",\
"[2] 2",\
"[3] 3",\
"[4] 4",\
"[5] 5",\
"[6] 6",\
"[7] 7",\
"[8] 8",\
"[9] 9",\
"[10] 10",\
"[11] 11",\
"[12] 12",\
"[13] 13",\
"[14] 14",\
"[15] 15",\
"[16] 16",\
"[17] 17",\
"[18] 18",\
"[19] 19",\
"[20] 20",\
"[21] 21",\
"[22] 22",\
"[23] 23",\
"[24] 24",\
"[25] 25",\
"[26] 26",\
"[27] 27",\
"[28] 28",\
"[29] 29",\
"[30] 30",\
"[31] 31",\
"[32] 32",\
"[33] 33",\
"[34] 34",\
"[35] 35",\
"[36] 36",\
"[37] 37",\
"[38] 38",\
"[39] 39",\
"[40] 40",\
"[41] 41",\
"[42] 42",\
"[43] 43",\
"[44] 44",\
"[45] 45",\
"[46] 46",\
"[47] 47",\
"[48] 48",\
"[49] 49",\
"[50] 50",\
"[51] 51",\
"[52] 52",\
"[53] 53",\
"Debug = BOOL : n",\
"Retries = INT : 10",\
"",\
"[.]",\
"Update Threshold = FLOAT[54] :",\
"[0] 0.1",\
"[1] 0.1",\
"[2] 0.1",\
"[3] 0.1",\
"[4] 0.1",\
"[5] 0.1",\
"[6] 0.1",\
"[7] 0.1",\
"[8] 0.1",\
"[9] 0.1",\
"[10] 0.1",\
"[11] 0.1",\
"[12] 0.1",\
"[13] 0.1",\
"[14] 0.1",\
"[15] 0.1",\
"[16] 0.1",\
"[17] 0.1",\
"[18] 0.1",\
"[19] 0.1",\
"[20] 0.1",\
"[21] 0.1",\
"[22] 0.1",\
"[23] 0.1",\
"[24] 0.1",\
"[25] 0.1",\
"[26] 0.1",\
"[27] 0.1",\
"[28] 0.1",\
"[29] 0.1",\
"[30] 0.1",\
"[31] 0.1",\
"[32] 0.1",\
"[33] 0.1",\
"[34] 0.1",\
"[35] 0.1",\
"[36] 0.1",\
"[37] 0.1",\
"[38] 0.1",\
"[39] 0.1",\
"[40] 0.1",\
"[41] 0.1",\
"[42] 0.1",\
"[43] 0.1",\
"[44] 0.1",\
"[45] 0.1",\
"[46] 0.1",\
"[47] 0.1",\
"[48] 0.1",\
"[49] 0.1",\
"[50] 0.1",\
"[51] 0.1",\
"[52] 0.1",\
"[53] 0.1",\
"Names Input = STRING[54] :",\
"[32] ClockEnB",\
"[32] Master",\
"[32] SyncSel",\
"[32] FanSel",\
"[32] RefSel",\
"[32] ExtClk",\
"[32] ExtSync",\
"[32] SATAClk",\
"[32] SATASync",\
"[32] SyncTmeS",\
"[32] SyncTmeE",\
"[32] ch0_high",\
"[32] ch0_low",\
"[32] ch0_byp",\
"[32] ch0_ph",\
"[32] ch1_high",\
"[32] ch1_low",\
"[32] ch1_byp",\
"[32] ch1_ph",\
"[32] ch2_high",\
"[32] ch2_low",\
"[32] ch2_byp",\
"[32] ch2_ph",\
"[32] ch3_high",\
"[32] ch3_low",\
"[32] ch3_byp",\
"[32] ch3_ph",\
"[32] ch4_high",\
"[32] ch4_low",\
"[32] ch4_byp",\
"[32] ch4_ph",\
"[32] ch5_high",\
"[32] ch5_low",\
"[32] ch5_byp",\
"[32] ch5_ph",\
"[32] ch6_high",\
"[32] ch6_low",\
"[32] ch6_byp",\
"[32] ch6_ph",\
"[32] ch7_high",\
"[32] ch7_low",\
"[32] ch7_byp",\
"[32] ch7_ph",\
"[32] CSAC_ena",\
"[32] CSAC_sta",\
"[32] CSAC_mod",\
"[32] CSAC_air",\
"[32] CSAC_pwr",\
"[32] CSAC_tcx",\
"[32] CSAC_lsr",\
"[32] CSAC_htr",\
"[32] CSAC_tmp",\
"[32] CSAC_sn",\
"[32] CSAC_ver",\
"Output Offset = FLOAT[54] :",\
"[0] 0",\
"[1] 0",\
"[2] 0",\
"[3] 0",\
"[4] 0",\
"[5] 0",\
"[6] 0",\
"[7] 0",\
"[8] 0",\
"[9] 0",\
"[10] 0",\
"[11] 0",\
"[12] 0",\
"[13] 0",\
"[14] 0",\
"[15] 0",\
"[16] 0",\
"[17] 0",\
"[18] 0",\
"[19] 0",\
"[20] 0",\
"[21] 0",\
"[22] 0",\
"[23] 0",\
"[24] 0",\
"[25] 0",\
"[26] 0",\
"[27] 0",\
"[28] 0",\
"[29] 0",\
"[30] 0",\
"[31] 0",\
"[32] 0",\
"[33] 0",\
"[34] 0",\
"[35] 0",\
"[36] 0",\
"[37] 0",\
"[38] 0",\
"[39] 0",\
"[40] 0",\
"[41] 0",\
"[42] 0",\
"[43] 0",\
"[44] 0",\
"[45] 0",\
"[46] 0",\
"[47] 0",\
"[48] 0",\
"[49] 0",\
"[50] 0",\
"[51] 0",\
"[52] 0",\
"[53] 0",\
"Output Factor = FLOAT[54] :",\
"[0] 1",\
"[1] 1",\
"[2] 1",\
"[3] 1",\
"[4] 1",\
"[5] 1",\
"[6] 1",\
"[7] 1",\
"[8] 1",\
"[9] 1",\
"[10] 1",\
"[11] 1",\
"[12] 1",\
"[13] 1",\
"[14] 1",\
"[15] 1",\
"[16] 1",\
"[17] 1",\
"[18] 1",\
"[19] 1",\
"[20] 1",\
"[21] 1",\
"[22] 1",\
"[23] 1",\
"[24] 1",\
"[25] 1",\
"[26] 1",\
"[27] 1",\
"[28] 1",\
"[29] 1",\
"[30] 1",\
"[31] 1",\
"[32] 1",\
"[33] 1",\
"[34] 1",\
"[35] 1",\
"[36] 1",\
"[37] 1",\
"[38] 1",\
"[39] 1",\
"[40] 1",\
"[41] 1",\
"[42] 1",\
"[43] 1",\
"[44] 1",\
"[45] 1",\
"[46] 1",\
"[47] 1",\
"[48] 1",\
"[49] 1",\
"[50] 1",\
"[51] 1",\
"[52] 1",\
"[53] 1",\
"Names Output = STRING[54] :",\
"[32] ClockENb",\
"[32] Master",\
"[32] SyncSel",\
"[32] FanSel",\
"[32] RefSel",\
"[32] ExtClk",\
"[32] ExtSync",\
"[32] SATAClk",\
"[32] SATASync",\
"[32] SyncTmeS",\
"[32] SyncTmeE",\
"[32] ch0_high",\
"[32] ch0_low",\
"[32] ch0_byp",\
"[32] ch0_ph",\
"[32] ch1_high",\
"[32] ch1_low",\
"[32] ch1_byp",\
"[32] ch1_ph",\
"[32] ch2_high",\
"[32] ch2_low",\
"[32] ch2_byp",\
"[32] ch2_ph",\
"[32] ch3_high",\
"[32] ch3_low",\
"[32] ch3_byp",\
"[32] ch3_ph",\
"[32] ch4_high",\
"[32] ch4_low",\
"[32] ch4_byp",\
"[32] ch4_ph",\
"[32] ch5_high",\
"[32] ch5_low",\
"[32] ch5_byp",\
"[32] ch5_ph",\
"[32] ch6_high",\
"[32] ch6_low",\
"[32] ch6_byp",\
"[32] ch6_ph",\
"[32] ch7_high",\
"[32] ch7_low",\
"[32] ch7_byp",\
"[32] ch7_ph",\
"[32] CSAC_ena",\
"[32] CSAC_sta",\
"[32] CSAC_mod",\
"[32] CSAC_alr",\
"[32] CSAC_pwr",\
"[32] CSAC_tcx",\
"[32] CSAC_lsr",\
"[32] CSAC_htr",\
"[32] CSAC_tmp",\
"[32] CSAC_sn",\
"[32] CSAC_ver",\
"",\
NULL }

#endif

#ifndef EXCL_EPICS

#define EPICS_COMMON_DEFINED

typedef struct {
  WORD      event_id;
  WORD      trigger_mask;
  char      buffer[32];
  INT       type;
  INT       source;
  char      format[8];
  BOOL      enabled;
  INT       read_on;
  INT       period;
  double    event_limit;
  DWORD     num_subevents;
  INT       log_history;
  char      frontend_host[32];
  char      frontend_name[32];
  char      frontend_file_name[256];
  char      status[256];
  char      status_color[32];
  BOOL      hidden;
} EPICS_COMMON;

#define EPICS_COMMON_STR(_name) const char *_name[] = {\
"[.]",\
"Event ID = WORD : 5",\
"Trigger mask = WORD : 0",\
"Buffer = STRING : [32] SYSTEM",\
"Type = INT : 17",\
"Source = INT : 0",\
"Format = STRING : [8] MIDAS",\
"Enabled = BOOL : y",\
"Read on = INT : 511",\
"Period = INT : 1000",\
"Event limit = DOUBLE : 0",\
"Num subevents = DWORD : 0",\
"Log history = INT : 0",\
"Frontend host = STRING : [32] grsmid00.triumf.ca",\
"Frontend name = STRING : [32] Epics",\
"Frontend file name = STRING : [256] frontend.c",\
"Status = STRING : [256] Ok",\
"Status color = STRING : [32] #00FF00",\
"Hidden = BOOL : n",\
"",\
NULL }

#define EPICS_SETTINGS_DEFINED

typedef struct {
  struct {
    INT       epics;
  } channels;
  char      keys[20][100];
  struct {
    struct {
      char      channel_name[20][32];
    } epics;
  } devices;
  char      names[20][32];
  float     update_threshold_measured[20];
} EPICS_SETTINGS;

#define EPICS_SETTINGS_STR(_name) const char *_name[] = {\
"[Channels]",\
"Epics = INT : 20",\
"",\
"[.]",\
"Keys = STRING[20] :",\
"[100] ",\
"[100] ",\
"[100] ",\
"[100] ",\
"[100] ",\
"[100] ",\
"[100] ",\
"[100] ",\
"[100] ",\
"[100] ",\
"[100] /Runinfo/Run number",\
"[100] /Equipment/HV-0/Variables/Measured[52]",\
"[100] /Equipment/HV-0/Variables/Measured[53]",\
"[100] /Equipment/HV-0/Variables/Measured[54]",\
"[100] /Equipment/HV-0/Variables/Measured[55]",\
"[100] /Equipment/scalar/Variables/SCLR[64]",\
"[100] /Equipment/Trigger/Statistics/Events per sec.",\
"[100] ",\
"[100] ",\
"[100] ",\
"",\
"[Devices/Epics]",\
"Channel Name = STRING[20] :",\
"[32] GRIF:SOH:VAR1",\
"[32] GRIF:SOH:VAR2",\
"[32] GRIF:SOH:VAR3",\
"[32] GRIF:SOH:VAR4",\
"[32] GRIF:SOH:VAR5",\
"[32] GRIF:SOH:VAR6",\
"[32] GRIF:SOH:VAR7",\
"[32] GRIF:SOH:VAR8",\
"[32] GRIF:SOH:VAR9",\
"[32] GRIF:SOH:VAR10",\
"[32] GRIF:EXP:VAR1",\
"[32] GRIF:EXP:VAR2",\
"[32] EPICS:PV12",\
"[32] EPICS:PV13",\
"[32] EPICS:PV14",\
"[32] EPICS:PV15",\
"[32] EPICS:PV16",\
"[32] EPICS:PV17",\
"[32] EPICS:PV18",\
"[32] EPICS:PV19",\
"",\
"[.]",\
"Names = STRING[20] :",\
"[32] HPGe 5 Blue Crystal",\
"[32] Events per sec.",\
"[32] kBytes per sec",\
"[32] HV  GRIF05-Blue",\
"[32] Default%CH 4",\
"[32] Default%CH 5",\
"[32] Default%CH 6",\
"[32] Default%CH 7",\
"[32] Default%CH 8",\
"[32] Run Number",\
"[32] Default%CH 10",\
"[32] Default%CH 11",\
"[32] Default%CH 12",\
"[32] Default%CH 13",\
"[32] Default%CH 14",\
"[32] Default%CH 15",\
"[32] Default%CH 16",\
"[32] Default%CH 17",\
"[32] Default%CH 18",\
"[32] Default%CH 19",\
"Update Threshold Measured = FLOAT[20] :",\
"[0] 1",\
"[1] 1",\
"[2] 1",\
"[3] 1",\
"[4] 1",\
"[5] 1",\
"[6] 1",\
"[7] 1",\
"[8] 1",\
"[9] 1",\
"[10] 1",\
"[11] 1",\
"[12] 1",\
"[13] 1",\
"[14] 1",\
"[15] 1",\
"[16] 1",\
"[17] 1",\
"[18] 1",\
"[19] 1",\
"",\
NULL }

#endif

