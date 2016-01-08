module led_driver (
  ////  System  ////
    ////  output  ////
    oLED,

    ////  input  ////
    iRSTN,
    iCLK,
    iDIG,
    iG_INT2,
    fine_tune

    ) ;

    input iRSTN ;
    input iCLK ;
    input [9:0] iDIG ;
    input iG_INT2 ;
    input fine_tune ;

    output [7:0] oLED ;

    reg [7:0] oLED ;

//=======================================================
//  REG/WIRE declarations
//=======================================================
    reg	[4:0] select_data ;
    wire signed_bit ;
    wire [3:0] abs_select_high ;
    
    reg ig_int2_dly ;
    reg dig_latch ;
    reg dig_acc_act ;
    reg [9:0] dig_1 ;
    reg [9:0] dig_2 ;
    reg [9:0] dig_3 ;
    reg [9:0] dig_4 ;
    reg [9:0] dig_5 ;
    reg [9:0] dig_6 ;
    reg [9:0] dig_7 ;
    reg [9:0] dig_8 ;
    reg [9:0] dig_9 ;
    reg [9:0] dig_10 ;
    reg [9:0] dig_11 ;
    reg [9:0] dig_12 ;
    reg [9:0] dig_13 ;
    reg [9:0] dig_14 ;
    reg [9:0] dig_15 ;
    reg [9:0] dig_16 ;
    reg [9:0] dig_17 ;
    reg [13:0] dig_acc ;
    wire [9:0] dig_new ;
    reg select_data_upd ;
    reg led_upd ;

    reg [9:0] dig_offset ;
    reg dig_offset_upd ;
    reg [13:0] dig_offset_acc ;
    reg dig_off_acc_enb ;
    reg [15:0] dig_offset_dcnt ;
    wire [9:0] pre_dig_offset ;
    reg det_dig_offset ;
