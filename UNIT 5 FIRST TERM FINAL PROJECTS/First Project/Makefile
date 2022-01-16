
CC=arm-none-eabi
CFLAGS=-mcpu=cortex-m3 -gdwarf-2
INCS=-I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
AS=$(wildcard *.s)
ASOBJ=$(AS:.s:.o)

Project_name=pressure_controller

all : $(Project_name).hex $(Project_name).bin
	@echo "Done Building"

%.o : %.s
	$(CC)-as.exe $(CFLAGS) $< -o $@

%.o : %.c
	$(CC)-gcc.exe $(CFLAGS) $(INCS) -c $< -o $@ 

$(Project_name).elf : $(OBJ)
	$(CC)-ld -T	linker_script.ld $(LIBS) $(OBJ) -o $@ -Map=map_file.map

$(Project_name).bin : $(Project_name).elf
	$(CC)-objcopy.exe -O binary $< $@  


$(Project_name).hex : $(Project_name).elf
	$(CC)-objcopy.exe -O ihex $< $@

clean_all:
	rm *.o *.bin *.elf
