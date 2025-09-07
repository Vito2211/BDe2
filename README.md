# BDe2


One of my first more or less serious C++ projects.  
I like it, as well as the **raycast** technique, although there is actually not much written about it.  
I hope it will be useful to someone.




C++ project using **Raylib** + **raygui**.

## Requirements

- C++17 compatible compiler (AppleClang, GCC, MSVC)
- [Raylib 5.x](https://www.raylib.com/)
- CMake 3.10 or higher

### macOS (Homebrew)
• brew install raylib cmake

### Linux (Ubuntu/Debian)
• sudo apt install libraylib-dev cmake build-essential

### Windows
• Install Raylib using vcpkg or from source
• Install CMake and a compiler (Visual Studio recommended)

### Build
From the project root:

```
cd /path/to/BDe2                                # go to project root
rm -rf build                                    # remove old build folder
mkdir build && cd build                         # create and enter build folder
cmake .. && make                                # generate and build
./BDe2                                          # run the application
```


### Notes
The **src/** folder contains raygui.h and other source files.
No need to modify **CMakeLists.txt** for basic builds.
Works on **macOS, Linux, and Windows** with proper Raylib installation.
The compiled binary is named **BDe2**.