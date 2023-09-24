@echo off
set solution_dir=%~1
set platform=%~2
set config=%~3
xcopy /e /v /y "%solution_dir%\bin\Engine\%platform%_%config%\Engine.dll" "%solution_dir%\bin\Game\%platform%_%config%\"
if exist "%solution_dir%\bin\Engine" (rmdir /s /q "%solution_dir%\bin\Engine")
if exist "%solution_dir%\obj\Engine" (rmdir /s /q "%solution_dir%\obj\Engine")

REM "$(SolutionDir)scripts\game_post_build.bat" "$(SolutionDir)" "$(Platform)" "$(Configuration)"