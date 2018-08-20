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

// variables
//TString hs_file_dir="/homes/jaehyeokyoo/MilliQan/data/2018"; 
//TString mq_file_dir="/net/cms26/cms26r0/milliqan/milliqanOffline/trees";
TString hs_file_dir="/homes/jaehyeokyoo/MilliQan/data_test";
TString mq_file_dir="/homes/jaehyeokyoo/MilliQan/data_test";
int sync_window_sec=5; 

//
class hsData 
{
  private: 
    int   event_mq_; 
    int   epoch_time_; 
    int   us_; 
    std::vector<bool>  data_hs_;
    std::vector<bool>  data_tp_;

  public:
    //
    hsData(int epoch_time, int us, std::vector<bool> data_hs, std::vector<bool> data_tp, int event_mq)
    {
      epoch_time_ = epoch_time;
      us_         = us;
      event_mq_   = event_mq;
      for(int i=0; i<data_hs.size(); i++) data_hs_.push_back(data_hs[i]);
      for(int i=0; i<data_tp.size(); i++) data_tp_.push_back(data_tp[i]);
    }
    //
    hsData(TString tstr_data)
    {
      tstr_data.ReplaceAll(" ",":"); 
      
      TObjArray *tk_data = tstr_data.Tokenize(":"); 
      epoch_time_ =  (static_cast<TObjString*>(tk_data->At(0)))->String().Atoi();  
      us_         =  (static_cast<TObjString*>(tk_data->At(7)))->String().Atoi(); 
      // hs data 
      for(int i=38; i<=164; i=i+2)
      {
        if(tstr_data[i]=='1') data_hs_.push_back(1);
        else data_hs_.push_back(0);
      }
      // trackpack data 
      for(int i=167; i<=213; i=i+2)
      {
        if(tstr_data[i]=='1') data_tp_.push_back(1);
        else data_tp_.push_back(0);
      }
      // extrg
      if(tstr_data[216]=='1') event_mq_=1; 
      else event_mq_=0;  

      delete tk_data;
    }
    //
    int getEpochTime()            {return epoch_time_;               }
    double getMicroTime()         {return epoch_time_+0.000001*us_;  }
    std::vector<bool> getHSData() {return data_hs_;                  }
    std::vector<bool> getTPData() {return data_tp_;                  }
    int isMQEvent()               {return event_mq_;  }
    void printData()            
    {
      std::cout << epoch_time_+0.000001*us_ << " " << event_mq_ << " ";  
      for(int i=0; i<data_hs_.size(); i++) std::cout << data_hs_.at(i);
      std::cout << " " ;
      for(int i=0; i<data_tp_.size(); i++) std::cout << data_tp_.at(i);
      std::cout << std::endl;
    }
};

//
TString kind_str(int kind)
{
  if(kind==-1) return "previous";
  else if(kind==1) return "next";
  else return "current";
}

//
void loadHSData(TString hs_file, std::vector<hsData> &hsDataLoaded, int kind)
{
  ifstream fin(Form("%s/%s", hs_file_dir.Data(), hs_file.Data())); 
  cout << (Form("Loading %s HS file: %s/%s", kind_str(kind).Data(), hs_file_dir.Data(), hs_file.Data())) << endl; 

  // Get the number of events
  int nLines=-1;
  string s;
  if(fin.is_open()) 
  {
    while(fin.good())
    {
      getline(fin, s);
      nLines++; 
    } 
  }
  cout << "Number of lines: " << nLines << endl;
  fin.close(); 
   
  // Add events to memory  
  ifstream finfile(Form("%s/%s", hs_file_dir.Data(), hs_file.Data())); 
  int line=0;
  if(finfile.is_open()) 
  {
    while(finfile.good())
    {
      // get a line from finfile
      getline(finfile, s);
      line++;
      
      if(line>nLines) break;
      
      if(kind==-1 && line<nLines*0.9) continue; 
      if(kind==1 && line>nLines*0.1) break;
      
      hsData hsDataOne(static_cast<TString>(s));
      hsDataLoaded.push_back(hsDataOne);
      
    }
  }
  finfile.close(); 
}

