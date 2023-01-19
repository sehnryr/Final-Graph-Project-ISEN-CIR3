#!/usr/bin/bash

# This script is used to run the experiment for the exact algorithm.

EXEC=./build/main
# TYPE="constructive"

GRAPH_GEN=./build/generate
TEMP_DIR=./temp

RESULTS_DIR=$TEMP_DIR

NUM_TRIALS=10

# Create TEMP_DIR
mkdir -p $TEMP_DIR

# Create RESULTS_DIR
mkdir -p $RESULTS_DIR

cat /dev/null > $TEMP_DIR/moyenne

# Run the experiment for each connectivity
for CONNECTIVITY in 25 50 75 ; do
    # Empty .dat file for the results
    echo "x y" > "$RESULTS_DIR/${TYPE}_${CONNECTIVITY}.dat"

    # Run the experiment with 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 vertices
    for VERTEX_COUNT in 100 200 300 400 500 600 700 800 900 1000; do
        # Run for each vertex count a 100 times to get a better average
        for ((i=1; i <= NUM_TRIALS; i++)) ; do

            # Generate a random graph
            $GRAPH_GEN $VERTEX_COUNT $CONNECTIVITY --output-dir=$TEMP_DIR

            # Run the algorithm
            for TYPE in constructive_degree_youn constructive_sum_alex constructive_sum_youn constructive_degree_alex; do

            $EXEC "$TEMP_DIR/${VERTEX_COUNT}_${CONNECTIVITY}.in" --type=${TYPE} --output-dir=$TEMP_DIR

            val=$(( $(cut -f2 -d" " $TEMP_DIR/${VERTEX_COUNT}_${CONNECTIVITY}_${TYPE}.out | head -n1) ))

            # echo -n "${VERTEX_COUNT}_${CONNECTIVITY} try = $i resultat =" >> $TEMP_DIR/resultat_${TYPE}
            echo $(($val)) >> $TEMP_DIR/resultat_${TYPE}
            done
        done

        
    done
done

# Remove the TEMP_DIR
# rm -rf $TEMP_DIR