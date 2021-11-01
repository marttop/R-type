# R-TYPE

## Build

### Build on linux

First time
```
sudo apt install libudev-dev
```

```
mkdir build && cd build && conan install .. --build=missing && cmake .. -G "Unix Makefiles" && cmake --build .
```

### Build on windows

```
mkdir build && cd build && conan install .. --build=missing && cmake .. -G "Visual Studio 16 2019" -A x64 && cmake --build .
```