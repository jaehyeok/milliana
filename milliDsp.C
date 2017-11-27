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
float hbotz = 180+1.05; 

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
  if(pack<0 || pack>4)  
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
  // bottom
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
    if(d==0) cordBar.SetXYZ(hbotx+0, hboty+2.1*3+2.1, hbotz-5);    
    if(d==1) cordBar.SetXYZ(hbotx+0, hboty+2.1*2+2.1, hbotz-5);    
    if(d==2) cordBar.SetXYZ(hbotx+0, hboty+2.1*1+2.1, hbotz-5);    
    if(d==3) cordBar.SetXYZ(hbotx+0, hboty+2.1*0+2.1, hbotz-5);    
    if(d==4) cordBar.SetXYZ(hbotx+0, hboty+2.1*3+2.1, hbotz-5+2.1);    
    if(d==5) cordBar.SetXYZ(hbotx+0, hboty+2.1*2+2.1, hbotz-5+2.1);    
    if(d==6) cordBar.SetXYZ(hbotx+0, hboty+2.1*1+2.1, hbotz-5+2.1);    
    if(d==7) cordBar.SetXYZ(hbotx+0, hboty+2.1*0+2.1, hbotz-5+2.1);    
  }
  // top 
  else if(pack==3) // horizontal
  { 
    if(d==0) cordBar.SetXYZ(htopx+0, htopy+2.1*3, htopz-3);    
    if(d==1) cordBar.SetXYZ(htopx+0, htopy+2.1*2, htopz-3);    
    if(d==2) cordBar.SetXYZ(htopx+0, htopy+2.1*1, htopz-3);    
    if(d==3) cordBar.SetXYZ(htopx+0, htopy+2.1*0, htopz-3);    
    if(d==4) cordBar.SetXYZ(htopx+0, htopy+2.1*3, htopz-3+2.1);    
    if(d==5) cordBar.SetXYZ(htopx+0, htopy+2.1*2, htopz-3+2.1);    
    if(d==6) cordBar.SetXYZ(htopx+0, htopy+2.1*1, htopz-3+2.1);    
    if(d==7) cordBar.SetXYZ(htopx+0, htopy+2.1*0, htopz-3+2.1);    
  }
  else  // vertical 
  { 
    if(d==0) cordBar.SetXYZ(htopx+2.1*2-3*2-1.05, htopy+0, htopz-8+2.1);    
    if(d==1) cordBar.SetXYZ(htopx+2.1*2-2*2-1.05, htopy+0, htopz-8+2.1);    
    if(d==2) cordBar.SetXYZ(htopx+2.1*2-1*2-1.05, htopy+0, htopz-8+2.1);    
    if(d==3) cordBar.SetXYZ(htopx+2.1*2-0*2-1.05, htopy+0, htopz-8+2.1);    
    if(d==4) cordBar.SetXYZ(htopx+2.1*2-3*2-1.05, htopy+0, htopz-8);    
    if(d==5) cordBar.SetXYZ(htopx+2.1*2-2*2-1.05, htopy+0, htopz-8);    
    if(d==6) cordBar.SetXYZ(htopx+2.1*2-1*2-1.05, htopy+0, htopz-8);    
    if(d==7) cordBar.SetXYZ(htopx+2.1*2-0*2-1.05, htopy+0, htopz-8);    
  }

  return cordBar;
}


std::vector<TVector3> getHitList(TString strData, bool isVertical)
{
  // remove space between packs
  strData.ReplaceAll(" ", "");
   
  std::vector<TVector3> hitList;
 
  for(int i=0; i<8*5; i++)
  { 
    int pack = i/8;
    int d = i%8; 

    if(isVertical && (pack==2 || pack==3)) continue;
    if(!isVertical && (pack<2 || pack>3)) continue;
    

    if(strData[i]=='1')  
    {
      //cout << pack << " " << d << " " << strData[i] << endl; // FIXME
      hitList.push_back(dataToBar(pack,d)); 
    }
  }

  return hitList;
}


/////////////////////////////////////////////////////////////////////////////////

