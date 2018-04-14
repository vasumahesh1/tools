cd ..
if not exist "build_windows" mkdir build_windows
cd build_windows
cmake -DCMAKE_BUILD_TYPE=Debug ..
msbuild Project.sln /p:Configuration=Debug /p:Platform="Win32"