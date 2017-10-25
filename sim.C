void sim()
{
  gStyle->SetOptStat(0);

  TH1D *h1_mc_occ = new TH1D("h1_mc_occ", "h1_mc_occ", 13, -0.5, 12.5);
  TH1D *h1_mc_occ_layer = new TH1D("h1_mc_occ_layer", "h1_mc_occ_layer", 4, -0.5, 3.5);
  TH1D *h1_mc_occ_cate = new TH1D("h1_mc_occ_cate", "h1_mc_occ_cate", 8, -0.5, 7.5);
  
  TH1D *h1_data_occ = new TH1D("h1_data_occ", "h1_data_occ", 13, -0.5, 12.5);
  TH1D *h1_data_occ_layer = new TH1D("h1_data_occ_layer", "h1_data_occ_layer", 4, -0.5, 3.5);
  TH1D *h1_data_occ_cate = new TH1D("h1_data_occ_cate", "h1_data_occ_cate", 8, -0.5, 7.5);

  ifstream fin_mc("detectorHits.txt");
  string line_mc;  
  if(fin_mc.is_open()) {
    while(fin_mc.good()){

      // get a line from fin_mc
      getline(fin_mc, line_mc);  

      if(line_mc.find("#")!=string::npos ) continue;
      // charge mass x y z (m) px py pz (MeV) x y z (m) px py pz (MeV) */*/*/*/* 
      // -1.0  105.0 33.0  -0.0377483330201  0.0340244299481 9196.10094566 -103.637254361  -6.0012614516 34.6627646749 -0.0551225667417  0.034966843793  8804.41796055 -91.1804012686  15.7343997837 2/-1/6 

      float q, m; 
      float ix,iy,iz;
      float ipx,ipy,ipz;
      float fx,fy,fz;
      float fpx,fpy,fpz;
      string hits;

      stringstream stream(line_mc);
      stream >> q;
      stream >> m;
      stream >> ix;
      stream >> iy;
      stream >> iz;
      stream >> ipx;
      stream >> ipy;
      stream >> ipz; 
      stream >> fx;
      stream >> fy;
      stream >> fz;
      stream >> fpx;
      stream >> fpy;
      stream >> fpz; 
      stream >> hits; 

      if(q==111111) break;

      // Get hits
      bool hit[12]; 
      for(int i=0; i<12; i++) hit[i]=0;
      TString tstr_hits = hits;
      TObjArray *tx = tstr_hits.Tokenize("/");
      for (Int_t i = 0; i < tx->GetEntries(); i++)
      {
        TString hit_temp = ((TObjString *)(tx->At(i)))->String();
        //cout << hit_temp << endl;
        if(hit_temp=="0") hit[0]=1;
        if(hit_temp=="1") hit[1]=1;
        if(hit_temp=="2") hit[2]=1;
        if(hit_temp=="3") hit[3]=1;
        if(hit_temp=="4") hit[4]=1;
        if(hit_temp=="5") hit[5]=1;
        if(hit_temp=="6") hit[6]=1;
        if(hit_temp=="7") hit[7]=1;
        if(hit_temp=="8") hit[8]=1;
        if(hit_temp=="9") hit[9]=1;
        if(hit_temp=="10") hit[10]=1;
        if(hit_temp=="11") hit[11]=1;
      }


      int Nocc = 0; 
      for (Int_t i = 0; i < 12; i++)  Nocc = Nocc + hit[i];
      h1_mc_occ->Fill(Nocc);

      int occ_layer1 = hit[0]+hit[1]+hit[2]+hit[3];
      int occ_layer2 = hit[4]+hit[5]+hit[6]+hit[7];
      int occ_layer3 = hit[8]+hit[9]+hit[10]+hit[11];
      h1_mc_occ_layer->Fill((occ_layer1>0)+(occ_layer2>0)+(occ_layer3>0));
     
      if(occ_layer1==0 && occ_layer2==0 && occ_layer3==0) h1_mc_occ_cate->Fill(0); 
      if(occ_layer1>0  && occ_layer2==0 && occ_layer3==0) h1_mc_occ_cate->Fill(1); 
      if(occ_layer1==0 && occ_layer2>0  && occ_layer3==0) h1_mc_occ_cate->Fill(2); 
      if(occ_layer1==0 && occ_layer2==0 && occ_layer3>0 ) h1_mc_occ_cate->Fill(3); 
      if(occ_layer1>0  && occ_layer2>0  && occ_layer3==0) h1_mc_occ_cate->Fill(4); 
      if(occ_layer1>0  && occ_layer2==0 && occ_layer3>0 ) h1_mc_occ_cate->Fill(5); 
      if(occ_layer1==0 && occ_layer2>0  && occ_layer3>0 ) h1_mc_occ_cate->Fill(6); 
      if(occ_layer1>0  && occ_layer2>0  && occ_layer3>0 ) h1_mc_occ_cate->Fill(7); 

      // look at only triple coincidence events in order to compare with data
      if(occ_layer1>0  && occ_layer2>0  && occ_layer3>0 ) 
      { 
        // occ per layer : 2D of layer vs ch  (3x4)
      } 

      if(0)
      {
        //cout << q << " " << m << " " 
        //     << ix << " " << iy << " " << iz << " "  
        //     << ipx << " " << ipy << " " << ipz << " "  
        //     << fx << " " << fy << " " << fz << " "  
        //     << fpx << " " << fpy << " " << fpz << " "   
        //     << hits << " ";
        for (Int_t i = 0; i < 12; i++)  cout << hit[i];
        cout << " "; 
        cout << occ_layer1 << occ_layer2 << occ_layer3; 
        cout << endl; 
      }   

    }
  }
  fin_mc.close();

  // 
  // Data
  //
  ifstream fin_data("data_mqtc.txt");
  string line_data;  
  if(fin_data.is_open()) {
    while(fin_data.good()){

      // get a line from fin_data
      getline(fin_data, line_data);  

      if(line_data.find("#")!=string::npos ) continue;
      //2017-09-21 12:49:34 010110100100 

      string date;
      string time;
      string hits;

      stringstream stream(line_data);
      stream >> date; 
      stream >> time; 
      stream >> hits; 
      
      if(date=="1111111") break;

      // Get hits
      bool hit[12]; 
      for(int i=0; i<12; i++) 
      { 
        if(hits[i]=='1') hit[i]=1;
        if(hits[i]=='0') hit[i]=0;
      }

      int Nocc = 0; 
      for (Int_t i = 0; i < 12; i++)  Nocc = Nocc + hit[i];
      h1_data_occ->Fill(Nocc);

      int occ_layer1 = hit[0]+hit[1]+hit[2]+hit[3];
      int occ_layer2 = hit[4]+hit[5]+hit[6]+hit[7];
      int occ_layer3 = hit[8]+hit[9]+hit[10]+hit[11];
      h1_data_occ_layer->Fill((occ_layer1>0)+(occ_layer2>0)+(occ_layer3>0));
     
      if(occ_layer1==0 && occ_layer2==0 && occ_layer3==0) h1_data_occ_cate->Fill(0); 
      if(occ_layer1>0  && occ_layer2==0 && occ_layer3==0) h1_data_occ_cate->Fill(1); 
      if(occ_layer1==0 && occ_layer2>0  && occ_layer3==0) h1_data_occ_cate->Fill(2); 
      if(occ_layer1==0 && occ_layer2==0 && occ_layer3>0 ) h1_data_occ_cate->Fill(3); 
      if(occ_layer1>0  && occ_layer2>0  && occ_layer3==0) h1_data_occ_cate->Fill(4); 
      if(occ_layer1>0  && occ_layer2==0 && occ_layer3>0 ) h1_data_occ_cate->Fill(5); 
      if(occ_layer1==0 && occ_layer2>0  && occ_layer3>0 ) h1_data_occ_cate->Fill(6); 
      if(occ_layer1>0  && occ_layer2>0  && occ_layer3>0 ) h1_data_occ_cate->Fill(7); 

      if(0)
      {
        cout << date << " " << time << " " 
             << hits << " ";
        for (Int_t i = 0; i < 12; i++)  cout << hit[i];
        cout << " "; 
        cout << occ_layer1 << occ_layer2 << occ_layer3; 
        cout << endl; 
      }   


    }
  }
  fin_data.close();



  TCanvas *c = new TCanvas("c","c",1200,900);
  c->Divide(4,3); 
  c->cd(1);
  c->cd(1)->SetLogy(1);
  h1_data_occ->SetMinimum(1);  
  h1_data_occ->DrawNormalized("hist");  
  h1_mc_occ->DrawNormalized("ep same");  
  c->cd(2);
  c->cd(2)->SetLogy(1);
  h1_data_occ_layer->SetMinimum(1);  
  h1_data_occ_layer->DrawNormalized("hist");  
  h1_mc_occ_layer->DrawNormalized("ep same");  
  c->cd(3);
  c->cd(3)->SetLogy(1);
  h1_data_occ_cate->SetMinimum(1);  
  h1_data_occ_cate->DrawNormalized("hist");  
  h1_mc_occ_cate->DrawNormalized("ep same");  
  
  c->Print("sim.pdf");
}
