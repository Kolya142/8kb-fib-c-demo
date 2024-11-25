#!/bin/bash
gcc main.c -Og -nostdlib -s -W -fwrapv -fomit-frame-pointer -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables -o scl