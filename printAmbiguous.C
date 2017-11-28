//vector<string> split(const string& str, const string& delim)
vector<int> split(const string& str, const string& delim)
{
    //vector<string> tokens;
    vector<int> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        //if (!token.empty()) tokens.push_back(token);
        if (!token.empty()) tokens.push_back(stoi(token));
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

void printAmbiguous()
{ 
  //
  TH1D *h1 = new TH1D("h1","h1",100,-9.5, 89.5);
  
  //
  int sec_before=0;
  int sec_now=0; 
  string line_before; 

  //
  ifstream fin_data("data/sync/sync_nov27.txt");
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
      int diff; 
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
      stream >> diff; 
      stream >> hs_hits1; 
      stream >> hs_hits2; 
      stream >> hs_hits3; 
      stream >> hs_hits4; 
      stream >> hs_hits5; 
      stream >> hits; 

      if(date=="111111") break;

      vector<int> int_date = split(date, "/");
      vector<int> int_time = split(time, ":"); 

      int days = int_date.at(2);
      if(int_date.at(1)==9)  days = days -23;
      if(int_date.at(1)==10) days = days + 7;
      if(int_date.at(1)==11) days = days + 31; 
      int sec = int_time.at(0)*3600 + int_time.at(1)*60 + int_time.at(2);
      sec = sec + days*86400;  

      int sec_diff = sec - sec_before;
      sec_before = sec; 

      h1->Fill(sec_diff);

      if (sec_diff<4 && sec_diff>-4) 
      {   
        cout << line_before << endl;
        cout << line_data << endl;
      }
      line_before = line_data;
//      cout << sec << endl;

    }
  }

  h1->Draw("e");
}
