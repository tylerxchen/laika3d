#! /bin/sh
echo "Creating cmake build files:"
cmake -S . -B out -DCMAKE_BUILD_TYPE=Debug
echo "Copying resource directory:"
cp -r demo/res out/demo/res
echo "Done!"
