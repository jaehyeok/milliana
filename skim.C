// Look at the channel map 
// https://www.dropbox.com/s/0lnhvhnc98lzqgw/demonstratorDiagram.pdf?dl=0 

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip> // for setw()

#include "TChain.h"
#include "TROOT.h"
#include "TF1.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TBranch.h"
#include "TString.h"
#include "TStyle.h"

void skim()
{  

  //  ---------------------------------------------------------------------------- 
  
  TChain chain("t");
  chain.Add("../data_test/Run1123_Physics/HSAdded/UX5MilliQan_Run1123.*.root"); 

  TFile *newfile= new TFile("skim.root","recreate");
  TTree* evt_tree=(TTree*) chain.CloneTree(0, "fast");

  //
  int   event = 0;                     chain.SetBranchAddress("event", &event);
  int   run = 0;                       chain.SetBranchAddress("run", &run);
  int   file = 0;                      chain.SetBranchAddress("file", &file);
  bool   beam = 0;                     chain.SetBranchAddress("beam", &beam);
  vector<int> *chan = 0;               chain.SetBranchAddress("chan", &chan);
  vector<int> *layer = 0;              chain.SetBranchAddress("layer", &layer);
  vector<int> *row = 0;                chain.SetBranchAddress("row", &row);
  vector<int> *column = 0;             chain.SetBranchAddress("column", &column);
  vector<int> *type = 0;               chain.SetBranchAddress("type", &type);
  vector<int> *height = 0;             chain.SetBranchAddress("height", &height);
  vector<float> *duration = 0;         chain.SetBranchAddress("duration", &duration);
  vector<float> *area = 0;             chain.SetBranchAddress("area", &area);
  vector<float> *nPE = 0;              chain.SetBranchAddress("nPE", &nPE);
  vector<int> *ipulse = 0;             chain.SetBranchAddress("ipulse", &ipulse);
  vector<Long64_t> *groupTDC_b0 = 0;   chain.SetBranchAddress("groupTDC_b0", &groupTDC_b0);
  vector<Long64_t> *groupTDC_b1 = 0;   chain.SetBranchAddress("groupTDC_b1", &groupTDC_b1);

  unsigned int nentries = (Int_t)chain.GetEntries();
  cout << "The number of events: " << nentries << endl;

  // main event loop
  for(unsigned int ievent = 0; ievent<nentries; ievent++)
  //for(unsigned int ievent = 0; ievent<10; ievent++)
  {
    chain.GetEntry(ievent);
  
    // synch b0 and b1
    bool digizers_synched=true; 
    for(int i=0; i<groupTDC_b1->size(); ++i) 
    { 
      if(groupTDC_b1->at(i)!=groupTDC_b1->at(i)) 
      { 
        digizers_synched=false;
        break;
      }
    }
    if(!digizers_synched) continue;

    bool slab18=false;
    bool slab20=false;
    bool slab21=false;
    bool slab28=false;
    for(int ich=0; ich<chan->size(); ich++) 
    { 
      if(chan->at(ich)==18 && nPE->at(ich)>200) slab18=true;
      if(chan->at(ich)==20 && nPE->at(ich)>200) slab20=true;
      if(chan->at(ich)==21 && nPE->at(ich)>200) slab21=true;
      if(chan->at(ich)==28 && nPE->at(ich)>100) slab28=true;
    }

    if(slab18 && slab20 && slab21 && slab28) 
    { 
      evt_tree->Fill(); 
    }
  } // main event loop

    newfile->cd();
    evt_tree->Write();
    newfile->Close();


}
