@ECHO OFF
ECHO Getting ready to flash the Debug build...
DEL /F /Q .\..\Debug\app.bin
IF NOT EXIST ./../Debug/app.elf (
	echo "Compiled file not found! Was there any error while compiling?"
	pause
	exit /b 1
)
C:/gcc-arm-none-eabi-4_8/bin/arm-none-eabi-objcopy -S -O binary ./../Debug/app.elf ./../Debug/app.bin
ECHO Flashing Debug...
python stm32loader.py -ewv -p COM30 ./../Debug/app.bin
IF NOT %errorlevel% EQU 0 (
	echo "Failed flashing image"
	pause
	exit /b 1
)
exit /b 0