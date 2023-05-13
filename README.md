# TankWar90
Remake with OpenGL.

## Build

### With GNU/Linux
Take `Ubuntu` as example:
- step 1:
  - run `sudo apt install curl libfreetype-dev libglfw3-dev libglew-dev libglm-dev libstb-dev` to install the dependence.
- step 2:
  - check [scripts/build.sh](scripts/build.sh) and run it. 
  - This will automatically download `irrKlang` and put it in a proper position. Then it call `CMake` and build the program.

### With Windows Visual Studio
- step 1:
  - run `vcpkg install glfw3 glm glew freetype stb`.
- step 2:
  - check [scripts/build.cmd](scripts/build.cmd) and run it. 
  - use command like this to generate a `Visual Studio` Solution: 
  - `cmake .. -G"Visual Studio 17 2022" -A=Win32  -DCMAKE_TOOLCHAIN_FILE=${your_vcpkg_root}/scripts/buildsystems/vcpkg.cmake`

## Refererce
 - [https://blog.csdn.net/weixin_46043195/article/details/125336555](https://blog.csdn.net/weixin_46043195/article/details/125336555)

## Dependency
- [glfw](https://github.com/glfw/glfw)
- [glew](https://github.com/nigels-com/glew)
- [glm](https://github.com/g-truc/glm)
- [stb](https://github.com/nothings/stb)
- [freetype](https://www.freetype.org/)
- [irrKlang](https://www.ambiera.com/irrklang/)

