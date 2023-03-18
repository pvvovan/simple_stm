CC_FLAGS = -std=c99 -O0 -g3 -mfloat-abi=soft -mcpu=cortex-m4 -mthumb -gdwarf-2 \
-Wall -Wextra -Wconversion -Wsign-conversion -Wpedantic

GCC_PATH = /home/elina/arm-gnu-toolchain-12.2.rel1-x86_64-arm-none-eabi/bin/

C_SOURCE = \
main.c \
startup.c

INC_DIR = \
-iquote ./ \
-I ./

all:
	$(GCC_PATH)arm-none-eabi-gcc -o f.elf $(C_SOURCE) -specs=nosys.specs -T linker_script.ld -nostartfiles $(CC_FLAGS)
	$(GCC_PATH)arm-none-eabi-objdump -D f.elf > f.elf.dump
	$(GCC_PATH)arm-none-eabi-objcopy -O ihex f.elf f.elf.ihex
	$(GCC_PATH)arm-none-eabi-objcopy -O srec f.elf f.elf.srec
	$(GCC_PATH)arm-none-eabi-size f.elf

.PHONY: clean
clean:
	-rm ./*.o ./*.elf ./*.ihex ./*.dump ./*.srec
