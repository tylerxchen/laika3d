#! /bin/sh
echo "Creating cmake build files:"
cmake -S . -B out -DCMAKE_BUILD_TYPE=Debug
echo "Copying resource directory:"
cp -r res out
echo "Done!"
