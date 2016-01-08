When launching demo.bat, a design downloads to the DECA board that differs slightly from the lab.

The hardware is the same, the software uses a fixed SSID value of DallasLogicWiFi

If you were to run the lab's ble_wifi_app.elf file using this demo.bat instead, you will find that the nios2-terminal does not currently accept user input.

There is an Altera knowledge database with more infomation:
https://www.altera.com/support/support-resources/knowledge-base/solutions/rd12312014_400.html

"Due to a problem in the Quartus® II software version 14.1, the Windows version of the nios2-terminal command line program does not send characters, it can only receive characters."