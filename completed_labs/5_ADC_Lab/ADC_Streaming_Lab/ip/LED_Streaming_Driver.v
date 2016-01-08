

//--------------------------
//	Declaration and ports
//--------------------------

module LED_Streaming_Driver (

	//clocks and resets
	input						sys_clk,
	input						reset_n,	
	
	//avalon_master to control ADC
	output reg [15:0] 	avalon_address,
	output	reg			avalon_read,
	output	reg			avalon_waitrequest,
	input		[31:0]		avalon_readdata,
	output	reg			avalon_write,
	output	reg [31:0]	avalon_writedata,
	
	// avalon streaming sink to receive ADC data
	input 					response_valid,
	input [4:0] 			response_channel,
	input [11:0] 			response_data,
	input 					response_startofpacket,
	input 					response_endofpacket,
	
	//gpio
	output	[7:0]		LED_OUT
	
);


////////////////////////////////////////////
// response
reg [4:0]  cur_adc_ch;
reg [11:0] adc_sample_data;
reg [10:0] pcm_abs;
reg [7:0]  vol;
reg [2:0]  reg_state; // state variable
reg [11:0] reg_linein_data;
reg [11:0] reg_ch0_data;
reg [11:0] reg_ch1_data;
 
 // State machine to control ADC configuration cycles
`define IDLE 		3'b000
`define ADC_START	3'b001
`define ADC_RUN 	3'b010

`define PCM_ZERO				12'h800
`define ADC_CMD_ADDR 		16'h0000
`define ADC_LINE_IN_CHAN 	5'h05
`define ADC_CH0 				5'h00
`define ADC_CH1			 	5'h01


// Configure the ADC using the Avalon Control & Status Register
 always @(posedge sys_clk or negedge reset_n)
 	if (!reset_n) 
 		begin
 			reg_state <= `IDLE;
			avalon_address <= `ADC_CMD_ADDR;
			avalon_read <= 1'b0;
			avalon_write <= 1'b0;
			avalon_writedata <= 32'b0;			
 		end
 	else	
	      case (reg_state)
		      `IDLE:		
		      		begin
							reg_state <= `ADC_START;
							avalon_address <= `ADC_CMD_ADDR;
							avalon_read <= 1'b0;
							avalon_write <= 1'b0;
							avalon_writedata <= 32'b0;
		      		end
		      `ADC_START:	
		      		begin
							reg_state <= `ADC_RUN;
							avalon_address <= `ADC_CMD_ADDR;
							avalon_read <= 1'b0;
							avalon_write <= 1'b1;
							avalon_writedata <= 32'b1;  // set the ADC Run bit
		      		end
		      `ADC_RUN: 
		      		begin
							reg_state <= `ADC_RUN;  // stay here
							avalon_address <= `ADC_CMD_ADDR;
							avalon_read <= 1'b0;
							avalon_write <= 1'b0;
							avalon_writedata <= 32'b0;
		      		end
	      endcase	
			
		
// latch the data from the response channel
always @ (posedge sys_clk)
begin
	if (response_valid)
	      case (response_channel)
		      `ADC_LINE_IN_CHAN:		
		      		begin
							reg_linein_data <= response_data;
		      		end
		      `ADC_CH0:	
		      		begin
							reg_ch0_data <= response_data;
		      		end
		      `ADC_CH1: 
		      		begin
							reg_ch1_data <= response_data;
		      		end
	      endcase			
end			

// adc_sample_data: hold 12-bit adc sample value
// Vout = Vin + 1.25V?	 
	 
////////////////////////////////////////////
// response	 
always @ (posedge sys_clk)
begin
		if (reg_linein_data >= `PCM_ZERO)
			pcm_abs <= reg_linein_data - `PCM_ZERO;
		else if (reg_linein_data == 0)
			pcm_abs <= `PCM_ZERO - 1;
		else
			pcm_abs <= `PCM_ZERO - reg_linein_data;
end	

// Translate the adc data into LED settings
always @ (posedge sys_clk)
begin
	case(pcm_abs[10:8])
	 3'b000:  vol = 8'b00000001;
	 3'b001:  vol = 8'b00000011;
	 3'b010:  vol = 8'b00000111;
	 3'b011:  vol = 8'b00001111;
	 3'b100:  vol = 8'b00011111;
	 3'b101:  vol = 8'b00111111;
	 3'b110:  vol = 8'b01111111;
	 3'b111:  vol = 8'b11111111;
	endcase
end

assign LED_OUT[7:0] = ~vol[7:0];  // led is active low

endmodule

	