int* convertRawToPhysCh(unsigned int raw_ch, bool isHS)
{ 
  int phys_ch={0,0,0}; // x, y, z 
  if(isHS) 
  { 
     // bottom vertical bars
     if(raw_ch==0)        phys_ch={ -4,  0,  2}; 
     else if(raw_ch==1)   phys_ch={ -3,  0,  2}; 
     else if(raw_ch==2)   phys_ch={ -2,  0,  2}; 
     else if(raw_ch==3)   phys_ch={ -1,  0,  2}; 
     else if(raw_ch==4)   phys_ch={ -4,  0,  1}; 
     else if(raw_ch==5)   phys_ch={ -3,  0,  1}; 
     else if(raw_ch==6)   phys_ch={ -2,  0,  1}; 
     else if(raw_ch==7)   phys_ch={ -1,  0,  1}; 
     else if(raw_ch==8)   phys_ch={  1,  0,  2}; 
     else if(raw_ch==9)   phys_ch={  2,  0,  2}; 
     else if(raw_ch==10)  phys_ch={  3,  0,  2}; 
     else if(raw_ch==11)  phys_ch={  4,  0,  2}; 
     else if(raw_ch==12)  phys_ch={  1,  0,  1}; 
     else if(raw_ch==13)  phys_ch={  2,  0,  1}; 
     else if(raw_ch==14)  phys_ch={  3,  0,  1}; 
     else if(raw_ch==15)  phys_ch={  4,  0,  1}; 
     // bottom horizontal bars
     else if(raw_ch==16)  phys_ch={  0,  8,  1}; 
     else if(raw_ch==17)  phys_ch={  0,  7,  1}; 
     else if(raw_ch==18)  phys_ch={  0,  6,  1}; 
     else if(raw_ch==19)  phys_ch={  0,  5,  1}; 
     else if(raw_ch==20)  phys_ch={  0,  8,  2}; 
     else if(raw_ch==21)  phys_ch={  0,  7,  2}; 
     else if(raw_ch==22)  phys_ch={  0,  6,  2}; 
     else if(raw_ch==23)  phys_ch={  0,  5,  2}; 
     else if(raw_ch==24)  phys_ch={  0,  4,  1}; 
     else if(raw_ch==25)  phys_ch={  0,  3,  1}; 
     else if(raw_ch==26)  phys_ch={  0,  2,  1}; 
     else if(raw_ch==27)  phys_ch={  0,  1,  1}; 
     else if(raw_ch==28)  phys_ch={  0,  4,  2}; 
     else if(raw_ch==29)  phys_ch={  0,  3,  2}; 
     else if(raw_ch==30)  phys_ch={  0,  2,  2}; 
     else if(raw_ch==31)  phys_ch={  0,  1,  2}; 
     // top horizontal bars
     else if(raw_ch==32)  phys_ch={  0,  4, -2}; 
     else if(raw_ch==33)  phys_ch={  0,  3, -2}; 
     else if(raw_ch==34)  phys_ch={  0,  2, -2}; 
     else if(raw_ch==35)  phys_ch={  0,  1, -2}; 
     else if(raw_ch==36)  phys_ch={  0,  4, -1}; 
     else if(raw_ch==37)  phys_ch={  0,  3, -1}; 
     else if(raw_ch==38)  phys_ch={  0,  2, -1}; 
     else if(raw_ch==39)  phys_ch={  0,  1, -1}; 
     else if(raw_ch==40)  phys_ch={  0,  8, -2}; 
     else if(raw_ch==41)  phys_ch={  0,  7, -2}; 
     else if(raw_ch==42)  phys_ch={  0,  6, -2}; 
     else if(raw_ch==43)  phys_ch={  0,  5, -2}; 
     else if(raw_ch==44)  phys_ch={  0,  8, -1}; 
     else if(raw_ch==45)  phys_ch={  0,  7, -1}; 
     else if(raw_ch==46)  phys_ch={  0,  6, -1}; 
     else if(raw_ch==47)  phys_ch={  0,  5, -1}; 
     // bottom vertical bars
     else if(raw_ch==48)  phys_ch={  4,  0, -2}; 
     else if(raw_ch==49)  phys_ch={  3,  0, -2}; 
     else if(raw_ch==50)  phys_ch={  2,  0, -2}; 
     else if(raw_ch==51)  phys_ch={  1,  0, -2}; 
     else if(raw_ch==52)  phys_ch={  4,  0, -1}; 
     else if(raw_ch==53)  phys_ch={  3,  0, -1}; 
     else if(raw_ch==54)  phys_ch={  2,  0, -1}; 
     else if(raw_ch==55)  phys_ch={  1,  0, -1}; 
     else if(raw_ch==56)  phys_ch={ -1,  0, -2}; 
     else if(raw_ch==57)  phys_ch={ -2,  0, -2}; 
     else if(raw_ch==58)  phys_ch={ -3,  0, -2}; 
     else if(raw_ch==59)  phys_ch={ -4,  0, -2}; 
     else if(raw_ch==60)  phys_ch={ -1,  0, -1}; 
     else if(raw_ch==61)  phys_ch={ -2,  0, -1}; 
     else if(raw_ch==62)  phys_ch={ -3,  0, -1}; 
     else if(raw_ch==63)  phys_ch={ -4,  0, -1}; 
     else 
     { 
       cout << "HS raw_ch = " << raw_ch << " is not correct. Enter a correct raw_ch." << endl; 
     }
  }
  else 
  { 
     if(raw_ch==0)        phys_ch={  0,  2,  4}; 
     else if(raw_ch==1)   phys_ch={  0,  2,  3}; 
     else if(raw_ch==2)   phys_ch={  0,  2,  2}; 
     else if(raw_ch==3)   phys_ch={  0,  2,  1}; 
     else if(raw_ch==4)   phys_ch={  0,  1,  4}; 
     else if(raw_ch==5)   phys_ch={  0,  1,  3}; 
     else if(raw_ch==6)   phys_ch={  0,  1,  2}; 
     else if(raw_ch==7)   phys_ch={  0,  1,  1}; 
     else if(raw_ch==8)   phys_ch={  0, -2,  1}; 
     else if(raw_ch==9)   phys_ch={  0, -2,  2}; 
     else if(raw_ch==10)  phys_ch={  0, -2,  3}; 
     else if(raw_ch==11)  phys_ch={  0, -2,  4}; 
     else if(raw_ch==12)  phys_ch={  0, -1,  1}; 
     else if(raw_ch==13)  phys_ch={  0, -1,  2}; 
     else if(raw_ch==14)  phys_ch={  0, -1,  3}; 
     else if(raw_ch==15)  phys_ch={  0, -1,  4}; 
     else if(raw_ch==16)  phys_ch={  0,  1,  1}; 
     else if(raw_ch==17)  phys_ch={  0,  1,  2}; 
     else if(raw_ch==18)  phys_ch={  0,  1,  3}; 
     else if(raw_ch==19)  phys_ch={  0,  1,  4}; 
     else if(raw_ch==20)  phys_ch={  0,  2,  1}; 
     else if(raw_ch==21)  phys_ch={  0,  2,  2}; 
     else if(raw_ch==22)  phys_ch={  0,  2,  3}; 
     else if(raw_ch==23)  phys_ch={  0,  2,  4}; 
     else 
     { 
       cout << "TP raw_ch = " << raw_ch << " is not correct. Enter a correct raw_ch." << endl; 
     }
  }

  return phys_ch;
}
 
