
# if ./build exists remove it
if [ -d "./build" ]; then
  rm -rf build
  mkdir build
else
  mkdir build
fi

cd build
cmake ..
make
