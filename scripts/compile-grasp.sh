#!/usr/bin/bash

# This script is used to compile the grasp algorithm with different RCL parameters.

# If the script is not run from the project root directory, exit
if [ ! -f "Final_project.pdf" ]; then
    echo "Please run this script from the project root directory."
    exit 1
fi

OUTPUT_DIR=$1

mkdir -p "$OUTPUT_DIR"

DEFAULT_ALPHA=5
DEFAULT_RETRIES=10

for ALPHA in 1 2 3 4 5 6 7 8 9; do
    for RETRIES in 5 6 7 8 9 10; do
        # Check if the file already exists
        if [ -f "${OUTPUT_DIR}/grasp_0.${ALPHA}_${RETRIES}" ]; then
            continue
        fi

        sed -i "14s/ALPHA 0.[0-9]/ALPHA 0.${ALPHA}/" src/algorithm/grasp_mewc.cpp
        sed -i "15s/RETRIES [0-9]+/\RETRIES ${RETRIES}/" src/algorithm/grasp_mewc.cpp

        make -j

        mv ./build/main "${OUTPUT_DIR}/grasp_0.${ALPHA}_${RETRIES}"
    done
done

sed -i "14s/ALPHA 0.[0-9]/ALPHA 0.${DEFAULT_ALPHA}/" src/algorithm/grasp_mewc.cpp
sed -i "15s/RETRIES [0-9]+/\RETRIES ${DEFAULT_RETRIES}/" src/algorithm/grasp_mewc.cpp