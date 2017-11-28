void print()
{
  TChain ch("t"); 
  ch.Add("../realTripleCoinc.root");
  
  ch.SetScanField(0);
  
  //ch.Scan("event_t_string:Max$(chan==0&&nPE>30):Max$(chan==1&&nPE>30):Max$(chan==2&&nPE>30):Max$(chan==3&&nPE>30):Max$(chan==4&&nPE>30):Max$(chan==5&&nPE>30):Max$(chan==6&&nPE>30):Max$(chan==7&&nPE>30):Max$(chan==8&&nPE>30):Max$(chan==9&&nPE>30):Max$(chan==10&&nPE>30):Max$(chan==11&&nPE>30)","Sum$(nPE>30&&(chan>=8&&chan<=11))>0&&Sum$(nPE>30&&(chan>=4&&chan<=7))>0&&Sum$(nPE>30&&(chan<4))>0","precision=2 col=20:2:2:2:2:2:2:2:2:2:2:2:2"); 

 // high threshold
 //ch.Scan("beam:run:file:event:event_t_string:Max$(chan==0&&nPE>300):Max$(chan==1&&nPE>300):Max$(chan==2&&nPE>300):Max$(chan==3&&nPE>300):Max$(chan==4&&nPE>300):Max$(chan==5&&nPE>300):Max$(chan==6&&nPE>300):Max$(chan==7&&nPE>300):Max$(chan==8&&nPE>100):Max$(chan==9&&nPE>100):Max$(chan==10&&nPE>30):Max$(chan==11&&nPE>30):(MinIf$(time_module_calibrated, layer==3)-MinIf$(time_module_calibrated, layer==1))", 
 //        "(Sum$(nPE>100&&chan>=8&&chan<=9)+Sum$(nPE>30&&chan>=10&&chan<=11))>0&&Sum$(nPE>300&&(chan>=4&&chan<=7))>0&&Sum$(nPE>300&&(chan<4))>0",
 //         "precision=2 col=2:5:5:10:20:2:2:2:2:2:2:2:2:2:2:2:10");
 // high threshold
 ch.Scan("beam:run:file:event:event_t_string:Max$(chan==0):Max$(chan==1):Max$(chan==2):Max$(chan==3):Max$(chan==4):Max$(chan==5):Max$(chan==6):Max$(chan==7):Max$(chan==8):Max$(chan==9):Max$(chan==10):Max$(chan==11):(MinIf$(time_module_calibrated, layer==3)-MinIf$(time_module_calibrated, layer==1))", 
         "Sum$(nPE*(chan>=8&&chan<=11))>30&&Sum$(nPE*(chan>=4&&chan<=7))>300&&Sum$(nPE*(chan<4))>300",
         "precision=2 col=2:5:5:10:20:2:2:2:2:2:2:2:2:2:2:2:10");
}
