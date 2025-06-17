@echo off

set PATH=%PATH%;C:\emsdk
call emsdk activate latest

:: Store the working directory
set WORK_DIR=%CD%
mkdir web

:: Copy the Shaders folder into web\Resources
xcopy /E /I "%WORK_DIR%\resources" "%WORK_DIR%\web\resources"

cd "%WORK_DIR%\web"

call emcmake cmake .. -DPLATFORM=Web -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXECUTABLE_SUFFIX=".html"
call emrun --port 8080 .
call emmake make