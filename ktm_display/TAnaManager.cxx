#include "TAnaManager.hxx"
#include "TV1720RawData.h"
#include "TCanvas.h"

#include <iostream>
#include <fstream>
#include <TSystem.h>

TAnaManager::TAnaManager(){



      f1VM4Waveform = new TH1D("1VM4WaveformRaw","1VM4 Waveform Raw",352,0,140.8);
      f1VM4Waveform->SetYTitle("Current (ADC counts)");
      f1VM4Waveform->SetXTitle("time (us)");


      f1VM4BeamOnValues = new TH1D("1VM4BeamOnRawValues","1VM4 Beam On Raw Values",1500,0,750000);
      f1VM4BeamOnValues->SetXTitle("Beam On Values (counts)");

      f1VM4BeamOffValues = new TH1D("1VM4BeamNotchRawValues","1VM4 Beam Notch Raw Values",1000,0,20000);
      f1VM4BeamOffValues->SetXTitle("Beam Notch Values (counts)");

      f1VM4WaveformCorrected = new TH1D("1VM4WaveformCalibrated","1VM4 Waveform Calibrated",88,0,140.8);
      f1VM4WaveformCorrected->SetYTitle("Beam Current (uA)");
      f1VM4WaveformCorrected->SetXTitle("time (us)");



      f1VM4NotchWidth = new TH1D("1VM4NotchWidth","1VM4 Notch Width (50%-50%)",140,0,140);
      f1VM4NotchWidth->SetXTitle("Notch Width (us)");

      f1VM4FallTime = new TH1D("1VM4FallTime","1VM4 Notch Fall Time (85%-10%)",60,0,60);
      f1VM4FallTime->SetXTitle("Notch Fall Time (us)");
      
      f1VM4ArrivalTime = new TH1D("1VM4ArrivalTime","1VM4 Notch Arrival Time (50%)",100,0,100);
      f1VM4ArrivalTime->SetXTitle("Notch Arrival Time (us)");

      f1VM4NotchCurrent[0]  = new TH1D("1VM4NotchCurrent_0_10","Average Notch Current 0-10us",550,-5,50);
      f1VM4NotchCurrent[0]->SetXTitle("Average Current (us)");
      f1VM4NotchCurrent[1] = new TH1D("1VM4NotchCurrent_10_20","Average Notch Current 10-20us",550,-5,50);
      f1VM4NotchCurrent[1]->SetXTitle("Average Current (us)");
      f1VM4NotchCurrent[2] = new TH1D("1VM4NotchCurrent_20_30","Average Notch Current 20-30us",550,-5,50);
      f1VM4NotchCurrent[2]->SetXTitle("Average Current (us)");
      f1VM4NotchCurrent[3] = new TH1D("1VM4NotchCurrent_30_40","Average Notch Current 30-40us",550,-5,50);
      f1VM4NotchCurrent[3]->SetXTitle("Average Current (us)");
      f1VM4NotchCurrent[4] = new TH1D("1VM4NotchCurrent_40_50","Average Notch Current 40-50us",550,-5,50);
      f1VM4NotchCurrent[4]->SetXTitle("Average Current (us)");
      f1VM4NotchCurrent[5] = new TH1D("1VM4NotchCurrent_50_60","Average Notch Current 50-60us",550,-5,50);
      f1VM4NotchCurrent[5]->SetXTitle("Average Current (us)");


      //f1VM4NotchCleaniness = new TH1D("1VM4NotchCleaniness","1VM4 Notch Cleaniness",1000,0,20000);
      //f1VM4NotchCleaniness->SetXTitle("???");

      c = new TCanvas("Calibrated1VM4WithMagnetRamp");;  
      rampUpLine = new TLine(40,0,40,120);
      rampUpLine->SetLineColor(2);
      rampUpLine->SetLineStyle(2);
      
      rampDownLine = new TLine(90,0,90,120);; 
      rampDownLine->SetLineColor(2);
      rampDownLine->SetLineStyle(2);

      kickerText = new TText(41,1," <--   Kicker Ramp Period   --> ");
      kickerText->SetTextColor(2);;
      kickerText->SetTextSize(kickerText->GetTextSize()*0.9);;
      kickerText->SetTextAngle(90);;

};


