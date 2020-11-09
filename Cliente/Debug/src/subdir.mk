################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Cliente.c \
../src/conexion.c \
../src/consola.c \
../src/mensajes.c 

OBJS += \
./src/Cliente.o \
./src/conexion.o \
./src/consola.o \
./src/mensajes.o 

C_DEPS += \
./src/Cliente.d \
./src/conexion.d \
./src/consola.d \
./src/mensajes.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/home/utnso/tp-2020-2c-GrupoSOK3072/Utilss/src -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


