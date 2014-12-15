################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/mss_gpio/mss_gpio.c 

OBJS += \
./drivers/mss_gpio/mss_gpio.o 

C_DEPS += \
./drivers/mss_gpio/mss_gpio.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/mss_gpio/%.o: ../drivers/mss_gpio/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -I../CMSIS -I../CMSIS/startup_gcc -I../drivers/at25df641 -I../drivers/mss_gpio -I../drivers/mss_spi -I../drivers/mss_sys_services -I../drivers/mss_uart -I../drivers_config/sys_config -I../hal -I../hal/CortexM3 -I../hal/CortexM3/GNU -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


