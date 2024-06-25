#!/bin/bash

BUILD_DIR="./build"
TESTS_DIR="./tests_bin"

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

run_event_tests() {
  folder_case="$1"
  run_tests_flags="build/ tests/events/$folder_case/cases/ single-client no-valgrind 60 10"
  compare_tests_flags="tests/events/$folder_case/cases/ tests/events/$folder_case/expected/"

  echo $run_tests_flags

  RUN_TESTS_EVENTS="./tests/events/$folder_case/run_tests.sh $run_tests_flags"
  COMPARE_TESTS_EVENTS="./tests/events/$folder_case/compare_outputs.sh $compare_tests_flags"

  $RUN_TESTS_EVENTS
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
  # if ./build.sh log
elif [[ $1 == "-debug" ]]; then
  echo "Building with debugging info"
  check_for_dir $BUILD_DIR

  cd $BUILD_DIR

  # Initialize cmake options variable
  CMAKE_OPTIONS=""

  # Check for additional parameters and set cmake options accordingly
  for param in "${@:2}"; do
    if [[ $param == "log" ]]; then
      CMAKE_OPTIONS+=" -DLOG=ON"
    elif [[ $param == "log_verbose" ]]; then
      CMAKE_OPTIONS+=" -DLOG_VERBOSE=ON"
    elif [[ $param == "cheats" ]]; then
      CMAKE_OPTIONS+=" -DCHEATS=ON"
    fi
  done

  cmake .. -DPRODUCTION=ON $CMAKE_OPTIONS

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
elif [[ $1 == "events" ]]; then
  echo "Building event tests"
  
  check_for_dir $BUILD_DIR

  cd $BUILD_DIR
  cmake -DEVENTS=ON ..
  make
  cd ..

  echo "Running event tests"
  run_event_tests "client_to_server"
  run_event_tests 'server_to_client'

  rm -r $BUILD_DIR
else [[ $1 == "physics" ]]
  echo "Building physics tests"

  check_for_dir $BUILD_DIR

  cd $BUILD_DIR
  cmake -DPHYSICS=ON ..
  make
  ./tests

  cd ..
  rm -r $BUILD_DIR
fi
