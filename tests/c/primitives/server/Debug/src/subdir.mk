################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ctest_prim_server.c 

OBJS += \
./src/ctest_prim_server.o 

C_DEPS += \
./src/ctest_prim_server.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/home/v/workspace/OpenSrc/SVCS/tests/c/primitives/include -I/home/v/workspace/OpenSrc/SVCS/utils/src -include/home/v/workspace/OpenSrc/SVCS/tests/c/primitives/include/cs_common.h -include/home/v/workspace/OpenSrc/SVCS/utils/src/svcs_client_server.c -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


