# QR_invader
A C remake of Space invader designed to fit within a QR code

command to compile:
crinkler /NODEFAULTLIB /ENTRY:_WinMainCRTStartup /SUBSYSTEM:WINDOWS main.o  kernel32.lib user32.lib gdi32.lib

(please rename main() to _WinMainCRTStartup)
needs to be compiled in x86 Native Tools Command Prompt for VS 2019
