################################################################################
# Automatically-generated file. Do not edit!
################################################################################

O_SRCS := 
C_SRCS := 
S_UPPER_SRCS := 
S_SRCS := 
OBJ_SRCS := 
MEMORYMAP := 
OBJS := 
C_DEPS := 
SRECFILES := 
IHEXFILES := 
LISTINGS := 
EXECUTABLE := 

# Every subdirectory with source files must be described here
SUBDIRS := \
. \
hal/CortexM3 \
hal/CortexM3/GNU \
drivers_config/sys_config \
drivers/mss_uart \
drivers/mss_sys_services \
drivers/mss_spi \
drivers/mss_gpio \
drivers/at25df641 \
CMSIS \
CMSIS/startup_gcc \

################################################################################
# Microsemi SoftConsole IDE Variables
################################################################################

BUILDCMD = arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -specs=bare.specs -L"C:\Users\cns-hadron\Desktop\microsemi\sf2\SoftConsole\ISP_USB_SPI_Flash" -T ../CMSIS/startup_gcc/production-execute-in-place.ld -Wl,-Map=$(EXECUTABLE).map -Xlinker -gc-sections 
SHELL := cmd.exe
EXECUTABLE := ISP_USB_SPI_FLASH

# Target-specific items to be cleaned up in the top directory.
clean::
	-$(RM) $(wildcard ./*.map) 
