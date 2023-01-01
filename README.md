# Final-Graph-Project-ISEN-CIR3
The Maximum Edge Weight Clique (MEWC) problem

## Table of Contents
- [Final-Graph-Project-ISEN-CIR3](#final-graph-project-isen-cir3)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Installation](#installation)
  - [Build](#build)
  - [Usage](#usage)
  - [Graph generator](#graph-generator)

## Introduction

Graph theory is a branch of mathematics that deals with the study of graphs,
which are mathematical structures used to model pairwise relationships between objects.
Graphs consist of vertices (also called nodes) that are connected by edges.
The edges can be directed (one-way) or undirected (two-way).

The Maximum Edge Weight Clique (MEWC) problem is an optimization problem in graph
theory that asks for the clique (a subset of vertices, all adjacent to one another)
with the maximum total weight in an edge-weighted undirected graph.
In the MEWC problem, each edge has a weight,
and the weight of a clique is the sum of the weights of its edges.
The goal is to find a clique with the maximum possible weight.

Now, the MEWC problem is NP-hard, which means that it is not possible to find an
efficient algorithm to solve it in polynomial time. It is also the generalization
of the Maximum Clique Problem (MCP), which is the special case where all edges
have the same weight.

The Maximum Edge Weight Clique (MEWC) problem can be used to model various types
of real-world situations where the goal is to find a subset of objects with the
maximum total weight, and the objects are connected by weighted edges.
Here are a few examples of such situations:
1. Network design: In a communication network, the MEWC problem can be used to 
   find the optimal subset of devices (vertices) to include in the network, 
   such that the total cost of communication between the devices (edges) is maximum.
1. Facility location: In a supply chain management problem, the MEWC problem can be
   used to find the optimal locations (vertices) for warehouses or distribution centers,
   such that the total transportation cost (edges) between the facilities is maximum.
1. Protein interaction: In biology, the MEWC problem can be used to find the optimal subset
   of proteins (vertices) in a protein-protein interaction network, such that the total
   interaction strength (edges) between the proteins is maximum.
1. Social network analysis: In a social network, the MEWC problem can be used to 
   find the optimal subset of individuals (vertices) with the maximum total
   relationship strength (edges) between them.

In this project, we will implement four algorithms to solve the MEWC problem:
1. Exact algorithm
1. Constructive algorithm
1. Local search algorithm
1. GRASP algorithm

## Installation
To install the project, you need to clone the repository.

```bash
git clone https://github.com/sehnryr/Final-Graph-Project-ISEN-CIR3.git
cd Final-Graph-Project-ISEN-CIR3
```

## Build
To build the project, you first need to install the c++ compiler and make.

```bash
sudo apt install build-essential make
```

Then, you can build the project with the following command.

```bash
make
```

## Usage
To run the project, you can use the following command.

```bash
./build/main <input-file> [options]
```

The `input-file` is the path to the input file.

The `options` are the following:
- `--type <algorithm-type>`: The algorithm type to use.
- `--output-dir=<dir>`: The directory to output the results to. (default: the input file directory)
- `--runs=<n>`: The number of runs to perform. (default: 1)
- `--help`: Display the help message.

The `algorithm-type` can be one of the following values:
- `exact` (default)
- `constructive`
- `local-search`
- `grasp`

The program will output the time taken to solve the problem in milliseconds.
The argument `--runs` can be used to perform multiple runs and output each time taken.

The program will also output the results in the `output-dir` directory with the
first line containing the number of vertices and the weight of the clique, and
the second line containing the vertices of the clique. The output file name will
be in the following file:
- `<input-file-name>-<algorithm>.out`: The output file containing the results.

> **Note**:
> You can get the average time taken by using the following command:
> ```bash
> ./build/main <input-file> --runs=<n> | awk '{sum+=$1} END {print sum/NR}'
> ```

## Graph generator
To generate a graph, you can compile the graph generator with the following command.

```bash
make generate
```

Then, you can run the graph generator with the following command.

```bash
./build/generate <num-vertices> <connectivity> [options]
```

The `num-vertices` is the number of vertices in the graph.
The `connectivity` is the connectivity of the graph, which is the probability
that an edge exists between two vertices.

The `options` are the following:
- `--output-dir=<dir>`: The directory to output the graph to. (default: the current directory)
- `--help`: Display the help message.

The program will output the graph in the `output-dir` directory with the first
line containing the number of vertices and the number of edges, and the following
lines containing the edges. The output file name will be in the following file:
- `<num-vertices>-<connectivity>.in`: The output file containing the graph.