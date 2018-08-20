#include "TGeoManager.h"

//
// Location of hodoscope 
//
// top
float htopx = 0;
float htopy = 0;
float htopz = -180;
// bottom 
float hbotx = 0;
float hboty = 0;
float hbotz = 180+1.05+2; 
//
bool showRow1=true;
bool showRow2=true;
bool showRow3=true;
bool showBar=false; 
bool showBrick=false;
bool showSlab=false;
bool showSheet=false;
bool showHS=false;
bool showPack=false;

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
  if(pack<0 || pack>8)  
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
    if(d==0) cordBar.SetXYZ(hbotx+2.1*4-2.1*7-1.05, hboty+0, hbotz+2.1);    
    if(d==1) cordBar.SetXYZ(hbotx+2.1*4-2.1*6-1.05, hboty+0, hbotz+2.1);    
    if(d==2) cordBar.SetXYZ(hbotx+2.1*4-2.1*5-1.05, hboty+0, hbotz+2.1);    
    if(d==3) cordBar.SetXYZ(hbotx+2.1*4-2.1*4-1.05, hboty+0, hbotz+2.1);    
    if(d==4) cordBar.SetXYZ(hbotx+2.1*4-2.1*7-1.05, hboty+0, hbotz+0);    
    if(d==5) cordBar.SetXYZ(hbotx+2.1*4-2.1*6-1.05, hboty+0, hbotz+0);    
    if(d==6) cordBar.SetXYZ(hbotx+2.1*4-2.1*5-1.05, hboty+0, hbotz+0);    
    if(d==7) cordBar.SetXYZ(hbotx+2.1*4-2.1*4-1.05, hboty+0, hbotz+0);    
  }
  else if(pack==1) // vertical 
  { 
    if(d==0) cordBar.SetXYZ(hbotx+2.1*4-2.1*3-1.05, hboty+0, hbotz+2.1);    
    if(d==1) cordBar.SetXYZ(hbotx+2.1*4-2.1*2-1.05, hboty+0, hbotz+2.1);    
    if(d==2) cordBar.SetXYZ(hbotx+2.1*4-2.1*1-1.05, hboty+0, hbotz+2.1);    
    if(d==3) cordBar.SetXYZ(hbotx+2.1*4-2.1*0-1.05, hboty+0, hbotz+2.1);    
    if(d==4) cordBar.SetXYZ(hbotx+2.1*4-2.1*3-1.05, hboty+0, hbotz+0);    
    if(d==5) cordBar.SetXYZ(hbotx+2.1*4-2.1*2-1.05, hboty+0, hbotz+0);    
    if(d==6) cordBar.SetXYZ(hbotx+2.1*4-2.1*1-1.05, hboty+0, hbotz+0);    
    if(d==7) cordBar.SetXYZ(hbotx+2.1*4-2.1*0-1.05, hboty+0, hbotz+0);    
  }
  else if(pack==2)  // horizontal
  { 
    if(d==0) cordBar.SetXYZ(hbotx+0, hboty+2.1*3+2.1*3, hbotz-5);    
    if(d==1) cordBar.SetXYZ(hbotx+0, hboty+2.1*2+2.1*3, hbotz-5);    
    if(d==2) cordBar.SetXYZ(hbotx+0, hboty+2.1*1+2.1*3, hbotz-5);    
    if(d==3) cordBar.SetXYZ(hbotx+0, hboty+2.1*0+2.1*3, hbotz-5);    
    if(d==4) cordBar.SetXYZ(hbotx+0, hboty+2.1*3+2.1*3, hbotz-5+2.1);    
    if(d==5) cordBar.SetXYZ(hbotx+0, hboty+2.1*2+2.1*3, hbotz-5+2.1);    
    if(d==6) cordBar.SetXYZ(hbotx+0, hboty+2.1*1+2.1*3, hbotz-5+2.1);    
    if(d==7) cordBar.SetXYZ(hbotx+0, hboty+2.1*0+2.1*3, hbotz-5+2.1);    
  }
  else if(pack==3) // horizontal
  { 
    if(d==0) cordBar.SetXYZ(hbotx+0, hboty+2.1*3-2.1, hbotz-5);    
    if(d==1) cordBar.SetXYZ(hbotx+0, hboty+2.1*2-2.1, hbotz-5);    
    if(d==2) cordBar.SetXYZ(hbotx+0, hboty+2.1*1-2.1, hbotz-5);    
    if(d==3) cordBar.SetXYZ(hbotx+0, hboty+2.1*0-2.1, hbotz-5);    
    if(d==4) cordBar.SetXYZ(hbotx+0, hboty+2.1*3-2.1, hbotz-5+2.1);    
    if(d==5) cordBar.SetXYZ(hbotx+0, hboty+2.1*2-2.1, hbotz-5+2.1);    
    if(d==6) cordBar.SetXYZ(hbotx+0, hboty+2.1*1-2.1, hbotz-5+2.1);    
    if(d==7) cordBar.SetXYZ(hbotx+0, hboty+2.1*0-2.1, hbotz-5+2.1);    
  }
  //  
  // top 
  //  
  else if(pack==4)  // horizontal: note that pack4 is down 
  { 
    if(d==0) cordBar.SetXYZ(hbotx+0, hboty+2.1*3-2.1, htopz-3);
    if(d==1) cordBar.SetXYZ(hbotx+0, hboty+2.1*2-2.1, htopz-3);
    if(d==2) cordBar.SetXYZ(hbotx+0, hboty+2.1*1-2.1, htopz-3);
    if(d==3) cordBar.SetXYZ(hbotx+0, hboty+2.1*0-2.1, htopz-3);
    if(d==4) cordBar.SetXYZ(hbotx+0, hboty+2.1*3-2.1, htopz-3+2.1);       
    if(d==5) cordBar.SetXYZ(hbotx+0, hboty+2.1*2-2.1, htopz-3+2.1);       
    if(d==6) cordBar.SetXYZ(hbotx+0, hboty+2.1*1-2.1, htopz-3+2.1);       
    if(d==7) cordBar.SetXYZ(hbotx+0, hboty+2.1*0-2.1, htopz-3+2.1);       
  }
  else if(pack==5)  // horizontal 
  { 
    if(d==0) cordBar.SetXYZ(hbotx+0, hboty+2.1*3+2.1*3, htopz-3);
    if(d==1) cordBar.SetXYZ(hbotx+0, hboty+2.1*2+2.1*3, htopz-3);
    if(d==2) cordBar.SetXYZ(hbotx+0, hboty+2.1*1+2.1*3, htopz-3);
    if(d==3) cordBar.SetXYZ(hbotx+0, hboty+2.1*0+2.1*3, htopz-3);
    if(d==4) cordBar.SetXYZ(hbotx+0, hboty+2.1*3+2.1*3, htopz-3+2.1);        
    if(d==5) cordBar.SetXYZ(hbotx+0, hboty+2.1*2+2.1*3, htopz-3+2.1);        
    if(d==6) cordBar.SetXYZ(hbotx+0, hboty+2.1*1+2.1*3, htopz-3+2.1);        
    if(d==7) cordBar.SetXYZ(hbotx+0, hboty+2.1*0+2.1*3, htopz-3+2.1);        
  }
  else if(pack==6)  // vertical 
  { 
    if(d==0) cordBar.SetXYZ(htopx+2.1*3+1.05, htopy+0, htopz-8);    
    if(d==1) cordBar.SetXYZ(htopx+2.1*2+1.05, htopy+0, htopz-8);    
    if(d==2) cordBar.SetXYZ(htopx+2.1*1+1.05, htopy+0, htopz-8);    
    if(d==3) cordBar.SetXYZ(htopx+2.1*0+1.05, htopy+0, htopz-8);    
    if(d==4) cordBar.SetXYZ(htopx+2.1*3+1.05, htopy+0, htopz-8+2.1);    
    if(d==5) cordBar.SetXYZ(htopx+2.1*2+1.05, htopy+0, htopz-8+2.1);    
    if(d==6) cordBar.SetXYZ(htopx+2.1*1+1.05, htopy+0, htopz-8+2.1);    
    if(d==7) cordBar.SetXYZ(htopx+2.1*0+1.05, htopy+0, htopz-8+2.1);    
  }
  else if(pack==7)  // vertical 
  { 
    if(d==0) cordBar.SetXYZ(htopx-2.1*0-1.05, htopy+0, htopz-8);    
    if(d==1) cordBar.SetXYZ(htopx-2.1*1-1.05, htopy+0, htopz-8);    
    if(d==2) cordBar.SetXYZ(htopx-2.1*2-1.05, htopy+0, htopz-8);    
    if(d==3) cordBar.SetXYZ(htopx-2.1*3-1.05, htopy+0, htopz-8);    
    if(d==4) cordBar.SetXYZ(htopx-2.1*0-1.05, htopy+0, htopz-8+2.1);    
    if(d==5) cordBar.SetXYZ(htopx-2.1*1-1.05, htopy+0, htopz-8+2.1);    
    if(d==6) cordBar.SetXYZ(htopx-2.1*2-1.05, htopy+0, htopz-8+2.1);    
    if(d==7) cordBar.SetXYZ(htopx-2.1*3-1.05, htopy+0, htopz-8+2.1);    
  }
  
  return cordBar;
}


