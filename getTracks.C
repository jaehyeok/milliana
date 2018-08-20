// compile with 
//  $ g++ -o addHSData.exe addHSData.C `root-config --cflags --glibs`

#include <time.h> 
#include <iostream> 
#include <fstream> 
#include <vector> 
#include <string> 

#include "TString.h" 
#include "TFile.h" 
#include "TTree.h" 
#include "TObjArray.h" 
#include "TObjString.h" 
#include "TH1D.h" 
#include "TH2D.h" 
#include "TBranch.h" 
#include "TCanvas.h" 
#include "TSystem.h" 

using namespace std;

// define the parametric line equation
void line(double t, const double *p, double &x, double &y, double &z) {
    // a parametric line is define from 6 parameters but 4 are independent
    // x0,y0,z0,z1,y1,z1 which are the coordinates of two points on the line
    // can choose z0 = 0 if line not parallel to x-y plane and z1 = 1;
    x = p[0] + p[1]*t;
    y = p[2] + p[3]*t;
    z = t;
 }

std::vector<int> convertRawToPhysCh(unsigned int raw_ch, bool isHS)
{ 
  int phys_ch[3] ={0,0,0}; // x, y, z 
  if(isHS) 
  { 
     // bottom vertical bars
     if(raw_ch==0)        {phys_ch[0]= -4;  phys_ch[1]=  0;  phys_ch[2]=  2;} 
     else if(raw_ch==1)   {phys_ch[0]= -3;  phys_ch[1]=  0;  phys_ch[2]=  2;} 
     else if(raw_ch==2)   {phys_ch[0]= -2;  phys_ch[1]=  0;  phys_ch[2]=  2;} 
     else if(raw_ch==3)   {phys_ch[0]= -1;  phys_ch[1]=  0;  phys_ch[2]=  2;} 
     else if(raw_ch==4)   {phys_ch[0]= -4;  phys_ch[1]=  0;  phys_ch[2]=  1;} 
     else if(raw_ch==5)   {phys_ch[0]= -3;  phys_ch[1]=  0;  phys_ch[2]=  1;} 
     else if(raw_ch==6)   {phys_ch[0]= -2;  phys_ch[1]=  0;  phys_ch[2]=  1;} 
     else if(raw_ch==7)   {phys_ch[0]= -1;  phys_ch[1]=  0;  phys_ch[2]=  1;} 
     else if(raw_ch==8)   {phys_ch[0]=  1;  phys_ch[1]=  0;  phys_ch[2]=  2;} 
     else if(raw_ch==9)   {phys_ch[0]=  2;  phys_ch[1]=  0;  phys_ch[2]=  2;} 
     else if(raw_ch==10)  {phys_ch[0]=  3;  phys_ch[1]=  0;  phys_ch[2]=  2;} 
     else if(raw_ch==11)  {phys_ch[0]=  4;  phys_ch[1]=  0;  phys_ch[2]=  2;} 
     else if(raw_ch==12)  {phys_ch[0]=  1;  phys_ch[1]=  0;  phys_ch[2]=  1;} 
     else if(raw_ch==13)  {phys_ch[0]=  2;  phys_ch[1]=  0;  phys_ch[2]=  1;} 
     else if(raw_ch==14)  {phys_ch[0]=  3;  phys_ch[1]=  0;  phys_ch[2]=  1;} 
     else if(raw_ch==15)  {phys_ch[0]=  4;  phys_ch[1]=  0;  phys_ch[2]=  1;} 
     // bottom horizontal bars
     else if(raw_ch==16)  {phys_ch[0]=  0;  phys_ch[1]=  8;  phys_ch[2]=  1;} 
     else if(raw_ch==17)  {phys_ch[0]=  0;  phys_ch[1]=  7;  phys_ch[2]=  1;} 
     else if(raw_ch==18)  {phys_ch[0]=  0;  phys_ch[1]=  6;  phys_ch[2]=  1;} 
     else if(raw_ch==19)  {phys_ch[0]=  0;  phys_ch[1]=  5;  phys_ch[2]=  1;} 
     else if(raw_ch==20)  {phys_ch[0]=  0;  phys_ch[1]=  8;  phys_ch[2]=  2;} 
     else if(raw_ch==21)  {phys_ch[0]=  0;  phys_ch[1]=  7;  phys_ch[2]=  2;} 
     else if(raw_ch==22)  {phys_ch[0]=  0;  phys_ch[1]=  6;  phys_ch[2]=  2;} 
     else if(raw_ch==23)  {phys_ch[0]=  0;  phys_ch[1]=  5;  phys_ch[2]=  2;} 
     else if(raw_ch==24)  {phys_ch[0]=  0;  phys_ch[1]=  4;  phys_ch[2]=  1;} 
     else if(raw_ch==25)  {phys_ch[0]=  0;  phys_ch[1]=  3;  phys_ch[2]=  1;} 
     else if(raw_ch==26)  {phys_ch[0]=  0;  phys_ch[1]=  2;  phys_ch[2]=  1;} 
     else if(raw_ch==27)  {phys_ch[0]=  0;  phys_ch[1]=  1;  phys_ch[2]=  1;} 
     else if(raw_ch==28)  {phys_ch[0]=  0;  phys_ch[1]=  4;  phys_ch[2]=  2;} 
     else if(raw_ch==29)  {phys_ch[0]=  0;  phys_ch[1]=  3;  phys_ch[2]=  2;} 
     else if(raw_ch==30)  {phys_ch[0]=  0;  phys_ch[1]=  2;  phys_ch[2]=  2;} 
     else if(raw_ch==31)  {phys_ch[0]=  0;  phys_ch[1]=  1;  phys_ch[2]=  2;} 
     // top horizontal bars
     else if(raw_ch==32)  {phys_ch[0]=  0;  phys_ch[1]=  4;  phys_ch[2]= -2;} 
     else if(raw_ch==33)  {phys_ch[0]=  0;  phys_ch[1]=  3;  phys_ch[2]= -2;} 
     else if(raw_ch==34)  {phys_ch[0]=  0;  phys_ch[1]=  2;  phys_ch[2]= -2;} 
     else if(raw_ch==35)  {phys_ch[0]=  0;  phys_ch[1]=  1;  phys_ch[2]= -2;} 
     else if(raw_ch==36)  {phys_ch[0]=  0;  phys_ch[1]=  4;  phys_ch[2]= -1;} 
     else if(raw_ch==37)  {phys_ch[0]=  0;  phys_ch[1]=  3;  phys_ch[2]= -1;} 
     else if(raw_ch==38)  {phys_ch[0]=  0;  phys_ch[1]=  2;  phys_ch[2]= -1;} 
     else if(raw_ch==39)  {phys_ch[0]=  0;  phys_ch[1]=  1;  phys_ch[2]= -1;} 
     else if(raw_ch==40)  {phys_ch[0]=  0;  phys_ch[1]=  8;  phys_ch[2]= -2;} 
     else if(raw_ch==41)  {phys_ch[0]=  0;  phys_ch[1]=  7;  phys_ch[2]= -2;} 
     else if(raw_ch==42)  {phys_ch[0]=  0;  phys_ch[1]=  6;  phys_ch[2]= -2;} 
     else if(raw_ch==43)  {phys_ch[0]=  0;  phys_ch[1]=  5;  phys_ch[2]= -2;} 
     else if(raw_ch==44)  {phys_ch[0]=  0;  phys_ch[1]=  8;  phys_ch[2]= -1;} 
     else if(raw_ch==45)  {phys_ch[0]=  0;  phys_ch[1]=  7;  phys_ch[2]= -1;} 
     else if(raw_ch==46)  {phys_ch[0]=  0;  phys_ch[1]=  6;  phys_ch[2]= -1;} 
     else if(raw_ch==47)  {phys_ch[0]=  0;  phys_ch[1]=  5;  phys_ch[2]= -1;} 
     // bottom vertical bars
     else if(raw_ch==48)  {phys_ch[0]=  4;  phys_ch[1]=  0;  phys_ch[2]= -2;} 
     else if(raw_ch==49)  {phys_ch[0]=  3;  phys_ch[1]=  0;  phys_ch[2]= -2;} 
     else if(raw_ch==50)  {phys_ch[0]=  2;  phys_ch[1]=  0;  phys_ch[2]= -2;} 
     else if(raw_ch==51)  {phys_ch[0]=  1;  phys_ch[1]=  0;  phys_ch[2]= -2;} 
     else if(raw_ch==52)  {phys_ch[0]=  4;  phys_ch[1]=  0;  phys_ch[2]= -1;} 
     else if(raw_ch==53)  {phys_ch[0]=  3;  phys_ch[1]=  0;  phys_ch[2]= -1;} 
     else if(raw_ch==54)  {phys_ch[0]=  2;  phys_ch[1]=  0;  phys_ch[2]= -1;} 
     else if(raw_ch==55)  {phys_ch[0]=  1;  phys_ch[1]=  0;  phys_ch[2]= -1;} 
     else if(raw_ch==56)  {phys_ch[0]= -1;  phys_ch[1]=  0;  phys_ch[2]= -2;} 
     else if(raw_ch==57)  {phys_ch[0]= -2;  phys_ch[1]=  0;  phys_ch[2]= -2;} 
     else if(raw_ch==58)  {phys_ch[0]= -3;  phys_ch[1]=  0;  phys_ch[2]= -2;} 
     else if(raw_ch==59)  {phys_ch[0]= -4;  phys_ch[1]=  0;  phys_ch[2]= -2;} 
     else if(raw_ch==60)  {phys_ch[0]= -1;  phys_ch[1]=  0;  phys_ch[2]= -1;} 
     else if(raw_ch==61)  {phys_ch[0]= -2;  phys_ch[1]=  0;  phys_ch[2]= -1;} 
     else if(raw_ch==62)  {phys_ch[0]= -3;  phys_ch[1]=  0;  phys_ch[2]= -1;} 
     else if(raw_ch==63)  {phys_ch[0]= -4;  phys_ch[1]=  0;  phys_ch[2]= -1;} 
     else 
     { 
       cout << "HS raw_ch = " << raw_ch << " is not correct. Enter a correct raw_ch." << endl;  
     }
  }
  else 
  { 
     if(raw_ch==0)        {phys_ch[0]=  0;  phys_ch[1]=  2;  phys_ch[2]=  4;} 
     else if(raw_ch==1)   {phys_ch[0]=  0;  phys_ch[1]=  2;  phys_ch[2]=  3;} 
     else if(raw_ch==2)   {phys_ch[0]=  0;  phys_ch[1]=  2;  phys_ch[2]=  2;} 
     else if(raw_ch==3)   {phys_ch[0]=  0;  phys_ch[1]=  2;  phys_ch[2]=  1;} 
     else if(raw_ch==4)   {phys_ch[0]=  0;  phys_ch[1]=  1;  phys_ch[2]=  4;} 
     else if(raw_ch==5)   {phys_ch[0]=  0;  phys_ch[1]=  1;  phys_ch[2]=  3;} 
     else if(raw_ch==6)   {phys_ch[0]=  0;  phys_ch[1]=  1;  phys_ch[2]=  2;} 
     else if(raw_ch==7)   {phys_ch[0]=  0;  phys_ch[1]=  1;  phys_ch[2]=  1;} 
     else if(raw_ch==8)   {phys_ch[0]=  0;  phys_ch[1]= -2;  phys_ch[2]=  1;} 
     else if(raw_ch==9)   {phys_ch[0]=  0;  phys_ch[1]= -2;  phys_ch[2]=  2;} 
     else if(raw_ch==10)  {phys_ch[0]=  0;  phys_ch[1]= -2;  phys_ch[2]=  3;} 
     else if(raw_ch==11)  {phys_ch[0]=  0;  phys_ch[1]= -2;  phys_ch[2]=  4;} 
     else if(raw_ch==12)  {phys_ch[0]=  0;  phys_ch[1]= -1;  phys_ch[2]=  1;} 
     else if(raw_ch==13)  {phys_ch[0]=  0;  phys_ch[1]= -1;  phys_ch[2]=  2;} 
     else if(raw_ch==14)  {phys_ch[0]=  0;  phys_ch[1]= -1;  phys_ch[2]=  3;} 
     else if(raw_ch==15)  {phys_ch[0]=  0;  phys_ch[1]= -1;  phys_ch[2]=  4;} 
     else if(raw_ch==16)  {phys_ch[0]=  0;  phys_ch[1]=  1;  phys_ch[2]=  1;} 
     else if(raw_ch==17)  {phys_ch[0]=  0;  phys_ch[1]=  1;  phys_ch[2]=  2;} 
     else if(raw_ch==18)  {phys_ch[0]=  0;  phys_ch[1]=  1;  phys_ch[2]=  3;} 
     else if(raw_ch==19)  {phys_ch[0]=  0;  phys_ch[1]=  1;  phys_ch[2]=  4;} 
     else if(raw_ch==20)  {phys_ch[0]=  0;  phys_ch[1]=  2;  phys_ch[2]=  1;} 
     else if(raw_ch==21)  {phys_ch[0]=  0;  phys_ch[1]=  2;  phys_ch[2]=  2;} 
     else if(raw_ch==22)  {phys_ch[0]=  0;  phys_ch[1]=  2;  phys_ch[2]=  3;} 
     else if(raw_ch==23)  {phys_ch[0]=  0;  phys_ch[1]=  2;  phys_ch[2]=  4;} 
     else 
     { 
       cout << "TP raw_ch = " << raw_ch << " is not correct. Enter a correct raw_ch." << endl; 
     }
  }

  std::vector<int> phys_ch_vec;
  phys_ch_vec.push_back(phys_ch[0]);
  phys_ch_vec.push_back(phys_ch[1]);
  phys_ch_vec.push_back(phys_ch[2]);
  return phys_ch_vec;
}

