################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../c/src/shunt_client_server.c \
../c/src/shunt_primitives.c \
../c/src/shunt_user_api.c 

OBJS += \
./c/src/shunt_client_server.o \
./c/src/shunt_primitives.o \
./c/src/shunt_user_api.o 

C_DEPS += \
./c/src/shunt_client_server.d \
./c/src/shunt_primitives.d \
./c/src/shunt_user_api.d 


# Each subdirectory must supply rules for building sources it contributes
c/src/%.o: ../c/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=gnu11 -Wall -Werror -Wpedantic -Wextra -Wno-odr  -shared -I"${SHUNT_HOME}/utils/dpi/include" -I"${SHUNT_HOME}/utils/c/include"  -I"$(SHUNT_SVDPI)" -include$(SHUNT_SVDPI)/svdpi.h -include"${SHUNT_HOME}/utils/c/include/shunt_primitives.h" -include"${SHUNT_HOME}/utils/c/include/shunt_client_server.h" -include"${SHUNT_HOME}/utils/c/include/shunt_user_api.h" -include"${SHUNT_HOME}/utils/dpi/include/shunt_dpi.h" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


