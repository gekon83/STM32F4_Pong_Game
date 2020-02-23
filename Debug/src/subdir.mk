################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Fonts.c \
../src/SSD1331.c \
../src/main.c \
../src/pong.c \
../src/stm32f4xx_it.c \
../src/syscalls.c \
../src/system_stm32f4xx.c 

OBJS += \
./src/Fonts.o \
./src/SSD1331.o \
./src/main.o \
./src/pong.o \
./src/stm32f4xx_it.o \
./src/syscalls.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/Fonts.d \
./src/SSD1331.d \
./src/main.d \
./src/pong.d \
./src/stm32f4xx_it.d \
./src/syscalls.d \
./src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F411VETx -DSTM32F4 -DSTM32 -DSTM32F411E_DISCO -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/inc" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/CMSIS/core" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/CMSIS/device" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/HAL_Driver/Inc/Legacy" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/HAL_Driver/Inc" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/ampire480272" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/ampire640480" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/Common" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/cs43l22" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/exc7200" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/ft6x06" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/ili9325" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/ili9341" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/l3gd20" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/lis302dl" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/lis3dsh" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/ls016b8uy" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/lsm303dlhc" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/mfxstm32l152" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/n25q128a" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/n25q256a" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/n25q512a" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/otm8009a" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/ov2640" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/s25fl512s" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/s5k5cag" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/st7735" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/st7789h2" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/stmpe1600" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/stmpe811" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/ts3510" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Components/wm8994" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/Fonts" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities" -I"E:/_Projekty/_1_cpp/STM32F4_Pong_Game/Utilities/STM32F411E-Discovery" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


