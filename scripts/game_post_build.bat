@echo off
set solution_dir=%~1
set platform=%~2
set config=%~3
xcopy /e /v /y "%solution_dir%\bin\Engine\%platform%_%config%\Engine.dll" "%solution_dir%\bin\Game\%platform%_%config%\"

REM "$(SolutionDir)scripts\game_post_build.bat" "$(SolutionDir)" "$(Platform)" "$(Configuration)"