void sim()
{  
    TH1D *hy = new TH1D("hy", "hy", 100, -0.17, 0.17);
    TH1D *hz = new TH1D("hz", "hz", 100, -0.17, 0.17);
    TH1D *hpx = new TH1D("hpx", "hpx", 100, 0, 100);
    TH1D *hpy = new TH1D("hpy", "hpy", 100, -1, 1);
    TH1D *hpz = new TH1D("hpz", "hpz", 100, -1, 1);
    TH1D *htheta = new TH1D("htheta", "htheta", 100, 0*180/3.141592, 0.2*180/3.141592);
    TH2D *hpxpt = new TH2D("hpxpt", "hpxpt", 100, 0, 100, 100, 0, 1);
    TH2D *hpxtheta = new TH2D("hpxtheta", "hpxtheta", 100, 0, 100, 100, 0*180/3.141592, 0.2*180/3.141592);
    TH2D *htop = new TH2D("htop", "htop", 100, -0.75, 0.75, 100, -0.75, 0.75);
    TH2D *hbottom = new TH2D("hbottom", "hbottom", 100, -0.75, 0.75, 100, -0.75, 0.75);
    TH2D *hsim = new TH2D("hsim", "hsim", 100, -0.75, 0.75, 100, -0.75, 0.75);

    int intop=0;

    ifstream fin("hits_45by45.txt");
    string line;  
    if(fin.is_open()) {
        while(fin.good()){

            // get a line from fin
            getline(fin, line);  
           // charge mass x y z (m) px py pz (MeV)
           //  1.000000  105.000000  33.000000 -0.085899 0.076362  553.284552  -7.225200 8.656843
        
            float q, m; 
            float x,y,z;
            float px,py,pz;
            
            stringstream stream(line);
            stream >> q;
            stream >> m;
            stream >> x;
            stream >> y;
            stream >> z;
            stream >> px;
            stream >> py;
            stream >> pz; 
  
            hsim->Fill(y,z); 

            // require bottom cross section
            bool inBottom = false;
            if (abs(y)<0.09 || abs(z-0.02)<0.045) inBottom = true;
            if (!inBottom) continue;
            hbottom->Fill(y,z); 

            // calculate cos theta
            float deno = TMath::Sqrt(x*x + y*y + z*z)*TMath::Sqrt(px*px + py*py + pz*pz); 
            float num = x*px + y*py + z*pz; 
            //cout << q << " " << m << " " << x << " " << y << " " << z << " " << px << " " << py << " " << px << " "; 
            //cout << num << "/" << deno << " " << TMath::ACos(num/deno)*180/3.141592<< endl;
         
            // calculate where it will hit on the top HS  
            // assume 3.6 m from bottom and top HS  
            float dy = 3.6*py/px;
            float dz = 3.6*pz/px;
            
            bool inTop = false;
            if(abs(y+dy)<0.045 || abs(z+dz)<0.045) inTop=true; 
            if(abs(y+dy)>0.225 || abs(z+dz)>0.225) inTop=false; 
            if(inTop) intop++;

            hy->Fill(y);
            hz->Fill(z);
            hpx->Fill(px/1000);
            hpy->Fill(py/1000);
            hpz->Fill(pz/1000);
            htheta->Fill(TMath::ACos(num/deno)*180/3.141592);
            hpxpt->Fill(px/1000, TMath::Sqrt(py*py+pz*pz)/1000);
            hpxtheta->Fill(px/1000, TMath::ACos(num/deno)*180/3.141592); 
            htop->Fill(y+dy,z+dz); 

        }
    }

    cout << intop << "/" << hy->Integral(-1,99999) << " " << intop/hy->Integral(-1,99999) << endl; 

    TCanvas *c = new TCanvas("c","c",1200,900);
    c->Divide(4,3); 
    c->cd(1);
    htheta->Draw("hist ep");  
    c->cd(1)->SetLogy(1);
    c->cd(2);
    c->cd(2)->SetLogy(1);
    //hy->SetLineWidth(2);
    //hy->SetLineColor(kBlack);
    //hy->SetFillColor(kRed-3);
    //hy->SetStats(0);
    hy->Draw("hist ep");  
    c->cd(3);
    c->cd(3)->SetLogy(1);
    hz->Draw("hist ep");  
    c->cd(4);
    c->cd(4)->SetLogy(1);
    hpx->Draw("hist ep");  
    c->cd(5);
    c->cd(5)->SetLogy(1);
    hpy->Draw("hist ep");  
    c->cd(6);
    c->cd(6)->SetLogy(1);
    hpz->Draw("hist ep");  
    c->cd(7);
    c->cd(7)->SetLogz(1);
    hpxpt->Draw("colz");  
    c->cd(8);
    c->cd(8)->SetLogz(1);
    hpxtheta->Draw("colz");  
    c->cd(9);
    c->cd(9)->SetLogz(0);
    htop->SetStats(0);  
    htop->Draw("colz");  
    c->cd(10);
    c->cd(10)->SetLogz(0);
    hbottom->SetStats(0);  
    hbottom->Draw("colz");  
    c->cd(11);
    c->cd(11)->SetLogz(0);
    hsim->SetStats(0);  
    hsim->Draw("colz");  

    c->Print("sim.pdf");
}
