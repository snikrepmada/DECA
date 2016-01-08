
module ADC_Top(

	//////////// CLOCKS //////////
	input 		          		ADC_CLK_10,
	input 		          		MAX10_CLK1_50,

	//////////// Buttons //////////
	input 		     [1:0]		KEY,

	//////////// LED //////////
	output		     [7:0]		LED

);


//Instantiate the Qsys System

    adc_qsys u0 (
        .clk_clk                              (MAX10_CLK1_50),       // clk.clk
        .reset_reset_n                        (KEY[0]),              // reset.reset_n
		  .led_out_export 							 (LED) 						// led_out.export
	  );

endmodule
