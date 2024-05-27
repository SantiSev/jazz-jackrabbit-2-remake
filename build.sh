

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
  make
fi
