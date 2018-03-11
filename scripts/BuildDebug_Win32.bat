cd ..
if not exist "build_windows" mkdir build_windows
cd build_windows
cmake ..
msbuild Project.sln /p:Configuration=Debug /p:Platform="Win32"