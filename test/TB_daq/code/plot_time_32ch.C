#include <stdio.h>

//int plot_waveform_32ch(const TString filename, const int min, const int max, const TString condition)
int plot_time_32ch(const TString filename)
{
  int channel;
  int ch_to_plot;
  FILE *fp;
  int file_size;
  int nevt;
  int ndraw;
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
  int i;
  int j;
  int cont;
  int pede[32];
  int left, right,up,down;
  ndraw = 10;
//  ndraw = 10;
  // get channel to plot, channel = 1 ~ 32
//  printf("Channel to plot(1~32) : ");
//  scanf("%d", &channel);
//  if (channel < 1)
//    ch_to_plot = 0;
//  else if (channel > 32)
//    ch_to_plot = 31;
//  else
//    ch_to_plot = channel - 1;
    
  TCanvas *c1 = new TCanvas("c1", "CAL DAQ", 1800, 1000);
  c1->Divide(3,2,0.001,0.001);
  gPad->SetLeftMargin(0);
  gPad->SetRightMargin(0);
  gPad->SetBottomMargin(0);
  gPad->SetTopMargin(0);

  TH1F *plot[32];
  TH1F *time[32];
  for( i = 0 ; i < 32 ; i ++)
  {
     plot[i] = new TH1F(Form("plot%d",i+1), Form("Waveform ch%d", i+1), 1023,0,1023);
     plot[i]->SetStats(0);  
     time[i] = new TH1F(Form("time%d",i+1), Form("time ch%d", i+1), 1023,0,1023);
	 time[i]->SetStats(1);
  }
  TFile *tfile = new TFile(filename+"_DWC_.root","RECREATE");
  

  // get # of events in file
  fp = fopen(filename, "rb");
  fseek(fp, 0L, SEEK_END);
  file_size = ftell(fp);
  fclose(fp);
  nevt = file_size / 65536;
  
  printf("-----------------------------------------------------------------------\n");
  fp = fopen(filename, "rb");

  TH1F * diffRL = new TH1F("diffRL","time diff RL",1023,-511,511);
  TH1F * diffUD = new TH1F("diffUD","time diff UD",1023,-511,511);
  for (evt = 0; evt < nevt; evt++) {
    // read header
    fread(data, 1, 64, fp);
    /*
    // data length
    data_length = data[0] & 0xFF;
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
    
    // fill waveform for channel to plotgecit 
    for( i = 0 ; i < 32 ; i ++)
    {
       plot[i]->Reset();
    }
	for (i=0;i<32;i++){
	  pede[i]=0;
      for (j=1;j<101;j++){
	    pede[i]+=adc[ j * 32 + i ]; 
	  }
	  pede[i]=pede[i]/100;
	}
    
    for (i = 0; i < 1023; i++) {
      for( j = 0; j < 32 ; j ++) {
//		if(j==21 || j == 22 || j ==23) cout << j << " th channel : " << adc[i * 32 + j]<< endl;
         plot[j]->Fill(i, pede[j]-adc[i * 32 + j]);
      }
    }
    
  for(i =0; i<32;i++){   
     /*c1->cd(i+1);
     plot[i]->GetYaxis()->SetRangeUser(min,max);
     plot[i]->GetYaxis()->SetLabelSize(0.05);
     plot[i]->Draw("hist");*/
//		std::cout << plot[i]->GetMaximum() << ", " << plot[i]->GetMaximumBin() << std::endl;
	 for (j=1;j<1024;j++){
       if(pede[i]-adc[j*32+i]>plot[i]->GetMaximum()*0.1){
	     time[i]->Fill(j);
		 if(i==24)right =j;
		 if(i==26)left=j;
		 if(i==28)up=j;
		 if(i==30)down=j;
//		 std::cout<<"ch is "<<i<<"|t0 is "<<pede[i]-adc[j*32+i]<<std::endl;
		 break;
	   }
	 }
	 
	 //std::cout<<"ch : "<<i<<"| to :"<<plot[i]->FindFirstBinAbove(plot[i]->GetMaximum()*0.1)<<std::endl;

  }
  //if(right != 0 && left != 0)diffRL->Fill(right-left);
  diffRL->Fill(right-left);
  diffUD->Fill(up-down);
    //c1->Modified();
    //c1->Update();
    //c1->SaveAs(filename+"_"+condition+Form("_AllchWave_evtNum%d.png", evt));      
    //c1->SaveAs(filename+Form("_AllchWave_evtNum%d.png", evt));      

    if (evt%100==0)printf("%d evt\n",evt);
//    scanf("%d", &cont);
    
//    if (cont == 0)
      //evt = nevt;
     // if(evt == ndraw) evt = nevt;
  }
  c1->cd(1);
  time[24]->Draw("hist");
  c1->cd(2);
  time[26]->Draw("hist");
  c1->cd(3);
  time[28]->Draw("hist");
  c1->cd(4);
  time[30]->Draw("hist");
  c1->cd(5);
  diffRL->Draw("hist");
  c1->cd(6);
  diffUD->Draw("hist");
  /*for (i=0;i<32;i++){
    c1->cd(i+1);
    time[i]->Draw("hist");
  }*/
  fclose(fp);

  c1->Write();
  tfile->Close();

  return 0;
}

