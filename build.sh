#!/usr/bin/bash

echo "removing build folder"
rm -rf build

echo "building..."
mkdir build && cd build && conan install -u .. --build=missing && cmake .. -G "Unix Makefiles" && cmake --build .
