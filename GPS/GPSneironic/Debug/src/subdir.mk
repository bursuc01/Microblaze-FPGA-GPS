################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

CPP_SRCS += \
../src/TinyGPS++.cpp \
../src/name.cpp \
../src/platform.cpp 

OBJS += \
./src/TinyGPS++.o \
./src/name.o \
./src/platform.o 

CPP_DEPS += \
./src/TinyGPS++.d \
./src/name.d \
./src/platform.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze g++ compiler'
	mb-g++ -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -IC:/Users/Jabbah/workspace/design_1_wrapper_1/export/design_1_wrapper_1/sw/design_1_wrapper_1/standalone_microblaze_0/bspinclude/include -mlittle-endian -mcpu=v11.0 -mxl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


