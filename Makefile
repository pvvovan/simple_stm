GCC_PATH = /mnt/sda1/pvv/gcc/arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-eabi/bin/

CC_FLAGS = \
	-std=c99 \
	-O0 \
	-g3 \
	-mfloat-abi=hard \
	-mcpu=cortex-m4 \
	-mthumb -gdwarf-2 \
	-Wall \
	-Wextra \
	-Wconversion \
	-Wsign-conversion \
	-Wpedantic \
	-D STM32F303xE

LD_FLAGS = \
	-specs=nosys.specs \
	-T linker_script.ld \
	-nostartfiles

C_SOURCE = \
	main.c \
	startup.c

INC_DIR = \
	-iquote ./ \
	-iquote ./STM32CubeF3/Drivers/CMSIS/Device/ST/STM32F3xx/Include \
	-iquote ./STM32CubeF3/Drivers/CMSIS/Core/Include

.DEFAULT:
all:
	$(GCC_PATH)arm-none-eabi-gcc -o f.elf $(INC_DIR) $(C_SOURCE) $(LD_FLAGS) $(CC_FLAGS)
	$(GCC_PATH)arm-none-eabi-objdump -D f.elf > f.elf.dump
	$(GCC_PATH)arm-none-eabi-objcopy -O ihex f.elf f.elf.ihex
	$(GCC_PATH)arm-none-eabi-objcopy -O srec f.elf f.elf.srec
	$(GCC_PATH)arm-none-eabi-size f.elf

.PHONY: clean
clean:
	-rm ./*.o ./*.elf ./*.ihex ./*.dump ./*.srec
