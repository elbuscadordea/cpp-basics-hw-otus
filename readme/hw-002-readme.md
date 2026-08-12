# Home work #2 : Development Environment setup and the first C++ practice
## Objectives 
- Install C++ dev. environment: IDE, Compiler and CMake.
- C++ practice: move out the function from the main.cpp to a separated files using #include.

## Homework Implementation

**Environment Setup:**

- **OS** : Windows 11 Home Edition.
- **IDE** : VS Code (already installed with MS C/C++ extensions).
- **Compilers** are already installed:
  - msvc (version 19.41.34120.0).
  - gcc (version 13.2.0, Rev3, Built by MSYS2 project).
- **CMake** (version 4.2.3).

**C++ practice:**

Implementation description:
1. Added a new header file `move_me_out.h` with declaration of the function `todo_move_me_out()`.
1. Added a new file `move_me_out.cpp` which contains the implementation of the function `todo_move_me_out()`. Actually, the code of function was copied from the `hello_world.cpp` file.
1. In `hello_world.cpp` file, delete the code of the function `todo_move_me_out()` and add the header `move_me_out.h` using `#include` directive. The code of the `main()` function is not changed.
1. In the file `CMakeLists.txt`, `move_me_out.cpp` and `move_me_out.h` were added to the function `add_executable()`.
1. CMake detected MSVC compiler and used it by default for building the application.

The resulting git branch is [otus/HW-002](https://github.com/elbuscadordea/cpp-basics-hw-otus/tree/otus/HW-002).

The modifications concerning the homework are in the [commit 1f772d6]( https://github.com/elbuscadordea/cpp-basics-hw-otus/commit/1f772d64ef0bb0b686073434174183ca39031e2f#diff-bc37d034bad564583790a46f19d807abfe519c5671395fd494d8cce506c42947).

## Linux Environment Tests
The Linux Environment was tested as well.
The Linux OS is installed on VM using Oracle VirtualBox.
IDE, compilers and CMake were newly installed.

**Environment:**
- **OS :** Ubuntu 24.04.4 LTS on VM.
- **IDE :** VS Code installed from App Center tool.
- **Compilers :**
  - gcc (version 13.3.0, Ubuntu 13.3.0-6ubuntu2~24.04.1).
  - CLang (version 18.1.3, 1ubuntu1).
- **CMake** (version 4.4.2).

**C++ practice:**

The C++ exercise to move function into a new module also was repeated on Linux environment.
The steps were the same as for C++ practice on Windows. The application logic does not depend on platforms.

2 compilers were used to build the application: `gcc` and `CLang`.

> **Note:** The DeepSeek chat was used to get help with CLang set up.

The next approach was used to make compilation with both compilers:
1. CMake commands were run from the source code directory, not from the `build` directory as had been made with msvc compiler on Windows.
1. Next commands were run for CMake builds:
  
  ```shell
  # Build with gcc
  cmake -B build-gcc -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
  cmake --build build-gcc
  ./build-gcc/hello_world

  # Build with CLang
  cmake -B build-clang -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
  cmake --build buid-clang
  ./build-clang/hello_world 
  ```
  Where: 
  - **-B** (build) flag indicates the directory for CMake build. Directories `build-gcc` and `build-clang` were created.
  - **--DCMAKE_C_COMPILER** flag is to indicate the C compiler: `gcc` or `clang`.
  - **--DCMAKE_CXX_COMPILER** flag is to indicate the C compiler: `g++` or `clang++`.

Both `gcc` and `CLang` compilers were installed just to understand how they work and their use in parallel. The lab showed this approach makes commands more complex as additional options need to be specified. Moreover, the developer must be vigilant on running commands from the source code directory.