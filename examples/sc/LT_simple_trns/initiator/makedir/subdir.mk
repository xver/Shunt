################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
CPP_SRCS += \
../design.cpp \
../testbench.cpp

OBJS += \
../bin/design.o \
../bin//testbench.o

CPP_DEPS += \
../bin/design.d \
../bin/testbench.d


# Each subdirectory must supply rules for building sources it contributes
%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I$(SYSTEMC_HOME) -I$(SYSTEMC_HOME)include -I$(SHUNT_HOME)/utils/sc/src -I$(SHUNT_HOME)/utils/c/include -I$(SHUNT_HOME)/utils/c/src -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


