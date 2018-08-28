#include "TGeoManager.h"
//
// Location of hodoscope 
//
// top
float htopx = 0.5;
float htopy = 0.;
float htopz = -180;
// bottom 
float hbotx = 0.5;
float hboty = -1.25;
float hbotz = 180; 
//
bool showRow1=true;
bool showRow2=true;
bool showRow3=true;
bool showBar=true; 
bool showBrick=false;
bool showSlab=true;
bool showSheet=true;
bool showHS=true;
bool showPack=false;

// nPEcut 
float nPEcut[32] = 
{500, 500, 500, 500, 500,
 500, 500, 500, 500, 500, 
 5,   5,   500, 500, 6, 
 10000, 500, 500, 200, 10, 
 200, 200, 500, 500, 500, 
 500, 15,  10,  100, 5, 
 20, 10};


// ------------------------------------------------------------------------
//  Fit 
// ------------------------------------------------------------------------
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
     if(raw_ch==0)        {phys_ch[0]=  0;  phys_ch[1]=  2;  phys_ch[2]=  4+8;} 
     else if(raw_ch==1)   {phys_ch[0]=  0;  phys_ch[1]=  2;  phys_ch[2]=  3+8;} 
     else if(raw_ch==2)   {phys_ch[0]=  0;  phys_ch[1]=  2;  phys_ch[2]=  2+8;} 
     else if(raw_ch==3)   {phys_ch[0]=  0;  phys_ch[1]=  2;  phys_ch[2]=  1+8;} 
     else if(raw_ch==4)   {phys_ch[0]=  0;  phys_ch[1]=  1;  phys_ch[2]=  4+8;} 
     else if(raw_ch==5)   {phys_ch[0]=  0;  phys_ch[1]=  1;  phys_ch[2]=  3+8;} 
     else if(raw_ch==6)   {phys_ch[0]=  0;  phys_ch[1]=  1;  phys_ch[2]=  2+8;} 
     else if(raw_ch==7)   {phys_ch[0]=  0;  phys_ch[1]=  1;  phys_ch[2]=  1+8;} 
     else if(raw_ch==8)   {phys_ch[0]=  0;  phys_ch[1]= -2;  phys_ch[2]=  1+4;} 
     else if(raw_ch==9)   {phys_ch[0]=  0;  phys_ch[1]= -2;  phys_ch[2]=  2+4;} 
     else if(raw_ch==10)  {phys_ch[0]=  0;  phys_ch[1]= -2;  phys_ch[2]=  3+4;} 
     else if(raw_ch==11)  {phys_ch[0]=  0;  phys_ch[1]= -2;  phys_ch[2]=  4+4;} 
     else if(raw_ch==12)  {phys_ch[0]=  0;  phys_ch[1]= -1;  phys_ch[2]=  1+4;} 
     else if(raw_ch==13)  {phys_ch[0]=  0;  phys_ch[1]= -1;  phys_ch[2]=  2+4;} 
     else if(raw_ch==14)  {phys_ch[0]=  0;  phys_ch[1]= -1;  phys_ch[2]=  3+4;} 
     else if(raw_ch==15)  {phys_ch[0]=  0;  phys_ch[1]= -1;  phys_ch[2]=  4+4;} 
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
        if(phys_ch_x>0) x = space_btw_packs/2 + 2./2 + (phys_ch_x-1)*2. + (phys_ch_x-1)*0.2;   
        else x = -1*space_btw_packs/2 - 2./2 + (phys_ch_x+1)*2. + (phys_ch_x+1)*0.2;   
        // z 
        z = 180 + 0.5 +  (phys_ch_z-1)*2. + 2./2 + (phys_ch_z-1)*0.2; 
        // y: approximate
        y=10;
      }
      // top: z<0
      else 
      { 
        // x: +/- 0.2 is put at the end to make the fit more reasonable
        if(phys_ch_x>0) x = space_btw_packs/2 + 2./2 + (phys_ch_x-1)*2. + (phys_ch_x-1)*0.2 + 0.2;    
        else x = -1*space_btw_packs/2 - 2./2 + (phys_ch_x+1)*2. + (phys_ch_x+1)*0.2 - 0.2;  
        // z 
        z = -180 - 10 - 0.5 + (1+phys_ch_z)*2. - 2./2 + (1+phys_ch_z)*0.2; 
        // y 
        y=0;
      }
      ex = TMath::Sqrt(2.*2./12.);
      ey = TMath::Sqrt(45.*45./12.);
      ez = TMath::Sqrt(2.*2./12.);
  
      ex = ex/100;
      ez = ez/100;
    }
    // horizontal: x=0 
    if(phys_ch_x==0)
    {
      // y 
      y = -1.25 + (phys_ch_y-1)*2. + (phys_ch_y-1)*0.2;   
      
      // bottom: z>0
      if(phys_ch_z>0) 
      { 
        z = 180 - (2-phys_ch_z)*2. - 2./2 - (2-phys_ch_z)*0.2; 
      }
      // top: z<0
      else
      { 
        z = -180 - 5 + (phys_ch_z+1)*2. - 2./2 + (phys_ch_z+1)*0.2; 
      }
      x=0;
     
      ex = TMath::Sqrt(45.*45./12.);
      ey = TMath::Sqrt(2.*2./12.);
      ez = TMath::Sqrt(2.*2./12.);
      
      ey = ey/100;
      ez = ez/100;
    }
  }
  else 
  {
      // y 
      if(phys_ch_y>0)
      {
          y = 17 + 1 + (phys_ch_y-1)*2. + (phys_ch_y-1)*0.2; 

          if(phys_ch_z>8) // pack8 
          { 
            z = 180 - 53 - 2/2 - (12-phys_ch_z)*2.+ (12-phys_ch_z)*0.2; 
          }
          else // pack10
          {
            z = 180 - 154 + 2/2 + (phys_ch_z-1)*2.+ (phys_ch_z-1)*0.2; 
          }
      }
      else 
      { 
          y = -22.5 - 1 + (phys_ch_y+1)*2. + (phys_ch_y+1)*0.2; 
          z = 180 - 118 + 2/2 + (phys_ch_z-5)*2.+ (phys_ch_z-5)*0.2; 
      }
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


// draw fitted track line
void line(double t, double *p, double &x, double &y, double &z)
{
  x = p[0] + p[1]*t; 
  y = p[2] + p[3]*t; 
  z = t; 
}

TPolyLine3D* fittedTrack(double *p)
{ 
  int ndiv = 1000;
  double t0 = 0; 
  double dt = 200;
  TPolyLine3D *l = new TPolyLine3D(ndiv);
  for(int i=0; i<2*ndiv; i++)
  {
    double t = t0 + dt*i/ndiv - dt;
    double x,y,z;
    line(t,p,x,y,z);
    l->SetPoint(i,x,y,z);
  }
  l->SetLineColor(kRed);
  l->SetLineWidth(4);
  return l;
}

void fittedTrack(double *p, TGeoTrack* &geo_track)
{
  int ndiv = 1000;
  double t0 = 0; 
  double dt = 200;
  for(int i=0; i<2*ndiv; i++)
  {
    double t = t0 + dt*i/ndiv - dt;
    double x,y,z;
    line(t,p,x,y,z);
    geo_track->AddPoint(x,y,z,t); // x,y,z,t
  }
  geo_track->SetLineColor(kRed);
  geo_track->SetLineWidth(4);
}

void fittedTrack(double *p, TGeoVolume* &top, TGeoVolume* &track_dot)
{
  int ndiv = 1000;
  double t0 = 0; 
  double dt = 200;
  for(int i=0; i<2*ndiv; i++)
  {
    double t = t0 + dt*i/ndiv - dt;
    double x,y,z;
    line(t,p,x,y,z);
    top->AddNodeOverlap(track_dot,1,new TGeoTranslation(x,y,z));
  }
}

// function that converts data to coordinates 
//  - "pack" is not the labels on the boards, but the order in which data is read 
//  - function returns the coord of the bar wrt reference point of the top/bottom 
//    hodoscope, i.e., hbotx, hboty, hbotz
TVector3 dataToBar(int pack, int d)
{

  TVector3 cordBar(-999,-999,-999);
  
  if(d<0 || d>7)  
  {
    cout << "[Error] wrong channel number" << endl;
    return cordBar;
  }
  if(pack<0 || pack>10)  
  {
    cout << "[Error] wrong pack number" << endl;
    return cordBar;
  }
/*
     hbotx+2.1*4-i*2.1-1.05,hboty,hbotz));
     hbotx+2.1*4-i*2.1-1.05,hboty,hbotz+2.1));
     hbotx,hboty+i*2.1,hbotz-5));
     hbotx,hboty+i*2.1,hbotz-5+2.1));
*/ 
  //  
  // bottom
  //  
  if(pack==0) // vertical 
  { 
    if(d==0) cordBar.SetXYZ(-1*hbotx-2*3-2/2-0.2*3, hboty+0, hbotz+0.5+2*1+2/2+0.2*1);    
    if(d==1) cordBar.SetXYZ(-1*hbotx-2*2-2/2-0.2*2, hboty+0, hbotz+0.5+2*1+2/2+0.2*1);    
    if(d==2) cordBar.SetXYZ(-1*hbotx-2*1-2/2-0.2*1, hboty+0, hbotz+0.5+2*1+2/2+0.2*1);    
    if(d==3) cordBar.SetXYZ(-1*hbotx-2*0-2/2-0.2*0, hboty+0, hbotz+0.5+2*1+2/2+0.2*1);    
    if(d==4) cordBar.SetXYZ(-1*hbotx-2*3-2/2-0.2*3, hboty+0, hbotz+0.5+2/2);               
    if(d==5) cordBar.SetXYZ(-1*hbotx-2*2-2/2-0.2*2, hboty+0, hbotz+0.5+2/2);             
    if(d==6) cordBar.SetXYZ(-1*hbotx-2*1-2/2-0.2*1, hboty+0, hbotz+0.5+2/2);               
    if(d==7) cordBar.SetXYZ(-1*hbotx-2*0-2/2-0.2*0, hboty+0, hbotz+0.5+2/2);              
  }
  else if(pack==1) // vertical 
  { 
    if(d==0) cordBar.SetXYZ(hbotx+2*0+2/2+0.2*0, hboty+0, hbotz+0.5+2*1+2/2+0.2*1);    
    if(d==1) cordBar.SetXYZ(hbotx+2*1+2/2+0.2*1, hboty+0, hbotz+0.5+2*1+2/2+0.2*1);    
    if(d==2) cordBar.SetXYZ(hbotx+2*2+2/2+0.2*2, hboty+0, hbotz+0.5+2*1+2/2+0.2*1);    
    if(d==3) cordBar.SetXYZ(hbotx+2*3+2/2+0.2*3, hboty+0, hbotz+0.5+2*1+2/2+0.2*1);    
    if(d==4) cordBar.SetXYZ(hbotx+2*0+2/2+0.2*0, hboty+0, hbotz+0.5+2/2);            
    if(d==5) cordBar.SetXYZ(hbotx+2*1+2/2+0.2*1, hboty+0, hbotz+0.5+2/2);            
    if(d==6) cordBar.SetXYZ(hbotx+2*2+2/2+0.2*2, hboty+0, hbotz+0.5+2/2);            
    if(d==7) cordBar.SetXYZ(hbotx+2*3+2/2+0.2*3, hboty+0, hbotz+0.5+2/2);            
  }
  else if(pack==2)  // horizontal
  { 
    if(d==0) cordBar.SetXYZ(hbotx+0, hboty+2*7+0.2*7, hbotz-2*1-2/2-0.2*1);    
    if(d==1) cordBar.SetXYZ(hbotx+0, hboty+2*6+0.2*6, hbotz-2*1-2/2-0.2*1);    
    if(d==2) cordBar.SetXYZ(hbotx+0, hboty+2*5+0.2*5, hbotz-2*1-2/2-0.2*1);    
    if(d==3) cordBar.SetXYZ(hbotx+0, hboty+2*4+0.2*4, hbotz-2*1-2/2-0.2*1);    
    if(d==4) cordBar.SetXYZ(hbotx+0, hboty+2*7+0.2*7, hbotz-2*0-2/2-0.2*0);    
    if(d==5) cordBar.SetXYZ(hbotx+0, hboty+2*6+0.2*6, hbotz-2*0-2/2-0.2*0);    
    if(d==6) cordBar.SetXYZ(hbotx+0, hboty+2*5+0.2*5, hbotz-2*0-2/2-0.2*0);    
    if(d==7) cordBar.SetXYZ(hbotx+0, hboty+2*4+0.2*4, hbotz-2*0-2/2-0.2*0);    
  }
  else if(pack==3) // horizontal
  { 
    if(d==0) cordBar.SetXYZ(hbotx+0, hboty+2*3+0.2*3, hbotz-2*1-2/2-0.2*1);
    if(d==1) cordBar.SetXYZ(hbotx+0, hboty+2*2+0.2*2, hbotz-2*1-2/2-0.2*1);
    if(d==2) cordBar.SetXYZ(hbotx+0, hboty+2*1+0.2*1, hbotz-2*1-2/2-0.2*1);
    if(d==3) cordBar.SetXYZ(hbotx+0, hboty+2*0+0.2*0, hbotz-2*1-2/2-0.2*1);
    if(d==4) cordBar.SetXYZ(hbotx+0, hboty+2*3+0.2*3, hbotz-2*0-2/2-0.2*0);    
    if(d==5) cordBar.SetXYZ(hbotx+0, hboty+2*2+0.2*2, hbotz-2*0-2/2-0.2*0);    
    if(d==6) cordBar.SetXYZ(hbotx+0, hboty+2*1+0.2*1, hbotz-2*0-2/2-0.2*0);    
    if(d==7) cordBar.SetXYZ(hbotx+0, hboty+2*0+0.2*0, hbotz-2*0-2/2-0.2*0);    
  }
  //  
  // top 
  //  
  else if(pack==4)  // horizontal: note that pack4 is down 
  { 
    if(d==0) cordBar.SetXYZ(hbotx+0, hboty+2*3+0.2*3, htopz-5-2*0-2/2-0.2*1);
    if(d==1) cordBar.SetXYZ(hbotx+0, hboty+2*2+0.2*2, htopz-5-2*0-2/2-0.2*1);
    if(d==2) cordBar.SetXYZ(hbotx+0, hboty+2*1+0.2*1, htopz-5-2*0-2/2-0.2*1);
    if(d==3) cordBar.SetXYZ(hbotx+0, hboty+2*0+0.2*0, htopz-5-2*0-2/2-0.2*1);
    if(d==4) cordBar.SetXYZ(hbotx+0, hboty+2*3+0.2*3, htopz-5-2*1-2/2-0.2*0);       
    if(d==5) cordBar.SetXYZ(hbotx+0, hboty+2*2+0.2*2, htopz-5-2*1-2/2-0.2*0);       
    if(d==6) cordBar.SetXYZ(hbotx+0, hboty+2*1+0.2*1, htopz-5-2*1-2/2-0.2*0);       
    if(d==7) cordBar.SetXYZ(hbotx+0, hboty+2*0+0.2*0, htopz-5-2*1-2/2-0.2*0);       
  }
  else if(pack==5)  // horizontal 
  { 
    if(d==0) cordBar.SetXYZ(hbotx+0, hboty+2*7+0.2*7, htopz-5-2*0-2/2-0.2*1);
    if(d==1) cordBar.SetXYZ(hbotx+0, hboty+2*6+0.2*6, htopz-5-2*0-2/2-0.2*1);
    if(d==2) cordBar.SetXYZ(hbotx+0, hboty+2*5+0.2*5, htopz-5-2*0-2/2-0.2*1);
    if(d==3) cordBar.SetXYZ(hbotx+0, hboty+2*4+0.2*4, htopz-5-2*0-2/2-0.2*1);
    if(d==4) cordBar.SetXYZ(hbotx+0, hboty+2*7+0.2*7, htopz-5-2*1-2/2-0.2*0);        
    if(d==5) cordBar.SetXYZ(hbotx+0, hboty+2*6+0.2*6, htopz-5-2*1-2/2-0.2*0);        
    if(d==6) cordBar.SetXYZ(hbotx+0, hboty+2*5+0.2*5, htopz-5-2*1-2/2-0.2*0);        
    if(d==7) cordBar.SetXYZ(hbotx+0, hboty+2*4+0.2*4, htopz-5-2*1-2/2-0.2*0);        
  }
  else if(pack==6)  // vertical 
  { 
    if(d==0) cordBar.SetXYZ(htopx+2*3+2/2+0.2*3, htopy+0, htopz-10-0.5-2*1-1-0.2*1);    
    if(d==1) cordBar.SetXYZ(htopx+2*2+2/2+0.2*2, htopy+0, htopz-10-0.5-2*1-1-0.2*1);    
    if(d==2) cordBar.SetXYZ(htopx+2*1+2/2+0.2*1, htopy+0, htopz-10-0.5-2*1-1-0.2*1);    
    if(d==3) cordBar.SetXYZ(htopx+2*0+2/2+0.2*0, htopy+0, htopz-10-0.5-2*1-1-0.2*1);    
    if(d==4) cordBar.SetXYZ(htopx+2*3+2/2+0.2*3, htopy+0, htopz-10-0.5-2*0-1-0.2*0);    
    if(d==5) cordBar.SetXYZ(htopx+2*2+2/2+0.2*2, htopy+0, htopz-10-0.5-2*0-1-0.2*0);    
    if(d==6) cordBar.SetXYZ(htopx+2*1+2/2+0.2*1, htopy+0, htopz-10-0.5-2*0-1-0.2*0);    
    if(d==7) cordBar.SetXYZ(htopx+2*0+2/2+0.2*0, htopy+0, htopz-10-0.5-2*0-1-0.2*0); 
  }
  else if(pack==7)  // vertical 
  { 
    if(d==0) cordBar.SetXYZ(-1*htopx-2*0-2/2-0.2*0, htopy+0, htopz-10-0.5-2*1-1-0.2*1);    
    if(d==1) cordBar.SetXYZ(-1*htopx-2*1-2/2-0.2*1, htopy+0, htopz-10-0.5-2*1-1-0.2*1);    
    if(d==2) cordBar.SetXYZ(-1*htopx-2*2-2/2-0.2*2, htopy+0, htopz-10-0.5-2*1-1-0.2*1);    
    if(d==3) cordBar.SetXYZ(-1*htopx-2*3-2/2-0.2*3, htopy+0, htopz-10-0.5-2*1-1-0.2*1);    
    if(d==4) cordBar.SetXYZ(-1*htopx-2*0-2/2-0.2*0, htopy+0, htopz-10-0.5-2*0-1-0.2*0);    
    if(d==5) cordBar.SetXYZ(-1*htopx-2*1-2/2-0.2*1, htopy+0, htopz-10-0.5-2*0-1-0.2*0);    
    if(d==6) cordBar.SetXYZ(-1*htopx-2*2-2/2-0.2*2, htopy+0, htopz-10-0.5-2*0-1-0.2*0);    
    if(d==7) cordBar.SetXYZ(-1*htopx-2*3-2/2-0.2*3, htopy+0, htopz-10-0.5-2*0-1-0.2*0); 
  }
  else if(pack==8)  // track pack 
  { 
    if(d==0) cordBar.SetXYZ(hbotx, 17+1+2*1+0.2*1, 180-53-2/2-2*0+0.2*0);
    if(d==1) cordBar.SetXYZ(hbotx, 17+1+2*1+0.2*1, 180-53-2/2-2*1+0.2*1);
    if(d==2) cordBar.SetXYZ(hbotx, 17+1+2*1+0.2*1, 180-53-2/2-2*2+0.2*2);
    if(d==3) cordBar.SetXYZ(hbotx, 17+1+2*1+0.2*1, 180-53-2/2-2*3+0.2*3);
    if(d==4) cordBar.SetXYZ(hbotx, 17+1+2*0+0.2*0, 180-53-2/2-2*0+0.2*0);        
    if(d==5) cordBar.SetXYZ(hbotx, 17+1+2*0+0.2*0, 180-53-2/2-2*1+0.2*1);        
    if(d==6) cordBar.SetXYZ(hbotx, 17+1+2*0+0.2*0, 180-53-2/2-2*2+0.2*2);        
    if(d==7) cordBar.SetXYZ(hbotx, 17+1+2*0+0.2*0, 180-53-2/2-2*3+0.2*3);        
  }
  else if(pack==9)  // track pack 
  { 
    if(d==0) cordBar.SetXYZ(hbotx, -22.5-1+2*1+0.2*1, 180-118+2/2+2*0+0.2*0);
    if(d==1) cordBar.SetXYZ(hbotx, -22.5-1+2*1+0.2*1, 180-118+2/2+2*1+0.2*1);
    if(d==2) cordBar.SetXYZ(hbotx, -22.5-1+2*1+0.2*1, 180-118+2/2+2*2+0.2*2);
    if(d==3) cordBar.SetXYZ(hbotx, -22.5-1+2*1+0.2*1, 180-118+2/2+2*3+0.2*3);
    if(d==4) cordBar.SetXYZ(hbotx, -22.5-1+2*0+0.2*0, 180-118+2/2+2*0+0.2*0);        
    if(d==5) cordBar.SetXYZ(hbotx, -22.5-1+2*0+0.2*0, 180-118+2/2+2*1+0.2*1);        
    if(d==6) cordBar.SetXYZ(hbotx, -22.5-1+2*0+0.2*0, 180-118+2/2+2*2+0.2*2);        
    if(d==7) cordBar.SetXYZ(hbotx, -22.5-1+2*0+0.2*0, 180-118+2/2+2*3+0.2*3);        
  }
  else if(pack==10)  // track pack 
  { 
    if(d==0) cordBar.SetXYZ(hbotx, 17+1+2*0+0.2*0, 180-154+2/2+2*0+0.2*0);
    if(d==1) cordBar.SetXYZ(hbotx, 17+1+2*0+0.2*0, 180-154+2/2+2*1+0.2*1);
    if(d==2) cordBar.SetXYZ(hbotx, 17+1+2*0+0.2*0, 180-154+2/2+2*2+0.2*2);
    if(d==3) cordBar.SetXYZ(hbotx, 17+1+2*0+0.2*0, 180-154+2/2+2*3+0.2*3);
    if(d==4) cordBar.SetXYZ(hbotx, 17+1+2*1+0.2*1, 180-154+2/2+2*0+0.2*0);        
    if(d==5) cordBar.SetXYZ(hbotx, 17+1+2*1+0.2*1, 180-154+2/2+2*1+0.2*1);        
    if(d==6) cordBar.SetXYZ(hbotx, 17+1+2*1+0.2*1, 180-154+2/2+2*2+0.2*2);        
    if(d==7) cordBar.SetXYZ(hbotx, 17+1+2*1+0.2*1, 180-154+2/2+2*3+0.2*3);        
  }
  
  return cordBar;
}


std::vector<TVector3> getHitList(TString strData, bool isVertical)
{
  // remove space between packs
  strData.ReplaceAll(" ", "");
 
  std::vector<TVector3> hitList;
 
  for(int i=0; i<8*11; i++)
  { 
    int pack = i/8;
    int d = i%8; 

    if(isVertical && (pack==2 || pack==3 || pack==4 || pack==5 || pack>=8)) continue;
    if(!isVertical && (pack==0 || pack==1 || pack==6 || pack==7)) continue;
    
    if(strData[i]=='1')  
    {
      //cout << pack << " " << d << " " << strData[i] << endl; // FIXME
      hitList.push_back(dataToBar(pack,d)); 
    }
  }
  
  return hitList;
}


/////////////////////////////////////////////////////////////////////////////////
void milliDspOne(TString time, TString run, TString file, TString event, TString beam, TString mqData, TString hsData, bool onlyMQ, bool drawHits=true)
{ 
  TGeoManager *geom = new TGeoManager("geom","My 3D Project");

  //------------------Creat materials-----------------------------
  TGeoMaterial *vacuum = new TGeoMaterial("vacuum",0,0,0);
  TGeoMaterial *Fe = new TGeoMaterial("Fe",55.84,26.7,7.87);
  TGeoMaterial *Cu = new TGeoMaterial("Cu",63.549,29,8.92);
  TGeoMaterial *Fe_transp = new TGeoMaterial("Fe_transp",55.84,26.7,7.87);
  Fe_transp->SetTransparency(30);

  //------------------Creat media----------------------------------
  TGeoMedium *Air = new TGeoMedium("Air",0,vacuum);
  TGeoMedium *Iron = new TGeoMedium("Iron",1,Fe);
  TGeoMedium *sheet_mat = new TGeoMedium("sheet_mat",1,Fe_transp);
  TGeoMedium *slab_mat = new TGeoMedium("slab_mat",1,Fe_transp);

  //------------------Create TOP volume----------------------------
  TGeoVolume *top = geom->MakeBox("top",Air,100,100,100);
  geom->SetTopVolume(top);
  geom->SetTopVisible(0);
  // If you want to see the boundary, please input the number, 1 instead of 0.
  // Like this, geom->SetTopVisible(1);

  //------------------ Create support structure ----------------------------
  TGeoVolume *tube=geom->MakeBox("tube",Iron,7.5,5,180);
  tube->SetLineColor(19);  
  top->AddNodeOverlap(tube,1,new TGeoTranslation(0,-12.5,0));

  //------------------ Data ---------------------------- 
  gSystem->mkdir(Form("fig/run%s_file%s_event%s",run.Data(), file.Data(), event.Data()));
  
  cout << "time: " << time << endl; 
  cout << "mq data: " << mqData << endl; 
  cout << "hs data: " << hsData << endl; 
  
  // MQ hits 
  vector<int> milliHits;  
  for(int i=0; i<32; i++) milliHits.push_back(mqData[i]=='1'?1:0);  

  //------------------ Create milliqan ----------------------------
  
  //
  // bars
  //
  TGeoVolume *mbar=geom->MakeBox("mbar",Iron,2.5,2.5,40); 
  TGeoVolume *pmt=geom->MakeTube("pmt",Iron,0,2.5,10);
  TGeoVolume *slab=geom->MakeBox("slab",slab_mat,2.54*8/2,2.54*12/2,2.54/2);
  TGeoVolume *lead=geom->MakeBox("lead",Iron,10,10,2.5);
  TGeoVolume *hsheet=geom->MakeBox("hsheet",sheet_mat,7*2.54/2, 0.274*2.54/2, 40*2.54/2);
  TGeoVolume *vsheet=geom->MakeBox("vsheet",sheet_mat,0.274*2.54/2, 7*2.54/2, 40*2.54/2);
  // can visulize the pulse height  
  //TGeoVolume *pmt_ch[12];
  //for(int i=0; i<12; i++)x pmt_ch[i] = geom->MakeTube(Form("pmt_ch%i",i),Iron,0,2.5,8);
  if(drawHits)
  {
      mbar->SetLineColor(38); 
      // layer 1 
      if(showRow1)
      {
        if(milliHits.at(8))  top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,0,120+10+2));  // 0.8
        if(milliHits.at(9))  top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,0,120+10+2));   // 0.9
      } 
      if(showRow2)
      {
        if(milliHits.at(24)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,6,120+10+2));  // 1.8
        if(milliHits.at(25)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,6,120+10+2));   // 1.9
      } 
      if(showRow3)
      {
        if(milliHits.at(0))  top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,12,120+10+2)); // 0.0
        if(milliHits.at(1))  top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,12,120+10+2));  // 0.1
      } 
      // layer 2 
      if(showRow1)
      {
        if(milliHits.at(12)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,0,0+10));    // 0.12
        if(milliHits.at(13)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,0,0+10));     // 0.13
      } 
      if(showRow2)
      {
        if(milliHits.at(16)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,6,0+10));    // 1.0
        if(milliHits.at(17)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,6,0+10));     // 1.1
      } 
      if(showRow3)
      {
        if(milliHits.at(6))  top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,12,0+10));   // 0.6
        if(milliHits.at(7))  top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,12,0+10));    // 0.7
      } 
      // layer 3 
      if(showRow1)
      {
        if(milliHits.at(4))  top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,0,-120+10-5));  // 0.4
        if(milliHits.at(5))  top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,0,-120+10-5));   // 0.5
      } 
      if(showRow2)
      {
        if(milliHits.at(22)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,6,-120+10-5)); // 1.6
        if(milliHits.at(23)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,6,-120+10-5));  // 1.7
      } 
      if(showRow3)
      {
        if(milliHits.at(2))  top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,12,-120+10-5)); // 0.2
        if(milliHits.at(3))  top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,12,-120+10-5));  // 0.3
      } 
      
      pmt->SetLineColor(15);  
      // layer 1 
      if(showRow1)
      {
        if(milliHits.at(8))  top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,0,120-40-10+10+2));  // 0.8
        if(milliHits.at(9))  top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,0,120-40-10+10+2));   // 0.9
      } 
      if(showRow2)
      {
        if(milliHits.at(24)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,6,120-40-10+10+2));  // 1.8
        if(milliHits.at(25)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,6,120-40-10+10+2));   // 1.9
      } 
      if(showRow3)
      {
        if(milliHits.at(0))  top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,12,120-40-10+10+2)); // 0.0
        if(milliHits.at(1))  top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,12,120-40-10+10+2));  // 0.1
      } 
      // layer 2 
      if(showRow1)
      {
        if(milliHits.at(12)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,0,-40-10+10));  // 0.12
        if(milliHits.at(13)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,0,-40-10+10));   // 0.13
      } 
      if(showRow2)
      {
        if(milliHits.at(16)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,6,-40-10+10));  // 1.0
        if(milliHits.at(17)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,6,-40-10+10));   // 1.1
      } 
      if(showRow3)
      {
        if(milliHits.at(6))  top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,12,-40-10+10)); // 0.6
        if(milliHits.at(7))  top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,12,-40-10+10));  // 0.7
      } 
      // layer 3 
      if(showRow1)
      {
        if(milliHits.at(4))  top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,0,-120-40-10+10-5));  // 0.4
        if(milliHits.at(5))  top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,0,-120-40-10+10-5));   // 0.5
      } 
      if(showRow2)
      {
        if(milliHits.at(22)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,6,-120-40-10+10-5)); // 1.6
        if(milliHits.at(23)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,6,-120-40-10+10-5));  // 1.7
      } 
      if(showRow3)
      {
        if(milliHits.at(2))  top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,12,-120-40-10+10-5)); // 0.2
        if(milliHits.at(3))  top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,12,-120-40-10+10-5));  // 0.3
      } 
  }
  else 
  { 
      mbar->SetLineColor(12); 
      // bottom pack
      top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,0,-120+10));
      top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,0,-120+10));
      top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,6,-120+10));
      top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,6,-120+10));
      // middle pack
      top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,0,0+10));
      top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,0,0+10));
      top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,6,0+10));
      top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,6,0+10));
      // top pack
      top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,0,120+10));
      top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,0,120+10));
      top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,6,120+10));
      top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,6,120+10));
      
      pmt->SetLineColor(15);  
      // bottom pack
      top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,0,-120-40-8+10));
      top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,0,-120-40-8+10));
      top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,6,-120-40-8+10));
      top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,6,-120-40-8+10));
      // middle pack
      top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,0,-40-8+10));
      top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,0,-40-8+10));
      top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,6,-40-8+10));
      top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,6,-40-8+10));
      // middle pack
      top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,0,120-40-8+10));
      top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,0,120-40-8+10));
      top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,6,120-40-8+10));
      top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,6,120-40-8+10));

  } 
  
  // lead bricks
  if(showBrick)
  {
    lead->SetLineColor(15);  
    top->AddNodeOverlap(lead,1,new TGeoTranslation(0,5,-68));
    top->AddNodeOverlap(lead,1,new TGeoTranslation(0,5,57));
  }

  // rotation matrix for slab/sheet pmts
  // TGeoRotation (const char *name, Double_t phi, Double_t theta, Double_t psi)
  // Euler angles: https://en.wikipedia.org/wiki/Euler_angles
  TGeoRotation   *rot_h = new TGeoRotation("rot_h", 90., 90., 0.);
  TGeoRotation   *rot_v = new TGeoRotation("rot_v", 0., 90., 0.);
  TGeoRotation   *rot_vp = new TGeoRotation("rot_vp", 10., 90., 0.);
  TGeoRotation   *rot_vm = new TGeoRotation("rot_vm", -10., 90., 0.);
  TGeoRotation   *rot_sheetp = new TGeoRotation("rot_sheetp", 0., 0., 10.);
  TGeoRotation   *rot_sheetm = new TGeoRotation("rot_sheetm", 0., 0., -10.);
 
  if(showSlab)
  {
    slab->SetLineColor(89);  
    if(milliHits.at(21)) top->AddNodeOverlap(slab,1,new TGeoTranslation(0,7.5,-181.5)); // slab3 1.5 
    if(milliHits.at(28)) top->AddNodeOverlap(slab,1,new TGeoTranslation(0,7.5,-72.5));  // slab2 1.12
    if(milliHits.at(20)) top->AddNodeOverlap(slab,1,new TGeoTranslation(0,7.5,53));   // slab1 1.4
    if(milliHits.at(18)) top->AddNodeOverlap(slab,1,new TGeoTranslation(0,7.5,174));  // slab0 1.2
  }
  
  if(showSheet)
  {
    hsheet->SetLineColor(30);  
    vsheet->SetLineColor(30);  
    // layer 1
    if(milliHits.at(27)) top->AddNodeOverlap(vsheet,1,new TGeoCombiTrans(-10.5+2, 10.75*2.54/2-7, 120+2, rot_sheetm)); // 1.11
    if(milliHits.at(10)) top->AddNodeOverlap(hsheet,1,new TGeoTranslation(0,16,120+2));                                // 0.10
    if(milliHits.at(29)) top->AddNodeOverlap(vsheet,1,new TGeoCombiTrans(10.5-2, 10.75*2.54/2-7, 120+2, rot_sheetp));  // 1.13
    // layer 2 
    if(milliHits.at(30)) top->AddNodeOverlap(vsheet,1,new TGeoCombiTrans(-10.5+2, 10.75*2.54/2-7, 0, rot_sheetm));   // 1.14
    if(milliHits.at(11)) top->AddNodeOverlap(hsheet,1,new TGeoTranslation(0,16,0));                                  // 0.11
    if(milliHits.at(19)) top->AddNodeOverlap(vsheet,1,new TGeoCombiTrans(10.5-2, 10.75*2.54/2-7, 0, rot_sheetp));    // 1.3
    // layer 3 
    if(milliHits.at(31)) top->AddNodeOverlap(vsheet,1,new TGeoCombiTrans(-10.5+2, 10.75*2.54/2-7, -120-5, rot_sheetm)); // 1.15
    if(milliHits.at(14)) top->AddNodeOverlap(hsheet,1,new TGeoTranslation(0,16,-120-5));                                // 0.14
    if(milliHits.at(26)) top->AddNodeOverlap(vsheet,1,new TGeoCombiTrans(10.5-2, 10.75*2.54/2-7, -120-5, rot_sheetp));  // 1.10
  } 
  
  //------------------ Create hodoscope ------------------------------- 
  if(showHS) 
  {
    if(drawHits) 
    { 
      //-------------------------------------------------
      // Mark bars with hits 
      //-------------------------------------------------

      // get a list of non-zero channels
      std::vector<TVector3> vhitList = getHitList(hsData, true); 
      std::vector<TVector3> hhitList = getHitList(hsData, false); 

      // vertical bars
      TGeoVolume *vhhit=geom->MakeBox("vhhit",Iron,1,22.5,1);
      vhhit->SetLineColor(46);  
      // horizontal bars
      TGeoVolume *hhhit=geom->MakeBox("hhhit",Iron,22.5,1,1);
      hhhit->SetLineColor(46);  

      for(int i=0; i<hhitList.size(); i++)
      {
        top->AddNodeOverlap(hhhit,1,new TGeoTranslation(hhitList.at(i).X(), hhitList.at(i).Y(), hhitList.at(i).Z()));
        cout << hhitList.at(i).X() << " " <<  hhitList.at(i).Y() << " " << hhitList.at(i).Z() << endl;
      }
      for(int i=0; i<vhitList.size(); i++) 
      {
        top->AddNodeOverlap(vhhit,1,new TGeoTranslation(vhitList.at(i).X(), vhitList.at(i).Y(), vhitList.at(i).Z()));
        cout << vhitList.at(i).X() << " " <<  vhitList.at(i).Y() << " " << vhitList.at(i).Z() << endl;
      } 
    } 
    else 
    {
      // vertical bars
      TGeoVolume *vhbar=geom->MakeBox("vhbar",Iron,1,22.5,1);
      vhbar->SetLineColor(12);  
      // horizontal bars
      TGeoVolume *hhbar=geom->MakeBox("hhbar",Iron,22.5,1,1);
      hhbar->SetLineColor(12);  

      // bottom  
      for(int i=0; i<8; i++) 
      {
        top->AddNodeOverlap(vhbar,1,new TGeoTranslation(hbotx+2.1*4-i*2.1-1.05,hboty,hbotz));
        top->AddNodeOverlap(vhbar,1,new TGeoTranslation(hbotx+2.1*4-i*2.1-1.05,hboty,hbotz+2.1));
      }
      for(int i=0; i<4; i++) 
      {
        top->AddNodeOverlap(hhbar,1,new TGeoTranslation(hbotx,hboty+i*2.1,hbotz-5));
        top->AddNodeOverlap(hhbar,1,new TGeoTranslation(hbotx,hboty+i*2.1,hbotz-5+2.1));
      }

      // top 
      for(int i=0; i<4; i++) 
      {
        top->AddNodeOverlap(vhbar,1,new TGeoTranslation(htopx+2.1*2-i*2.1-1.05,htopy,htopz-8));
        top->AddNodeOverlap(vhbar,1,new TGeoTranslation(htopx+2.1*2-i*2.1-1.05,htopy,htopz-8+2.1));
      }
      for(int i=0; i<4; i++) 
      {
        top->AddNodeOverlap(hhbar,1,new TGeoTranslation(htopx,htopy+i*2.1,htopz-3));
        top->AddNodeOverlap(hhbar,1,new TGeoTranslation(htopx,htopy+i*2.1,htopz-3+2.1));
      }
    }
  } 
  
  // trackpacks
  if(showPack) 
  {
      TGeoVolume *hhhit=geom->MakeBox("hhhit",Iron,22.5,1,1);
      hhhit->SetLineColor(46);  
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, 17,     40));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, 17,     40-2.1*1));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, 17,     40-2.1*2));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, 17,     40-2.1*3));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, 17+2.1, 40));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, 17+2.1, 40-2.1*1));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, 17+2.1, 40-2.1*2));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, 17+2.1, 40-2.1*3));

      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, -20,     80));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, -20,     80-2.1*1));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, -20,     80-2.1*2));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, -20,     80-2.1*3));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, -20-2.1, 80));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, -20-2.1, 80-2.1*1));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, -20-2.1, 80-2.1*2));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, -20-2.1, 80-2.1*3));
      
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, 17,     120));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, 17,     120-2.1*1));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, 17,     120-2.1*2));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, 17,     120-2.1*3));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, 17+2.1, 120));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, 17+2.1, 120-2.1*1));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, 17+2.1, 120-2.1*2));
      top->AddNodeOverlap(hhhit,1,new TGeoTranslation(0, 17+2.1, 120-2.1*3));
  }
  
  //------------------------------- 
  //  Draw tracks 
  //------------------------------- 
  
  // 1. do the fit
  std::vector<int> hs_data;
  std::vector<int> tp_data;
  int n_hs_ver=0;
  int n_hs_hor=0;
  int n_hs_bot=0;
  int n_hs_top=0;
  for(int i=0; i<64; i++) 
  {
    if(hsData[i]=='1') hs_data.push_back(i);
    if((i<16 || i>=48) && hsData[i]=='1') n_hs_ver++; 
    if((i>=16 && i<48) && hsData[i]=='1') n_hs_hor++; 
    if(i<32 && hsData[i]=='1') n_hs_bot++; 
    if(i>=32 && hsData[i]=='1') n_hs_top++; 
  }
  for(int i=65; i<89; i++) 
  {
    if(hsData[i]=='1') tp_data.push_back(i-65);
  }
  cout << "HS data size: " << hs_data.size() << endl;
  cout << "  n_hs_ver: " << n_hs_ver << endl;
  cout << "  n_hs_hor: " << n_hs_hor << endl;
  cout << "  n_hs_bot: " << n_hs_bot << endl;
  cout << "  n_hs_top: " << n_hs_top << endl;
  cout << "TP data size: " << tp_data.size() << endl;

  // do fit only when there's at least one this in each side of hs 
  bool doTrackFit = false;
  doTrackFit = n_hs_ver>1 && n_hs_hor>1; 
  //doTrackFit = n_hs_bot>1 && n_hs_top>1; 

  TPolyLine3D* track;
  
  if(doTrackFit) 
  {
    // arrays for fit
    int xz_n=0; // vertical bars
    int yz_n=0; // horizontal bars
    for(int i=0; i<hs_data.size(); i++) 
    { 
      if(hs_data.at(i)>=16 && hs_data.at(i)<48) yz_n++;
      else xz_n++; 
    }
    Double_t xz_x[xz_n], xz_y[xz_n], xz_z[xz_n];
    Double_t xz_ex[xz_n], xz_ey[xz_n], xz_ez[xz_n];
    Double_t yz_x[yz_n], yz_y[yz_n], yz_z[yz_n];
    Double_t yz_ex[yz_n], yz_ey[yz_n], yz_ez[yz_n];

    // 1. convert to physical channels 
    // Hodoscope 
    // vertical 
    cout << "Number of xz hits: " << xz_n << endl; 
    int xz_i = 0;
    for(int i=0; i<hs_data.size(); i++)
    { 
      std::vector<int> phys_ch = convertRawToPhysCh(hs_data.at(i), true);
      std::vector<float> coord_ch = convertPhysChToCoord(phys_ch, true);
      
      if(hs_data.at(i)<16 || hs_data.at(i)>=48)
      { 
        xz_x[xz_i]  = coord_ch[0];
        xz_y[xz_i]  = coord_ch[1];
        xz_z[xz_i]  = coord_ch[2];
        xz_ex[xz_i] = coord_ch[3];
        xz_ey[xz_i] = coord_ch[4];
        xz_ez[xz_i] = coord_ch[5];
        cout << xz_x[xz_i] << " " << xz_y[xz_i] << " " << xz_z[xz_i] << endl; 
        xz_i++;
      }
      phys_ch.clear(); 
      coord_ch.clear(); 
    }
    // horizontal 
    cout << "Number of yz hits: " << yz_n << endl; 
    int yz_i = 0;
    for(int i=0; i<hs_data.size(); i++)
    { 
      std::vector<int> phys_ch = convertRawToPhysCh(hs_data.at(i), true);
      //cout << hs_data.at(i) << " :: " << phys_ch[0] << " " << phys_ch[1] << " " << phys_ch[2] << endl; 
      std::vector<float> coord_ch = convertPhysChToCoord(phys_ch, true);
      //cout << coord_ch[0] << " +/- " << coord_ch[3] << endl; 
      //cout << coord_ch[1] << " +/- " << coord_ch[4] << endl; 
      //cout << coord_ch[2] << " +/- " << coord_ch[5] << endl; 
      //cout << endl; 
      if(hs_data.at(i)>=16 && hs_data.at(i)<48)
      {
        yz_x[yz_i]  = coord_ch[0];
        yz_y[yz_i]  = coord_ch[1];
        yz_z[yz_i]  = coord_ch[2];
        yz_ex[yz_i] = coord_ch[3];
        yz_ey[yz_i] = coord_ch[4];
        yz_ez[yz_i] = coord_ch[5];
        cout << yz_x[yz_i] << " " << yz_y[yz_i] << " " << yz_z[yz_i] << endl;  
        yz_i++;
      }
      phys_ch.clear(); 
      coord_ch.clear(); 
    }
    
    cout << " -- xz -- " << endl;
    for(int i=0; i<xz_n; i++) { cout << xz_n << " :: " << xz_x[i] << " " << xz_y[i] << " " << xz_z[i] << endl; }  
    cout << " -- yz -- " << endl;
    for(int i=0; i<yz_n; i++) { cout << yz_n << " :: " << yz_x[i] << " " << xz_y[i] << " " << yz_z[i] << endl; } 
   
    // Trackpacks   
    //for(int i=0; i<24; i++)
    //{ 
    //  std::vector<int> phys_ch = convertRawToPhysCh(i, false);
    //  cout << i << " :: " << phys_ch[0] << " " << phys_ch[1] << " " << phys_ch[2] << endl; 
    //}
  
    //
    // 2. do the fit 
    //
   
    // x-z fit: vertical bars    
    TGraphErrors *g_xz = new TGraphErrors(xz_n, xz_x, xz_z, xz_ex, xz_ez); 
    TF1 *f_xz = new TF1("f_xz","x*[0]+[1]", -40, 40);  
    if(xz_n>1) g_xz->Fit("f_xz");
    // y-z fit: horizontal bars  
    TGraphErrors *g_yz = new TGraphErrors(yz_n, yz_y, yz_z, yz_ey, yz_ez); 
    TF1 *f_yz = new TF1("f_yz","x*[0]+[1]", -40, 40);  
    if(yz_n>1) g_yz->Fit("f_yz");
  
    cout << " -- Fit results -- " << endl;
    cout << " xz slope: " << f_xz->GetParameter(0) << ", intercept: " << f_xz->GetParameter(1) << " " 
         << f_xz->GetChisquare() << "/" << f_xz->GetNDF() << endl;
    cout << " yz slope: " << f_yz->GetParameter(0) << ", intercept:" << f_yz->GetParameter(1) << " " 
         << f_yz->GetChisquare() << "/" << f_yz->GetNDF() << endl;
     
  
    // 2. draw the fitted line  
    double parFit[4]={-1000,1000000,-1000,1000000};
    if(xz_n>1)
    {
      parFit[0] =  -1.*f_xz->GetParameter(1)/f_xz->GetParameter(0);  
      parFit[1] =  1./f_xz->GetParameter(0);  
    }
    if(yz_n>1)
    {
      parFit[2] =  -1.*f_yz->GetParameter(1)/f_yz->GetParameter(0);  
      parFit[3] =  1./f_yz->GetParameter(0);
    }
    track = fittedTrack(parFit);

    // TGeoTrack
    TGeoTrack *geo_track = new TGeoTrack(0,-13); 
    fittedTrack(parFit, geo_track); 
    int index = geom->AddTrack(0,-13,geo_track);
    geom->SetTminTmax(-200,200);
    //geom->DrawTracks("");
    
    //fittedTrack(parFit, top, track_dot); 
    int ndiv = 200;
    double t0 = 0; 
    double dt = 200;
    for(int i=0; i<2*ndiv; i++)
    {
      double t = t0 + dt*i/ndiv - dt;
      double x,y,z;
      line(t,parFit,x,y,z);
      TGeoVolume *track_dot = geom->MakeSphere(Form("track_dot_%i",i),Iron,0,0.2);
      track_dot->SetFillColor(kRed);
      track_dot->SetLineColor(kRed);
      track_dot->SetLineWidth(2);
      top->AddNodeOverlap(track_dot,1,new TGeoTranslation(x,y,z));
    }
  }
  // --------------------------------------------------
  
  //------------------draw on GL viewer------------------------------- 
  top->SetVisibility(0);
  //geom->CloseGeometry();
  top->Draw("ogl"); 

  TGLViewer * v = (TGLViewer *)gPad->GetViewer3D();
  // lights 
  TGLLightSet* ls = v->GetLightSet();
  ls->SetLight(TGLLightSet::kLightBottom, kFALSE); 
  // Draw style 
  v->SetLineScale(0.5);
  v->SetStyle(TGLRnrCtx::kOutline); 
  //v->SetStyle(TGLRnrCtx::kWireFrame); 
  //v->SetStyle(TGLRnrCtx::kFill); 
  if(doTrackFit) geom->DrawTracks("/*");
  // Camera 
  v->SetCurrentCamera(TGLViewer::kCameraPerspXOZ); 
  Double_t center[3]={0,0,0}; 
  // side view
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(6, 30., center, 0.01, -3.141592); 
  v->SavePictureUsingFBO(Form("fig/run%s_file%s_event%s/run%s_file%s_event%s_side.png",run.Data(),file.Data(),event.Data(),run.Data(),file.Data(),event.Data()),1000,200,0); 
  // top view
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(6, 30., center, -3.141592/2+0.01, -3.141592); 
  v->SavePictureUsingFBO(Form("fig/run%s_file%s_event%s/run%s_file%s_event%s_top.png",run.Data(),file.Data(),event.Data(),run.Data(),file.Data(),event.Data()),1000,200,0); 
  // perspectivpe view
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(25, 30., center, -0.5, -2); 
  v->SavePictureUsingFBO(Form("fig/run%s_file%s_event%s/run%s_file%s_event%s_pers.png",run.Data(),file.Data(),event.Data(),run.Data(),file.Data(),event.Data()),1000,1000,0.01); 
  // perspectivpe view bottomw component
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(5, 30., center, -1., -1.); 
  v->CurrentCamera().Truck(95,-125); 
  v->SavePicture(Form("fig/run%s_file%s_event%s/run%s_file%s_event%s_pers_bottom.png",run.Data(),file.Data(),event.Data(),run.Data(),file.Data(),event.Data())); 
  // perspectivpe view top component 
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(4, 30., center, -1., -1.); 
  v->CurrentCamera().Truck(-95,125); 
  v->SavePicture(Form("fig/run%s_file%s_event%s/run%s_file%s_event%s_pers_top.png",run.Data(),file.Data(),event.Data(),run.Data(),file.Data(),event.Data())); 
  // side view top component 
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(5, 30., center, 0.01, 0.); 
  v->CurrentCamera().Truck(-180,0); 
  v->SavePicture(Form("fig/run%s_file%s_event%s/run%s_file%s_event%s_side_top.png",run.Data(),file.Data(),event.Data(),run.Data(),file.Data(),event.Data())); 
  // side view bottom component 
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(5, 30., center, 0.01, 0.); 
  v->CurrentCamera().Truck(180,0); 
  v->SavePicture(Form("fig/run%s_file%s_event%s/run%s_file%s_event%s_side_bottom.png",run.Data(),file.Data(),event.Data(),run.Data(),file.Data(),event.Data())); 
  // top view top component 
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(5, 30., center, -3.141592/2+0.01, 0.0); 
  v->CurrentCamera().Truck(-180,0); 
  v->SavePicture(Form("fig/run%s_file%s_event%s/run%s_file%s_event%s_top_top.png",run.Data(),file.Data(),event.Data(),run.Data(),file.Data(),event.Data())); 
  // top view bottom component 
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(5, 30., center, -3.141592/2+0.01, 0.0); 
  v->CurrentCamera().Truck(180,0); 
  v->SavePicture(Form("fig/run%s_file%s_event%s/run%s_file%s_event%s_top_bottom.png",run.Data(),file.Data(),event.Data(),run.Data(),file.Data(),event.Data())); 
  v->DoDraw();  

  // cleaning
  //delete geom;
  //delete v;
} 

