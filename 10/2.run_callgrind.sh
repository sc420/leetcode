#!/bin/bash

valgrind \
    --tool=callgrind \
    \
    --callgrind-out-file=callgrind.out \
    --log-file=callgrind.log \
    \
    debug/10

# Replace "/mnt/c/Users" with "C:/Users"
# So that you can see source code when opening the file with QCachegrind
sed 's/\/mnt\/c\/Users/C:\/Users/g' callgrind.out > callgrind.windows.out
