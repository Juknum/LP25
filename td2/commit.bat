git checkout jconstan
git add *
set /p message="Commit message: "
git commit -m "%message%"
git push -u origin jconstan

pause
cls