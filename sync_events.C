void sync_events()
{  
  cout << "Syncing HS and MQ events"  << endl;
  TH1D *hdt = new TH1D("hdt","hdt", 40, -20, 20);
  ifstream fin("data/mq/mq_nov22.dat");
  string line;  

  if(fin.is_open()) {
    while(fin.good()){

      // get a line from fin
      getline(fin, line);  
      if( line.find("#")!=string::npos ) continue;

      int beam_, run_, file_, event_, y_, mo_, d_, h_, mi_, s_, ch_[12];
      // 0   94  387      7728 2017 10 31 09 11 39 0 0 1 1 0 1 0 1 0 1 1 0
      stringstream stream(line);
      stream >> beam_;
      stream >> run_;
      stream >> file_;
      stream >> event_;
      stream >> y_;
      stream >> mo_;
      stream >> d_;
      stream >> h_;
      stream >> mi_;
      stream >> s_;
      for(int i=0; i<12; i++) stream >> ch_[i];

      int org_mo_ = mo_;
      int org_d_  = d_;
      int org_h_  = h_;
      int org_mi_ = mi_;
      int org_s_  = s_;


      // convert UTC to CERN time
      //if(h_<22) h_ = h_ + 2;  
      //if(h_>=22) { h_ = h_ - 22;  d_ = d_ + 1; }
      //cout << y_ << " " << mo_ << " " << d_ << " " << h_ << " " << mi_ << " " << s_ << endl;

      // --------------------------------------------------------------- //
      //ifstream finhodo("data/hs/hs_oct3.txt");
      //ifstream finhodo("data/hs/hs_nov22.txt");
      //ifstream finhodo("data/hs/hs_oct10.txt");
      //ifstream finhodo("data/hs/hs_nooct3.txt");
      //ifstream finhodo("data/hs/hs_afteroct29.txt");
      ifstream finhodo("data/hs/hs_nov22_gmt.txt");
      string linehodo;  
      if(finhodo.is_open()) {
        while(finhodo.good()){ 

          getline(finhodo, linehodo);  

          if( linehodo.find(" ")==string::npos ) continue;
          if( linehodo.find("#")!=string::npos ) continue;

          linehodo.replace(4,1," ");
          linehodo.replace(7,1," ");
          linehodo.replace(10,1," ");
          linehodo.replace(13,1," ");
          linehodo.replace(16,1," ");
          linehodo.replace(19,1," ");

          int y, mo, d, h, mi, s, us, trg, cnt;
          string p0, p1, p2, p3, p4; 

          stringstream streamhodo(linehodo);
          streamhodo >> y; 
          streamhodo >> mo; 
          streamhodo >> d; 
          streamhodo >> h; 
          streamhodo >> mi; 
          streamhodo >> s; 
          streamhodo >> us; 
          streamhodo >> trg; 
          streamhodo >> cnt; 
          streamhodo >> p0; 
          streamhodo >> p1; 
          streamhodo >> p2; 
          streamhodo >> p3; 
          streamhodo >> p4; 

          //2017: 9:23:14:39:34:504889  0 0000 00000000 00010001 00010001 00000000 00000000
          //0         1         2         3         4         5         6         7 
          //0123456789012345678901234567890123456789012345678901234567890123456789012345678 

          //cout << "MilliQan : " << hour << ":" << min << ":" << sec << endl; 
          //cout << "Hodoscope: " << y << "/" << mo << "/" << d << " " << h << ":" << mi << ":" << s << endl; 

          // convert to second 
          int day_mq = d_
          if(mo_==9)  day_mq_ = day_mq-23; 
          if(mo_==10) day_mq = day_mq+7; 
          if(mo_==11) day_mq = day_mq+30; 
          int sec_mq = day_mq*86400 + h_*3600 + mi_*60 + s_;  
          int day_hs = d; 
          if(mo==9)  day_hs_ = day_hs-23; 
          if(mo==10) day_hs = day_hs+7; 
          if(mo==11) day_hs = day_hs+30; 
          int sec_hs = day_hs*86400 + h*3600 + mi*60 + s;  

          //if(mo_==mo && d_==d && h_==h && mi_==mi)  
          //{ 
            float timediff = sec_mq-sec_hs;
            if(timediff<=-20) timediff=-19.99999;
            if(timediff>=20) timediff=19.99999;
            hdt->Fill(timediff); 
          //} 

          //if(mo_==mo && d_==d && h_==h && mi_==mi && abs(s_-s)<3)
          if(abs(sec_mq-sec_hs)<3)
          {
            //cout << y << "/" << mo << "/" << d << " " << h << ":" << mi << ":" << s << " ";  // HS time
            //cout << y_ << "/" << mo_ << "/" << d_ << " " << h_ << ":" << mi_ << ":" << s_ << " ";  // MQ time
            cout << beam_ << " " << run_ << " " << file_ << " " << event_ << " "; 
            cout << y << "/" << org_mo_ << "/" << org_d_ << " " << org_h_ << ":" << org_mi_ << ":" << org_s_ << " "; 
            cout << sec_mq-sec_hs << " "; 
            cout << p0 << " " << p1 << " " << p2 << " " << p3 << " " << p4 << " ";
            for(int i=0; i<12; i++) cout << ch_[i]; 
            cout << endl;

          }

        }
      }
      finhodo.close();
      // --------------------------------------------------------------- //
    }
  }

  TCanvas *c = new TCanvas("c","c",400,300);
  c->cd(1);
  hdt->SetLineWidth(2);
  hdt->SetLineColor(kBlack);
  hdt->SetFillColor(kRed-3);
  hdt->SetStats(0);
  hdt->Draw("hist ep");
  c->Print("fig/dt.pdf");
}

