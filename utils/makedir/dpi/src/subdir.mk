################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../dpi/src/shunt_dpi.c

OBJS += \
./dpi/src/shunt_dpi.o

C_DEPS += \
./dpi/src/shunt_dpi.d


# Each subdirectory must supply rules for building sources it contributes
dpi/src/%.o: ../dpi/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -Wall -Werror -Wpedantic -Wextra $(USER_OPT) -shared -std=gnu11  -I"${SHUNT_HOME}/utils/dpi/include" -I"${SHUNT_HOME}/utils/c/include" -I"$(SHUNT_SVDPI)" -include$(SHUNT_SVDPI)/svdpi.h -include"${SHUNT_HOME}/utils/c/include/shunt_primitives.h" -include"${SHUNT_HOME}/utils/c/include/shunt_client_server.h" -include"${SHUNT_HOME}/utils/c/include/shunt_user_api.h" -include"${SHUNT_HOME}/utils/dpi/include/shunt_dpi.h" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


