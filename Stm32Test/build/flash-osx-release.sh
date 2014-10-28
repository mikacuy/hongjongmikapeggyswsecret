#!/bin/bash
echo "Getting ready to flash the Release build..."
rm ../Release/app.bin &> /dev/null
if [ ! -f ../Release/app.elf ]; then
	echo "Compiled file not found! Was there any error while compiling?"
	echo "Press a key to exit"
	read -n 1
	exit 1
fi
~/gcc-arm-none-eabi-4_8/bin/arm-none-eabi-objcopy -S -O binary ../Release/app.elf ../Release/app.bin
echo "Flashing Release..."
serials=(/dev/tty.usbserial-*)
if [ ${#serials[@]} -eq 0 ] || [ "${serials[0]}" == "/dev/tty.usbserial-*" ]; then
    echo "Can't detect a serial device, have you connected the board?"
	echo "Press a key to exit"
	read -n 1
	exit 1
fi
python stm32loader.py -ewv -p ${serials[0]} ../Release/app.bin
ret=$?
if [ $ret -ne 0 ]; then
	echo "Failed flashing image"
	echo "Press a key to exit"
	read -n 1
	exit 1
fi
exit 0