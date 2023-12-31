#include <stdio.h>

int show_fast_one_sipm(const int runnum, const int mid, const int ch)
{
  int channel;
  int ch_to_plot;
  FILE *fp;
  int file_size;
  int nevt;
  char header[64];
  short data[96];
  int evt;
  int i;
  int energy;
  int timing;
  char outname[100];
  char filename[100];
  int filenum;

  // get channel to plot, channel = 1 ~ 32
 // printf("Channel to plot(1~32) : ");
  //scanf("%d", &channel);
  //ch_to_plot = ch;
  if (ch < 1)
    ch_to_plot = 0;
  else if (ch > 32)
    ch_to_plot = 31;
  else
    ch_to_plot = ch - 1;
  sprintf(outname,"fast_%d_%d_%d.root",runnum,mid,ch);
  TFile *fp_root = new TFile(outname,"recreate");  
  TCanvas *c1 = new TCanvas("c1", "CAL DAQ", 800, 800);
  c1->Divide(1, 2);
  TH1F *plot_e = new TH1F("plot_e", "Energy", 1000000, -10000, 1000000); 
  TH1F *plot_t = new TH1F("plot_t", "Timing", 1000, 0, 16000); 
  plot_e->Reset();
  plot_t->Reset();

  // get # of events in file
  for (filenum=0;filenum < 200;filenum++){
    //sprintf(filename,"/Users/drc_daq/scratch/Aug2022TB/SSD/SSD_Run_%d/Run_%d_Fast/Run_%d_Fast_MID_%d/Run_%d_Fast_MID_%d_FILE_%d.dat",runnum,runnum,runnum,mid,runnum,mid,filenum);
    sprintf(filename,"/Volumes/HDD_16TB_2/HDD_Run_%d/Run_%d_Fast/Run_%d_Fast_MID_%d/Run_%d_Fast_MID_%d_FILE_%d.dat",runnum,runnum,runnum,mid,runnum,mid,filenum);
    if (access(filename,0)!=0) break;
    printf("%s\n",filename);
    fp = fopen(filename, "rb");
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    fclose(fp);
    nevt = file_size / 256;
    
    fp = fopen(filename, "rb");
   
    for (evt = 0; evt < nevt; evt++) {
      // read header
      fread(header, 1, 64, fp);
      
      // read fast data
      fread(data, 2, 96, fp);
      
      // fill waveform for channel to plot
      energy = data[ch_to_plot * 3 + 1] & 0xFFFF;
      energy = energy * 65536;
      energy = energy + (data[ch_to_plot * 3] & 0xFFFF);
   
      timing = data[ch_to_plot * 3 + 2] & 0xFFFF;
      //if (timing>10000){
      //printf("energy : %d evt : %d\n",energy,evt);
      if(timing>1000&&timing<3000)plot_e->Fill(energy);
      plot_t->Fill(timing);
      //}
    }
    
   
    c1->cd(1);
    plot_e->Draw();
    c1->cd(2);
    plot_t->Draw();
   
    c1->Write();
    c1->Modified();
    c1->Update();
        
    fclose(fp);
    }
  fp_root->Close();
  return 0;
}

