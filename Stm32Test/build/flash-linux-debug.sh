#!/bin/bash
echo "Getting ready to flash the Debug build..."
rm ../Debug/app.bin &> /dev/null
if [ ! -f ../Debug/app.elf ]; then
	echo "Compiled file not found! Was there any error while compiling?"
	echo "Press a key to exit"
	read -n 1
	exit 1
fi
~/gcc-arm-none-eabi-4_8/bin/arm-none-eabi-objcopy -S -O binary ../Debug/app.elf ../Debug/app.bin
echo "Flashing Debug..."
python stm32loader.py -ewv -p /dev/ttyUSB0 ../Debug/app.bin
ret=$?
if [ $ret -ne 0 ]; then
	echo "Failed flashing image"
	echo "Press a key to exit"
	read -n 1
	exit 1
fi
exit 0