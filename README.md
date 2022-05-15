# utility

@ECHO OFF
set name=%date%
echo %name%
mkdir %name%
ROBOCOPY .  %name% *.zip *.7z *.rar *.mp3  /move /s /maxage:1
cd %name%
"C:\Program Files\7-Zip\7z.exe" e *.zip *.7z *.rar
del *.zip *.7z *.rar /s /f

ffmpeg -i "01 Pain.flac" -ab 320k -map_metadata 0 -id3v2_version 3 output.mp3

for %%f in (*.flac) do (ffmpeg -i "%%f" -ab 320k -map_metadata 0 -id3v2_version 3 "%%f.mp3")