//
void getTracks(std::vector<bool> hs_data, std::vector<bool> tp_data)
{ 
  // 1. convert to physical channels 
  // Hodoscope 
   
  
  // Trackpacks   


  // 2. do the fit 
  // note that the variance of a flat distribution is l^3/12 

}

// 3. estimate which channels are hit
//void getHitBars(std::vector<bool> hs_data, std::vector<bool> tp_data)

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
  std::cout << Form("Input MQ file : %s", mq_file_name.Data()) << std::endl; 
  TString new_mq_file_name = Form("UX5MilliQan_Run%i.%i_%s_hsadded.root",run,ifile,tag.Data()); 
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
  
  // get epoch time of the first event  
  t->GetEntry(0); 
  double event_time_fromTDC_begin = event_time_fromTDC;  
  t->GetEntry(999); 
  double event_time_fromTDC_end = event_time_fromTDC;  

  cout << "Start time of this MQ file: " << Form("%lf",event_time_fromTDC_begin) << endl;
  cout << "End time of this MQ file  : " << Form("%lf",event_time_fromTDC_end) << endl;
  
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

  cout << "HS files in consideration: " << endl; 
  cout << hs_previous_file << endl;
  cout << hs_current_file << endl;
  cout << hs_next_file << endl;
  
  cout <<  Form("Time: %d%02d%02d %02d:%02d:%02d", date->tm_year+1900, date->tm_mon+1, date->tm_mday, date->tm_hour, date->tm_min, date->tm_sec) << endl; 

  // ------------------------------------------------------------------------------------ 
  //  Store HS data in memory 
  // ------------------------------------------------------------------------------------ 
  // 1. if near boundary then look at two adjacent files  
  if(date->tm_min<3 && ifile>1)
  {
    loadHSData(hs_previous_file, hsDataLoaded, -1);
  }
  // 2. load events in the main file
  loadHSData(hs_current_file, hsDataLoaded, 0);

  // 3. if the end time is in the next file, add events to memory 
  if(date->tm_min>57)
  {
    loadHSData(hs_next_file, hsDataLoaded, 1);
  }

  cout << "Number of loaded HS events: " << hsDataLoaded.size() << endl; 
  
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
  //nentries = 0; // FIXME debug 
  for(int i=0; i<nentries; i++)
  {
    t->GetEntry(i); 
    mq_current_time = event_time_fromTDC;  
    
    // get the indices for sync window 
    int first_hs_evt = hsDataLoaded.size() * (mq_current_time-sync_window_sec-hs_begin_time)/hs_total_time;   
    int last_hs_evt  = hsDataLoaded.size() * (mq_current_time+sync_window_sec-hs_begin_time)/hs_total_time;   

    if(0) // debug 
    {
      cout << Form("%.6f",event_time_fromTDC) << endl; 
      cout << mq_current_time << " - " << mq_previous_time << " = " << mq_current_time-mq_previous_time << endl;  
      cout << first_hs_evt << " - " << last_hs_evt << endl; 
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
      cout << "dT synch range: " << range_low << " - " << range_high << endl;
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
      cout << Form("%.6f",event_time_fromTDC) << endl; 
      cout << mq_current_time << " - " << mq_previous_time << " = " << mq_current_time-mq_previous_time << endl;  
      cout << first_hs_evt << " - " << last_hs_evt << endl; 
    } 

    // Loop over selected HS events 
    double hs_current_time=0; 
    double hs_previous_time=0; 
    for(int ihs=0; ihs<hsDataLoaded.size(); ++ihs) 
    {
      hs_time = -1;
      hs_data->clear();
      tp_data->clear();
      
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

        // tracking 
        getTracks(hs_data,tp_data);

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
  cout << Form("Moving new output file %s to %s/Run%i_%s/HSAdded",new_mq_file_name.Data(),mq_file_dir.Data(),run,tag.Data()) << endl;
  gSystem->Exec(Form("mv %s %s/Run%i_%s/HSAdded",new_mq_file_name.Data(),mq_file_dir.Data(),run,tag.Data()));
  delete t; 
  ff->Close();
 
  // clean up 
  hsDataLoaded.clear();
  hsDataLoaded.shrink_to_fit();
  if(hsDataLoaded.size()!=0) cout << "[Error] Vector not clear" << endl;
  else cout << "vector clear" << endl;
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

  cout << "------------------------------" << endl; 
  cout << " Run   : " << run << endl; 
  cout << " Tag   : " << tag << endl; 
  cout << " files : " << ifile_begin << " - " << ifile_end << endl; 
  cout << "------------------------------" << endl; 
  cout << endl; 

  int temp;
  for(int i=ifile_begin; i<=ifile_end; i++) 
  { 
    temp = addHSData(tag, run, i);
    if(temp) cout << "[Error] Something went wrong: "<< temp << endl;
  }
}
# endif

