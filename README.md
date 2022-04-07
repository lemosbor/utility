# utility

@ECHO OFF
set name=%date%
echo %name%
mkdir %name%
ROBOCOPY .  %name% *.zip *.7z *.rar *.mp3  /move /s /maxage:1
cd %name%
"C:\Program Files\7-Zip\7z.exe" e *.zip *.7z *.rar
del *.zip *.7z *.rar /s /f
