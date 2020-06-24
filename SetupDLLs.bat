echo on

cd Dependencies\FreeImage\

set dest=..\..\bin\Debug\
set file=FreeImage.dll
ROBOCOPY %cd% %dest% *%file%* /copy:DATSO

cd ..\..\Dependencies\FreeType\

set dest=..\..\bin\Debug\
set file=freetype.dll
ROBOCOPY %cd% %dest% *%file%* /copy:DATSO

pause