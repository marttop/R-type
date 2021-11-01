# R-TYPE

## Build

### Build on linux

```
mkdir build && cd build && conan insatll .. --build=missing && cmake .. -G "Unix Makefiles" && cmake --build .
```

### Build on windows

```
mkdir build && cd build && conan insatll .. --build=missing && cmake .. -G "Visual Studio 16 2019" -A x64 && cmake --build .
```