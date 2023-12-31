#include <stdio.h>

int plot_waveform_32ch_5ADC(const TString filename)
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
  int cont;

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
  c1->Divide(8,4,0.001,0.001);
  gPad->SetLeftMargin(0);
  gPad->SetRightMargin(0);
  gPad->SetBottomMargin(0);
  gPad->SetTopMargin(0);

  TH1F *plot1 = new TH1F("plot", "Waveform ch1", 1023, 0, 1023); 
  TH1F *plot2 = new TH1F("plot", "Waveform ch2", 1023, 0, 1023);
  TH1F *plot3 = new TH1F("plot", "Waveform ch3", 1023, 0, 1023);
  TH1F *plot4 = new TH1F("plot", "Waveform ch4", 1023, 0, 1023);
  TH1F *plot5 = new TH1F("plot", "Waveform ch5", 1023, 0, 1023);
  TH1F *plot6 = new TH1F("plot", "Waveform ch6", 1023, 0, 1023);
  TH1F *plot7 = new TH1F("plot", "Waveform ch7", 1023, 0, 1023);
  TH1F *plot8 = new TH1F("plot", "Waveform ch8", 1023, 0, 1023);
  TH1F *plot9 = new TH1F("plot", "Waveform ch9", 1023, 0, 1023);
  TH1F *plot10 = new TH1F("plot", "Waveform ch10", 1023, 0, 1023);
  TH1F *plot11 = new TH1F("plot", "Waveform ch11", 1023, 0, 1023);
  TH1F *plot12 = new TH1F("plot", "Waveform ch12", 1023, 0, 1023);
  TH1F *plot13 = new TH1F("plot", "Waveform ch13", 1023, 0, 1023);
  TH1F *plot14 = new TH1F("plot", "Waveform ch14", 1023, 0, 1023);
  TH1F *plot15 = new TH1F("plot", "Waveform ch15", 1023, 0, 1023);
  TH1F *plot16 = new TH1F("plot", "Waveform ch16", 1023, 0, 1023);
  TH1F *plot17 = new TH1F("plot", "Waveform ch17", 1023, 0, 1023);
  TH1F *plot18 = new TH1F("plot", "Waveform ch18", 1023, 0, 1023);
  TH1F *plot19 = new TH1F("plot", "Waveform ch19", 1023, 0, 1023);
  TH1F *plot20 = new TH1F("plot", "Waveform ch20", 1023, 0, 1023);
  TH1F *plot21 = new TH1F("plot", "Waveform ch21", 1023, 0, 1023);
  TH1F *plot22 = new TH1F("plot", "Waveform ch22", 1023, 0, 1023);
  TH1F *plot23 = new TH1F("plot", "Waveform ch23", 1023, 0, 1023);
  TH1F *plot24 = new TH1F("plot", "Waveform ch24", 1023, 0, 1023);
  TH1F *plot25 = new TH1F("plot", "Waveform ch25", 1023, 0, 1023);
  TH1F *plot26 = new TH1F("plot", "Waveform ch26", 1023, 0, 1023);
  TH1F *plot27 = new TH1F("plot", "Waveform ch27", 1023, 0, 1023);
  TH1F *plot28 = new TH1F("plot", "Waveform ch28", 1023, 0, 1023);
  TH1F *plot29 = new TH1F("plot", "Waveform ch29", 1023, 0, 1023);
  TH1F *plot30 = new TH1F("plot", "Waveform ch30", 1023, 0, 1023);
  TH1F *plot31 = new TH1F("plot", "Waveform ch31", 1023, 0, 1023);
  TH1F *plot32 = new TH1F("plot", "Waveform ch32", 1023, 0, 1023);

  plot1->SetStats(0);
  plot2->SetStats(0);
  plot3->SetStats(0);
  plot4->SetStats(0);
  plot5->SetStats(0);
  plot6->SetStats(0);
  plot7->SetStats(0);
  plot8->SetStats(0);
  plot9->SetStats(0);
  plot10->SetStats(0);
  plot11->SetStats(0);
  plot12->SetStats(0);
  plot13->SetStats(0);
  plot14->SetStats(0);
  plot15->SetStats(0);
  plot16->SetStats(0);
  plot17->SetStats(0);
  plot18->SetStats(0);
  plot19->SetStats(0);
  plot20->SetStats(0);
  plot21->SetStats(0);
  plot22->SetStats(0);
  plot23->SetStats(0);
  plot24->SetStats(0);
  plot25->SetStats(0);
  plot26->SetStats(0);
  plot27->SetStats(0);
  plot28->SetStats(0);
  plot29->SetStats(0);
  plot30->SetStats(0);
  plot31->SetStats(0);
  plot32->SetStats(0);

  // get # of events in file
  fp = fopen(filename, "rb");
  fseek(fp, 0L, SEEK_END);
  file_size = ftell(fp);
  fclose(fp);
  nevt = file_size / 65536;
  
  printf("-----------------------------------------------------------------------\n");
  fp = fopen(filename, "rb");

  for (evt = 0; evt < nevt; evt++) {
    // read header
    fread(data, 1, 64, fp);
    
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
    
    // read waveform
    fread(adc, 2, 32736, fp);
    
    // fill waveform for channel to plotgecit 
    plot1->Reset();
    plot2->Reset();
    plot3->Reset();
    plot4->Reset();
    plot5->Reset();
    plot6->Reset();
    plot7->Reset();
    plot8->Reset();
    plot9->Reset();
    plot10->Reset();
    plot11->Reset();
    plot12->Reset();
    plot13->Reset();
    plot14->Reset();
    plot15->Reset();
    plot16->Reset();
    plot17->Reset();
    plot18->Reset();
    plot19->Reset();
    plot20->Reset();
    plot21->Reset();
    plot22->Reset();
    plot23->Reset();
    plot24->Reset();
    plot25->Reset();
    plot26->Reset();
    plot27->Reset();
    plot28->Reset();
    plot29->Reset();
    plot30->Reset();
    plot31->Reset();
    plot32->Reset();
    
    for (i = 0; i < 1023; i++) {
      plot1->Fill(i, adc[i * 32 + 0]);
      plot2->Fill(i, adc[i * 32 + 1]);
      plot3->Fill(i, adc[i * 32 + 2]);
      plot4->Fill(i, adc[i * 32 + 3]);
      plot5->Fill(i, adc[i * 32 + 4]);
      plot6->Fill(i, adc[i * 32 + 5]);
      plot7->Fill(i, adc[i * 32 + 6]);
      plot8->Fill(i, adc[i * 32 + 7]);
      plot9->Fill(i, adc[i * 32 + 8]);
      plot10->Fill(i, adc[i * 32 + 9]);
      plot11->Fill(i, adc[i * 32 + 10]);
      plot12->Fill(i, adc[i * 32 + 11]);
      plot13->Fill(i, adc[i * 32 + 12]);
      plot14->Fill(i, adc[i * 32 + 13]);
      plot15->Fill(i, adc[i * 32 + 14]);
      plot16->Fill(i, adc[i * 32 + 15]);
      plot17->Fill(i, adc[i * 32 + 16]);
      plot18->Fill(i, adc[i * 32 + 17]);
      plot19->Fill(i, adc[i * 32 + 18]);
      plot20->Fill(i, adc[i * 32 + 19]);
      plot21->Fill(i, adc[i * 32 + 20]);
      plot22->Fill(i, adc[i * 32 + 21]);
      plot23->Fill(i, adc[i * 32 + 22]);
      plot24->Fill(i, adc[i * 32 + 23]);
      plot25->Fill(i, adc[i * 32 + 24]);
      plot26->Fill(i, adc[i * 32 + 25]);
      plot27->Fill(i, adc[i * 32 + 26]);
      plot28->Fill(i, adc[i * 32 + 27]);
      plot29->Fill(i, adc[i * 32 + 28]);
      plot30->Fill(i, adc[i * 32 + 29]);
      plot31->Fill(i, adc[i * 32 + 30]);
      plot32->Fill(i, adc[i * 32 + 31]);

      //if (adc[i * 32 + ch_to_plot] < 3000) printf("abnormal value = %d @ %d\n", adc[i * 32 + ch_to_plot], evt);
    }
    //plot->GetXaxis()->SetRangeUser(0,1000);
    //TH1F* plot_copy= (TH1F*)plot->Clone();
    int min =0;
    int max =0;
    c1->cd(1);
    max = plot1->GetMaximum() + 10;
    min = plot1->GetMinimum() - 10;
    plot1->GetYaxis()->SetRangeUser(min,max);
    plot1->GetYaxis()->SetLabelSize(0.05);
    plot1->Draw("hist");
    c1->cd(2);
    max = plot2->GetMaximum() + 10;
    min = plot2->GetMinimum() - 10;
    plot2->GetYaxis()->SetRangeUser(min,max);
    plot2->GetYaxis()->SetLabelSize(0.05);
    plot2->Draw("hist");    
    c1->cd(3);
    max = plot3->GetMaximum() + 10;
    min = plot3->GetMinimum() - 10;
    plot3->GetYaxis()->SetRangeUser(min,max);
    plot3->GetYaxis()->SetLabelSize(0.05);
    plot3->Draw("hist");    
    c1->cd(4);
    max = plot4->GetMaximum() + 10;
    min = plot4->GetMinimum() - 10;
    plot4->GetYaxis()->SetRangeUser(min,max);
    plot4->GetYaxis()->SetLabelSize(0.05);
    plot4->Draw("hist");    
    c1->cd(5);
    max = plot5->GetMaximum() + 10;
    min = plot5->GetMinimum() - 10;
    plot5->GetYaxis()->SetRangeUser(min,max);
    plot5->GetYaxis()->SetLabelSize(0.05);
    plot5->Draw("hist");    
    c1->cd(6);
    max = plot6->GetMaximum() + 10;
    min = plot6->GetMinimum() - 10;
    plot6->GetYaxis()->SetRangeUser(min,max);
    plot6->GetYaxis()->SetLabelSize(0.05);
    plot6->Draw("hist");    
    c1->cd(7);
    max = plot7->GetMaximum() + 10;
    min = plot7->GetMinimum() - 10;
    plot7->GetYaxis()->SetRangeUser(min,max);
    plot7->GetYaxis()->SetLabelSize(0.05);
    plot7->Draw("hist");    
    c1->cd(8);
    max = plot8->GetMaximum() + 10;
    min = plot8->GetMinimum() - 10;
    plot8->GetYaxis()->SetRangeUser(min,max);
    plot8->GetYaxis()->SetLabelSize(0.05);
    plot8->Draw("hist");    
    c1->cd(9);
    max = plot9->GetMaximum() + 10;
    min = plot9->GetMinimum() - 10;
    plot9->GetYaxis()->SetRangeUser(min,max);
    plot9->GetYaxis()->SetLabelSize(0.05);
    plot9->Draw("hist");    
    c1->cd(10);
    max = plot10->GetMaximum() + 10;
    min = plot10->GetMinimum() - 10;
    plot10->GetYaxis()->SetRangeUser(min,max);
    plot10->GetYaxis()->SetLabelSize(0.05);
    plot10->Draw("hist");    
    c1->cd(11);
    max = plot11->GetMaximum() + 10;
    min = plot11->GetMinimum() - 10;
    plot11->GetYaxis()->SetRangeUser(min,max);
    plot11->GetYaxis()->SetLabelSize(0.05);
    plot11->Draw("hist");    
    c1->cd(12);
    max = plot12->GetMaximum() + 10;
    min = plot12->GetMinimum() - 10;
    plot12->GetYaxis()->SetRangeUser(min,max);
    plot12->GetYaxis()->SetLabelSize(0.05);
    plot12->Draw("hist");    
    c1->cd(13);
    max = plot13->GetMaximum() + 10;
    min = plot13->GetMinimum() - 10;
    plot13->GetYaxis()->SetRangeUser(min,max);
    plot13->GetYaxis()->SetLabelSize(0.05);
    plot13->Draw("hist");    
    c1->cd(14);
    max = plot14->GetMaximum() + 10;
    min = plot14->GetMinimum() - 10;
    plot14->GetYaxis()->SetRangeUser(min,max);
    plot14->GetYaxis()->SetLabelSize(0.05);
    plot14->Draw("hist");    
    c1->cd(15);
    max = plot15->GetMaximum() + 10;
    min = plot15->GetMinimum() - 10;
    plot15->GetYaxis()->SetRangeUser(min,max);
    plot15->GetYaxis()->SetLabelSize(0.05);
    plot15->Draw("hist");    
    c1->cd(16);
    max = plot16->GetMaximum() + 10;
    min = plot16->GetMinimum() - 10;
    plot16->GetYaxis()->SetRangeUser(min,max);
    plot16->GetYaxis()->SetLabelSize(0.05);
    plot16->Draw("hist");    
    c1->cd(17);
    max = plot17->GetMaximum() + 10;
    min = plot17->GetMinimum() - 10;
    plot17->GetYaxis()->SetRangeUser(min,max);
    plot17->GetYaxis()->SetLabelSize(0.05);
    plot17->Draw("hist");    
    c1->cd(18);
    max = plot18->GetMaximum() + 10;
    min = plot18->GetMinimum() - 10;
    plot18->GetYaxis()->SetRangeUser(min,max);
    plot18->GetYaxis()->SetLabelSize(0.05);
    plot18->Draw("hist");    
    c1->cd(19);
    max = plot19->GetMaximum() + 10;
    min = plot19->GetMinimum() - 10;
    plot19->GetYaxis()->SetRangeUser(min,max);
    plot19->GetYaxis()->SetLabelSize(0.05);
    plot19->Draw("hist");    
    c1->cd(20);
    max = plot20->GetMaximum() + 10;
    min = plot20->GetMinimum() - 10;
    plot20->GetYaxis()->SetRangeUser(min,max);
    plot20->GetYaxis()->SetLabelSize(0.05);
    plot20->Draw("hist");    
    c1->cd(21);
    max = plot21->GetMaximum() + 10;
    min = plot21->GetMinimum() - 10;
    plot21->GetYaxis()->SetRangeUser(min,max);
    plot21->GetYaxis()->SetLabelSize(0.05);
    plot21->Draw("hist");    
    c1->cd(22);
    max = plot22->GetMaximum() + 10;
    min = plot22->GetMinimum() - 10;
    plot22->GetYaxis()->SetRangeUser(min,max);
    plot22->GetYaxis()->SetLabelSize(0.05);
    plot22->Draw("hist");    
    c1->cd(23);
    max = plot23->GetMaximum() + 10;
    min = plot23->GetMinimum() - 10;
    plot23->GetYaxis()->SetRangeUser(min,max);
    plot23->GetYaxis()->SetLabelSize(0.05);
    plot23->Draw("hist");    
    c1->cd(24);
    max = plot24->GetMaximum() + 10;
    min = plot24->GetMinimum() - 10;
    plot24->GetYaxis()->SetRangeUser(min,max);
    plot24->GetYaxis()->SetLabelSize(0.05);
    plot24->Draw("hist");    
    c1->cd(25);
    max = plot25->GetMaximum() + 10;
    min = plot25->GetMinimum() - 10;
    plot25->GetYaxis()->SetRangeUser(min,max);
    plot25->GetYaxis()->SetLabelSize(0.05);
    plot25->Draw("hist");    
    c1->cd(26);
    max = plot26->GetMaximum() + 10;
    min = plot26->GetMinimum() - 10;
    plot26->GetYaxis()->SetRangeUser(min,max);
    plot26->GetYaxis()->SetLabelSize(0.05);
    plot26->Draw("hist");    
    c1->cd(27);
    max = plot27->GetMaximum() + 10;
    min = plot27->GetMinimum() - 10;
    plot27->GetYaxis()->SetRangeUser(min,max);
    plot27->GetYaxis()->SetLabelSize(0.05);
    plot27->Draw("hist");    
    c1->cd(28);
    max = plot28->GetMaximum() + 10;
    min = plot28->GetMinimum() - 10;
    plot28->GetYaxis()->SetRangeUser(min,max);
    plot28->GetYaxis()->SetLabelSize(0.05);
    plot28->Draw("hist");    
    c1->cd(29);
    max = plot29->GetMaximum() + 10;
    min = plot29->GetMinimum() - 10;
    plot29->GetYaxis()->SetRangeUser(min,max);
    plot29->GetYaxis()->SetLabelSize(0.05);
    plot29->Draw("hist");    
    c1->cd(30);
    max = plot30->GetMaximum() + 10;
    min = plot30->GetMinimum() - 10;
    plot30->GetYaxis()->SetRangeUser(min,max);
    plot30->GetYaxis()->SetLabelSize(0.05);
    plot30->Draw("hist");    
    c1->cd(31);
    max = plot31->GetMaximum() + 10;
    min = plot31->GetMinimum() - 10;
    plot31->GetYaxis()->SetRangeUser(min,max);
    plot31->GetYaxis()->SetLabelSize(0.05);
    plot31->Draw("hist");    
    c1->cd(32);
    max = plot32->GetMaximum() + 10;
    min = plot32->GetMinimum() - 10;
    plot32->GetYaxis()->SetRangeUser(min,max);
    plot32->GetYaxis()->SetLabelSize(0.05);
    plot32->Draw("hist");    
    //plot_copy->Rebin(10);
    //plot_copy->GetYaxis()->SetLabelOffset(0.25);
//    plot_copy->Draw("hist");
    c1->Modified();
    c1->Update();
    c1->SaveAs(filename+Form("_AllchWave_%d.png", evt));      

    printf("Continue? ");
    scanf("%d", &cont);
    
    if (cont == 0)
      evt = nevt;
  }

  fclose(fp);

  return 0;
}

