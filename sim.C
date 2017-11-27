#include "/Users/jaehyeok/macros/JaeStyle.C"

void sim()
{
  //JaeStyle();
  //gROOT->ForceStyle();

  gStyle->SetPalette(kRainBow);

  //gStyle->SetPaintTextFormat("6.2f");
  gStyle->SetOptStat(0);

  TH1D *h1_mc_occ = new TH1D("h1_mc_occ", "h1_mc_occ", 13, -0.5, 12.5);
  TH1D *h1_mc_occ_layer = new TH1D("h1_mc_occ_layer", "h1_mc_occ_layer", 4, -0.5, 3.5);
  TH1D *h1_mc_occ_cate = new TH1D("h1_mc_occ_cate", "h1_mc_occ_cate", 8, -0.5, 7.5);
  TH2D *h2_mc_occ_cate = new TH2D("h2_mc_occ_cate", "h2_mc_occ_cate", 3, 0.5, 3.5, 4, 0.5, 4.5);
  TH2D *h2_mc_cate_pt = new TH2D("h2_mc_cate_pt", "h2_mc_cate_pt", 8, -0.5, 7.5, 20, 0, 50);
  
  TH1D *h1_data_occ = new TH1D("h1_data_occ", "h1_data_occ", 13, -0.5, 12.5);
  TH1D *h1_data_occ_layer = new TH1D("h1_data_occ_layer", "h1_data_occ_layer", 4, -0.5, 3.5);
  TH1D *h1_data_occ_cate = new TH1D("h1_data_occ_cate", "h1_data_occ_cate", 8, -0.5, 7.5);
  TH2D *h2_data_occ_cate = new TH2D("h2_data_occ_cate", "h2_data_occ_cate", 3, 0.5, 3.5, 4, 0.5, 4.5);
  TH2D *h2_data_hit = new TH2D("h2_data_hit", "h2_data_hit", 25, -0.5, 24.5, 25, -0.5, 24.5);
  TH2D *h2_data_hit_boff = new TH2D("h2_data_hit_boff", "h2_data_hit_boff", 25, -0.5, 24.5, 25, -0.5, 24.5);
  TH2D *h2_data_hit_bon = new TH2D("h2_data_hit_bon", "h2_data_hit_bon", 25, -0.5, 24.5, 25, -0.5, 24.5);
  

  //ifstream fin_mc("data/hits_withHodo.txt");
  ifstream fin_mc("data/hits_withSideHits.txt");
  string line_mc;  
  if(fin_mc.is_open()) {
    while(fin_mc.good()){

      // get a line from fin_mc
      getline(fin_mc, line_mc);  

      if(line_mc.find("#")!=string::npos ) continue;
      // charge mass x y z (m) px py pz (MeV) x y z (m) px py pz (MeV) */*/*/*/* 
      // -1.0  105.0 33.0  -0.0377483330201  0.0340244299481 9196.10094566 -103.637254361  -6.0012614516 34.6627646749 -0.0551225667417  0.034966843793  8804.41796055 -91.1804012686  15.7343997837 2/-1/6 
     // -1.0	105.0	33.0140700394	-0.0182195248556	0.0415869806007	8357.68372716	-93.4326067188	2.0054470523	36.2064428616	-0.0418233559651	0.0374667958614	7613.35744269	-43.9701964041	-24.3069312816	2/-1/6/-1/10/-1

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
      
      // number of hits per layer
      int occ_layer1 = hit[0]+hit[1]+hit[2]+hit[3];
      int occ_layer2 = hit[4]+hit[5]+hit[6]+hit[7];
      int occ_layer3 = hit[8]+hit[9]+hit[10]+hit[11];
      h1_mc_occ_layer->Fill((occ_layer1>0)+(occ_layer2>0)+(occ_layer3>0));
    
      // select tripple coincidence events
      if((occ_layer1==0) || (occ_layer2==0) || (occ_layer3==0)) continue;

      int Nocc = 0; 
      for (Int_t i = 0; i < 12; i++)  Nocc = Nocc + hit[i];
      h1_mc_occ->Fill(Nocc);

      if(occ_layer1==0 && occ_layer2==0 && occ_layer3==0) { h1_mc_occ_cate->Fill(0); h2_mc_cate_pt->Fill(0., ipx/1000); }
      if(occ_layer1>0  && occ_layer2==0 && occ_layer3==0) { h1_mc_occ_cate->Fill(1); h2_mc_cate_pt->Fill(1., ipx/1000); }
      if(occ_layer1==0 && occ_layer2>0  && occ_layer3==0) { h1_mc_occ_cate->Fill(2); h2_mc_cate_pt->Fill(2., ipx/1000); }
      if(occ_layer1==0 && occ_layer2==0 && occ_layer3>0 ) { h1_mc_occ_cate->Fill(3); h2_mc_cate_pt->Fill(3., ipx/1000); }
      if(occ_layer1>0  && occ_layer2>0  && occ_layer3==0) { h1_mc_occ_cate->Fill(4); h2_mc_cate_pt->Fill(4., ipx/1000); }
      if(occ_layer1>0  && occ_layer2==0 && occ_layer3>0 ) { h1_mc_occ_cate->Fill(5); h2_mc_cate_pt->Fill(5., ipx/1000); }
      if(occ_layer1==0 && occ_layer2>0  && occ_layer3>0 ) { h1_mc_occ_cate->Fill(6); h2_mc_cate_pt->Fill(6., ipx/1000); }
      if(occ_layer1>0  && occ_layer2>0  && occ_layer3>0 ) { h1_mc_occ_cate->Fill(7); h2_mc_cate_pt->Fill(7., ipx/1000); }

      // look at only triple coincidence events in order to compare with data
      if(occ_layer1>0  && occ_layer2>0  && occ_layer3>0 ) 
      { 
        // occ per layer : 2D of layer vs ch  (3x4)  
        h2_mc_occ_cate->Fill(1, occ_layer1);
        h2_mc_occ_cate->Fill(2, occ_layer2);
        h2_mc_occ_cate->Fill(3, occ_layer3);
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
  ifstream fin_data("data/sync/sync_nov22.txt");
  string line_data;  
  if(fin_data.is_open()) {
    while(fin_data.good()){

      // get a line from fin_data
      getline(fin_data, line_data);  

      if(line_data.find("#")!=string::npos ) continue;
      //2017-09-21 12:49:34 010110100100 

      int beam;
      int run;
      int file; 
      int event; 
      string date;
      string time;
      string hs_hits1;
      string hs_hits2;
      string hs_hits3;
      string hs_hits4;
      string hs_hits5;
      string hits;

      stringstream stream(line_data);
      stream >> beam; 
      stream >> run; 
      stream >> file; 
      stream >> event; 
      stream >> date; 
      stream >> time; 
      stream >> hs_hits1; 
      stream >> hs_hits2; 
      stream >> hs_hits3; 
      stream >> hs_hits4; 
      stream >> hs_hits5; 
      stream >> hits; 
      
      if(date=="111111") break;

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
      
      // look at only triple coincidence events in order to compare with data
      if(occ_layer1>0  && occ_layer2>0  && occ_layer3>0 ) 
      { 
        // occ per layer : 2D of layer vs ch  (3x4)  
        h2_data_occ_cate->Fill(1, occ_layer1);
        h2_data_occ_cate->Fill(2, occ_layer2);
        h2_data_occ_cate->Fill(3, occ_layer3);
      } 

      // hit bot vs top 
      float occ_hs_bot = 0;
      float occ_hs_top = 0;
      for(int i=0; i<8; i++) 
      { 
        if(hs_hits1[i]=='1') occ_hs_bot++;
        if(hs_hits2[i]=='1') occ_hs_bot++;
        if(hs_hits3[i]=='1') occ_hs_bot++;
        if(hs_hits4[i]=='1') occ_hs_top++;
        if(hs_hits5[i]=='1') occ_hs_top++;
      }
      //h2_data_hitfrac->Fill(occ_hs_bot/24., occ_hs_top/16.);
      h2_data_hit->Fill(occ_hs_bot, occ_hs_top);
      if(beam) h2_data_hit_bon->Fill(occ_hs_bot, occ_hs_top);
      if(!beam) h2_data_hit_boff->Fill(occ_hs_bot, occ_hs_top);

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
  h1_data_occ->SetLineColor(kBlack);  
  h1_data_occ->SetLineWidth(2);  
  h1_mc_occ->SetLineColor(kRed);  
  h1_mc_occ->SetLineWidth(2);  
  h1_data_occ->SetMinimum(1);  
  h1_data_occ->Draw("e");  
  h1_mc_occ->Scale(h1_data_occ->Integral()/h1_mc_occ->Integral());  
  h1_mc_occ->Draw("e same");  
  c->cd(2);
  c->cd(2)->SetLogy(1);
  h1_data_occ_layer->SetLineColor(kBlack);  
  h1_data_occ_layer->SetLineWidth(2);  
  h1_mc_occ_layer->SetLineColor(kRed);  
  h1_mc_occ_layer->SetLineWidth(2);  
  h1_data_occ_layer->SetMinimum(1);  
  h1_data_occ_layer->DrawNormalized("e");  
  h1_mc_occ_layer->DrawNormalized("e same");  
  c->cd(3);
  c->cd(3)->SetLogy(1);
  h1_data_occ_cate->SetLineColor(kBlack);  
  h1_data_occ_cate->SetLineWidth(2);  
  h1_mc_occ_cate->SetLineColor(kRed);  
  h1_mc_occ_cate->SetLineWidth(2);  
  h1_data_occ_cate->SetMinimum(1);  
  h1_data_occ_cate->DrawNormalized("e");  
  h1_mc_occ_cate->DrawNormalized("e same");  
  c->cd(4);
  c->cd(4)->SetLogz(1); 
  h2_mc_occ_cate->SetMarkerSize(2);
  h2_mc_occ_cate->DrawNormalized("colz text");
  c->cd(5);
  c->cd(5)->SetLogz(1); 
  h2_data_occ_cate->SetMarkerSize(2);
  h2_data_occ_cate->DrawNormalized("colz text");
  c->cd(6);
  c->cd(6)->SetLogz(1);
  h2_mc_cate_pt->DrawNormalized("colz text"); 
  c->cd(7);
  c->cd(7)->SetLogz(1);
  h2_data_hit->Draw("colz text");
  c->cd(8);
  c->cd(8)->SetLogz(1);
  h2_data_hit_boff->Draw("colz text");
  c->cd(9);
  c->cd(9)->SetLogz(1);
  h2_data_hit_bon->Draw("colz text");

  c->Print("fig/data_sim.pdf");
}
