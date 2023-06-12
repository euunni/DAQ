#include <stdio.h>

int intADC_peak_range(const int runnum, const int Mid, const int channel, const int min, const int max, const double time)
{
  int ch_to_plot;
  FILE *fp;
  FILE *fp2;
  long long file_size;
  int nevt;
  char data[64];
  short adc[32736];
  int evt;
  int data_length;
  int run_number;
  int tcb_trig_type;
  int tcb_trig_number;
  long long tcb_trig_time;
  int mid;
  int local_trig_number;
  int local_trigger_pattern;
  long long local_trig_time;
  long long diff_time;
  long long fine_time;
  long long coarse_time;
  int itmp;
  long long ltmp;
  int cont;
  char filename[100];
  char rootfilename[100];
  float intADC;
  int ifile;
  int i;
  int ped;
  int pedsum;


  // get channel to plot, channel = 1 ~ 32
  if (channel < 1)
    ch_to_plot = 0;
  else if (channel > 32)
    ch_to_plot = 31;
  else
    ch_to_plot = channel - 1;


  //TFile *file = new TFile((TString)("IntADC_Run_" + std::to_string(runnum) + ".root"), "RECREATE");
  // TCanvas *c = new TCanvas("c", "IntADC");
  TH1F *intADCHist = new TH1F("IntADC", "IntADC;Int.ADC;Evts", 1000, -1000., 800000.);
  std::vector<float> tmpWave;
  intADCHist->SetLineColor(kBlack);

  gStyle->SetOptFit(1);

  // for ( ifile = 0; ifile < 200; ifile++ ) {  
    sprintf(filename,"/Users/yhep/scratch/YUdaq/Run_%d/Run_%d_Wave/Run_%d_Wave_MID_%d/Run_%d_Wave_MID_%d_FILE_0.dat",runnum,runnum,runnum,Mid,runnum,Mid);
    // if (access(filename,0)!=0) break;
    printf("%s\n",filename);
    fp = fopen(filename, "rb");
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    fclose(fp);
    nevt = file_size / 65536;
    
    printf("-----------------------------------------------------------------------\n");
    fp = fopen(filename, "rb");
   
   
    for (evt = 0; evt < nevt; evt++) {
     
      fread(data, 1, 64, fp);
      fread(adc, 2, 32736, fp);
   
      tmpWave.clear();

      ped = 0;
      pedsum = 0;
      for ( i = 1; i < 101; i++) {
        pedsum += adc[i * 32 + ch_to_plot];
      }
      ped += pedsum / 100.;
   
      for ( i = 0; i < 1023; i++ ) {
        tmpWave.push_back(adc[i * 32 + ch_to_plot]);
      }

      double peak1 = 0;
      double peak2 = 0;

      peak1 = *std::min_element(tmpWave.begin() + 200, tmpWave.begin() + 300);
      peak2 = *std::min_element(tmpWave.begin() + 600, tmpWave.begin() + 1000);

      if ( peak1 > 3200. )
        continue;
      if ( peak2 < 3200.)
        continue;

      float intADC = 0.f;
      for ( i = min; i < max; i++ ) {
          int waveformBin = i + 1;
          intADC += ped - tmpWave[waveformBin];
      }
   
      intADCHist->Fill(intADC);
    }
    fclose(fp);
  // }

  // c->cd();
  intADCHist->Scale(1./time);
  //intADCHist->SetOption("HIST");
  //intADCHist->Write();
  //file->Close();
  intADCHist->Draw("HIST");

  return 0;
}