//=======================================================
//  Structural coding
//=======================================================

  ////////  dig_offset bus  ////////////////
  always @(posedge iCLK or negedge iRSTN)
    begin
      if (!iRSTN)
        dig_offset <= 'b0 ;
      else
        if (dig_offset_upd)
          dig_offset <= dig_offset_acc[13:4] ;
        else
          dig_offset <= dig_offset ;
    end
  ////////  dig_offset bus end  ////////////////

  ////////  dig_offset_upd signal  ////////////////
  always @(posedge iCLK or negedge iRSTN)
    begin
      if (!iRSTN)
        dig_offset_upd <= 1'b0 ;
      else
        if ( dig_off_acc_enb  &&  dig_acc_act &&  ( dig_offset_dcnt == 16'h0000) )
          dig_offset_upd <= 1'b1 ;
        else
          dig_offset_upd <= 1'b0 ;
    end
  ////////  dig_offset_upd signal end  ////////////////

  ////////  dig_offset_acc bus  ////////////////
  always @(posedge iCLK or negedge iRSTN)
    begin
      if (!iRSTN)
        dig_offset_acc <= 'b0 ;
      else
        if (dig_off_acc_enb && dig_acc_act)
          dig_offset_acc <= dig_offset_acc + pre_dig_offset ;
        else
          dig_offset_acc <= dig_offset_acc ;
    end
  ////////  dig_offset_acc bus end  ////////////////

  ////////  dig_off_acc_enb signal  ////////////////
  always @(posedge iCLK or negedge iRSTN)
    begin
      if (!iRSTN)
        dig_off_acc_enb <= 1'b0 ;
      else
        if (dig_acc_act && (dig_offset_dcnt == 16'h0010))
          dig_off_acc_enb <= 1'b1 ;
        else
          if (dig_acc_act && (dig_offset_dcnt == 16'h0000))
            dig_off_acc_enb <= 1'b0 ;
          else
            dig_off_acc_enb <= dig_off_acc_enb ;
    end
  ////////  dig_off_acc_enb signal end  ////////////////

  ////////  dig_offset_dcnt bus  ////////////////
  always @(posedge iCLK or negedge iRSTN)
    begin
      if (!iRSTN)
        dig_offset_dcnt <= 16'h1390 / 4  ;  // 5sec * (1000ms/1ms)
      else
        if (dig_acc_act)
          if (dig_offset_dcnt == 16'h0000)
            dig_offset_dcnt <= 16'h0000 ;
          else
            dig_offset_dcnt <= dig_offset_dcnt - 1'b1 ;
        else
          dig_offset_dcnt <= dig_offset_dcnt ;
    end
  ////////  dig_offset_dcnt bus end  ////////////////

  ////////  pre_dig_offset bus  ////////////////
  assign pre_dig_offset = 10'h200 - iDIG ;
  ////////  pre_dig_offset bus end  ////////////////

  ////////  det_dig_offset signal  ////////////////
  always @(posedge iCLK or negedge iRSTN)
    begin
      if (!iRSTN)
        det_dig_offset <= 1'b1;
      else
        if (dig_offset_upd)
          det_dig_offset <= 1'b0 ;
        else
          det_dig_offset <= det_dig_offset ;
    end
  ////////  det_dig_offset signal end  ////////////////

  ////////  ig_int2_dly signal  ////////////////
  always @(posedge iCLK or negedge iRSTN)
    begin
      if (!iRSTN)
        ig_int2_dly <= 1'b0 ;
      else
        ig_int2_dly <= iG_INT2 ;
    end
  ////////  ig_int2_dly signal end  ////////////////

  ////////  dig_latch signal  ////////////////
  always @(posedge iCLK or negedge iRSTN)
    begin
      if (!iRSTN)
        dig_latch <= 1'b0 ;
      else
        if (!iG_INT2 && ig_int2_dly)
          dig_latch <= 1'b1 ;
        else
          dig_latch <= 1'b0 ;
    end
  ////////  dig_latch signal end  ////////////////

  ////////  dig_acc_act signal  ////////////////
  always @(posedge iCLK or negedge iRSTN)
    begin
      if (!iRSTN)
        dig_acc_act <= 1'b0 ;
      else
        dig_acc_act <= dig_latch ;
    end
  ////////  dig_acc_act signal end  ////////////////

  ////////  iDIG to dig_17 shift  ////////////////
  always @(posedge iCLK or negedge iRSTN)
    begin
      if (!iRSTN)
        begin
          dig_1  <= 'b0 ;
          dig_2  <= 'b0 ;
          dig_3  <= 'b0 ;
          dig_4  <= 'b0 ;
          dig_5  <= 'b0 ;
          dig_6  <= 'b0 ;
          dig_7  <= 'b0 ;
          dig_8  <= 'b0 ;
          dig_9  <= 'b0 ;
          dig_10 <= 'b0 ;
          dig_11 <= 'b0 ;
          dig_12 <= 'b0 ;
          dig_13 <= 'b0 ;
          dig_14 <= 'b0 ;
          dig_15 <= 'b0 ;
          dig_16 <= 'b0 ;
          dig_17 <= 'b0 ;
        end
      else
        if (dig_latch)
          begin
            dig_1  <= iDIG + dig_offset ;
            dig_2  <= dig_1  ;
            dig_3  <= dig_2  ;
            dig_4  <= dig_3  ;
            dig_5  <= dig_4  ;
            dig_6  <= dig_5  ;
            dig_7  <= dig_6  ;
            dig_8  <= dig_7  ;
            dig_9  <= dig_8  ;
            dig_10 <= dig_9  ;
            dig_11 <= dig_10 ;
            dig_12 <= dig_11 ;
            dig_13 <= dig_12 ;
            dig_14 <= dig_13 ;
            dig_15 <= dig_14 ;
            dig_16 <= dig_15 ;
            dig_17 <= dig_16 ;
          end
        else
          begin
            dig_1  <= dig_1  ;
            dig_2  <= dig_2  ;
            dig_3  <= dig_3  ;
            dig_4  <= dig_4  ;
            dig_5  <= dig_5  ;
            dig_6  <= dig_6  ;
            dig_7  <= dig_7  ;
            dig_8  <= dig_8  ;
            dig_9  <= dig_9  ;
            dig_10 <= dig_10 ;
            dig_11 <= dig_11 ;
            dig_12 <= dig_12 ;
            dig_13 <= dig_13 ;
            dig_14 <= dig_14 ;
            dig_15 <= dig_15 ;
            dig_16 <= dig_16 ;
            dig_17 <= dig_17 ;
          end
    end
  ////////  iDIG to dig_17 shift end  ////////////////

  ////////  dig_acc bus  ////////////////
  always @(posedge iCLK or negedge iRSTN)
    begin
      if (!iRSTN)
        dig_acc <= 'b0 ;
      else
        if (dig_acc_act)
          dig_acc <= dig_acc + dig_1 - dig_17 ;
        else
          dig_acc <= dig_acc ;
    end
  ////////  dig_acc bus end  ////////////////

  ////////  dig_new bus  ////////////////
  assign dig_new = dig_acc[13:4] ;
  ////////  dig_new bus end  ////////////////

  ////////  select_data_upd signal  ////////////////
  always @(posedge iCLK or negedge iRSTN)
    begin
      if (!iRSTN)
        select_data_upd <= 1'b0 ;
      else
        select_data_upd <= dig_acc_act ;
    end
  ////////  select_data_upd signal end  ////////////////

  ////////  led_upd signal  ////////////////
  always @(posedge iCLK or negedge iRSTN)
    begin
      if (!iRSTN)
        led_upd <= 1'b0 ;
      else
        led_upd <= select_data_upd ;
    end
  ////////  led_upd signal end  ////////////////


  ////////  select_data bus  ////////////////
  always @(posedge iCLK or negedge iRSTN)
    begin
      if (!iRSTN)
        select_data <= 'b0 ;
      else
        if (select_data_upd)
          if (fine_tune)
            if (dig_new[9])
              select_data <= {dig_new[9], |dig_new[8:5], dig_new[4:2]} ;
            else
              select_data <= {dig_new[9], &dig_new[8:5], dig_new[4:2]} ;
          else
            select_data <= dig_new[9:5] ;
        else
          select_data <= select_data ;
    end
  ////////  select_data bus end  ////////////////

assign signed_bit = select_data[4];
assign abs_select_high = signed_bit ? ~select_data[3:0] : select_data[3:0]; // the negitive number here is the 2's complement - 1

  ////////  oLED bus  ////////////////
  always @(posedge iCLK or negedge iRSTN)
    begin
      if (!iRSTN)
        oLED <= 8'h00 ;
      else
        if (det_dig_offset)
          oLED <= {8{dig_offset_dcnt[9]}} ;
        else
          if (led_upd)
            casex(abs_select_high[3:0])  // synopsys parallel_case
              4'b111x : oLED <= 8'b0001_1000 ;
              4'b1101 :
                begin
                  if (signed_bit)
                    oLED <= 8'b0001_0000 ;
                  else
                    oLED <= 8'b0000_1000 ;
                end
              4'b1100 :
                begin
                  if (signed_bit)
                    oLED <= 8'b0010_0000 ;
                  else
                    oLED <= 8'b0000_0100 ;
                end
              4'b1011 :
                begin
                  if (signed_bit)
                    oLED <= 8'b0100_0000 ;
                  else
                    oLED <= 8'b0000_0010 ;
                end
              4'b1001 :
                begin
                  if (signed_bit)
                    oLED <= 8'b1000_0000 ;
                  else
                    oLED <= 8'b0000_0001 ;
                end
              default :
                begin
                  if (signed_bit)
                    oLED <= 8'b1000_0000 ;
                  else
                    oLED <= 8'b0000_0001 ;
                end
            endcase 
          else
            oLED <= oLED ;
    end
  ////////  oLED bus end  ////////////////

endmodule
