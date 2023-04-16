################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk


-include c/src/subdir.mk
-include subdir.mk
-include objects.mk

ifeq ($(MAKECMDGOALS),$(filter $(MAKECMDGOALS),all ${SHUNT_HOME}/bin/libutils.so))
-include dpi/src/subdir.mk
endif

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:  ${SHUNT_HOME}/bin/libutils.so ${SHUNT_HOME}/bin/libCutils.so

# Tool invocations
${SHUNT_HOME}/bin/libutils.so: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc -std=gnu11 -Wall -Werror -Wpedantic -Wextra  -Wno-odr $(USER_OPT) -shared -o "${SHUNT_HOME}/bin/libutils.so" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

${SHUNT_HOME}/bin/libCutils.so: $(C_OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc -std=gnu11 -Wall -Werror -Wpedantic -Wextra  -Wno-odr $(USER_OPT) -shared -o "${SHUNT_HOME}/bin/libCutils.so" $(C_OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM)	$(OBJS)	$(C_DEPS) $(LIBRARIES) ${SHUNT_HOME}/bin/libutils.so ${SHUNT_HOME}/bin/libCutils.so ${SHUNT_HOME}/bin/build ${SHUNT_HOME}/bin/shunt* ${SHUNT_HOME}/bin/__pycache__ ${SHUNT_HOME}/bin/_shunt*

	-@echo ' '
swig_py:
	cd ${SHUNT_HOME}/bin && python3 ${SHUNT_HOME}/utils/py/src/setup.py build_ext && mv ${SHUNT_HOME}/utils/py/src/shunt.py ${SHUNT_HOME}/bin && mv ${SHUNT_HOME}/utils/py/src/shunt_wrap.c ${SHUNT_HOME}/bin
	cd ${SHUNT_HOME}/bin && python3  ${SHUNT_HOME}/utils/py/src/setup.py install --install-platlib=.


.PHONY: all clean dependents swig_py
.SECONDARY:

-include ../makefile.targets
