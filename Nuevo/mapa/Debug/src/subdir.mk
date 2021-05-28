################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/mapa.c \
../src/niv_gui.c \
../src/tad_niv.c 

OBJS += \
./src/mapa.o \
./src/niv_gui.o \
./src/tad_niv.o 

C_DEPS += \
./src/mapa.d \
./src/niv_gui.d \
./src/tad_niv.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


