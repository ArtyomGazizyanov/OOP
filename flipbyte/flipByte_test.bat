echo off
set PROGRAM="Debug/flipbyte.exe" 

%PROGRAM% 
if ERRORLEVEL 1 goto err 

%PROGRAM% 12
if ERRORLEVEL 1 goto err  

%PROGRAM% 42galaxy
if ERRORLEVEL 1 goto err  

%PROGRAM% galaxy42
if ERRORLEVEL 1 goto err  

%PROGRAM% 256
if ERRORLEVEL 1 goto err  

%PROGRAM% -25
if ERRORLEVEL 1 goto err  

echo Program testing succeeded 
pause 
exit 0 

:err 
echo Program testing failed 
pause 
exit 1