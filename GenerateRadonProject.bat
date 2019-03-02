@echo off
color a
cls

set BUILD_SYSTEM_EXEC=premake5.exe
set BUILD_SCRIPT_FILE=Build.lua
set PROJECT_TYPE=vs2017

set /A ARGS_COUNT=0    
set %%A in (%*) do SET /A ARGS_COUNT+=1    

if %ARGS_COUNT% GEQ 1 (
	set BUILD_SYSTEM_EXEC=%1
)

if exist %BUILD_SYSTEM_EXEC% (
	cmd /k %BUILD_SYSTEM_EXEC% --file=%BUILD_SCRIPT_FILE% %PROJECT_TYPE% %*
) else (
	echo "failed to locate the build system executable: %BuildSystemExec%"
)