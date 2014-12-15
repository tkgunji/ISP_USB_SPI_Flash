################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../hal/CortexM3/GNU/hal.s \
../hal/CortexM3/GNU/hw_reg_access.s 

OBJS += \
./hal/CortexM3/GNU/hal.o \
./hal/CortexM3/GNU/hw_reg_access.o 


# Each subdirectory must supply rules for building sources it contributes
hal/CortexM3/GNU/%.o: ../hal/CortexM3/GNU/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Assembler'
	arm-none-eabi-gcc -c -mthumb -mcpu=cortex-m3 -specs=bare.specs  -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