std::vector<float> convertPhysChToCoord(std::vector<int> phys_ch, bool isHS)
{
  // unit = cm
  float space_btw_packs = 1;  
  float space_btw_bars  = 0.2;  

  int phys_ch_x = phys_ch[0];
  int phys_ch_y = phys_ch[1];
  int phys_ch_z = phys_ch[2];
  
  float x=-999;
  float y=-999;
  float z=-999;
  float ex=-999;
  float ey=-999;
  float ez=-999;

  if(isHS)
  {
    // vertical: y=0  
    if(phys_ch_y==0)
    {
      // bottom: z>0
      if(phys_ch_z>0) 
      { 
        // x
        if(phys_ch_x>0) x = space_btw_packs/2 + 2.5/2 + (phys_ch_x-1)*2.5 + (phys_ch_x-1)*0.2;   
        else x = -1*space_btw_packs/2 - 2.5/2 + (phys_ch_x+1)*2.5 + (phys_ch_x+1)*0.2;   
        // z 
        z = 180 + 0.5 +  (phys_ch_z-1)*2.5 + 2.5/2 + (phys_ch_z-1)*0.2; 
        // y: approximate
        y=10;
      }
      // top: z<0
      else 
      { 
        // x
        if(phys_ch_x>0) x = space_btw_packs/2 + 2.5/2 + (phys_ch_x-1)*2.5 + (phys_ch_x-1)*0.2;   
        else x = -1*space_btw_packs/2 - 2.5/2 + (phys_ch_x+1)*2.5 + (phys_ch_x+1)*0.2;   
        // z 
        z = -180 - 10 - 0.5 + (1+phys_ch_z)*2.5 - 2.5/2 + (1+phys_ch_z)*0.2; 
        // y 
        y=0;
      }
      ex = TMath::Sqrt(2.*2./12.);
      ey = TMath::Sqrt(45.*45./12.);
      ez = TMath::Sqrt(2.*2./12.);
    }
    // horizontal: x=0 
    if(phys_ch_x==0)
    {
      // y 
      y = -1.25 + (phys_ch_y-1)*2.5 + (phys_ch_y-1)*0.2;   
      
      // bottom: z>0
      if(phys_ch_z>0) 
      { 
        z = 180 - (2-phys_ch_z)*2.5 - 2.5/2 - (2-phys_ch_z)*0.2; 
      }
      // top: z<0
      else
      { 
        z = -180 - 5 + (phys_ch_z+1)*2.5 - 2.5/2 + (phys_ch_z+1)*0.2; 
      }
      x=0;
     
      ex = TMath::Sqrt(45.*45./12.);
      ey = TMath::Sqrt(2.*2./12.);
      ez = TMath::Sqrt(2.*2./12.);
    }
  }
  else 
  {
    cout << "TP ... " << endl;
  }

  std::vector<float> coord_vec;
  coord_vec.push_back(x);
  coord_vec.push_back(y);
  coord_vec.push_back(z);
  // uncertainty
  // note that the variance of a flat distribution is l^2/12 where l is the width 
  coord_vec.push_back(ex);
  coord_vec.push_back(ey);
  coord_vec.push_back(ez);
  return coord_vec;
}

