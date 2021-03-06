################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../engine/golem.c \
../engine/golemblock.c \
../engine/golembuilderclass.c \
../engine/golembuilderclosure.c \
../engine/golembuilderextern.c \
../engine/golembuilderfunction.c \
../engine/golemcinvoke.c \
../engine/golemclosure.c \
../engine/golemcompiled.c \
../engine/golemconstant.c \
../engine/golemcontext.c \
../engine/golemdebugobject.c \
../engine/golemdeclaration.c \
../engine/golemerror.c \
../engine/golemexpression.c \
../engine/golemexpressioncomplex.c \
../engine/golemextends.c \
../engine/golemidentificator.c \
../engine/golemif.c \
../engine/goleminit.c \
../engine/goleminvoke.c \
../engine/golemllm.c \
../engine/golemmember.c \
../engine/golemnew.c \
../engine/golemparser.c \
../engine/golemreturn.c \
../engine/golemruntime.c \
../engine/golemsharedobject.c \
../engine/golemstatement.c \
../engine/golemstructinfo.c \
../engine/golemtypeinfo.c \
../engine/golemwhile.c 

OBJS += \
./engine/golem.o \
./engine/golemblock.o \
./engine/golembuilderclass.o \
./engine/golembuilderclosure.o \
./engine/golembuilderextern.o \
./engine/golembuilderfunction.o \
./engine/golemcinvoke.o \
./engine/golemclosure.o \
./engine/golemcompiled.o \
./engine/golemconstant.o \
./engine/golemcontext.o \
./engine/golemdebugobject.o \
./engine/golemdeclaration.o \
./engine/golemerror.o \
./engine/golemexpression.o \
./engine/golemexpressioncomplex.o \
./engine/golemextends.o \
./engine/golemidentificator.o \
./engine/golemif.o \
./engine/goleminit.o \
./engine/goleminvoke.o \
./engine/golemllm.o \
./engine/golemmember.o \
./engine/golemnew.o \
./engine/golemparser.o \
./engine/golemreturn.o \
./engine/golemruntime.o \
./engine/golemsharedobject.o \
./engine/golemstatement.o \
./engine/golemstructinfo.o \
./engine/golemtypeinfo.o \
./engine/golemwhile.o 

C_DEPS += \
./engine/golem.d \
./engine/golemblock.d \
./engine/golembuilderclass.d \
./engine/golembuilderclosure.d \
./engine/golembuilderextern.d \
./engine/golembuilderfunction.d \
./engine/golemcinvoke.d \
./engine/golemclosure.d \
./engine/golemcompiled.d \
./engine/golemconstant.d \
./engine/golemcontext.d \
./engine/golemdebugobject.d \
./engine/golemdeclaration.d \
./engine/golemerror.d \
./engine/golemexpression.d \
./engine/golemexpressioncomplex.d \
./engine/golemextends.d \
./engine/golemidentificator.d \
./engine/golemif.d \
./engine/goleminit.d \
./engine/goleminvoke.d \
./engine/golemllm.d \
./engine/golemmember.d \
./engine/golemnew.d \
./engine/golemparser.d \
./engine/golemreturn.d \
./engine/golemruntime.d \
./engine/golemsharedobject.d \
./engine/golemstatement.d \
./engine/golemstructinfo.d \
./engine/golemtypeinfo.d \
./engine/golemwhile.d 


# Each subdirectory must supply rules for building sources it contributes
engine/%.o: ../engine/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	clang -std=c99 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


