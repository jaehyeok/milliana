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

TString convertTimeToDate(int time)
{ 
  int d = time/86400;
  int h = time/3600 - d*24;
  int m = time/60 - (d*24+h)*60;
  int s = time%60; 
  int mo = 9; 
  if(d>7) { mo = 10; d = d-7;}
  if(d>31) { mo = 11; d = d-31;}
  TString date = Form("2017:%2d:%2d:%2d:%2d:%2d",mo,d,h,m,s);
  return date;
}


//
void hodoAnalysis()
{  
  TH1D *h1 = new TH1D("h1","h1",1488,0.5,1488.5);
  TH1D *h1level = new TH1D("h1level","h1level",15,0,15);
  TH1D *h1levelnorm = new TH1D("h1levelnorm","h1levelnorm",15,0,15);
  TH1D *h1nolevel = new TH1D("h1nolevel","h1nolevel",15,0,15);
  TH1D *h1nolevelnorm = new TH1D("h1nolevelnorm","h1nolevelnorm",15,0,15);

  // Get fill, time, lumi  
  vector<int> fill_number;
  vector<int> fill_start;
  vector<int> fill_end;
  vector<Float_t> fill_lumi;
  vector<Float_t> fill_lumi_bril;
  ifstream finlumi("../collisionsTimeList.txt");
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
 
  // Get normalization for lumilevel plot 
  for(int i=0; i<number_of_fills; i++) 
  {
    int fill_duration = (fill_end.at(i)-fill_start.at(i))/3600; 
    if(fill_duration<1) continue;
    if(fill_number.at(i)<6297) 
    {
      for(int ibin=1; ibin<=fill_duration; ibin++) 
        h1nolevelnorm->SetBinContent(ibin, h1nolevelnorm->GetBinContent(ibin)+1);  
    }
    else
    {
      for(int ibin=1; ibin<=fill_duration; ibin++) 
        h1levelnorm->SetBinContent(ibin, h1levelnorm->GetBinContent(ibin)+1);  
    }
  }

  // get no beam time
  Int_t Nocc_nobeam=0;    
  Int_t Nocc_beam=0;    
  Int_t t_beam=0;
  for(int i=0; i<number_of_fills; i++) t_beam = t_beam + fill_end.at(i) - fill_start.at(i); 

  // loop over data files
  for(int ls=1; ls<=9900; ls++) 
  //for(int ls=1820; ls<=1875; ls++) 
  //for(int ls=1875; ls<=9990; ls++) 
  {  

    if(ls!=1870) continue; // FIXME
    //if(ls<5361) continue; // FIXME 

    ifstream fin(Form("../data/data_%i.dat",ls));
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
        if(month==11) time = time + (day+7+31)*24*60*60; 
        else if(month==10) time = time + (day+7)*24*60*60; 
        else if(month==9) time = time + (day-23)*24*60*60; 

        // for ls 1870
        if(ls==1870 && day==3)  
        {
            time_before = time_now; 
            time_now = time; 
            if(time_now < 864600 && time_before>886500) round++; 
            time = time + round*(6*60*60+25*60+2.2);
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
        if((botv || both) && (topv || toph))    
        //if(botv && both && topv && toph)    
        //if(time>1383000)    
        {

          if(ls==1870)
          {  
            //2017: 9:23:14:39:34:504889  0 0000 00000000 00010001 00010001 00000000 00000000
            //0123456789012345678901234567890123456789012345678901234567890123456789012345678 
            //0         1         2         3         4         5         6         7 
            //cout << line << endl;  // FIXME I am here 
            cout << convertTimeToDate(time); 
            for(int iline=19; iline<=78; iline++) cout <<line[iline];
            cout << endl;
          }
          else 
          {
            cout << line << endl;  
          }
 
          int bin = (int)(time/3600);
          h1->SetBinContent(bin,h1->GetBinContent(bin)+1); 
          
          int get_fill_number=-1;
          int get_fill_start=-1;
          int get_fill_end=-1;
          for(int i=0; i<fill_number.size(); i++)
          { 
            if(time>fill_start.at(i) && time<=fill_end.at(i))  
            { 
              get_fill_number=fill_number.at(i);
              get_fill_start=fill_start.at(i);
              get_fill_end=fill_end.at(i);
            }
          }  
          int fill_duration = (get_fill_end-get_fill_start)/3600;
          if(get_fill_number>=6297 && fill_duration>1) 
          {
            if(0) cout << get_fill_number << " :: " << time << " - " << get_fill_start << " = " << (time-get_fill_start)/3600 << endl;
            h1level->Fill((time-get_fill_start)/3600); 
          }
          else if(get_fill_number<6297 && fill_duration>1) 
          {
            if(0) cout << get_fill_number << " :: " << time << " - " << get_fill_start << " = " << (time-get_fill_start)/3600 << endl;
            h1nolevel->Fill((time-get_fill_start)/3600); 
          }
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

          // Consider XeXe beam on:  fill 6295 (6:30hours)  2017.10.12 20:21:25 - 2017.10.13 02:51:01 
          // 2017.10.12 20:21:25 UTC = 2017.10.12 22:21:25 CERN = 1745461   
          // 2017.10.13 02:51:01 UTC = 2017.10.13 04:51:01 CERN = 1722085
          if(time>1722085 && time<1745461) isCollisions=true; 

          if(isCollisions==false) Nocc_nobeam++; 
          if(isCollisions==true && (time<1722085 || time>1745461)) Nocc_beam++; 
        } 
      }
    }
  }
    
  //2615340 from 9/23 1:41 to 10/23 8:10 
  //cout << 2615340-(t_beam+1855572-1587792) << " "  << Nocc_nobeam  << " = " << Nocc_nobeam/(2615340-(t_beam+1855572-1587792)) <<  endl; 
  //cout << 2615340-(t_beam+1745461-1722085) << " "  << Nocc_nobeam  << " = " << Nocc_nobeam/(2615340-(t_beam+1745461-1722085)) <<  endl; 
  //cout << t_beam << " " << Nocc_beam << " = "  << Nocc_beam/t_beam << " " << Nocc_beam/t_beam*3600 << endl;
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
  int days = 1488/24; 
  for(int i=0; i<days; i++)
  { 
    if(i%3!=0) continue;
    if((i+23)<=30)  h1->GetXaxis()->SetBinLabel(24*i+1, Form("9/%d",i+23)); 
    else if((i+23)<=30+31)  h1->GetXaxis()->SetBinLabel(24*i+1, Form("10/%d",i+23-30)); 
    else  h1->GetXaxis()->SetBinLabel(24*i+1, Form("11/%d",i+23-30-31)); 
  } 
  
  //
  TCanvas *c = new TCanvas("c","c",1200,300);
  c->cd(1);
  c->SetRightMargin(0.03);
  c->SetLeftMargin(0.075);
  h1->Rebin(1);
  for(int i=1; i<=1488; i++) h1->SetBinContent(i, h1->GetBinContent(i)-0.00049*3600); // 444./908858 = 0.000488525
  //for(int i=1; i<=912; i++) h1->SetBinContent(i, h1->GetBinContent(i)-0.0000*3600); // 444./908858 = 0.000488525
  h1->SetTitle("Number of events with at least one hit in each end");
  h1->LabelsOption("h","X");
  h1->SetStats(0); 
  h1->SetLabelSize(0.05,"Y");
  h1->SetLabelSize(0.10,"X");
  h1->SetMaximum(h1->GetMaximum()*1.2);
  h1->SetMinimum(-2.);
  h1->GetYaxis()->SetTitle("Rate [/hour]");
  h1->GetYaxis()->SetTitleSize(0.05);
  h1->GetYaxis()->SetTitleOffset(0.5);
  h1->Draw("hist");
  c->Print("fig/occ.pdf");
  
  //
  TCanvas *clevel = new TCanvas("clevel","clevel",400,300);
  clevel->cd(1);
  //clevel->SetRightMargin(0.03);
  //clevel->SetLeftMargin(0.075); 
  clevel->cd(1)->SetGrid();
  for(int i=1; i<=15; i++) 
  {
    cout << i << " " << h1level->GetBinContent(i)  <<  " +- " << h1level->GetBinError(i) << "/" << h1levelnorm->GetBinContent(i) << endl;
    h1level->SetBinError(i, h1level->GetBinError(i)/h1levelnorm->GetBinContent(i)); 
    h1level->SetBinContent(i, h1level->GetBinContent(i)/h1levelnorm->GetBinContent(i)-0.00049*3600); // 444./908858 = 0.000488525 
    h1nolevel->SetBinError(i, h1nolevel->GetBinError(i)/h1nolevelnorm->GetBinContent(i)); 
    h1nolevel->SetBinContent(i, h1nolevel->GetBinContent(i)/h1nolevelnorm->GetBinContent(i)-0.00049*3600); // 444./908858 = 0.000488525 
  }   
  h1level->SetTitle("Number of events with at least one hit in each end");
  h1level->LabelsOption("h","X");
  h1level->SetStats(0); 
  h1level->SetLabelSize(0.05,"Y");
  h1level->SetLabelSize(0.05,"X");
  h1level->SetMaximum(h1level->GetMaximum()*1.2);
  h1level->SetMinimum(0);
  h1level->GetYaxis()->SetTitle("Rate [/hour]");
  h1level->GetYaxis()->SetTitleSize(0.05);
  h1level->GetYaxis()->SetTitleOffset(1); 
  h1level->GetXaxis()->SetTitle("hours");
  h1level->GetXaxis()->SetTitleSize(0.05);
  h1level->SetMarkerStyle(20);
  h1level->SetMarkerColor(kBlack);
  h1level->SetLineColor(kBlack);
  h1level->SetLineWidth(2);
  h1level->Draw("ep");
  TF1 *f_expo = new TF1("f_expo","expo",3,15);
  h1level->Fit("f_expo","R");
  TF1 *f_flat = new TF1("f_flat","pol0",0,3);
  h1level->Fit("f_flat","R+");
  h1nolevel->SetMarkerStyle(20);
  h1nolevel->SetMarkerColor(kBlue);
  h1nolevel->SetLineColor(kBlue);
  h1nolevel->SetLineWidth(2);
  h1nolevel->Draw("ep same");
  clevel->Print("fig/lumilevel.pdf");
 
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
  
  // Subtract non-beam contribution 
  for(int i=0; i<number_of_fills; i++) 
          Nocc[i] = Nocc[i] - (fill_end.at(i)-fill_start.at(i))*0.00049; // 
  if(0)
  {
    for(int i=0; i<number_of_fills; i++) 
      cout << fill_number.at(i) << " :: "  
                << Form("%.1f +/- %.1f ", lumi_bril_gr[i], lumi_bril_error_gr[i]) 
                << " \t " 
                << Form("%1.f ", Nocc[i] + (fill_end.at(i)-fill_start.at(i))*0.00049)   
                << " \t " 
                << Form("%1.f +/- %.1f ", Nocc[i], Nocc_error[i]) << endl;  
  }

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
  gr_bril->Draw("AP same"); 
  gr_bril->GetYaxis()->SetRangeUser(-20.,150.);
  gr_bril->GetXaxis()->SetLimits(-20.,900.); 
  gr_bril->Draw("AP same"); 
  c2d->Update();
  gr_bril->Fit("pol1");  
  gr_bril->GetFunction("pol1")->SetLineColorAlpha(kBlue,0.5);
  gr_bril->GetFunction("pol1")->SetLineWidth(5); 
  gr_bril->SetTitle(Form("chi2/ndf=%.1f/%i", gr_bril->GetFunction("pol1")->GetChisquare(),gr_bril->GetFunction("pol1")->GetNDF()));
  c2d->Print("fig/occ2d.pdf");

  

} 
