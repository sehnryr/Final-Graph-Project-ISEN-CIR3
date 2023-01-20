#!/usr/bin/bash

# This script is used to run the experiment for the exact algorithm.

# If the script is not run from the project root directory, exit
if [ ! -f "Final_project.pdf" ]; then
    echo "Please run this script from the project root directory."
    exit 1
fi

GRAPH_GEN=./build/generate

TEMP_DIR=./temp
RESULTS_DIR=./report/experiment_data
GRASP_BIN_DIR=./build/grasp

NUM_TRIALS=10

# Create TEMP_DIR
mkdir -p $TEMP_DIR

# Create RESULTS_DIR
mkdir -p $RESULTS_DIR

# define function to get the weight of the clique found from a .out file
function get_result_clique_weight {
    head -n1 "$1" | cut -f2 -d" "
}

function get_alpha {
    echo "0.$(rev <<< "$1" | cut -f1 -d"." | rev | cut -f1 -d"_")"
}

function get_retries {
    rev <<< "$1" | cut -f1 -d"_" | rev
}

BASE_CONNECTIVITY=50

# Compile the grasp algorithm
./scripts/compile-grasp.sh $GRASP_BIN_DIR >> /dev/null

# Empty .dat file for the results
cat /dev/null > "$RESULTS_DIR/grasp_RCL_param.dat"

for VERTEX_COUNT in 10 20 30 40 50 60 70 80 90 100 ; do
    # Run for each vertex count a 100 times to get a better average
    for ((i=1; i <= NUM_TRIALS; i++)) ; do
        # Generate a random graph
        $GRAPH_GEN $VERTEX_COUNT $BASE_CONNECTIVITY --output-dir=$TEMP_DIR

        for GRASP in "$GRASP_BIN_DIR"/* ; do
            ALPHA=$(get_alpha "$GRASP")
            RETRIES=$(get_retries "$GRASP")

            # Run the algorithm
            TIME=$($GRASP "$TEMP_DIR/${VERTEX_COUNT}_${BASE_CONNECTIVITY}.in" --type=grasp --output-dir=$TEMP_DIR)

            RESULT=$(get_result_clique_weight "$TEMP_DIR/${VERTEX_COUNT}_${BASE_CONNECTIVITY}_grasp.out")

            # Add the time to the result file
            echo "$VERTEX_COUNT $ALPHA $RETRIES $TIME $RESULT" >> "$RESULTS_DIR/grasp_RCL_param.dat"
        done
    done
    echo "Done with $VERTEX_COUNT"
done

# Remove TEMP_DIR
rm -rf $TEMP_DIR