// --------------------------------------------------------------------- //
void milliDsp(int FILE=0, int EVENT=0)
{ 
  // 
  if(showBar) 
  { 
    showRow1=true;
    showRow2=true;
    showRow3=true;
  }
  bool onlyMQ=false;
  int id=0;
  
  //
  // root file
  //
  TFile *f = new TFile("skim_hsadded.root");
  TTree *t = (TTree*)f->Get("t"); 
  
  double hs_time=-1;      t->SetBranchAddress("hs_time", &hs_time);
  int run=-1;             t->SetBranchAddress("run",     &run);
  int file=-1;            t->SetBranchAddress("file",    &file);
  int event=-1;           t->SetBranchAddress("event",   &event);
  bool beam=0;            t->SetBranchAddress("beam",    &beam);
  vector<int> *hs=0;      t->SetBranchAddress("hs",      &hs);
  vector<int> *tp=0;      t->SetBranchAddress("tp",      &tp);
  vector<float> *chan=0;  t->SetBranchAddress("chan",    &chan);
  vector<float> *nPE=0;   t->SetBranchAddress("nPE",     &nPE);
 
  //for(int ievt=0; ievt<t->GetEntries(); ievt++)
  for(int ievt=0; ievt<100; ievt++)
  {
    t->GetEntry(ievt); 

    if(FILE!=0 && EVENT!=0 && FILE!=file && EVENT!=event) continue;
 
    //milliDspOne(TString time, TString run, TString file, TString event, TString beam, TString mq_data_str, TString hs_data_str, bool onlyMQ, bool drawHits=true)
    //2222222222.22222  111 111   111 1 00100000000000001010110011001000 0000000010001000000000001000100000000000010001000000000000010001 000000000000000000000000
    
    TString mqData, hsData;  
    for(int i=0; i<32; i++) 
    { 
      TString bit="0";
      for(int imq=0; imq<chan->size(); imq++) 
      { 
        if(chan->at(imq)==i && nPE->at(imq)>nPEcut[i]) 
        {
          bit = "1";
          break;
        }
      }
      mqData = mqData+bit;
    }

    for(int i=0; i<64; i++) 
    { 
      TString bit="0";
      for(int ihs=0; ihs<hs->size(); ihs++) 
      { 
        if(hs->at(ihs)==i) 
        {
          bit = "1";
          break;
        }
      }
      hsData = hsData+bit;
    }
    hsData = hsData+" ";
    for(int i=0; i<24; i++) 
    { 
      TString bit="0";
      for(int itp=0; itp<tp->size(); itp++) 
      { 
        if(tp->at(itp)==i) 
        {
          bit = "1";
          break;
        }
      }
      hsData = hsData+bit;
    }

    if(0) //debug 
    {
      mqData = "11111111111111111111111111111111";
      hsData = "1111111111111111111111111111111111111111111111111111111111111111 111111111111111111111111";
    }
    cout << run << " " << file << " " << event << endl;  
    cout << mqData << endl; 
    cout << hsData << endl; 
   


    //milliDspOne(TString time, TString run, TString file, TString event, TString beam, TString mq_data_str, TString hs_data_str, bool onlyMQ, bool drawHits=true)
    milliDspOne(Form("%lf",hs_time), Form("%d",run), Form("%d",file), Form("%d",event), Form("%d",beam), 
                mqData, hsData, onlyMQ);

    mqData="";
    hsData="";
  }

  // text file input
  /* 
  fstream fin("test.txt");
  string line;
  if(fin.is_open()) {
    while(fin.good()){

      // get a line from fin
      getline(fin, line);  
      if( line.find(" ")==string::npos ) continue;
      if( line.find("#")!=string::npos ) continue;
      TString data = line; 
      milliDspOne(data, onlyMQ, id);
      id++; 
    }
  }
  fin.close();
  */
}

