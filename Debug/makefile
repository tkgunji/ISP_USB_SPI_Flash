################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include hal/CortexM3/subdir.mk
-include hal/CortexM3/GNU/subdir.mk
-include drivers_config/sys_config/subdir.mk
-include drivers/mss_uart/subdir.mk
-include drivers/mss_sys_services/subdir.mk
-include drivers/mss_spi/subdir.mk
-include drivers/mss_gpio/subdir.mk
-include drivers/at25df641/subdir.mk
-include CMSIS/subdir.mk
-include CMSIS/startup_gcc/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
MEMORYMAP += \
memory-map.xml \

IHEXFILES += \
ISP_USB_SPI_FLASH.hex \

SRECFILES += \
ISP_USB_SPI_FLASH.srec \

LISTINGS += \
ISP_USB_SPI_FLASH.lst \


# All Target
all: ISP_USB_SPI_FLASH secondary-outputs

# Tool invocations
ISP_USB_SPI_FLASH: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU C Linker'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -specs=bare.specs -L"C:\Users\cns-hadron\Desktop\microsemi\sf2\SoftConsole\ISP_USB_SPI_Flash\Debug" -T ../CMSIS/startup_gcc/debug-in-microsemi-smartfusion2-esram.ld -Wl,-Map=$(EXECUTABLE).map -Xlinker -gc-sections -o"ISP_USB_SPI_FLASH" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

memory-map.xml: $(EXECUTABLE)
	@echo 'Invoking: Memory map generator'
	actel-map -o "memory-map.xml" $(EXECUTABLE) $(BUILDCMD)
	@echo 'Finished building: $@'
	@echo ' '

ISP_USB_SPI_FLASH.hex: $(EXECUTABLE)
	@echo 'Invoking: GNU Intel Hex File Generator'
	arm-none-eabi-objcopy -O ihex $(EXECUTABLE) "ISP_USB_SPI_FLASH.hex"
	@echo 'Finished building: $@'
	@echo ' '

ISP_USB_SPI_FLASH.srec: $(EXECUTABLE)
	@echo 'Invoking: GNU S-Record Generator'
	arm-none-eabi-objcopy -O srec $(EXECUTABLE) "ISP_USB_SPI_FLASH.srec"
	@echo 'Finished building: $@'
	@echo ' '

ISP_USB_SPI_FLASH.lst: $(EXECUTABLE)
	@echo 'Invoking: GNU Listing Generator'
	arm-none-eabi-objdump -h -S $(EXECUTABLE) > "ISP_USB_SPI_FLASH.lst"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean::
	-$(RM) $(MEMORYMAP)$(OBJS)$(C_DEPS)$(SRECFILES)$(IHEXFILES)$(LISTINGS)$(EXECUTABLE) ISP_USB_SPI_FLASH
	-@echo ' '

secondary-outputs: $(MEMORYMAP) $(IHEXFILES) $(SRECFILES) $(LISTINGS)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
