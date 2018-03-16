#ifndef TAnaManager_h
#define TAnaManager_h

// Use this list here to decide which type of equipment to use.

#include "TH1D.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TText.h"
#include "TDataContainer.hxx"


/// This is an example of how to organize a set of different histograms
/// so that we can access the same information in a display or a batch
/// analyzer.
/// Change the set of ifdef's above to define which equipment to use.
class TAnaManager  {
public:
  TAnaManager();
  virtual ~TAnaManager(){};

  /// Processes the midas event, fills histograms, etc.
  int ProcessMidasEvent(TDataContainer& dataContainer);

  TH1D * GetRawWaveform(){return f1VM4Waveform;}
  TH1D * GetCalibratedWaveform(){return f1VM4WaveformCorrected;};



private:

  TH1D *f1VM4Waveform;
  TH1D *f1VM4WaveformCorrected;
  TH1D *f1VM4BeamOnValues;
  TH1D *f1VM4BeamOffValues;
  TH1D *f1VM4NotchWidth;
  TH1D *f1VM4FallTime;
  TH1D *f1VM4ArrivalTime;

  TH1D *f1VM4NotchCurrent[6];
  TH1D *f1VM4NotchCleaniness;

  TCanvas *c;  
  TLine *rampUpLine;
  TLine *rampDownLine; 
  TText *kickerText;



};



#endif


