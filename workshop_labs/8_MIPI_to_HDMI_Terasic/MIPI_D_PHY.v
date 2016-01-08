module MIPI_D_PHY(
	input CLK,
	input RESET_n,
	input LP_P,
	input LP_N,
	
	
	
	output HS_MODE
);


reg [1:0] pre_pre_LP_PD;
reg [1:0] pre_LP_PD;
wire LP_PD;

assign LP_PD = {LP_P, LP_N};

always @(posedge CLK or negedge RESET_n)
begin
	if (~RESET_n)
	begin
		pre_LP_PD <= 2'b11;
		pre_pre_LP_PD <= 2'b11;
	end
	else if (LP_PD != pre_LP_PD)
	begin
		pre_pre_LP_PD <= pre_LP_PD;
		pre_LP_PD <= LP_PD;
	end
end


//
reg in_hs_mode;

assign HS_MODE = in_hs_mode;
always @(posedge CLK or negedge RESET_n)
begin
	if (~RESET_n)
		in_hs_mode <= 1'b0;
	else if (pre_pre_LP_PD == 2'b11 && pre_LP_PD == 2'b01 && LP_PD == 2'b00)
		in_hs_mode <= 1'b1;
	else if (LP_PD == 2'b11)
		in_hs_mode <= 1'b0;
end



endmodule

