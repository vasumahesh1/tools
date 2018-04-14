cd ..
if not exist "build_windows_release" mkdir build_windows_release
cd build_windows_release
cmake -DCMAKE_BUILD_TYPE=Release ..
msbuild Project.sln /p:Configuration=Release /p:Platform="Win32"