################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/Stm32_F103C6_gpio_driver.c \
../Inc/keypad.c \
../Inc/lcd.c 

OBJS += \
./Inc/Stm32_F103C6_gpio_driver.o \
./Inc/keypad.o \
./Inc/lcd.o 

C_DEPS += \
./Inc/Stm32_F103C6_gpio_driver.d \
./Inc/keypad.d \
./Inc/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/Stm32_F103C6_gpio_driver.o: ../Inc/Stm32_F103C6_gpio_driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/cources/[0]embedded_LID/Proteus/stm/mcal/Stm32_F103C6_Drivers/inc" -I"D:/cources/[0]embedded_LID/Proteus/stm/mcal/Stm32_F103C6_Drivers/KEYPAD_DRIVER" -I"D:/cources/[0]embedded_LID/Proteus/stm/mcal/Stm32_F103C6_Drivers/LCD_DRIVER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/Stm32_F103C6_gpio_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Inc/keypad.o: ../Inc/keypad.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/cources/[0]embedded_LID/Proteus/stm/mcal/Stm32_F103C6_Drivers/inc" -I"D:/cources/[0]embedded_LID/Proteus/stm/mcal/Stm32_F103C6_Drivers/KEYPAD_DRIVER" -I"D:/cources/[0]embedded_LID/Proteus/stm/mcal/Stm32_F103C6_Drivers/LCD_DRIVER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/keypad.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Inc/lcd.o: ../Inc/lcd.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/cources/[0]embedded_LID/Proteus/stm/mcal/Stm32_F103C6_Drivers/inc" -I"D:/cources/[0]embedded_LID/Proteus/stm/mcal/Stm32_F103C6_Drivers/KEYPAD_DRIVER" -I"D:/cources/[0]embedded_LID/Proteus/stm/mcal/Stm32_F103C6_Drivers/LCD_DRIVER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/lcd.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

