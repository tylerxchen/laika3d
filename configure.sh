#! /bin/sh
echo "Creating cmake build files:"
cmake -S src -B build -DCMAKE_BUILD_TYPE=Debug
echo "Copying resource directory:"
cp -r res build
echo "Done!"
