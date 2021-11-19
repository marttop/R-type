#!/usr/bin/bash

echo "Removing build folder..."
rm -rf build

echo "Building shared libraries..."
cd src/server/entities && make && cd ../../..

echo "Building project..."
mkdir build && cd build && conan install -u .. --build=missing && cmake .. -G "Unix Makefiles" && cmake --build .