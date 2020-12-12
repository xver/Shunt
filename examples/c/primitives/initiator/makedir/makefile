################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ${SHUNT_HOME}/bin/primC_Initiator

# Tool invocations
${SHUNT_HOME}/bin/primC_Initiator: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc  -Wall -Werror -Wpedantic -Wextra -o "${SHUNT_HOME}/bin/primC_Initiator" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) ${SHUNT_HOME}/bin/primC_Initiator
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
