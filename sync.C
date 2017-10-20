void sync()
{  
  TH1D *hdt = new TH1D("hdt","hdt", 40, -20, 20);

  ifstream fin("mdaq.txt");
  string line;  
  if(fin.is_open()) {
    while(fin.good()){

      // get a line from fin
      getline(fin, line);  
      if( line.find("#")!=string::npos ) continue;

      int y_, mo_, d_, h_, mi_, s_, ch_[12]; 
    // 2017 09 25 03 35 06 0 0 1 0 0 0 1 0 0 0 1 1
      stringstream stream(line);
      stream >> y_;
      stream >> mo_;
      stream >> d_;
      stream >> h_;
      stream >> mi_;
      stream >> s_;
      for(int i=0; i<12; i++) stream >> ch_[i];

      // convert UTC to CERN time
      if(h_<22) h_ = h_ + 2;  
      if(h_>=22) { h_ = h_ - 22;  d_ = d_ + 1; }
      //cout << y_ << " " << mo_ << " " << d_ << " " << h_ << " " << mi_ << " " << s_ << endl;

      // --------------------------------------------------------------- //
      ifstream finhodo("data/data_skim_sep27.txt");
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
   
          if(d_==d && h_==h && mi_==mi)  
          { 
              float timediff = s_-s;
              if(timediff<=-20) timediff=-19.99999;
              if(timediff>=20) timediff=19.99999;
              hdt->Fill(timediff); 
          } 

          if(d_==d && h_==h && mi_==mi && abs(s_-s)<3)
          {
            //cout << "MilliQan : " << hour << ":" << min << ":" << sec << endl; 
            //cout << "Hodoscope: " << y << "/" << mo << "/" << d << " " << h << ":" << mi << ":" << s << endl; 
            cout << y << "/" << mo << "/" << d << " " << h << ":" << mi << ":" << s << " "; 
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
    c->Print("dt.pdf");
}
 
