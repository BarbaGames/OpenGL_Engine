@echo off
set solution_dir=%~1
set platform=%~2
set config=%~3

if exist "%solution_dir%\lib\Engine" (rmdir /s /q "%solution_dir%\lib\Engine")
mkdir "%solution_dir%\lib\Engine\lib"
REM Copying the .lib file
xcopy /e /v /y "%solution_dir%\bin\Engine\%platform%_%config%\Engine.lib" "%solution_dir%\lib\Engine\lib"

mkdir "%solution_dir%\lib\Engine\include"
REM Copying all the header files from the Engine.
for %%i in ("%solution_dir%\src\Engine\*.h") do (
    xcopy /e /v /y "%%i" "%solution_dir%\lib\Engine\include"
)

REM "$(SolutionDir)scripts\engine_post_build.bat" "$(SolutionDir)" "$(Platform)" "$(Configuration)"