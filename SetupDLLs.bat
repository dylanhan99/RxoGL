echo on

cd Dependencies\FreeImage\

set dest=..\..\bin\Debug\
set file=FreeImage.dll
ROBOCOPY %cd% %dest% *%file%* /mir