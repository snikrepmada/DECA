module  TP   (
 input  RESET_N , 
 input  SYS_CLK  ,   
 input  CLK_50 , 
 input  CS   ,
 input  SCLK,
 input  DIN ,
 input  DO   ,
 input  INT1 , 
 input  INT2 , 
 input  BYTE ,
 
 //--test
 input  [7:0]ST  ,
 input  [7:0]BIT_CNT ,
 input   [7:0]WORD_CNT ,
 input  [15:0]RDATA  ,

 
 input [15:0] OUT_X ,//two’s complement left-justified.\
 input [7:0] WHO_AM_I ,
 input [7:0] OUT_X_L  ,
 input [7:0] OUT_X_H   ,
 input  [16:0]  data_x ,
 input   [16:0] s_data_x ,
 input   DATA_RDY  
 );
 endmodule

