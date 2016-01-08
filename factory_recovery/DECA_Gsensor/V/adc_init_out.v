module  adc_init_out (  
input adc_clk,
input reset_n , 

input response_valid , 
input [11:0] response_data , 

output  reg command_valid ,
output  reg [11:0]data_z 


) ;

reg [23:0] command_cnt ; 
//-- ADC data out --
always @(posedge adc_clk)
  begin
    if (!reset_n)
      data_z <= 'b0 ;
    else
      if ( response_valid)
        data_z <= response_data ;
      else
        data_z <= data_z ;
  end

//--ADC initially 
always @(posedge adc_clk or negedge reset_n)
  begin
    if (!reset_n)
      command_cnt <= 'b0 ;
    else
      if (command_cnt == 24'h00_2710)
         command_cnt <= 'b0 ;
      else
        command_cnt <= command_cnt + 1'b1 ;
  end

always @(posedge adc_clk or negedge reset_n)
  begin
    if (!reset_n)
      command_valid <= 1'b0 ;
    else
      if (command_cnt <= 24'h00_0001)
        command_valid <= 1'b1 ;
      else
        command_valid <= 1'b0 ;
  end
endmodule 
