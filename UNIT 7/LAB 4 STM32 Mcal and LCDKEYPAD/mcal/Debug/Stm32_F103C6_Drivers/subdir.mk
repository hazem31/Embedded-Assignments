################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/keypad.c 

OBJS += \
./Stm32_F103C6_Drivers/keypad.o 

C_DEPS += \
./Stm32_F103C6_Drivers/keypad.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/keypad.o: ../Stm32_F103C6_Drivers/keypad.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/cources/[0]embedded_LID/Proteus/stm/mcal/Stm32_F103C6_Drivers/inc" -I"D:/cources/[0]embedded_LID/Proteus/stm/mcal/Stm32_F103C6_Drivers/KEYPAD_DRIVER" -I"D:/cources/[0]embedded_LID/Proteus/stm/mcal/Stm32_F103C6_Drivers/LCD_DRIVER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32_F103C6_Drivers/keypad.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