long long gLastUpdate = gSystem->Now();
int gUpdateInterval = 5000;

#ifdef HAVE_MIDAS
#include "midas.h"
HNDLE hDB;
#endif

int TAnaManager::ProcessMidasEvent(TDataContainer& dataContainer){


  //std::cout << "Timestamp: " << dataContainer.GetMidasEvent().GetTimeStamp() << std::endl;
  
  TGenericData *data = dataContainer.GetEventData<TGenericData>("KTMG");
  if(!data) return 1;
  
  f1VM4Waveform->Reset();
  f1VM4WaveformCorrected->Reset();
  
  
  double offset = 3974.0;
  double avg = 0.0;
  int nnn = 0;
  
  
  //std::cout << "size " << data->GetSize() << std::endl;
  for(int i = 0; i < data->GetSize()-4; i++){
    
    uint32_t word = data->GetData32()[i+3];
    
    double adc = (word & 0x3fffff);
    double time = i*0.4;
    //std::cout << time << " " << volt << std::endl;
    f1VM4Waveform->SetBinContent(i+1,adc);

    if(time < 6) f1VM4BeamOnValues->Fill(adc);
    if(time > 30 && time < 50) f1VM4BeamOffValues->Fill(adc);
    

    avg += adc;
    nnn++;
    if(nnn >= 4){
      
      avg /= (float) nnn;

      //double calibrated_current = (avg - offset) * 0.00023116;
      //  New calibration, based on June 9 analysis
      double calibrated_current = 0.0;
      if(avg*avg >= 1.4746e7)
	calibrated_current = sqrt((avg*avg - 1.4746e7)/2.4156e7); 
      //      if(time < 20){
      //std::cout << avg << " " << calibrated_current << std::endl;

      //      }
      f1VM4WaveformCorrected->SetBinContent((i+1.0)/4.0,calibrated_current);


      avg = 0.0;
      nnn = 0;

    }
    
  }

  // Plot the waveform in canvas, with lines marking magnet ramp period
  c->cd();
  c->Clear();
  f1VM4WaveformCorrected->Draw();

  c->Update();


  double y1 = gPad->GetUymin();
  double y2 = gPad->GetUymax();  



  // Add text
  kickerText->SetY((y2-y1)*0.6);
  kickerText->Draw("SAME");

  // Draw lines for ramp-period
  rampUpLine->SetY1(y1);   rampUpLine->SetY2(y2);
  rampDownLine->SetY1(y1);   rampDownLine->SetY2(y2);
  rampUpLine->Draw("SAME");
  rampDownLine->Draw("SAME");

  c->Update();
  

  // Now analyze the calibrated waveform
  
  // calculate the beam on current by looking at first 8 samples
  double avg_beam_on_current = 0.0;
  for(int i = 0; i < 8; i++){
    avg_beam_on_current += f1VM4WaveformCorrected->GetBinContent(i+1);
  }
  avg_beam_on_current /= 8.0;

  //  std::cout << "Average beam on current " << avg_beam_on_current << std::endl;

  // Define beam current at 90%, 50% and 10% of nominal.
  double currentlevels[3]; double fractions[3] = {0.85,0.5,0.1};
  currentlevels[0] = avg_beam_on_current * fractions[0];
  currentlevels[1] = avg_beam_on_current * fractions[1];
  currentlevels[2] = avg_beam_on_current * fractions[2];

  // Find the times when notch goes below and above those values
  double timebelow[3] = {-1.0,-1.0,-1.0};
  double timeabove[3] = {-1.0,-1.0,-1.0};

  for(int i = 1; i < f1VM4WaveformCorrected->GetXaxis()->GetNbins();i++){

    double this_sample = f1VM4WaveformCorrected->GetBinContent(i);
    double next_sample = f1VM4WaveformCorrected->GetBinContent(i+1);
    double this_time = f1VM4WaveformCorrected->GetBinCenter(i);
    double next_time = f1VM4WaveformCorrected->GetBinCenter(i+1);
    double slope = (next_sample - this_sample)/(next_time-this_time);

    // Check if we have gone below a threshold
    for(int j = 0; j < 3; j++){
      if(timebelow[j] < 0.0) {  // make sure we didn't already find the crossing
	if(this_sample >= currentlevels[j] && next_sample < currentlevels[j]){ // found crossing
	  timebelow[j] = (currentlevels[j]-this_sample)/slope + this_time;
	  //	  std::cout << "Crossing ("<<fractions[j] <<") at time " << timebelow[j] << " RAW: " //
	  //	    << this_sample <<"/"<< currentlevels[j] <<"/"<< next_sample << "/" << this_time << std::endl;
	}	
      }
    }

    // Check if we have gone above a threshold
    for(int j = 0; j < 3; j++){
      if(timeabove[j] < 0.0) {  // make sure we didn't already find the crossing
	if(this_sample <= currentlevels[j] && next_sample > currentlevels[j]){ // found crossing
	  timeabove[j] = (currentlevels[j]-this_sample)/slope + this_time;
	  //std::cout << "AboveCrossing ("<<fractions[j] <<") at time " << timebelow[j] << " RAW: " 
	  //<< this_sample <<"/"<< currentlevels[j] <<"/"<< next_sample << "/" << this_time << std::endl;
	}	
      }
    }

  }
  
  // Use 50% crossing to calculate the width
  double width = 0;
  if(timeabove[1] > 0){
    f1VM4NotchWidth->Fill(timeabove[1]-timebelow[1]);
    width = timeabove[1]-timebelow[1];
  }else{
    f1VM4NotchWidth->Fill(f1VM4WaveformCorrected->GetBinCenter(f1VM4WaveformCorrected->GetXaxis()->GetNbins())
			  -timebelow[1]);
  }

  // Use 85%->10% time for fall time;
  double fallTime = timebelow[2]-timebelow[0];
  f1VM4FallTime->Fill(timebelow[2]-timebelow[0]);
  
  // Use 50% crossing for arrival time
  f1VM4ArrivalTime->Fill(timebelow[1]);   

  double averageCurrent[6], numberSamples[6];
  for(int i = 0; i < 6; i++){ averageCurrent[i] = 0.0; numberSamples[i] = 0.0;}

  // Loop again.  Calculate the average amount of current in periods after 50% height...
  for(int i = 1; i < f1VM4WaveformCorrected->GetXaxis()->GetNbins();i++){

    double this_sample = f1VM4WaveformCorrected->GetBinContent(i);
    double this_time = f1VM4WaveformCorrected->GetBinCenter(i);
    
    // Loop over the different periods after the 50% notch
    for(int j = 0; j < 6; j++){
      if((this_time >= timebelow[1] + j*10) && // Look for notch periods
	 (this_time < timebelow[1] + (j+1)*10)){
	averageCurrent[j] += this_sample;
	numberSamples[j] += 1.0;
      } 
    }

  }


  // Calculate the averages.
  //  std::cout << "Average current in notch: ";
  for(int j = 0; j < 6; j++){
    averageCurrent[j] /= numberSamples[j];
    f1VM4NotchCurrent[j]->Fill(averageCurrent[j]);    
    //std::cout << " " << averageCurrent[j];
  }
  // std::cout << std::endl;


  // Write out history values
  long long now = gSystem->Now();
  if(now - gLastUpdate > gUpdateInterval){
    gLastUpdate = now;

#ifdef HAVE_MIDAS
    // Create the variables, if not already existing
    if(!hDB){
      cm_get_experiment_database(&hDB,NULL);
      if(!hDB){
	std::cerr << "Data handle is null; can't connect!" << std::endl;
	std::exit(2);
      }else{
	std::cout << "Connected to MIDAS" << std::endl;
      }
    

      int ret = db_create_key(hDB,0,"/KTM_Analyzer/NotchArrivalTime",TID_DOUBLE);
      if(ret != DB_SUCCESS && ret != DB_KEY_EXIST){
	std::cerr << "Failed to create key Arrivaltime " << std::endl;
	return 1;
      }

      ret = db_create_key(hDB,0,"/KTM_Analyzer/NotchFallTime",TID_DOUBLE);
      ret = db_create_key(hDB,0,"/KTM_Analyzer/NotchWidth",TID_DOUBLE);
      ret = db_create_key(hDB,0,"/KTM_Analyzer/NotchCurrent_0_10",TID_DOUBLE);
      ret = db_create_key(hDB,0,"/KTM_Analyzer/NotchCurrent_10_20",TID_DOUBLE);
      ret = db_create_key(hDB,0,"/KTM_Analyzer/NotchCurrent_20_30",TID_DOUBLE);
      ret = db_create_key(hDB,0,"/KTM_Analyzer/NotchCurrent_30_40",TID_DOUBLE);
      ret = db_create_key(hDB,0,"/KTM_Analyzer/NotchCurrent_40_50",TID_DOUBLE);
      ret = db_create_key(hDB,0,"/KTM_Analyzer/NotchCurrent_50_60",TID_DOUBLE);
    }      

    HNDLE hKey;
    if(db_find_key(hDB,0,"/KTM_Analyzer/NotchArrivalTime",&hKey) != DB_SUCCESS){
      std::cerr << "Couldn't find key" << std::endl;
    }
    
    if(db_set_num_values(hDB,hKey,1) != DB_SUCCESS){
      std::cerr << "Another fail" << std::endl;
    }

    db_set_value(hDB,0,"/KTM_Analyzer/NotchArrivalTime",&timebelow[1],sizeof(double),1,TID_DOUBLE);

    db_find_key(hDB,0,"/KTM_Analyzer/NotchFallTime",&hKey);
    db_set_value(hDB,0,"/KTM_Analyzer/NotchFallTime",&fallTime,
		 sizeof(double),1,TID_DOUBLE);
    db_find_key(hDB,0,"/KTM_Analyzer/NotchWidth",&hKey);
    db_set_value(hDB,0,"/KTM_Analyzer/NotchWidth",&width,
		 sizeof(double),1,TID_DOUBLE);

    db_find_key(hDB,0,"/KTM_Analyzer/NotchCurrent_0_10",&hKey);
    db_set_value(hDB,0,"/KTM_Analyzer/NotchCurrent_0_10",&averageCurrent[0],
		 sizeof(double),1,TID_DOUBLE);
    db_find_key(hDB,0,"/KTM_Analyzer/NotchCurrent_10_20",&hKey);
    db_set_value(hDB,0,"/KTM_Analyzer/NotchCurrent_10_20",&averageCurrent[1],
		 sizeof(double),1,TID_DOUBLE);
    db_find_key(hDB,0,"/KTM_Analyzer/NotchCurrent_20_30",&hKey);
    db_set_value(hDB,0,"/KTM_Analyzer/NotchCurrent_20_30",&averageCurrent[2],
		 sizeof(double),1,TID_DOUBLE);
    db_find_key(hDB,0,"/KTM_Analyzer/NotchCurrent_30_40",&hKey);
    db_set_value(hDB,0,"/KTM_Analyzer/NotchCurrent_30_40",&averageCurrent[3],
		 sizeof(double),1,TID_DOUBLE);
    db_find_key(hDB,0,"/KTM_Analyzer/NotchCurrent_40_50",&hKey);
    db_set_value(hDB,0,"/KTM_Analyzer/NotchCurrent_40_50",&averageCurrent[4],
		 sizeof(double),1,TID_DOUBLE);
    db_find_key(hDB,0,"/KTM_Analyzer/NotchCurrent_50_60",&hKey);
    db_set_value(hDB,0,"/KTM_Analyzer/NotchCurrent_50_60",&averageCurrent[5],
		 sizeof(double),1,TID_DOUBLE);


#endif

  }


  return 1;
}





