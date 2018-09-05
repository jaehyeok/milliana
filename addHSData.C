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

#include "utilities.h" 

using namespace std;

// variables
TString hs_file_dir="/homes/jaehyeokyoo/MilliQan/data/2018"; 
TString mq_file_dir="/net/cms26/cms26r0/milliqan/milliqanOffline/trees";
//TString hs_file_dir="/homes/jaehyeokyoo/MilliQan/data_test";
//TString mq_file_dir="/homes/jaehyeokyoo/MilliQan/data_test";
TString mq_outfile_dir="/net/cms26/cms26r0/jaehyeokyoo/data/2018/HSAdded";
int sync_window_sec=5; 

//
int addHSData(TString tag, int run, int ifile)
{
  std::cout << "Processing tag  = " << tag << std::endl; 
  std::cout << "Processing run  = " << run << std::endl; 
  std::cout << "Processing file = " << ifile << std::endl; 

  // protection from missing argement  
  if(run==-999)
  {
    std::cout << "[Error] Provide currect run number" << std::endl;
    return 0;
  }
  if(ifile<1)
  {
    std::cout << "[Error] Provide currect file number" << std::endl;
    return 0;
  }

  // list of hodoscope data
  std::vector<hsData> hsDataLoaded; 

  // histograms
  TH1D *h1_dt        = new TH1D("h1_dt",       "h1_dt",       100000,-10,10);
  TH1D *h1_dt_of_dt  = new TH1D("h1_dt_of_dt", "h1_dt_of_dt", 1000, -10,10);
  TH2D *h2_dt_vs_dt  = new TH2D("h1_dt_vs_dt", "h1_dt_vs_dt", 1000, 0, 1, 1000, 0, 1);


  // ------------------------------------------------------------------------------------ 
  // Loop over MQ files   
  // ------------------------------------------------------------------------------------ 
  TString mq_file_name = Form("File: %s/Run%i_%s/UX5MilliQan_Run%i.%i_%s.root",mq_file_dir.Data(),run,tag.Data(),run,ifile,tag.Data()); 
  TString new_mq_file_name = Form("%s/UX5MilliQan_Run%i.%i_%s_hsadded.root",mq_outfile_dir.Data(),run,ifile,tag.Data()); 
  std::cout << Form("Input MQ file : %s", mq_file_name.Data()) << std::endl; 
  std::cout << Form("Output MQ file: %s", new_mq_file_name.Data()) << std::endl; 
  
  // open a MQ files in order 
  // count the number of files and look one by one
  TFile *f = new TFile(Form("%s/Run%i_%s/UX5MilliQan_Run%i.%i_%s.root",mq_file_dir.Data(),run,tag.Data(),run,ifile,tag.Data())); 
  TTree *t_org = static_cast<TTree*>(f->Get("t"));
  double event_time_fromTDC;  
  t_org->SetBranchAddress("event_time_fromTDC", &event_time_fromTDC);
  
  //
  // New tree  
  //
  TFile *ff = new TFile(new_mq_file_name,"recreate");
  TTree *t = t_org->CopyTree("");
  t->SetName("t");
  int   extrg = 0;              // extrg
  TBranch *extrg_b =  t->Branch("extrg", &extrg);
  double   hs_time=-1;          // HS time stamp 
  TBranch *hs_time_b =  t->Branch("hs_time", &hs_time); 
  vector<int>   *hs_data = 0;   // HS data 
  TBranch *hs_data_b =  t->Branch("hs", &hs_data); 
  vector<int>   *tp_data = 0;   // TP data 
  TBranch *tp_data_b =  t->Branch("tp", &tp_data); 
  vector<double>   *fit_xz = 0;   // fit in xz plane 
  TBranch *fit_xz_b =  t->Branch("fit_xz", &fit_xz); 
  vector<double>   *fit_yz = 0;   // fit in yz plane 
  TBranch *fit_yz_b =  t->Branch("fit_yz", &fit_yz); 
  
  // get epoch time of the first event  
  t->GetEntry(0); 
  double event_time_fromTDC_begin = event_time_fromTDC;  
  //t->GetEntry(999); 
  //double event_time_fromTDC_end = event_time_fromTDC;  

  std::cout << "Start time of this MQ file: " << Form("%lf",event_time_fromTDC_begin) << std::endl;
  //cout << "End time of this MQ file  : " << Form("%lf",event_time_fromTDC_end) << std::endl;
  
  // ------------------------------------------------------------------------------------ 
  //  Find HS files to look at 
  // ------------------------------------------------------------------------------------ 
  // 1 hour before  
  time_t epoch_previous_file    = static_cast<int>(event_time_fromTDC_begin-3600);
  struct tm *date_previous_file = gmtime(&epoch_previous_file);
  TString hs_previous_file = Form("data_%d%02d%02d%02d.txt", date_previous_file->tm_year+1900, date_previous_file->tm_mon+1, date_previous_file->tm_mday, date_previous_file->tm_hour); 
  // 1 hour after  
  time_t epoch_next_file    = static_cast<int>(event_time_fromTDC_begin+3600);
  struct tm *date_next_file = gmtime(&epoch_next_file);
  TString hs_next_file = Form("data_%d%02d%02d%02d.txt", date_next_file->tm_year+1900, date_next_file->tm_mon+1, date_next_file->tm_mday, date_next_file->tm_hour); 
  // current  
  time_t epoch    = static_cast<int>(event_time_fromTDC_begin);
  struct tm *date = gmtime(&epoch);
  TString hs_current_file = Form("data_%d%02d%02d%02d.txt", date->tm_year+1900, date->tm_mon+1, date->tm_mday, date->tm_hour); 

  std::cout << "HS files in consideration: " << std::endl; 
  std::cout << hs_previous_file << std::endl;
  std::cout << hs_current_file << std::endl;
  std::cout << hs_next_file << std::endl;
  
  std::cout <<  Form("Time: %d%02d%02d %02d:%02d:%02d", date->tm_year+1900, date->tm_mon+1, date->tm_mday, date->tm_hour, date->tm_min, date->tm_sec) << std::endl; 

  // ------------------------------------------------------------------------------------ 
  //  Store HS data in memory 
  // ------------------------------------------------------------------------------------ 
  // 1. if near boundary then look at two adjacent files  
  if(date->tm_min<3 && ifile>1)
  {
    loadHSData(hs_file_dir, hs_previous_file, hsDataLoaded, -1);
  }
  // 2. load events in the main file
  loadHSData(hs_file_dir, hs_current_file, hsDataLoaded, 0);

  // 3. if the end time is in the next file, add events to memory 
  if(date->tm_min>57)
  {
    loadHSData(hs_file_dir, hs_next_file, hsDataLoaded, 1);
  }

  std::cout << "Number of loaded HS events: " << hsDataLoaded.size() << std::endl; 
  
  // debug  
  if(0) for(int ihs=0; ihs<hsDataLoaded.size(); ihs++) hsDataLoaded.at(ihs).printData();
  
  // Get the window of HS events to compare 
  double hs_begin_time = hsDataLoaded.at(0).getMicroTime();
  double hs_end_time = hsDataLoaded.at(hsDataLoaded.size()-1).getMicroTime();
  double hs_total_time = hs_end_time-hs_begin_time;

  std::cout << "HS time: " << Form("%lf",hs_begin_time) << " to " <<  Form("%lf",hs_end_time) << " = " << hs_total_time << " [seconds]" << std::endl;

  // for each MQ file, make a distribution of delta T and find the peak
  // also compare delta T between consecutive events  
  // store synched events 

  // ------------------------------------------------------------------------------------ 
  //  Loop over events get calculate dT(mq,hs) and dT(evt1,evt2)
  // ------------------------------------------------------------------------------------ 
  double mq_current_time=event_time_fromTDC_begin; 
  double mq_previous_time=event_time_fromTDC_begin; 
  int nentries = t->GetEntries(); 
  for(int i=0; i<nentries; i++)
  {
    t->GetEntry(i);  
    mq_current_time = event_time_fromTDC;  
    
    // get the indices for sync window 
    int first_hs_evt = hsDataLoaded.size() * (mq_current_time-sync_window_sec-hs_begin_time)/hs_total_time;   
    int last_hs_evt  = hsDataLoaded.size() * (mq_current_time+sync_window_sec-hs_begin_time)/hs_total_time;   

    if(0) // debug 
    {
      std::cout << Form("%.6f",event_time_fromTDC) << std::endl; 
      std::cout << mq_current_time << " - " << mq_previous_time << " = " << mq_current_time-mq_previous_time << std::endl;  
      std::cout << first_hs_evt << " - " << last_hs_evt << std::endl; 
    } 

    // Loop over selected HS events 
    double hs_current_time=0; 
    double hs_previous_time=0; 
    for(int ihs=0; ihs<hsDataLoaded.size(); ihs++) 
    {
      // only extrg events
      //if(!hsDataLoaded.at(ihs).isMQEvent()) continue;

      hs_current_time = hsDataLoaded.at(ihs).getMicroTime();
      
      double dt_of_dt = (mq_current_time-mq_previous_time) - (hs_current_time-hs_previous_time);
      dt_of_dt = 0; // not using dt_of_dt in the syncing decision
      if(TMath::Abs(dt_of_dt)<0.00001) h1_dt->Fill(mq_current_time-hs_current_time); 

      hs_previous_time = hs_current_time; 
    }

    mq_previous_time = mq_current_time; 
  }

  // ------------------------------------------------------------------------------------ 
  //  Loop over events again to save synched events 
  // ------------------------------------------------------------------------------------ 
  // Get the range 
  //int maxBin = h1_dt->GetMaximumBin(); 
  //double range_low = h1_dt->GetBinLowEdge(maxBin-1);
  //double range_high = h1_dt->GetBinLowEdge(maxBin+2);
  vector<int> maxBin;
  for(int i=1; i<=h1_dt->GetXaxis()->GetNbins(); i++) 
  { 
    if(h1_dt->GetBinContent(i)>100) 
    {
      maxBin.push_back(i);
      double range_low = h1_dt->GetBinLowEdge(i-1);
      double range_high = h1_dt->GetBinLowEdge(i+2);
      std::cout << "dT synch range: " << range_low << " - " << range_high << std::endl;
    }
  }

  for(int i=0; i<nentries; i++)
  {
    t->GetEntry(i); 
    mq_current_time = event_time_fromTDC;  
    
    // get the indices for sync window 
    int first_hs_evt = hsDataLoaded.size() * (mq_current_time-sync_window_sec-hs_begin_time)/hs_total_time;   
    int last_hs_evt  = hsDataLoaded.size() * (mq_current_time+sync_window_sec-hs_begin_time)/hs_total_time;   

    if(0) // debug 
    {
      std::cout << Form("%.6f",event_time_fromTDC) << std::endl; 
      std::cout << mq_current_time << " - " << mq_previous_time << " = " << mq_current_time-mq_previous_time << std::endl;  
      std::cout << first_hs_evt << " - " << last_hs_evt << std::endl; 
    } 

    // Loop over selected HS events 
    double hs_current_time=0; 
    double hs_previous_time=0; 
    for(int ihs=0; ihs<hsDataLoaded.size(); ++ihs) 
    {
      // only extrg events
      //if(!hsDataLoaded.at(ihs).isMQEvent()) continue;
      extrg = hsDataLoaded.at(ihs).isMQEvent();

      hs_current_time = hsDataLoaded.at(ihs).getMicroTime();
      
      double dt_of_dt = (mq_current_time-mq_previous_time) - (hs_current_time-hs_previous_time);
      dt_of_dt = 0; // not using dt_of_dt in the syncing decision

      bool synched=false;
      for(int ipeak=0; ipeak<maxBin.size(); ipeak++) 
      {
         double range_low = h1_dt->GetBinLowEdge(maxBin.at(ipeak)-1);
         double range_high = h1_dt->GetBinLowEdge(maxBin.at(ipeak)+2);
      
        if( mq_current_time-hs_current_time>range_low && mq_current_time-hs_current_time<range_high
            && TMath::Abs(dt_of_dt)<0.00001 ) synched = true;
      }

      if(synched)
      {
        h1_dt_of_dt->Fill(dt_of_dt*1000*1000); 
        h2_dt_vs_dt->Fill((mq_current_time-mq_previous_time), (hs_current_time-hs_previous_time)); 

        std::vector<bool> hsData_tmp = hsDataLoaded.at(ihs).getHSData();  
        for(int j=0; j<hsData_tmp.size(); j++)
        {
          if(hsData_tmp.at(j)==1) hs_data->push_back(j);
        }
        std::vector<bool> tpData_tmp = hsDataLoaded.at(ihs).getTPData();  
        for(int j=0; j<tpData_tmp.size(); j++)
        {
          if(tpData_tmp.at(j)==1) tp_data->push_back(j);
        }

        hs_time = hs_current_time;
            
        // Tracking 
        // get fit parameter
        vector<double> parFit = doFit(hs_data);

        if(parFit.size()>0) 
        {
          //cout << parFit[0] << " " << parFit[1] << endl;
          //cout << parFit[2] << " " << parFit[3] << endl;

          fit_xz->push_back(parFit[0]);
          fit_xz->push_back(parFit[1]);
          fit_yz->push_back(parFit[2]);
          fit_yz->push_back(parFit[3]);
        }
        parFit.clear();

        // debug 
        if(0)
        {
          bool something_in_hs = false; 
          for(int j=0; j<hsData_tmp.size(); j++)
            if(hsData_tmp.at(j)==1) something_in_hs=true; 
          if(something_in_hs) hsDataLoaded.at(ihs).printData();
        }
        break; 
      
      } 
      
      hs_previous_time = hs_current_time; 
    }
    
    mq_previous_time = mq_current_time; 
    
    extrg_b->Fill();
    hs_time_b->Fill();
    hs_data_b->Fill();
    tp_data_b->Fill();
    fit_xz_b->Fill();
    fit_yz_b->Fill();
      
    extrg   = 0;
    hs_time = 0;
    hs_data->clear();
    tp_data->clear();
    fit_xz->clear();
    fit_yz->clear();
  }
  
  // ------------------------------------------------------------------------------------ 
  //  Draw some plots for sanity check
  // ------------------------------------------------------------------------------------ 
  TCanvas *c = new TCanvas("c","c",800,800); 
  c->Divide(2,2);
  c->cd(1);
  h1_dt->Draw("hist");
  c->cd(2);
  h1_dt_of_dt->Draw("hist");
  c->cd(3);
  h2_dt_vs_dt->Draw("colz");
  c->Print("plots_sync.pdf"); 
  c->Print("plots_sync.C"); 
  
  // ------------------------------------------------------------------------------------ 
  // Write new file
  // ------------------------------------------------------------------------------------ 
  t->Write("t");
  //std::cout << Form("Moving new output file %s to %s",new_mq_file_name.Data(),mq_outfile_dir.Data()) << std::endl;
  //gSystem->Exec(Form("mv %s %s",new_mq_file_name.Data(),mq_outfile_dir.Data()));
  delete t; 
  ff->Close();
 
  // clean up 
  hsDataLoaded.clear();
  hsDataLoaded.shrink_to_fit();
  if(hsDataLoaded.size()!=0) std::cout << "[Error] Vector not clear" << std::endl;
  else std::cout << "vector clear" << std::endl;
  delete t_org; 
  f->Close();
  
  delete h1_dt;
  delete h1_dt_of_dt;
  delete h2_dt_vs_dt; 
  delete c; 

  delete hs_data;
  delete tp_data;

  return 0;
}

# ifndef __CINT__  // the following code will be invisible for the interpreter
int main(int argc, char **argv)
{ 
  TString tag = argv[1];
  int run = stoi(argv[2]);
  int ifile_begin = stoi(argv[3]);
  int ifile_end = stoi(argv[3]);
  if(argc>4) ifile_end = stoi(argv[4]);

  std::cout << "------------------------------" << std::endl; 
  std::cout << " Run   : " << run << std::endl; 
  std::cout << " Tag   : " << tag << std::endl; 
  std::cout << " files : " << ifile_begin << " - " << ifile_end << std::endl; 
  std::cout << "------------------------------" << std::endl; 
  std::cout << std::endl; 

  int temp;
  for(int i=ifile_begin; i<=ifile_end; i++) 
  { 
    temp = addHSData(tag, run, i);
    if(temp) std::cout << "[Error] Something went wrong: "<< temp << std::endl;
  }
}
# endif

