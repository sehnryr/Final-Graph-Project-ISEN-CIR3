# Final-Graph-Project-ISEN-CIR3
The Maximum Edge Weight Clique Problem

- [Final-Graph-Project-ISEN-CIR3](#final-graph-project-isen-cir3)
  - [Installation](#installation)
  - [Build](#build)
  - [Usage](#usage)


## Installation
To install the project, you need to clone the repository.

```bash
git clone https://github.com/sehnryr/Final-Graph-Project-ISEN-CIR3.git
cd Final-Graph-Project-ISEN-CIR3
```

## Build
To build the project, you first need to install the c++ compiler and make.

```bash
sudo apt install build-essential
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