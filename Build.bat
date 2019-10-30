copy %1src\raylib.dll %2 /Y
cd %2
mkdir Resources
xcopy %1src\Resources %2Resources /S /Y