void hodoAlign()
{  
    TH1D *hv = new TH1D("hv", "hv", 9, -4.5, 4.5);
    //TH1D *hv = new TH1D("hv", "hv", 5, -2.5, 2.5);
    TH1D *hh = new TH1D("hh", "hh", 5, -2.5, 2.5);
    
    ifstream fin("data_skim.txt");
    string line;  
    if(fin.is_open()) {
        while(fin.good()){

            // get a line from fin
            getline(fin, line);  

            //2017: 9:23:14:39:34:504889  0 0000 00000000 00010001 00010001 00000000 00000000
            //0123456789012345678901234567890123456789012345678901234567890123456789012345678 
            //0         1         2         3         4         5         6         7 
        
            int pack0[8], pack1[8], pack2[8], pack3[8], pack4[8]; 

            for(int i=35; i<=42; i++) pack0[i-35] = (line[i]=='1'?1:0); // v 
            for(int i=44; i<=51; i++) pack1[i-44] = (line[i]=='1'?1:0); // v
            for(int i=53; i<=60; i++) pack2[i-53] = (line[i]=='1'?1:0); // h
            for(int i=62; i<=69; i++) pack3[i-62] = (line[i]=='1'?1:0); // h
            for(int i=71; i<=78; i++) pack4[i-71] = (line[i]=='1'?1:0); // v
/*   
            for(int i=0; i<8; i++) 
                cout << pack0[i] << " " 
                     << pack1[i] << " " 
                     << pack2[i] << " " 
                     << pack3[i] << " " 
                     << pack4[i] << " "  
                     << endl;
*/    

            for(int i=0; i<8; i++)  cout << pack0[i];  cout << " ";   
            for(int i=0; i<8; i++)  cout << pack1[i];  cout << " ";   
            for(int i=0; i<8; i++)  cout << pack2[i];  cout << " ";   
            for(int i=0; i<8; i++)  cout << pack3[i];  cout << " ";   
            for(int i=0; i<8; i++)  cout << pack4[i];  cout << endl;   
            
            // vertical packs 
/*
            if(pack0[3] || pack0[7])  
            {
                if(pack4[0] || pack4[4]) hv->Fill(-1);
                if(pack4[1] || pack4[5]) hv->Fill(0);
                if(pack4[2] || pack4[6]) hv->Fill(1);
                if(pack4[3] || pack4[7]) hv->Fill(2);
            }  
*/
/*
            if(pack1[0] || pack1[4])  
            {
                if(pack4[0] || pack4[4]) hv->Fill(-2);
                if(pack4[1] || pack4[5]) hv->Fill(-1);
                if(pack4[2] || pack4[6]) hv->Fill(0);
                if(pack4[3] || pack4[7]) hv->Fill(1);
            }  
*/

/*
            if(pack4[2] || pack4[6])  
            {
                if(pack0[0] || pack0[4]) hv->Fill(-4);
                if(pack0[1] || pack0[5]) hv->Fill(-3);
                if(pack0[2] || pack0[6]) hv->Fill(-2);
                if(pack0[3] || pack0[7]) hv->Fill(-1);
                if(pack1[0] || pack1[4]) hv->Fill(0);
                if(pack1[1] || pack1[5]) hv->Fill(1);
                if(pack1[2] || pack1[6]) hv->Fill(2);
                if(pack1[3] || pack1[7]) hv->Fill(3);
            }
*/

            if(pack4[1] || pack4[5])  
            {
                if(pack0[0] || pack0[4]) hv->Fill(-3);
                if(pack0[1] || pack0[5]) hv->Fill(-2);
                if(pack0[2] || pack0[6]) hv->Fill(-1);
                if(pack0[3] || pack0[7]) hv->Fill(0);
                if(pack1[0] || pack1[4]) hv->Fill(1);
                if(pack1[1] || pack1[5]) hv->Fill(2);
                if(pack1[2] || pack1[6]) hv->Fill(3);
                if(pack1[3] || pack1[7]) hv->Fill(4);
            }  

            // horizontal packs
/*
            if(pack2[2] || pack2[6])  
            {
                if(pack3[0] || pack3[4]) hh->Fill(2);
                if(pack3[1] || pack3[5]) hh->Fill(1);
                if(pack3[2] || pack3[6]) hh->Fill(0);
                if(pack3[3] || pack3[7]) hh->Fill(-1);
            }  
*/

            if(pack2[1] || pack2[5])  
            {
                if(pack3[0] || pack3[4]) hh->Fill(1);
                if(pack3[1] || pack3[5]) hh->Fill(0);
                if(pack3[2] || pack3[6]) hh->Fill(-1);
                if(pack3[3] || pack3[7]) hh->Fill(-2);
            }  




        }
    }
    
    TCanvas *c = new TCanvas("c","c",400,300);
    c->cd(1);
    hv->SetLineWidth(2);
    hv->SetLineColor(kBlack);
    hv->SetFillColor(kRed-3);
    hv->SetStats(0);
    hv->Draw("hist"); 
    c->Print("align.pdf");
}
