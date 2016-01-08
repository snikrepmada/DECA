
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
%QUARTUS_BIN%\\quartus_pgm.exe -m jtag -c 1 -o "p;mipi_to_hdmi_terasic.sof"
@ set SOPC_BUILDER_PATH=%SOPC_KIT_NIOS2%+%SOPC_BUILDER_PATH%
@ ECHO.
@ ECHO run this command in System Console:   source vipmix.tcl
@ "%QUARTUS_BIN%\\cygwin\bin\bash.exe" --rcfile ".\demo.sh"

