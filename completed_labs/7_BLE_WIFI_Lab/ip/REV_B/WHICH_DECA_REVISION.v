// This module determines which DECA revision we are targeting through the Quartus II Revisions...
//  Nios II can read this value to determine whether to read the accelerometer via an ADC (Rev B)
//   or read the accelerometer via SPI (Rev C)

module WHICH_DECA_REVISION
(
	output [7:0] DECA_REV
);
  
	assign DECA_REV = 8'h01;  // REV B
//	assign DECA_REV = 8'h02;  // REV C


endmodule
