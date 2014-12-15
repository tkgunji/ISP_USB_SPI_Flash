################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers_config/sys_config/sys_config.c 

OBJS += \
./drivers_config/sys_config/sys_config.o 

C_DEPS += \
./drivers_config/sys_config/sys_config.d 


# Each subdirectory must supply rules for building sources it contributes
drivers_config/sys_config/%.o: ../drivers_config/sys_config/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -DNDEBUG -I../CMSIS -I../CMSIS/startup_gcc -I../drivers/at25df641 -I../drivers/mss_gpio -I../drivers/mss_spi -I../drivers/mss_sys_services -I../drivers/mss_uart -I../drivers_config/sys_config -I../hal -I../hal/CortexM3 -I../hal/CortexM3/GNU -O2 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