//
int getTracks()
{
 
  std::vector<int> hs_data;
  std::vector<int> tp_data;

  hs_data.push_back(1);
  hs_data.push_back(5);
  hs_data.push_back(57);
  hs_data.push_back(61);
  hs_data.push_back(19);
  hs_data.push_back(23);
  hs_data.push_back(32);
  hs_data.push_back(36);
  
  cout << hs_data.size() << endl;

  // arrays for fit
  const int n = hs_data.size();
  Double_t x[n], y[n], z[n];
  Double_t ex[n], ey[n], ez[n];

  // 1. convert to physical channels 
  // Hodoscope 
  for(int i=0; i<hs_data.size(); i++)
  { 
    std::vector<int> phys_ch = convertRawToPhysCh(hs_data.at(i), true);
    cout << hs_data.at(i) << " :: " << phys_ch[0] << " " << phys_ch[1] << " " << phys_ch[2] << endl; 
    std::vector<float> coord_ch = convertPhysChToCoord(phys_ch, true);
    cout << coord_ch[0] << " +/- " << coord_ch[3] << endl; 
    cout << coord_ch[1] << " +/- " << coord_ch[4] << endl; 
    cout << coord_ch[2] << " +/- " << coord_ch[5] << endl; 
    cout << endl; 
    x[i] = coord_ch[0];
    y[i] = coord_ch[1];
    z[i] = coord_ch[2];
    ex[i] = coord_ch[3];
    ey[i] = coord_ch[4];
    ez[i] = coord_ch[5];
    phys_ch.clear(); 
    coord_ch.clear(); 
  }
 
  
  // Trackpacks   
  //for(int i=0; i<24; i++)
  //{ 
  //  std::vector<int> phys_ch = convertRawToPhysCh(i, false);
  //  cout << i << " :: " << phys_ch[0] << " " << phys_ch[1] << " " << phys_ch[2] << endl; 
  //}
/* 
  const int n = 7;
  Double_t x[n]={1,2,3,4,5,6,7};
  Double_t y[n]={1,2,3,4,5,6,7};
  Double_t z[n]={1,2,3,4,5,6,7};
  Double_t ex[n]={0.01,0.01,0.01,0.01,0.01,0.01,0.01};
  Double_t ey[n]={0.01,0.01,0.01,0.01,0.01,0.01,0.01};
  Double_t ez[n]={0.01,0.01,0.01,0.01,0.01,0.01,0.01};
*/

  //
  // 2. do the fit 
  //
 
  TCanvas *c_fit = new TCanvas("c_fit", "c_fit", 200,1000);
  c_fit->Divide(2,1);
  // x-z fit: vertical bars    
  c_fit->cd(1);
  TGraphErrors *g_xz = new TGraphErrors(n, x, z, ex, ez); 
  TF1 *f_xz = new TF1("f_xz","x*[0]+[1]", -40, 40);  
  g_xz->Draw("AP");
  g_xz->Fit("f_xz");
  // y-z fit: horizontal bars  
  c_fit->cd(2);
  TGraphErrors *g_yz = new TGraphErrors(n, y, z, ey, ez); 
  TF1 *f_yz = new TF1("f_yz","x*[0]+[1]", -40, 40);  
  g_yz->Draw("AP");
  g_yz->Fit("f_yz");

  cout << f_xz->GetParameter(0) << " " << f_xz->GetParameter(1) << " " 
       << f_xz->GetChisquare() << "/" << f_xz->GetNDF() << endl;
  cout << f_yz->GetParameter(0) << " " << f_yz->GetParameter(1) << " " 
       << f_yz->GetChisquare() << "/" << f_yz->GetNDF() << endl;
  
  //
  // 2. show the fitted line 
  //
 // TCanvas *c_3d = new TCanvas("c_3d", "c_3d", 1000,1000);
  // draw the fitted line
  double parFit[4];
  parFit[0] =  -1.*f_xz->GetParameter(1)/f_xz->GetParameter(0);  
  parFit[1] =  1./f_xz->GetParameter(0);  
  parFit[2] =  -1.*f_yz->GetParameter(1)/f_yz->GetParameter(0);  
  parFit[3] =  1./f_yz->GetParameter(0);  
  int ndiv = 1000;
  double t0 = 0;
  double dt = 10;
  TPolyLine3D *l = new TPolyLine3D(ndiv);
  for (int i = 0; i <ndiv;++i) 
  {
    double t = t0+ dt*i/ndiv;
    double x,y,z;
    line(t,parFit,x,y,z);
    l->SetPoint(i,x,y,z);
  }
  l->SetLineColor(kRed);
//  l->Draw("same");

  // 3. estimate which channels are hit 
  //void getHitBars(std::vector<bool> hs_data, std::vector<bool> tp_data)

  return 0;
}

// complications 
// - there can be more than 1 track
// - need to store chi2 of the fit\
// - 

