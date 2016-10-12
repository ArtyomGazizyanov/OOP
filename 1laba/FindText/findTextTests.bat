set PROGRAM="../Debug/FindText.exe" 

%PROGRAM% empty-file.txt findme 
if ERRORLEVEL 1 goto err 

%PROGRAM% russian-text-a-Sound-of-Thunder.txt нет
if ERRORLEVEL 1 goto err 

%PROGRAM% english-text.txt who
if ERRORLEVEL 1 goto err 

%PROGRAM% english-text.txt 
if NOT ERRORLEVEL 1 goto err 

%PROGRAM% file-non-exist.txt "nothing here"
if NOT ERRORLEVEL 1 goto err 

echo Program testing succeeded 
pause 
exit 0 

:err 
echo Program testing failed 
pause 
exit 1