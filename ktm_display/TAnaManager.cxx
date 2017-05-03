#include "TAnaManager.hxx"
#include "TV1720RawData.h"

#include <iostream>
#include <fstream>


TAnaManager::TAnaManager(){

	fKTMHistogram = 0;
#ifdef USE_KTM
	fKTMHistogram = new TKTMHistograms();
	fKTMHistogram->DisableAutoUpdate();  // disable auto-update.  Update histo in AnaManager.
#endif

};



int TAnaManager::ProcessMidasEvent(TDataContainer& dataContainer){


  std::cout << "Timestamp: " << dataContainer.GetMidasEvent().GetTimeStamp() << std::endl;

  if(fKTMHistogram) fKTMHistogram->UpdateHistograms(dataContainer); 
  
  return 1;
}



bool TAnaManager::HaveKTMHistograms(){
	if(fKTMHistogram) return true; 
	return false;
}



TKTMHistograms* TAnaManager::GetKTMHistograms() {return fKTMHistogram;}


