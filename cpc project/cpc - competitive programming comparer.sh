#!/bin/bash

# Script version
VERSION="1.0.0"

# Add a log function for logging
log() {
    local msg="$1"
    local logfile="script.log"

    echo "$(date): $msg" >> $logfile
    [ $verbose -eq 1 ] && echo $msg
}

# Function to display help information
help_info() {
    echo "Usage: $0 [options]"
    echo ""
    echo "Options:"
    echo "-d    specify the test directory"
    echo "-f    specify the cpp file name"
    echo "-o    specify the output cpp file name"
    echo "-v    enable verbose mode"
    echo "-i    enable interactive mode"
    echo "-h    display this help information"
    echo "-V    display script version"
    exit 1
}

# default cpp file names
cppFileName="main.cpp"
outputCppFileName="main.cpp"

# default tests directory
testsDirectory="tests"

# default verbose mode
verbose=0

# default interactive mode
interactive=0

# parse command-line options
while getopts d:f:o:ivhV option
do
case "${option}"
in
d) testsDirectory=${OPTARG};;
f) cppFileName=${OPTARG};;
o) outputCppFileName=${OPTARG};;
v) verbose=1;;
i) interactive=1;;
h) help_info;;
V) echo "Version: $VERSION"; exit 0;;
esac
done

# interactive mode
if [ $interactive -eq 1 ]
then
    echo "Interactive mode is enabled. Please answer the following questions:"
    read -p "Enter the test directory: " testsDirectory
    read -p "Enter the cpp file name: " cppFileName
    read -p "Enter the output cpp file name: " outputCppFileName
    read -p "Enable verbose mode? (yes/no): " verboseAnswer
    [ "$verboseAnswer" = "yes" ] && verbose=1
fi 

# error check for g++ installation
if ! command -v g++ &> /dev/null
then
    log "g++ could not be found, please install g++"
    exit
fi

# compile the C++ code
g++ $cppFileName -o "main.out"
if [[ $? -ne 0 ]]; then
    log "Compilation failed!"
    exit 1
fi
log "Compiled $cppFileName to main.out"

# compile the output C++ code if -o option is set
if [ "$outputCppFileName" != "$cppFileName" ]
then
  g++ $outputCppFileName -o "output.out"
  if [[ $? -ne 0 ]]; then
      echo "Compilation failed!"
      exit 1
  fi
  [ $verbose -eq 1 ] && echo "Compiled $outputCppFileName to output.out"
fi

# initial test counts
totalTests=0
passedTests=0
totalLines=0
correctLines=0

# start writing to summary file
echo $'Test Summary:\n' > summary.txt

# for every .in file in the specified directory
for infile in "$testsDirectory"/*.in
do
  # increment total test count
  ((totalTests++))

  # get the base name (without the .in extension)
  base="${infile%.*}"

  # generate the corresponding .txt file
  startTime=$(date +%s%3N)
  ./main.out < "$infile" > "$base.txt"
  endTime=$(date +%s%3N)
  timeTaken=$((endTime - startTime))

  # print time taken to console and write to summary file
  echo "Time taken for test $base: $timeTaken ms" >> summary.txt

  # generate the corresponding .out file if -o option is set
  if [ "$outputCppFileName" != "$cppFileName" ]
  then
    ./output.out < "$infile" > "$base.out"
  fi

  # check if there is a corresponding .out file
  if [ -f "$base.out" ]
  then
    # compare the .out and .txt files
    diffResult=$(diff -u --color=always "$base.out" "$base.txt")
    lineComparison=$(diff -y --suppress-common-lines "$base.out" "$base.txt")

    # count the number of different and identical lines
    diffLines=$(echo "$lineComparison" | wc -l)
    #  make diffLines smaller by one
    ((diffLines--))

    totalLinesForTest=$(wc -l < "$base.out")
    identicalLines=$(expr $totalLinesForTest - $diffLines)

    # add to the total line and correct line counts
    ((totalLines += totalLinesForTest))
    ((correctLines += identicalLines))

    if [ -z "$diffResult" ]
    then
      echo "Test $base: PASSED" >> summary.txt
      echo "$(tput setaf 2)Test $base PASSED [$timeTaken ms]$(tput sgr0)"
      ((passedTests++))
    else
      echo "$(tput setaf 1)Test $base FAILED [$timeTaken ms]$(tput sgr0)"
      echo "Test $base: FAILED" >> summary.txt
      echo "$diffResult" >> summary.txt
    fi

    # write detailed results to summary file
    echo "Identical lines: $identicalLines" >> summary.txt
    echo "Different lines: $diffLines" >> summary.txt
    echo $'\n-----------------------------\n' >> summary.txt
  else
    echo "$(tput setaf 3)No .out file for test $base$(tput sgr0)"
  fi
done

# write total results to summary file
failedTests=$(expr $totalTests - $passedTests)
echo "Total tests: $totalTests" >> summary.txt
echo "Passed tests: $passedTests" >> summary.txt
echo "Failed tests: $failedTests" >> summary.txt
passRate=$(awk "BEGIN {printf \"%.2f\", $passedTests / $totalTests * 100}")
echo "Pass rate: $passRate%" >> summary.txt

incorrectLines=$(expr $totalLines - $correctLines)
echo "Total lines: $totalLines" >> summary.txt
echo "Correct lines: $correctLines" >> summary.txt
echo "Incorrect lines: $incorrectLines" >> summary.txt