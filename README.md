# Snake (OpenGL)
### - [How to build project?](#how-to-build-project)

![Demo](assets/snake_preview.gif)<br>

![Demo](assets/image.png)<br>

# How to build project
### To build project you need CMake. You can install Cmake [here](https://cmake.org/download/).<br>
### Then you need to clone repo on your computer and in the local repo enter these comands to console:<br>- `cmake -B build -S .` to generate build files<br>- `cmake --build build` to build project<br>Also you can generate build files and build project with CMake GUI.
### Repo contains `CmakePresets.json`.<br>You can enter:<br>- `cmake --preset <preset_name>` to generate build files<br>- `cmake --build --preset <preset_name>` to build it<br>To use these commands you must have generator and compiler listed in preset on your computer.