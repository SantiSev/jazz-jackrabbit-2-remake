#/usr/bash

echo "Installing dependencies"
sudo apt install -y libsdl2-dev 1> /dev/null
echo "libsdl2-dev installed"

sudo apt install -y libsdl2-image-dev 1> /dev/null
echo "libsdl2-image-dev installed"
sudo apt install -y libsdl2-ttf-dev 1> /dev/null
echo "libsdl2-ttf-dev installed"
sudo apt install -y libsdl2-mixer-dev 1> /dev/null
echo "libsdl2-mixer-dev installed"

# if ./build.sh
if [ $# -eq 0 ]; then
  echo "Building project"

  # if ./build exists remove it
  if [ -d "./build" ]; then
    rm -rf build
    mkdir build
  else
    mkdir build
  fi

  cd build
  cmake ..

  echo "Copying assets"
  cp -r ../assets .

  make

# if ./build.sh tests
else [ $1 == "tests" ]
  echo "Building tests"
  if [ -d "./tests_bin" ]; then
    rm -rf tests_bin
    mkdir tests_bin
  else
    mkdir tests_bin
  fi

  cd tests_bin
  cmake -DTESTS=ON ..

  echo "Copying assets"
  cp -r ../assets .
  
  make
fi
