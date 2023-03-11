@echo off
set i=0
set /p command= ^>^>^>
echo %command% >>Extreme.txt
:loop
set /a i=i+1
TestExtreme >>Extreme.txt
if %i%==3  echo --------------------->>Extreme.txt &&exit
goto loop