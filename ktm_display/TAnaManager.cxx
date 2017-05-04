#include "TAnaManager.hxx"
#include "TV1720RawData.h"

#include <iostream>
#include <fstream>


TAnaManager::TAnaManager(){



      f1VM4Waveform = new TH1D("1VM4 Waveform","1VM4 Waveform",350,0,70);
      f1VM4Waveform->SetYTitle("Pule Height");
      f1VM4Waveform->SetXTitle("time (us)");

      f1VM4WaveformCorrected = new TH1D("1VM4 Waveform Corrected","1VM4 Waveform Corrected",43,0,68.8);
      f1VM4WaveformCorrected->SetYTitle("Pule Height");
      f1VM4WaveformCorrected->SetXTitle("time (us)");

      f1VM4BeamOnValues = new TH1D("1VM4 Beam On Values","1VM4 Beam On Values",1000,0,200000);
      f1VM4BeamOnValues->SetXTitle("Beam On Values (counts)");


      f1VM4BeamOffValues = new TH1D("1VM4 Beam Notch Values","1VM4 Beam Notch Values",1000,0,20000);
      f1VM4BeamOffValues->SetXTitle("Beam Notch Values (counts)");

      f1VM4NotchWidth = new TH1D("1VM4 Notch Width","1VM4 Notch Width (50%-50%)",1000,0,20000);
      f1VM4NotchWidth->SetXTitle("Beam Width (us)");

      f1VM4FallTime = new TH1D("1VM4 Fall Time","1VM4 Notch Fall Time (90%-10%)",1000,0,20000);
      f1VM4FallTime->SetXTitle("Fall Time (us)");
      
      f1VM4ArrivalTime = new TH1D("1VM4 Arrival Time","1VM4 Notch Arrival Time (50%)",1000,0,20000);
      f1VM4ArrivalTime->SetXTitle("Arrival Time (us)");

      f1VM4NotchCleaniness = new TH1D("1VM4 Notch Cleaniness","1VM4 Notch Cleaniness",1000,0,20000);
      f1VM4NotchCleaniness->SetXTitle("???");
      

};



int TAnaManager::ProcessMidasEvent(TDataContainer& dataContainer){


  std::cout << "Timestamp: " << dataContainer.GetMidasEvent().GetTimeStamp() << std::endl;
  
  TGenericData *data = dataContainer.GetEventData<TGenericData>("KTMG");
  if(!data) return 1;
  
  f1VM4Waveform->Reset();
  f1VM4WaveformCorrected->Reset();
  
  

  double avg = 0.0;
  int nnn = 0;
  //std::cout << "size " << data->GetSize() << std::endl;
  for(int i = 0; i < data->GetSize()-4; i++){
    
    uint32_t word = data->GetData32()[i+3];
    
    double adc = (word & 0x3fffff);
    double time = i*0.2;
    //std::cout << time << " " << volt << std::endl;
    f1VM4Waveform->SetBinContent(i+1,adc);

    if(time < 6) f1VM4BeamOnValues->Fill(adc);
    if(time > 30 && time < 50) f1VM4BeamOffValues->Fill(adc);
    

    avg += adc;
    nnn++;
    if(nnn >= 8){
      
      avg /= (float) nnn;
      f1VM4WaveformCorrected->SetBinContent((i+1)/8,avg);
      avg = 0.0;
      nnn = 0;

    }
    
  }





  return 1;
}





