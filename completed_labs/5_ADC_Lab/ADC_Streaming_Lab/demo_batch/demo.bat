
@ REM ######################################
@ REM # Variable to ignore <CR> in DOS
@ REM # line endings
@ set SHELLOPTS=igncr

@ REM ######################################
@ REM # Variable to ignore mixed paths
@ REM # i.e. G:/$SOPC_KIT_NIOS2/bin
@ set CYGWIN=nodosfilewarning

@set QUARTUS_BIN=%QUARTUS_ROOTDIR%\\bin64
@if exist %QUARTUS_BIN%\\quartus_pgm.exe (goto DownLoad)


:DownLoad
 %QUARTUS_BIN%\\quartus_pgm.exe -m jtag -c 1 -o "p;ADC_Streaming_Lab.sof"
@ set SOPC_BUILDER_PATH=%SOPC_KIT_NIOS2%+%SOPC_BUILDER_PATH%
@ ECHO ""
@ ECHO Play audio file for VU meter,
@ ECHO launch the ADC Toolkit to view the waveform, or
@ ECHO launch Signal Tap to see data captured
@ pause

