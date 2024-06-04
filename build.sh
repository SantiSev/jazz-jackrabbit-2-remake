#!/bin/bash

sudo apt-get update 1> /dev/null

BUILD_DIR="./build"
TESTS_DIR="./tests_bin"
TIBURONCIN_SRC="https://github.com/eldipa/tiburoncin.git"

echo "Installing dependencies"
sudo apt install -y libsdl2-dev 1> /dev/null
echo "libsdl2-dev installed"

sudo apt install -y libsdl2-image-dev 1> /dev/null
echo "libsdl2-image-dev installed"
sudo apt install -y libsdl2-ttf-dev 1> /dev/null
echo "libsdl2-ttf-dev installed"
sudo apt install -y libsdl2-mixer-dev 1> /dev/null
echo "libsdl2-mixer-dev installed"

# if dir exists remove it
check_for_dir() {
  dir="$1"
  
  if [ -d $dir ]; then
    rm -rf $dir
    mkdir $dir
  else
    mkdir $dir
  fi
}

install_tiburoncin() {
  git clone $TIBURONCIN_SRC > /dev/null
  cd tiburoncin
  make 1> /dev/null
  sudo cp tiburoncin /usr/bin/
  cd ..
  rm -rf tiburoncin
}

run_event_tests() {
  folder_case="$1"
  run_tests_flags="build/ tests/events/$folder_case/cases/ single-client no-valgrind 60 10"
  compare_tests_flags="tests/events/$folder_case/cases/ tests/events/$folder_case/expected/"

  echo $run_tests_flags

  RUN_TESTS_EVENTS="./tests/events/$folder_case/run_tests.sh $run_tests_flags"
  COMPARE_TESTS_EVENTS="./tests/events/$folder_case/compare_outputs.sh $compare_tests_flags"

  $RUN_TESTS_EVENTS > /dev/null
  $COMPARE_TESTS_EVENTS
}

# if ./build.sh
if [[ $# -eq 0 ]]; then
  echo "Building project"
  check_for_dir $BUILD_DIR

  cd $BUILD_DIR
  cmake .. -DPRODUCTION=ON

  echo "Copying assets"
  cp -r ../assets .

  make
# if ./build.sh graphics
elif [[ $1 == "graphics" ]]; then
  echo "Building tests"
  check_for_dir $TESTS_DIR

  cd tests_bin
  cmake -DGRAPHICS=ON ..

  echo "Copying assets"
  cp -r ../assets .
  
  make
# if ./build.sh events
else [[ $1 == "events" ]]
  echo "Building event tests"
  
  check_for_dir $BUILD_DIR
  
  echo "Installing tiburoncin"
  install_tiburoncin

  echo "Installing valgrind"
  sudo apt-get install -y valgrind 1> /dev/null

  cd $BUILD_DIR
  cmake -DEVENTS=ON ..
  make
  cd ..

  echo "Running event tests"
  run_event_tests "client_to_server"
  run_event_tests 'server_to_client'

  rm -r $BUILD_DIR
fi
