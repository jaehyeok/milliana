void print()
{
  TChain ch("t"); 
  ch.Add("/net/cms6/cms6r0/milliqan/milliqanOffline/skims/thru_going/UX5MilliQan_Run*.TripleCoincidence.root");
  
  ch.SetScanField(0);
  
  ch.Scan("event_t_string:Max$(chan==0&&nPE>30):Max$(chan==1&&nPE>30):Max$(chan==2&&nPE>30):Max$(chan==3&&nPE>30):Max$(chan==4&&nPE>30):Max$(chan==5&&nPE>30):Max$(chan==6&&nPE>30):Max$(chan==7&&nPE>30):Max$(chan==8&&nPE>30):Max$(chan==9&&nPE>30):Max$(chan==10&&nPE>30):Max$(chan==11&&nPE>30)","Sum$(nPE>30&&(chan>=8&&chan<=11))>0&&Sum$(nPE>30&&(chan>=4&&chan<=7))>0&&Sum$(nPE>30&&(chan<4))>0","precision=2 col=20:2:2:2:2:2:2:2:2:2:2:2:2"); 

}
