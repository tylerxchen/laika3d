#! /bin/sh
echo "Creating cmake build files:"
cmake -S src -B build
echo "Copying resource directory:"
cp -r res build
echo "Done!"
