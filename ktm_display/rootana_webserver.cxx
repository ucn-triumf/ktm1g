/// Program for analyzing the KTM waveforms and serving them up on web (via
// JSROOT server).
//
// T. Lindner

#include <stdio.h>
#include <iostream>
#include <time.h>

#include "TRootanaEventLoop.hxx"
#include "TAnaManager.hxx"


class Analyzer: public TRootanaEventLoop {




public:

  // An analysis manager.  Define and fill histograms in 
  // analysis manager.
  TAnaManager *anaManager;
  
  Analyzer() {
    //DisableAutoMainWindow();
    DisableRootOutput(true);
    UseBatchMode();
    anaManager = 0;
    
  };

  virtual ~Analyzer() {};

  void Initialize(){

#ifdef HAVE_THTTP_SERVER
    std::cout << "Using THttpServer in read/write mode" << std::endl;
    SetTHttpServerReadWrite();
#endif

  }

  void InitManager(){
    
    if(anaManager)
      delete anaManager;
    anaManager = new TAnaManager();
    
  }
  
  
  void BeginRun(int transition,int run,int time){
    
    InitManager();
    
  }


  bool ProcessMidasEvent(TDataContainer& dataContainer){

    if(!anaManager) InitManager();
    
    anaManager->ProcessMidasEvent(dataContainer);

    return true;
  }


}; 


int main(int argc, char *argv[])
{

  Analyzer::CreateSingleton<Analyzer>();
  return Analyzer::Get().ExecuteLoop(argc, argv);

}

