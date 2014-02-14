#!/bin/bash
echo "$(tput setaf 1)-----start of crc-----$(tput sgr0)"
make
if [ $? -eq 0 ]
then
  echo "$(tput setaf 1)-----start of run-----$(tput sgr0)"
  ./runTests
  rm cr.exe
fi
make clean
echo "$(tput setaf 1)-----end of crc-----$(tput sgr0)"
