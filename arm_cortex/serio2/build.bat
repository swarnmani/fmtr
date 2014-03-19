rem You may need to adjust the library path in the linker command
arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -g -c init.c -o init.o
arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -g -c main.c -o main.o
arm-none-eabi-ld init.o main.o -L "C:\Program Files (x86)\GNU Tools ARM Embedded\4.7 2013q3\lib\gcc\arm-none-eabi\4.7.4\armv6-m" -lgcc -T linker_script.ld --cref -Map main.map -nostartfiles -o main.elf
objcopy -O ihex main.elf main.hex
