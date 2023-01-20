#!/usr/bin/bash

# This script is used to run the experiment for the exact algorithm.

# If the script is not run from the project root directory, exit
if [ ! -f "Final_project.pdf" ]; then
    echo "Please run this script from the project root directory."
    exit 1
fi

EXEC=./build/main

GRAPH_GEN=./build/generate
TEMP_DIR=./temp

RESULTS_DIR=./report/experiment_data

NUM_TRIALS=10

# Create TEMP_DIR
mkdir -p $TEMP_DIR

# Create RESULTS_DIR
mkdir -p $RESULTS_DIR

# define function to get the weight of the clique found from a .out file
function get_result_clique_weight {
    head -n1 "$1" | cut -f2 -d" "
}

# Run the experiment for each connectivity
for CONNECTIVITY in 25 50 75 ; do
    # Empty .dat file for the results
    cat /dev/null > "$RESULTS_DIR/accuracy_${CONNECTIVITY}.dat"

    # Run the experiment with 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 vertices
    for VERTEX_COUNT in 10 20 30 40 50 60 70 80 90 100 ; do
        # Run for each vertex count a 100 times to get a better average
        for ((i=1; i <= NUM_TRIALS; i++)) ; do
            # Generate a random graph
            $GRAPH_GEN $VERTEX_COUNT $CONNECTIVITY --output-dir=$TEMP_DIR

            # Run the algorithm
            for TYPE in "exact" "constructive" "local-search" "grasp" ; do
                $EXEC "$TEMP_DIR/${VERTEX_COUNT}_${CONNECTIVITY}.in" --output-dir=$TEMP_DIR --type=$TYPE >> /dev/null
            done

            EXACT=$(get_result_clique_weight "$TEMP_DIR/${VERTEX_COUNT}_${CONNECTIVITY}_exact.out")
            CONSTRUCTIVE=$(get_result_clique_weight "$TEMP_DIR/${VERTEX_COUNT}_${CONNECTIVITY}_constructive.out")
            LOCAL_SEARCH=$(get_result_clique_weight "$TEMP_DIR/${VERTEX_COUNT}_${CONNECTIVITY}_local_search.out")
            GRASP=$(get_result_clique_weight "$TEMP_DIR/${VERTEX_COUNT}_${CONNECTIVITY}_grasp.out")

            EXACT_PERCENT=$(echo "scale=2; $EXACT / $EXACT * 100" | bc)
            CONSTRUCTIVE_PERCENT=$(echo "scale=2; $CONSTRUCTIVE / $EXACT * 100" | bc)
            LOCAL_SEARCH_PERCENT=$(echo "scale=2; $LOCAL_SEARCH / $EXACT * 100" | bc)
            GRASP_PERCENT=$(echo "scale=2; $GRASP / $EXACT * 100" | bc)

            # Add the time to the result file
            echo "$VERTEX_COUNT $EXACT_PERCENT $CONSTRUCTIVE_PERCENT $LOCAL_SEARCH_PERCENT $GRASP_PERCENT" >> "$RESULTS_DIR/accuracy_${CONNECTIVITY}.dat"
        done
    done
done

# Remove the TEMP_DIR
rm -rf $TEMP_DIR