void milliDspOne(TString data, bool drawHits=true)
{ 
  TGeoManager *geom = new TGeoManager("geom","My 3D Project");

  //------------------Creat materials-----------------------------
  TGeoMaterial *vacuum = new TGeoMaterial("vacuum",0,0,0);
  TGeoMaterial *Fe = new TGeoMaterial("Fe",55.84,26.7,7.87);
  TGeoMaterial *Cu = new TGeoMaterial("Cu",63.549,29,8.92);

  //------------------Creat media----------------------------------
  TGeoMedium *Air = new TGeoMedium("Air",0,vacuum);
  TGeoMedium *Iron = new TGeoMedium("Iron",1,Fe);

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
  //2017/9/25 18:44:40  00010001 00000000 00000000 11111111 11111111 001101011111 
  //01234567890123456789012345678901234567890123456789012345678901234567890123456
  //0         1         2         3         4         5         6         7 
  //1 73 280 2549 2017/10/22 9:32:19 00000000 10001000 10001000 00000000 00010001 000100110001
  TObjArray *tx = data.Tokenize(" ");
  TString time = ((TObjString *)(tx->At(4)))->String()+" "+((TObjString *)(tx->At(5)))->String();
  for(int i=0; i<10; i++) 
  { 
    time.ReplaceAll(Form("/%i/",i),Form("/0%i/",i)); 
    time.ReplaceAll(Form("/%i ",i),Form("/0%i ",i));  
    time.ReplaceAll(Form(" %i:",i),Form(" 0%i:",i));  
    time.ReplaceAll(Form(":%i:",i),Form(":0%i:",i));  
    time.ReplaceAll(Form(":%i ",i),Form(":0%i ",i));  
  }
  time.ReplaceAll(" ","_");  
  time.ReplaceAll(":","");  
  time.ReplaceAll("/","");  
  time.ReplaceAll("___","_");   
  time.ReplaceAll("__","_");   
  gSystem->mkdir(Form("fig/%s",time.Data()));
  TString tempData= ((TObjString *)(tx->At(6)))->String()
                    +" "+((TObjString *)(tx->At(7)))->String() 
                    +" "+((TObjString *)(tx->At(8)))->String() 
                    +" "+((TObjString *)(tx->At(9)))->String() 
                    +" "+((TObjString *)(tx->At(10)))->String() 
                    +" "+((TObjString *)(tx->At(11)))->String(); 
  cout << "time: " << time << endl; 
  cout << "data: " << tempData << endl; 
  vector<int> milliHits;  
  for(int i=0; i<12; i++) milliHits.push_back(tempData[i+45]=='1'?1:0);  
    

  //------------------ Create milliqan ----------------------------
  
  //
  // bars
  //
  TGeoVolume *mbar=geom->MakeBox("mbar",Iron,2.5,2.5,40); 
  TGeoVolume *pmt=geom->MakeTube("pmt",Iron,0,2.5,8);
  // can visulize the pulse height  
  //TGeoVolume *pmt_ch[12];
  //for(int i=0; i<12; i++)x pmt_ch[i] = geom->MakeTube(Form("pmt_ch%i",i),Iron,0,2.5,8);
  if(drawHits)
  {
      mbar->SetLineColor(38); 
      // bottom pack
      if(milliHits.at(0)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,0,120+10));
      if(milliHits.at(1)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,0,120+10));
      if(milliHits.at(2)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,6,120+10));
      if(milliHits.at(3)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,6,120+10));
      // middle pack
      if(milliHits.at(4)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,0,0+10));
      if(milliHits.at(5)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,0,0+10));
      if(milliHits.at(6)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,6,0+10));
      if(milliHits.at(7)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,6,0+10));
      // top pack
      if(milliHits.at(8)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,0,-120+10));
      if(milliHits.at(9)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,0,-120+10));
      if(milliHits.at(10)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(-3,6,-120+10));
      if(milliHits.at(11)) top->AddNodeOverlap(mbar,1,new TGeoTranslation(3,6,-120+10));
      
      pmt->SetLineColor(15);  
      // bottom pack
      if(milliHits.at(0)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,0,120-40-8+10));
      if(milliHits.at(1)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,0,120-40-8+10));
      if(milliHits.at(2)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,6,120-40-8+10));
      if(milliHits.at(3)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,6,120-40-8+10));
      // middle pack
      if(milliHits.at(4)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,0,-40-8+10));
      if(milliHits.at(5)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,0,-40-8+10));
      if(milliHits.at(6)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,6,-40-8+10));
      if(milliHits.at(7)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,6,-40-8+10));
      // middle pack
      if(milliHits.at(8)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,0,-120-40-8+10));
      if(milliHits.at(9)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,0,-120-40-8+10));
      if(milliHits.at(10)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(-3,6,-120-40-8+10));
      if(milliHits.at(11)) top->AddNodeOverlap(pmt,1,new TGeoTranslation(3,6,-120-40-8+10));
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

  //------------------ Create hodoscope ------------------------------- 
  if(drawHits) 
  { 
    //-------------------------------------------------
    // Mark bars with hits 
    //-------------------------------------------------

    // get a list of non-zero channels
    std::vector<TVector3> vhitList = getHitList(tempData, true); 
    std::vector<TVector3> hhitList = getHitList(tempData, false); 

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
  v->CurrentCamera().Configure(6, 30., center, 0.01, 0.); 
  //v->SavePicture(Form("fig/%s/%s_side.pdf",time.Data(),time.Data())); 
  v->SavePictureUsingFBO(Form("fig/%s/%s_side.png",time.Data(),time.Data()),1000,200,0); 
  // top view
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(6, 30., center, -3.141592/2+0.01, 0.00); 
  //v->SavePicture(Form("fig/%s/%s_top.pdf",time.Data(),time.Data())); 
  v->SavePictureUsingFBO(Form("fig/%s/%s_top.png",time.Data(),time.Data()),1000,200,0.5); 
  // perspectivpe view
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(25, 30., center, -1., -1.); 
  //v->SavePicture(Form("fig/%s/%s_pers.pdf",time.Data(),time.Data())); 
  v->SavePictureUsingFBO(Form("fig/%s/%s_pers.png",time.Data(),time.Data()),1000,1000,0.01); 
  
  // perspectivpe view bottomw component
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(5, 30., center, -1., -1.); 
  v->CurrentCamera().Truck(95,-125); 
  //v->SavePicture(Form("fig/%s/%s_pers_bottom.pdf",time.Data(),time.Data())); 
  v->SavePicture(Form("fig/%s/%s_pers_bottom.png",time.Data(),time.Data())); 
  // perspectivpe view top component 
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(4, 30., center, -1., -1.); 
  v->CurrentCamera().Truck(-95,125); 
  //v->SavePicture(Form("fig/%s/%s_pers_top.pdf",time.Data(),time.Data())); 
  v->SavePicture(Form("fig/%s/%s_pers_top.png",time.Data(),time.Data()));  
  // side view top component 
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(5, 30., center, 0.01, 0.); 
  v->CurrentCamera().Truck(-180,0); 
  //v->SavePicture(Form("fig/%s/%s_side_top.pdf",time.Data(),time.Data())); 
  v->SavePicture(Form("fig/%s/%s_side_top.png",time.Data(),time.Data()));  
  // side view bottom component 
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(5, 30., center, 0.01, 0.); 
  v->CurrentCamera().Truck(180,0); 
  //v->SavePicture(Form("fig/%s/%s_side_bottom.pdf",time.Data(),time.Data())); 
  v->SavePicture(Form("fig/%s/%s_side_bottom.png",time.Data(),time.Data()));  
  // top view top component 
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(5, 30., center, -3.141592/2+0.01, 0.0); 
  v->CurrentCamera().Truck(-180,0); 
  //v->SavePicture(Form("fig/%s/%s_top_top.pdf",time.Data(),time.Data())); 
  v->SavePicture(Form("fig/%s/%s_top_top.png",time.Data(),time.Data()));  
  // top view bottom component 
  v->CurrentCamera().Reset(); 
  v->CurrentCamera().Configure(5, 30., center, -3.141592/2+0.01, 0.0); 
  v->CurrentCamera().Truck(180,0); 
  //v->SavePicture(Form("fig/%s/%s_top_bottom.pdf",time.Data(),time.Data())); 
  v->SavePicture(Form("fig/%s/%s_top_bottom.png",time.Data(),time.Data()));  
  
  v->DoDraw();  

  // cleaning
  delete geom;
  delete v;
} 

// --------------------------------------------------------------------- //
void milliDsp()
{ 
  //fstream fin("data/data_sync_mqtime_20171101.txt");
  fstream fin("test.txt");
  string line;
  if(fin.is_open()) {
    while(fin.good()){

      // get a line from fin
      getline(fin, line);  
      if( line.find(" ")==string::npos ) continue;
      TString data = line; 
      milliDspOne(data);
    }
  }
  fin.close();
}

