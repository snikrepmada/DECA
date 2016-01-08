module SPI_CTRL	(	
input				iCLK,
input	   [15:0]iCREG,
output	reg [15:0]oADC_D,

output	reg	oDIN,
output	reg 	oCS_n,
output	reg	oSCLK,
input				iDOUT
				);
					
reg [3:0] ST; 
reg [4:0] COUNTER ;
reg [15:0]CREG ;
reg [15:0]ADC_DATA;

always@(posedge iCLK )
begin
case (ST)
0:begin 
      ST     <=1;
		oCS_n  <=1; 
		oSCLK  <=1;
		COUNTER<=15;
		CREG   <=iCREG ;
		{ oADC_D[15:0] , ADC_DATA[15:0] } <= { ADC_DATA[15:0] ,16'h0};
  end 
1:begin 
      oCS_n  <=0; 
      ST<=2;
  end 
2:begin 
      {oDIN,CREG[15:0]} <= {CREG[15:0], 1'b0} ;
       ADC_DATA[15:0]   <= {ADC_DATA[14:0], iDOUT} ; 		
       ST<=3;
  end 
3:begin 
      oSCLK  <=0;
      COUNTER<=COUNTER-1;
      ST<=4;
  end 
4:begin 
      oSCLK  <=1;
      if ( COUNTER!=0) ST<=2 ; 
      else ST<=0 ;
  end 
endcase
end






endmodule
