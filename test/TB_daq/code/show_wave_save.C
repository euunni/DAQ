#include <stdio.h>

int show_wave_save(const int mid, const int runnum)
{
  int channel;
  int ch_to_plot;
  FILE *fp;
  int file_size;
  int nevt;
  char data[64];
  short adc[32736];
  int evt;
  int data_length;
  int run_number;
  int tcb_trig_type;
  int tcb_trig_number;
  long long tcb_trig_time;
  //int mid;
  int local_trig_number;
  int local_trigger_pattern;
  long long local_trig_time;
  long long diff_time;
  long long fine_time;
  long long coarse_time;
  int itmp;
  long long ltmp;
  int i;
  int cont;
  char outname[100];
  char filename[100];
  char pngname[100];
  int ped=0;
  
  // get channel to plot, channel = 1 ~ 32
  printf("Channel to plot(1~32) : ");
  scanf("%d", &channel);
  if (channel < 1)
    ch_to_plot = 0;
  else if (channel > 32)
    ch_to_plot = 31;
  else
    ch_to_plot = channel - 1;
  //sprintf(outname,"wave_%d_%d_%d.root",runnum,mid,ch_to_plot+1);
  //TFile *fp_root = new TFile(outname,"recreate");
  TCanvas *c1 = new TCanvas("c1", "CAL DAQ", 800, 500);
  TH1F *plot = new TH1F("plot", "Waveform", 1023, 0, 1023); 
  //plot->SetStats(1);
  //TH1F *peak = new TH1F("peak","peak",4096,0,4096);

  // get # of events in file
  sprintf(filename,"/Users/yhep/scratch/YUdaq/SSD/SSD_Run_%d/Run_%d_Wave/Run_%d_Wave_MID_%d/Run_%d_Wave_MID_%d_FILE_0.dat",runnum,runnum,runnum,mid,runnum,mid);
  printf("%s\n",filename);
  fp = fopen(filename, "rb");
  fseek(fp, 0L, SEEK_END);
  file_size = ftell(fp);
  fclose(fp);
  nevt = file_size / 65536;
  
  printf("-----------------------------------------------------------------------\n");
  fp = fopen(filename, "rb");
//  fp = fopen("cal_sipm_pmt_10k.dat", "rb");

  //btcb_trig_time = 0;

  for (evt = 0; evt < nevt; evt++) {
    // read header
    fread(data, 1, 64, fp);
    
    // data length
 /*   data_length = data[0] & 0xFF;
    itmp = data[1] & 0xFF;
    itmp = itmp << 8;
    data_length = data_length + itmp;
    itmp = data[2] & 0xFF;
    itmp = itmp << 16;
    data_length = data_length + itmp;
    itmp = data[3] & 0xFF;
    itmp = itmp << 24;
    data_length = data_length + itmp;

    // run number
    run_number = data[4] & 0xFF;
    itmp = data[5] & 0xFF;
    itmp = itmp << 8;
    run_number = run_number + itmp;
    
    // trigger type
    tcb_trig_type = data[6] & 0xFF;
    
    // TCB trigger #
    tcb_trig_number = data[7] & 0xFF;
    itmp = data[8] & 0xFF;
    itmp = itmp << 8;
    tcb_trig_number = tcb_trig_number + itmp;
    itmp = data[9] & 0xFF;
    itmp = itmp << 16;
    tcb_trig_number = tcb_trig_number + itmp;
    itmp = data[10] & 0xFF;
    itmp = itmp << 24;
    tcb_trig_number = tcb_trig_number + itmp;

    // TCB trigger time
    fine_time = data[11] & 0xFF;
    fine_time = fine_time * 11;     // actually * (1000 / 90)
    coarse_time = data[12] & 0xFF;
    ltmp = data[13] & 0xFF;
    ltmp = ltmp << 8;
    coarse_time = coarse_time + ltmp;
    ltmp = data[14] & 0xFF;
    ltmp = ltmp << 16;
    coarse_time = coarse_time + ltmp;
    ltmp = data[15] & 0xFF;
    ltmp = ltmp << 24;
    coarse_time = coarse_time + ltmp;
    ltmp = data[16] & 0xFF;
    ltmp = ltmp << 32;
    coarse_time = coarse_time + ltmp;
    ltmp = data[17] & 0xFF;
    ltmp = ltmp << 40;
    coarse_time = coarse_time + ltmp;
    coarse_time = coarse_time * 1000;   // get ns
    tcb_trig_time = fine_time + coarse_time;
    
    // mid
    mid = data[18] & 0xFF;

    // local trigger #
    local_trig_number = data[19] & 0xFF;
    itmp = data[20] & 0xFF;
    itmp = itmp << 8;
    local_trig_number = local_trig_number + itmp;
    itmp = data[21] & 0xFF;
    itmp = itmp << 16;
    local_trig_number = local_trig_number + itmp;
    itmp = data[22] & 0xFF;
    itmp = itmp << 24;
    local_trig_number = local_trig_number + itmp;

    // local trigger #
    local_trigger_pattern = data[23] & 0xFF;
    itmp = data[24] & 0xFF;
    itmp = itmp << 8;
    local_trigger_pattern = local_trigger_pattern + itmp;
    itmp = data[25] & 0xFF;
    itmp = itmp << 16;
    local_trigger_pattern = local_trigger_pattern + itmp;
    itmp = data[26] & 0xFF;
    itmp = itmp << 24;
    local_trigger_pattern = local_trigger_pattern + itmp;

    // local trigger time
    fine_time = data[27] & 0xFF;
    fine_time = fine_time * 11;     // actually * (1000 / 90)
    coarse_time = data[28] & 0xFF;
    ltmp = data[29] & 0xFF;
    ltmp = ltmp << 8;
    coarse_time = coarse_time + ltmp;
    ltmp = data[30] & 0xFF;
    ltmp = ltmp << 16;
    coarse_time = coarse_time + ltmp;
    ltmp = data[31] & 0xFF;
    ltmp = ltmp << 24;
    coarse_time = coarse_time + ltmp;
    ltmp = data[32] & 0xFF;
    ltmp = ltmp << 32;
    coarse_time = coarse_time + ltmp;
    ltmp = data[33] & 0xFF;
    ltmp = ltmp << 40;
    coarse_time = coarse_time + ltmp;
    coarse_time = coarse_time * 1000;   // get ns
    local_trig_time = fine_time + coarse_time;

    diff_time = local_trig_time - tcb_trig_time;
    printf("evt = %d, data length = %d, run # = %d, mid = %d\n", evt, data_length, run_number, mid);
    printf("trigger type = %X, local trigger pattern = %X\n", tcb_trig_type, local_trigger_pattern);
    printf("TCB trigger # = %d, local trigger # = %d\n", tcb_trig_number, local_trig_number);
    printf("TCB trigger time = %lld, local trigger time = %lld, difference = %lld\n", tcb_trig_time, local_trig_time, diff_time);
    printf("-----------------------------------------------------------------------\n");
   */ 
    // read waveform
    fread(adc, 2, 32736, fp);
    for (i=1;i<101;i++){
      ped+=adc[i * 32 + ch_to_plot];
	}
	ped = ped/100;
    // fill waveform for channel to plotgecit 
    plot->Reset();
    for (i = 0; i < 1023; i++) {
      plot->Fill(i,ped - adc[i * 32 + ch_to_plot]);
    }
//	peak->Fill(plot->GetMaximum());
	//plot->GetYaxis()->SetRangeUser(0,4096);
   // plot->Draw("hist");
   // plot->Write();
    
    //sprintf(pngname,"wave_%d.png",evt);
    //c1->SaveAs(filename+Form(("_%d.png"),evt));
    c1->Modified();
    c1->Update();
      
    printf("Continue? ");
    scanf("%d", &cont);
    
    if (cont == 0)
      evt = nevt;
  }
  //peak -> Write();
  fclose(fp);

 // fp_root->Close();
  return 0;
}

