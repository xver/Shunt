################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/apiC_Target.c

OBJS += \
./src/apiC_Target.o

C_DEPS += \
./src/apiC_Target.d


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler ./examples/c/user_api/target/makedir/src/subdir.mk:19'
	gcc   $(USER_OPT)  -I"${SHUNT_HOME}/utils/c/include" -include"${SHUNT_HOME}/utils/c/include/shunt_primitives.h" -include"${SHUNT_HOME}/utils/c/include/shunt_client_server.h" -include"${SHUNT_HOME}/utils/c/include/shunt_user_api.h" -include"${SHUNT_HOME}/utils/c/src/shunt_primitives.c" -include"${SHUNT_HOME}/utils/c/src/shunt_client_server.c" -include"${SHUNT_HOME}/utils/c/src/shunt_user_api.c" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


