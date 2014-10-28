@ECHO OFF
ECHO Getting ready to flash the Release build...
DEL /F /Q .\..\Release\app.bin
IF NOT EXIST ./../Release/app.elf (
	echo "Compiled file not found! Was there any error while compiling?"
	pause
	exit /b 1
)
C:/gcc-arm-none-eabi-4_8/bin/arm-none-eabi-objcopy -S -O binary ./../Release/app.elf ./../Release/app.bin
ECHO Flashing Release...
python stm32loader.py -ewv -p COM30 ./../Release/app.bin
IF NOT %errorlevel% EQU 0 (
	echo "Failed flashing image"
	pause
	exit /b 1
)
exit /b 0