cd /d %~dp0

vcpkg install glfw3 glm glew freetype stb
rmdir  /s/q build

mkdir ..\build
cd ..\build

:: wget -o irrklang.zip https://www.ambiera.at/downloads/irrKlang-32bit-1.6.0.zip
:: unzip -o irrklang.zip

powershell -c "invoke-webrequest -outfile irrKlang-32bit-1.6.0.zip -uri https://www.ambiera.at/downloads/irrKlang-32bit-1.6.0.zip"
powershell -c "Expand-Archive irrKlang-32bit-1.6.0.zip -DestinationPath ."

mkdir  ..\third_party\include\irrklang
mkdir  ..\third_party\lib\win

cp  irrKlang-1.6.0//bin//win32-visualStudio//*.dll ..//third_party//lib//win//
cp  irrKlang-1.6.0//lib//win32-visualStudio//*.lib ..//third_party//lib//win//
cp  irrKlang-1.6.0//include//* ..//third_party//include//irrklang//

cmake .. -G"Visual Studio 16 2019" -A=Win32  -DCMAKE_TOOLCHAIN_FILE=D://Software//vcpkg//scripts//buildsystems//vcpkg.cmake
cmake --build .

cd ..


