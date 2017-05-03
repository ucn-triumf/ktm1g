#include <stdio.h>
#include <iostream>
#include <fstream>

#include "TRootanaDisplay.hxx"
#include "TH1D.h"
#include "TV792Data.hxx"

#include "TFancyHistogramCanvas.hxx"
#include "TInterestingEventManager.hxx"


#include "TAnaManager.hxx"


class MyTestLoop: public TRootanaDisplay { 

public:
	
  // An analysis manager.  Define and fill histograms in 
  // analysis manager.
  TAnaManager *anaManager;

  MyTestLoop() {
    SetOutputFilename("example_output");
    DisableRootOutput(false);
    anaManager = new TAnaManager();
    // Number of events to skip before plotting one.
    //SetNumberSkipEvent(10);
    // Choose to use functionality to update after X seconds
    SetOnlineUpdatingBasedSeconds();
    // Uncomment this to enable the 'interesting event' functionality.
    //iem_t::instance()->Enable();
    ProcessThisEventID(1);
  }

  void AddAllCanvases(){

    // Set up tabbed canvases
        
    if(anaManager->HaveKTMHistograms()) 
      AddSingleCanvas(new TFancyHistogramCanvas(anaManager->GetKTMHistograms(),"KTM"));
    
    SetDisplayName(" KTM  Display");
  };

  virtual ~MyTestLoop() {};

  void BeginRun(int transition,int run,int time) {
    std::cout << "User BOR method" << std::endl;

    //Initialize .csv File for output
    ofstream outfile;
    outfile.open ("PulseDetails.csv");
    outfile << "Timestamp, notchLength, fallTime, currentInNotch\n";

    ofstream outfile2;
    outfile2.open("PulseDetailsBoard.csv");
    outfile2<< "Timestamp, TriggerOffset, meanOffset, highVoltage, lowVolate, measuredNotchWidth \n";

  }

  void EndRun(int transition,int run,int time) {
    std::cout << "User EOR method" << std::endl;
  }

  void ResetHistograms(){}

  void UpdateHistograms(TDataContainer& dataContainer){
    
    anaManager->ProcessMidasEvent(dataContainer);
  }

  void PlotCanvas(TDataContainer& dataContainer){}


}; 






int main(int argc, char *argv[])
{
  MyTestLoop::CreateSingleton<MyTestLoop>();  
  return MyTestLoop::Get().ExecuteLoop(argc, argv);
}

