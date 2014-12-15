================================================================================
                    SmartFusion2 USB ISP example
================================================================================

This example project demonstrates the use of the SmartFusion2 In System
Programming (ISP) using USB driver.

This example uses the USB driver in USB Device mode with MSC class. When
SmartFusion2 is connected to host PC through USB micro-AB connector, it will
appear as a removable mass storage drive. You can drag and drop the
programming file onto this drive which will then be used to program SmartFusion2.
The programming file must be stored on the root directory of this drive. Multiple
programming files can be copied on the drive.

--------------------------------------------------------------------------------
                            How to use this example
--------------------------------------------------------------------------------
Before requesting any programming option, user should copy bit stream file
(.spi file) on the root directory of the drive.

This example project requires MMUART1 to be connected to a host PC. The host PC
must connect to the serial port using a terminal emulator such as HyperTerminal
or PuTTY configured as follows:
    - 57600 baud
    - 8 data bits
    - 1 stop bit
    - no parity
    - no flow control

The example project will display instructions over the serial port.
This example scans for .spi files in the root directory and list out all .spi
files on UART terminal window.
User must select the desired file for programming and then provide the input to
indicate the required operation to be performed. 
Possible operations are

    - Scan for .spi files on drive
        Looks for  available .spi files on root directory and lists them
        on hyper terminal.

    - Select file
        Asks user to select the file to be programmed. User should enter
        the file name.

    - Authentication
        This option will perform Authentication operation using bitstream file
        to be programmed on to device. It is recommended to perform 
        this operation before Programming.
        Exit Status: Function will return with 0 in case of requested operation
                     is successful and returns error code in case of failure.

    - Programming
        This option will perform actual programming of bitstream on to device.
        At the start of programming device will go in to Flash*Freeze mode and
        it will come out of it after programming is complete.
        Exit Status- On RevD Silicon function will return with 0 in case of
                     requested operation is successful and returns error code
                     in case of failure.
                     On RevC Silicon reset will happen upon successful operation
                     but exit message won't be displayed.
    - Verification
        This option verifies the programmed bitstream with the bitstream file
        stored on the drive.
        Exit Status- On RevD Silicon function will return with 0 in case of
                     requested operation is successful and returns error code in
                     case of failure.
                     On RevC Silicon reset will happen upon successful operation
                     but exit message won't be displayed.

NOTE: In debug mode, Optimization level is set to -O2, as the code size 
      exceeding the sram limits.

--------------------------------------------------------------------------------
                            How to observe programming behaviour
--------------------------------------------------------------------------------
A sample programming file (.spi) is provided along with this example project. 
You may want to use this .spi file as a start. On completion of programming this
.spi file, LEDs on board will toggle alternatively. 

--------------------------------------------------------------------------------
                                Target hardware
--------------------------------------------------------------------------------
This example project is targeted at a SmartFusion2 design which has SPI0 and
MMUART1 enabled and connected to a host PC. The example project is built for a
design using a SmartFusion2 MSS CortexM3 clock frequency of 50MHz.
     - Enable IO pins of SPI0 and MMUART1 for availability in Flash*Freeze mode.
     - Select On-chip 25/50 MHz RC Oscillator as clock source in Flash*Freeze mode

--------------------------------------------------------------------------------
                                Jumper Settings
--------------------------------------------------------------------------------
For Dev-Kit
    To connect the SmartFusion2 SPI0 to the external on-board flash:
            J121: jumper between pins 1 and 2
            J110: jumper between pins 1 and 2
            J119: jumper between pins 1 and 2
            J118: jumper between pins 1 and 2

    Below jumper settings are required for the USB phy
            J139 - connect (1 - 2)  - USB reset
            J163 - connect (1 - 2)  - USB V-bus
            J164 - Mount for USB Host,OTG mode operations
            May not be mounted when operating in Device mode alone)

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                          Silicon revision dependencies
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
This example is built to execute on an M2S050T die (M2S050T revision C and RevD).
You will need to overwrite this example project's "drivers_config/sys_config" and
"CMSIS" folders with the one generated by Libero for your hardware design if
using a newer silicon revision.
The "drivers_config/sys_config" folder contains information about your hardware
design. This information is used by the CMSIS to initialize clock frequencies
global variables which are used by the SmartFusion2 drivers to derive baud
rates. The CMSIS boot code may also complete the device's clock configuration
depending on silicon version. The "CMSIS" and "drivers_config/sys_config" for
your design can be found in the "firmware" folder of your Libero design.