std::vector<TVector3> getHitList(TString strData, bool isVertical)
{
  // remove space between packs
  strData.ReplaceAll(" ", "");
   
  std::vector<TVector3> hitList;
 
  for(int i=0; i<8*8; i++)
  { 
    int pack = i/8;
    int d = i%8; 

    if(isVertical && (pack==2 || pack==3 || pack==4 || pack==5)) continue;
    if(!isVertical && (pack<2 || pack>5)) continue;

    if(strData[i]=='1')  
    {
      //cout << pack << " " << d << " " << strData[i] << endl; // FIXME
      hitList.push_back(dataToBar(pack,d)); 
    }
  }
  
  return hitList;
}


/////////////////////////////////////////////////////////////////////////////////

void milliDspOne(TString data, bool onlyMQ, int id, bool drawHits=true)
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
  // split time and data  
  //01234567890123456789012345678901234567890123456789012345678901234567890123456
  //0         1         2         3         4         5         6         7 
  //1 73 280 2549 2017/10/22 9:32:19 00000000 10001000 10001000 00000000 00010001 000100110001
  
  //01234567890123456789012345678901234567890123456789012345678901234567890123456
  //0         1         2         3         4         5         6         7 
  //2018:03:21:20:09:41 10000111001111000000000000000000
  //1524996495.743901 816 129   824 1 00000001000000100011110000001100
  TObjArray *tx = data.Tokenize(" ");
  TString time; 
  TString run; 
  TString file; 
  TString event; 
  TString beam; 
  time = ((TObjString *)(tx->At(0)))->String();
  gSystem->mkdir(Form("fig/%s_%i",time.Data(), id));
  run = ((TObjString *)(tx->At(1)))->String();
  file = ((TObjString *)(tx->At(2)))->String();
  event = ((TObjString *)(tx->At(3)))->String();
  beam = ((TObjString *)(tx->At(4)))->String();
  TString mqData;
  TString hsData;
  if(onlyMQ)
  {
    mqData = ((TObjString *)(tx->At(5)))->String();
  }
  else
  {
    mqData = ((TObjString *)(tx->At(5)))->String();
    hsData = ((TObjString *)(tx->At(6)))->String() 
                    +" "+((TObjString *)(tx->At(7)))->String(); 
  }
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
    if(milliHits.at(21)) top->AddNodeOverlap(slab,1,new TGeoTranslation(0,7.5,-178)); // slab3 1.5 
    if(milliHits.at(28)) top->AddNodeOverlap(slab,1,new TGeoTranslation(0,7.5,-73));  // slab2 1.12
    if(milliHits.at(20)) top->AddNodeOverlap(slab,1,new TGeoTranslation(0,7.5,53));   // slab1 1.4
    if(milliHits.at(18)) top->AddNodeOverlap(slab,1,new TGeoTranslation(0,7.5,175));  // slab0 1.2
  }
  
  if(showSheet)
  {
    hsheet->SetLineColor(30);  
    vsheet->SetLineColor(30);  
    // layer 1
    if(milliHits.at(27)) top->AddNodeOverlap(vsheet,1,new TGeoCombiTrans(-10.5+2, 10.75*2.54/2-8, 120+2, rot_sheetm)); // 1.11
    if(milliHits.at(10)) top->AddNodeOverlap(hsheet,1,new TGeoTranslation(0,15,120+2));                                // 0.10
    if(milliHits.at(29)) top->AddNodeOverlap(vsheet,1,new TGeoCombiTrans(10.5-2, 10.75*2.54/2-8, 120+2, rot_sheetp));  // 1.13
    // layer 2 
    if(milliHits.at(30)) top->AddNodeOverlap(vsheet,1,new TGeoCombiTrans(-10.5+2, 10.75*2.54/2-8, 0, rot_sheetm));   // 1.14
    if(milliHits.at(11)) top->AddNodeOverlap(hsheet,1,new TGeoTranslation(0,15,0));                                  // 0.11
    if(milliHits.at(19)) top->AddNodeOverlap(vsheet,1,new TGeoCombiTrans(10.5-2, 10.75*2.54/2-8, 0, rot_sheetp));    // 1.3
    // layer 3 
    if(milliHits.at(31)) top->AddNodeOverlap(vsheet,1,new TGeoCombiTrans(-10.5+2, 10.75*2.54/2-8, -120-5, rot_sheetm)); // 1.15
    if(milliHits.at(14)) top->AddNodeOverlap(hsheet,1,new TGeoTranslation(0,15,-120-5));                                // 0.14
    if(milliHits.at(26)) top->AddNodeOverlap(vsheet,1,new TGeoCombiTrans(10.5-2, 10.75*2.54/2-8, -120-5, rot_sheetp));  // 1.10
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
        top->AddNodeOverlap(hhhit,1,new TGeoTranslation(hhitList.at(i).X(), hhitList.at(i).Y(), hhitList.at(i).Z()));
      for(int i=0; i<vhitList.size(); i++) 
        top->AddNodeOverlap(vhhit,1,new TGeoTranslation(vhitList.at(i).X(), vhitList.at(i).Y(), vhitList.at(i).Z()));
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
  // 
  top->SetVisibility(0);
  geom->CloseGeometry();

  //-------------------------------------------------
  // Fit the line to get the trajectory
  //-------------------------------------------------
  // ..... 
  // ..... 
  // ..... 
  // ..... 
  // ..... 

  //------------------draw on GL viewer------------------------------- 
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
  // Camera 
  v->SetCurrentCamera(TGLViewer::kCameraPerspXOZ); 
  Double_t center[3]={0,0,0}; 

  // side view
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(6, 30., center, 0.01, -3.141592); 
  v->SavePictureUsingFBO(Form("fig/%s_%i/%s_%i_side.png",time.Data(),id,time.Data(),id),1000,200,0); 
  // top view
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(6, 30., center, -3.141592/2+0.01, -3.141592); 
  v->SavePictureUsingFBO(Form("fig/%s_%i/%s_%i_top.png",time.Data(),id,time.Data(),id),1000,200,0); 
  // perspectivpe view
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(25, 30., center, -0.5, -2); 
  v->SavePictureUsingFBO(Form("fig/%s_%i/%s_%i_pers.png",time.Data(),id,time.Data(),id),1000,1000,0.01); 
 /* 
  // perspectivpe view bottomw component
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(5, 30., center, -1., -1.); 
  v->CurrentCamera().Truck(95,-125); 
  v->SavePicture(Form("fig/%s_%i/%s_%i_pers_bottom.png",time.Data(),id,time.Data(),id)); 
  // perspectivpe view top component 
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(4, 30., center, -1., -1.); 
  v->CurrentCamera().Truck(-95,125); 
  v->SavePicture(Form("fig/%s_%i/%s_%i_pers_top.png",time.Data(),id,time.Data(),id));  
  // side view top component 
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(5, 30., center, 0.01, 0.); 
  v->CurrentCamera().Truck(-180,0); 
  v->SavePicture(Form("fig/%s_%i/%s_%i_side_top.png",time.Data(),id,time.Data(),id));  
  // side view bottom component 
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(5, 30., center, 0.01, 0.); 
  v->CurrentCamera().Truck(180,0); 
  v->SavePicture(Form("fig/%s_%i/%s_%i_side_bottom.png",time.Data(),id,time.Data(),id));  
  // top view top component 
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(5, 30., center, -3.141592/2+0.01, 0.0); 
  v->CurrentCamera().Truck(-180,0); 
  v->SavePicture(Form("fig/%s_%i/%s_%i_top_top.png",time.Data(),id,time.Data(),id));  
  // top view bottom component 
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(5, 30., center, -3.141592/2+0.01, 0.0); 
  v->CurrentCamera().Truck(180,0); 
  v->SavePicture(Form("fig/%s_%i/%s_%i_top_bottom.png",time.Data(),id,time.Data(),id));  
*/  
  v->DoDraw();  

  // cleaning
  //delete geom;
  //delete v;
} 

// --------------------------------------------------------------------- //
void milliDsp()
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
  //fstream fin("data/data_sync_mqtime_20171101.txt");
  //fstream fin("mq_run374_layer2_cosmics.txt");
  //fstream fin("thru_frac.txt");
  fstream fin("full.txt");
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
}

