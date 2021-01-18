#! /bin/sh
echo "Creating cmake build files:"
cmake -S . -B out -DCMAKE_BUILD_TYPE=Debug
echo "Copying resource directories:"
cp -r demo/res out/demo/
cp -r test/res out/test/
echo "Done!"
