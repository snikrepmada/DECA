//================================================
// This File is used to enbale design of control endpoint controller inside the hardware
// to verify the ULPI Interface functinality of reference design with HOST PC.
// 
//
// Macro SR_ENABLE should be disabled in this file to implement the control 
// endpoint controller inside the hardware. 
//
// Debug mode implementation of the IP Core is useful for debug purpose only.If reference
// design is designed from scratch or reference design is generated for any new usb development 
// board then there can be a number of problems for failed usb communication with HOST PC.
// Debug mode will be useful to verify the pin connection of ULPI Phy chip interface as 
// well as ULPI Phy chip functinality on the board.
//
// Compilation of USB20SR IP Core reference design in Debug mode will generate a standalone 
// SOF file with internal support of default device enumeration on HOST PC during device 
// attachement through USB cable without nios.
//
//
//******************************
// Steps for debug mode testing
//******************************
// 1) Disable SR_ENABLE MACRO 
// 2) Regenerate reference design
// 3) Download SOF file on board
// 4) Connect device with HOST PC through USB2.0 compliant cable
// 5) Look inside the USB view. Default sls usb device should be enumerated on HOST PC.
// 6) If device enumeration fails then debug the hardware problem.
// 7) After successful device enumeration enable SR_ENABLE macro and switch back to normal mode.
// 8) Continue with your reference design testing with nios.
//================================================
`define   SR_ENABLE




