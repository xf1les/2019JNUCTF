#!/bin/bash

python generate_code.py binary.c
mips64el-linux-gnuabi64-gcc -c -o binary.o binary.c
LANG= objdump -x binary.o > dumpinfo
objcopy -O binary binary.o binary.bin
