#!/usr/bin/bash

# This script is used to run the benchmarks automatically.

# If the script is not run from the project root directory, exit
if [ ! -f "Final_project.pdf" ]; then
    echo "Please run this script from the project root directory."
    exit 1
fi

./scripts/benchmark-exact.sh
echo "Exact benchmark finished."

./scripts/benchmark-constructive.sh
echo "Constructive benchmark finished."

./scripts/benchmark-local-search.sh
echo "Local search benchmark finished."

./scripts/benchmark-grasp.sh
echo "GRASP benchmark finished."