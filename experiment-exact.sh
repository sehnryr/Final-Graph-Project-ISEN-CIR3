#!/usr/bin/bash

# This script is used to run the experiment for the exact algorithm.

EXEC=./build/main
TYPE="exact"

GRAPH_GEN=./build/generate
TEMP_DIR=./temp

RESULTS_DIR=./report/experiment_data

NUM_TRIALS=5

# Create TEMP_DIR
mkdir -p $TEMP_DIR

# Create RESULTS_DIR
mkdir -p $RESULTS_DIR

# Run the experiment for each connectivity
for CONNECTIVITY in 25 50 75 ; do
    # Empty .dat file for the results
    echo "x y" > "$RESULTS_DIR/${TYPE}_${CONNECTIVITY}.dat"

    # Run the experiment with 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 vertices
    for VERTEX_COUNT in 10 20 30 40 50 60 70 80 90 100 ; do
        # Run for each vertex count a 100 times to get a better average
        for ((i=1; i <= NUM_TRIALS; i++)) ; do
            # Generate a random graph
            $GRAPH_GEN $VERTEX_COUNT $CONNECTIVITY --output-dir=$TEMP_DIR

            # Run the algorithm
            TIME_EXEC=$($EXEC "$TEMP_DIR/${VERTEX_COUNT}_${CONNECTIVITY}.in" --type=$TYPE --output-dir=$TEMP_DIR)

            # Add the time to the result file
            echo "$VERTEX_COUNT $TIME_EXEC" >> "$RESULTS_DIR/${TYPE}_${CONNECTIVITY}.dat"
        done
    done
done

# Remove the TEMP_DIR
rm -rf $TEMP_DIR