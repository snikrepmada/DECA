module TEMP_LM71CIMF(
	input clk,
	input reset,
	
	// mm slave
	input [1:0] address,
	input	s_write,
	input	[15:0] s_writedata,
	input	s_read,
	output	reg [15:0]   s_readdata,
	
	// export
	output	spi_cs_n,
	output	spi_sc,
	inout	   spi_sio
);

`define READ_CLK_NUM		 16
`define FULL_CLK_NUM		 32


`define WRITE_MODE   2'b01
`define READ_STATUS	2'b10
`define READ_DATA	   2'b11

reg  cs_n,data_o;
wire data_i;
reg [7:0]	clk_count; 
reg  status/*synthesis noprune*/;
reg [15:0]  read_data,data_mode/*synthesis noprune*/;

assign data_i= spi_sio;
assign spi_sio=((clk_count>=`READ_CLK_NUM+1) && (clk_count<=`FULL_CLK_NUM) ) ? data_o : 1'bz;
assign spi_sc=clk;
assign spi_cs_n=cs_n;

always @ (negedge clk)
begin
   if (reset)
	   begin
	     cs_n<=1;
		  status<=0;
		  data_mode<=0;
	   end
	else if(s_write && address==`WRITE_MODE )
	   begin
		  cs_n<=0;
		  status<=1'b0; 
		  data_mode<=s_writedata;
	    end
   else if(clk_count==`FULL_CLK_NUM)
      begin
		   cs_n<=1;
			status<=1'b1; 
		end
end

always @ (negedge clk)
begin
   if (reset)
	   s_readdata<=0;
   else if((address==`READ_STATUS) && s_read ) 
		s_readdata<= status ;
   else if ((address==`READ_DATA) && s_read )
      s_readdata<=read_data;
end


 //count clk
always @ (posedge clk)
begin	
	  if (reset)
	     clk_count<=8'h0;
	  else if(!cs_n && clk_count<`FULL_CLK_NUM)
        clk_count<=clk_count+1;
     else clk_count<=8'h0;
end

	  

always @ (negedge clk)
begin
   if (reset)
	   begin
	   read_data<=16'h0;
		data_o<=1'b0;
		end
	else if(clk_count>0 && clk_count<=`READ_CLK_NUM)
	     read_data[`READ_CLK_NUM-clk_count]<= data_i;
	else if(clk_count>`READ_CLK_NUM && clk_count<=`FULL_CLK_NUM)
	     data_o<=  data_mode[`FULL_CLK_NUM-clk_count];
	else  data_o<=1'b0;
end

			 
endmodule