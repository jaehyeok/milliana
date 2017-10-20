int charToInt(char c)
{
  if(c=='0')  return 0;
  else if(c=='1')  return 1;
  else if(c=='2')  return 2;
  else if(c=='3')  return 3;
  else if(c=='4')  return 4;
  else if(c=='5')  return 5;
  else if(c=='6')  return 6;
  else if(c=='7')  return 7;
  else if(c=='8')  return 8;
  else if(c=='9')  return 9;
  else if(c==' ')  return 0;
  else return -1;
} 

//
void hodoAnalysis()
{  
  TH1D *h1 = new TH1D("h1","h1",720,0.5,720.5);

  // Get fill, time, lumi  
  vector<int> fill_number;
  vector<int> fill_start;
  vector<int> fill_end;
  vector<Float_t> fill_lumi;
  vector<Float_t> fill_lumi_bril;
  ifstream finlumi("collisionsTimeList.txt");
  string linelumi;  
  if(finlumi.is_open()) {
      while(finlumi.good()){

          // get a line from finlumi
          getline(finlumi, linelumi); 
          if( linelumi.find("#")!=string::npos ) continue; 
          if( linelumi.find(" ")==string::npos ) continue; 

          int fill;
          unsigned long int t_start, t_end;
          Float_t lumi; 
          string t_str_day;
          string t_str_time;
          Float_t lumi_bril; 

          stringstream stream(linelumi);
          stream >> fill;
          stream >> t_start;
          stream >> t_end;
          stream >> lumi;
          stream >> t_str_day; 
          stream >> t_str_time; 
          stream >> lumi_bril;
        
          // epoch time is 1506124800 taken from https://www.epochconverter.com
          t_start = t_start - 1506124800 + 3600*2;
          t_end = t_end - 1506124800 + 3600*2; 
          fill_number.push_back(fill);
          fill_start.push_back(t_start);
          fill_end.push_back(t_end);
          fill_lumi.push_back(lumi/1000);
          fill_lumi_bril.push_back(lumi_bril);
      }
  } 
  cout << fill_number.size() << endl;  
  const Int_t number_of_fills = fill_number.size();
  Float_t Nocc[number_of_fills]; 
  for(int i=0; i<number_of_fills; i++) Nocc[i]=0; 
  
  // get no beam time
  Int_t Nocc_nobeam=0;    
  Int_t t_beam=0;
  for(int i=0; i<number_of_fills; i++) t_beam = t_beam + fill_end.at(i) - fill_start.at(i); 

  // loop over data files
  for(int ls=1; ls<=3800; ls++) 
  { 
    ifstream fin(Form("data/data_%i.dat",ls));
    string line;  
    // salvage screwed Pi timing in ls 1870
    int round = 0;
    int time_before = 0;
    int time_now = 0;
    if(fin.is_open()) {
      while(fin.good()){


        // get a line from fin
        getline(fin, line);  

        if( line.find("2017")==string::npos ) continue;
        if( line.find("#")!=string::npos ) continue;

        //2017: 9:23:14:39:34:504889  0 0000 00000000 00010001 00010001 00000000 00000000
        //0123456789012345678901234567890123456789012345678901234567890123456789012345678 
        //0         1         2         3         4         5         6         7 

        int month   = 10*charToInt(line[5])+charToInt(line[6]);
        int day     = 10*charToInt(line[8])+charToInt(line[9]);
        int hour    = 10*charToInt(line[11])+charToInt(line[12]);
        int minute  = 10*charToInt(line[14])+charToInt(line[15]);
        int second  = 10*charToInt(line[17])+charToInt(line[18]); 

        // time = 0 is 9/23 00:00:00
        // epoch time is 1506124800 taken from https://www.epochconverter.com
        int time = hour*60*60 + 60*minute + second;  
        if(month==10) time = time + (day+7)*24*60*60; 
        else if(month==9) time = time + (day-23)*24*60*60; 

        // for ls 1870
        if(ls==1870)  
        {
            time_before = time_now; 
            time_now = time; 
            if(time_now < 864600 && time_before>886500) round++; 
            time = time + round*(6*60*60+25*60+1);
        }
        //cout << month << ":" << day << ":" << hour << ":" << minute << ":" << second << " = " << time << " " << (int)(time/3600) << endl; 
        //if(time_now < 864600 && time_before>886500) cout << " round " << round << " " << time << endl; // FIXME  

        bool botv = false; 
        bool both = false; 
        bool topv = false; 
        bool toph = false; 
        for(int ibot=35; ibot<=51; ibot++) if(line[ibot]=='1') botv = true;
        for(int ibot=53; ibot<=60; ibot++) if(line[ibot]=='1') both = true;
        for(int itop=62; itop<=69; itop++) if(line[itop]=='1') toph = true;
        for(int itop=71; itop<=78; itop++) if(line[itop]=='1') topv = true;
        //if(botv || both)    
        if((botv || both) && (topv || toph))    
        //if(botv && both && topv && toph)    
        {
          //cout << line << endl;  
          int bin = (int)(time/3600);
          h1->SetBinContent(bin,h1->GetBinContent(bin)+1); 
            

          // fill occ per fill  
          bool isCollisions=false;
          for(int i=0; i<fill_number.size(); i++) 
          { 
            if(time>fill_start.at(i) && time<=fill_end.at(i)) 
            {
                Nocc[i]++;  
                isCollisions=true;
                //cout << fill_start.at(i) << " " << fill_end.at(i) << " " << time << endl;  // FIXME
            }
          }

          // consider XeXe period as beam on 
          if(time>1855572 && time<1587792) isCollisions=true; 

          if(isCollisions==false) Nocc_nobeam++; 
        } 
      }
    }
  }

  cout << 2096940-(t_beam+1855572-1587792) << " "  << Nocc_nobeam  << endl; // 2096940 from 9/23 1:41 to 10/17 8:10

  for(int i=0; i<fill_number.size(); i++)  
  { 
     cout << fill_number.at(i) << "  " << fill_lumi.at(i) << "\t" << "  " 
          << fill_end.at(i)-fill_start.at(i) << " " << Nocc[i] << " ";
     cout << Nocc[i] << endl; 
  }


  h1->SetLineWidth(2);
  h1->SetLineColor(kBlack);
  h1->SetFillColor(kRed-3);
  h1->SetStats(0);

  // Set label 
  // 9/23 00:00 is bin 1 
  // one bin is one hour
  int days = 720/24; 
  for(int i=0; i<days; i++)
  { 
    if(i%2!=0) continue;
    if((i+23)<=30)  h1->GetXaxis()->SetBinLabel(24*i+1, Form("9/%d",i+23)); 
    else  h1->GetXaxis()->SetBinLabel(24*i+1, Form("10/%d",i+23-30)); 
  } 
  
  //
  TCanvas *c = new TCanvas("c","c",800,300);
  c->cd(1);
  c->SetRightMargin(0.03);
  c->SetLeftMargin(0.075);
  h1->Rebin(1);
  h1->SetTitle("Number of events with at least one hit in each end");
  h1->LabelsOption("h","X");
  h1->SetStats(0); 
  h1->SetLabelSize(0.05,"Y");
  h1->SetLabelSize(0.10,"X");
  h1->SetMaximum(h1->GetMaximum()*1.2);
  h1->GetYaxis()->SetTitle("Rate [/hour]");
  h1->GetYaxis()->SetTitleSize(0.05);
  h1->GetYaxis()->SetTitleOffset(0.5);
  h1->Draw("hist");
  c->Print("occ.pdf");
  c->Print("occ.C");
  
  //
  Float_t lumi_gr[number_of_fills];
  Float_t lumi_bril_gr[number_of_fills];
  Float_t lumi_bril_error_gr[number_of_fills];
  Float_t Nocc_error[number_of_fills];
  for(int i=0; i<number_of_fills; i++) 
  {
    lumi_gr[i]=fill_lumi.at(i); 
    lumi_bril_gr[i]=fill_lumi_bril.at(i); 
    lumi_bril_error_gr[i]=lumi_bril_gr[i]*0.05; 
    Nocc_error[i]=TMath::Sqrt(Nocc[i]); 
   }
  for(int i=0; i<number_of_fills; i++) 
    cout << i << " " << lumi_bril_gr[i] << " +/- " << lumi_bril_error_gr[i] 
              << " " << Nocc[i] << " +/- " << Nocc_error[i] << endl;  
  
  // Subtract non-beam contribution 
  for(int i=0; i<number_of_fills; i++) 
          Nocc[i] = Nocc[i] - (fill_end.at(i)-fill_start.at(i))*0.00047; // 370/784916=0.00047 

  TCanvas *c2d = new TCanvas("c2d","c2d",400,300); 
  c2d->cd(1);
  TGraph *gr = new TGraphAsymmErrors(number_of_fills,
                                     lumi_gr,Nocc, 
                                     lumi_bril_error_gr, lumi_bril_error_gr, 
                                     Nocc_error, Nocc_error); 
  TGraph *gr_bril = new TGraphAsymmErrors(number_of_fills,
                                     lumi_bril_gr, Nocc, 
                                     lumi_bril_error_gr, lumi_bril_error_gr, 
                                     Nocc_error, Nocc_error); 
  gr->SetMarkerStyle(20);
  gr->SetMarkerSize(0.5);
  gr_bril->SetMarkerStyle(20);
  gr_bril->SetMarkerSize(0.5);
  gr_bril->SetMarkerColor(kBlack);
  gr_bril->SetLineColor(kBlack);
  gr_bril->SetLineWidth(2);
  //gr->Draw("AP");
  gr_bril->Draw("AP"); 
  gr_bril->Fit("pol1");  
  gr_bril->GetFunction("pol1")->SetLineColorAlpha(kBlue,0.5);
  gr_bril->GetFunction("pol1")->SetLineWidth(5); 
  gr_bril->SetTitle(Form("chi2/ndf=%.1f/%i", gr_bril->GetFunction("pol1")->GetChisquare(),gr_bril->GetFunction("pol1")->GetNDF()));
  c2d->Print("occ2d.pdf");
  c2d->Print("occ2d.C");

  

} 
