################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Ext_Drivers/Src/ADC.c \
../Ext_Drivers/Src/ring_buffer.c \
../Ext_Drivers/Src/systick.c \
../Ext_Drivers/Src/telemetry.c 

OBJS += \
./Ext_Drivers/Src/ADC.o \
./Ext_Drivers/Src/ring_buffer.o \
./Ext_Drivers/Src/systick.o \
./Ext_Drivers/Src/telemetry.o 

C_DEPS += \
./Ext_Drivers/Src/ADC.d \
./Ext_Drivers/Src/ring_buffer.d \
./Ext_Drivers/Src/systick.d \
./Ext_Drivers/Src/telemetry.d 


# Each subdirectory must supply rules for building sources it contributes
Ext_Drivers/Src/%.o Ext_Drivers/Src/%.su Ext_Drivers/Src/%.cyclo: ../Ext_Drivers/Src/%.c Ext_Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I/home/junaidahmadmir/Designs/Coding_Designs/ST-Workspace/Chip_Headers/CMSIS/Device/ST/STM32F4xx/Include -I/home/junaidahmadmir/Designs/Coding_Designs/ST-Workspace/Chip_Headers/CMSIS/Include -I"/home/junaidahmadmir/Designs/Coding_Designs/ST-Workspace/STM32F4xx_DISC_ADC_PROJECT/Ext_Drivers/Inc" -I"/home/junaidahmadmir/Designs/Coding_Designs/ST-Workspace/STM32F4xx_DISC_ADC_PROJECT/Ext_Drivers/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Ext_Drivers-2f-Src

clean-Ext_Drivers-2f-Src:
	-$(RM) ./Ext_Drivers/Src/ADC.cyclo ./Ext_Drivers/Src/ADC.d ./Ext_Drivers/Src/ADC.o ./Ext_Drivers/Src/ADC.su ./Ext_Drivers/Src/ring_buffer.cyclo ./Ext_Drivers/Src/ring_buffer.d ./Ext_Drivers/Src/ring_buffer.o ./Ext_Drivers/Src/ring_buffer.su ./Ext_Drivers/Src/systick.cyclo ./Ext_Drivers/Src/systick.d ./Ext_Drivers/Src/systick.o ./Ext_Drivers/Src/systick.su ./Ext_Drivers/Src/telemetry.cyclo ./Ext_Drivers/Src/telemetry.d ./Ext_Drivers/Src/telemetry.o ./Ext_Drivers/Src/telemetry.su

.PHONY: clean-Ext_Drivers-2f-Src

