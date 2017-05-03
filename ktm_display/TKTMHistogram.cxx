#include "TKTMHistogram.h"
#include <iostream>
#include <fstream>

#include "TDirectory.h"

const int Nchannels = 2;
 #include <sys/time.h>

/// Reset the histograms for this canvas
TKTMHistograms::TKTMHistograms(){  
  
  CreateHistograms();
}


void TKTMHistograms::CreateHistograms(){
  

  // Otherwise make histograms
  clear();
  
  for(int i = 0; i < Nchannels; i++){ // loop over channels    

    char name[100];
    char title[100];
    sprintf(name,"KTM_%i_%i",0,i);

    // Delete old histograms, if we already have them
    TH1D *old = (TH1D*)gDirectory->Get(name);
    if (old){
      delete old;
    }


    // Create new histograms
    
    sprintf(title,"1VM4 Waveform",i);	
    
    TH1D *tmp = new TH1D(name,title,350,0,70);
    tmp->SetYTitle("Pule Height");
    tmp->SetXTitle("time (us)");
    push_back(tmp);
  }

}



  
/// Update the histograms for this canvas.
void TKTMHistograms::UpdateHistograms(TDataContainer& dataContainer){

  TGenericData *data = dataContainer.GetEventData<TGenericData>("KTMG");
  if(!data) return;
  
  GetHistogram(0)->Reset();
  
  //std::cout << "size " << data->GetSize() << std::endl;
  for(int i = 0; i < data->GetSize()-4; i++){
    
    uint32_t word = data->GetData32()[i+3];
    
    double adc = (word & 0x3fffff);
    //std::cout << time << " " << volt << std::endl;
    GetHistogram(0)->SetBinContent(i+1,adc);
    
  }
  
	//Find 50% valve for this pulse
	Int_t maxBin = GetHistogram(0)->GetMaximumBin();
	double halfMaxValue = GetHistogram(0)->GetBinContent(maxBin)/2;
	std::cout<<std::endl<<"Maximum Bin:"<<GetHistogram(0)->GetBinCenter(maxBin)<<"	Half Maximum Bin Value: "<<halfMaxValue<< std::endl;
	
	//If 50% < .1 then is probably not a pulse
	if (halfMaxValue < .1)	
		return;
	
	//Otherwise look for falling edge
	bool fallingedge = false;
	//int currentbin = GetHistogram(0)->FindFirstBinAbove(halfMaxValue);
	int currentbin = 1;
	int nbins = GetHistogram(0)->GetNbinsX();

	//Find the first falling edge 
	while(GetHistogram(0)->GetBinContent(currentbin)>halfMaxValue && currentbin<nbins)
		{currentbin++;}		
	
	/*	
	if(GetHistogram(0)->GetBinContent(currentbin)>GetHistogram(0)->GetBinContent(currentbin+1))
	{
		while(GetHistogram(0)->GetBinContent(currentbin)<halfMaxValue && currentbin<nbins)
			{currentbin++;}
		while(GetHistogram(0)->GetBinContent(currentbin)>halfMaxValue && currentbin<nbins)
			{currentbin++;} 
	}*/

	//If Falling edge not found, return
	if(currentbin==1)
		return;
	std::cout<<"Half Max Falling Edge Bin: "<<GetHistogram(0)->GetBinCenter(currentbin)<<std::endl;

	double fallTime = GetHistogram(0)->GetBinCenter(currentbin);

	while(!fallingedge && currentbin<nbins)
	{
		if( GetHistogram(0)->GetBinContent(currentbin) < halfMaxValue*.04)
			fallingedge=true;
		else
			currentbin++;
	}
	
	std::cout<<"Found falling edge? "<<fallingedge<<std::endl;
 	if (!fallingedge)
		return; 
  	//Look for a rising edge after the falling edge
  	bool risingedge = false;
	double riseTime = -1;
	int nocurrentstartbin = currentbin;
	
	while (!risingedge && currentbin<nbins)
	{
		if( GetHistogram(0)->GetBinContent(currentbin)>=halfMaxValue)
			risingedge=true;
		else
			currentbin++;
	}
	std::cout<<"Found Rising Edge? "<<risingedge<<std::endl;
	if (risingedge)
	{
		riseTime = GetHistogram(0)->GetBinCenter(currentbin);
		std::cout<<"Pulse Length: "<<riseTime-fallTime<<std::endl;
	
		//If there is a rising edge, calculate the current during notch time	
		double currentduringpulse=0;

		for(int i=nocurrentstartbin; i<=currentbin;i++)
		{
			currentduringpulse+= GetHistogram(0)->GetBinContent(i);
		}
		
		std::cout<<"Falling Edge Time: "<<GetHistogram(0)->GetBinCenter(nocurrentstartbin)-fallTime<<std::endl;
		std::cout<<"Falling Edge Start: "<<GetHistogram(0)->GetBinCenter(nocurrentstartbin)<<std::endl;
		std::cout<<"Falling Edge End: "<<fallTime<<std::endl;
		
		std::cout<<"Current During Pulse: "<<currentduringpulse<<std::endl;

		//Write to the .csv File 
		std::ofstream outfile; 
		outfile.open ("PulseDetails.csv",std::ios_base::app);
		outfile<<dataContainer.GetMidasEvent().GetTimeStamp()<<", "<<riseTime-fallTime<<", "<<GetHistogram(0)->GetBinCenter(nocurrentstartbin)-fallTime<<", "<<currentduringpulse<<std::endl;
		outfile.close();	
	}


}



/// Take actions at begin run
void TKTMHistograms::BeginRun(int transition,int run,int time){

  CreateHistograms();

}

/// Take actions at end run  
void TKTMHistograms::EndRun(int transition,int run,int time){

}
