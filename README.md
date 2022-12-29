# Final-Graph-Project-ISEN-CIR3
The Maximum Edge Weight Clique Problem

```
Maximum_Edge_Weight_Clique(Graph G = (V, E))
  maximum_clique <- empty stack
  maximum_weight = 0

  for i = 0 to n
    for j = i + 1 to n
      weight = w(edge(i, j))

      clique <- empty stack
      enqueue(i, clique)
      enqueue(j, clique)

      for k = j + 1 to n
        if k is adjacent to all vertices in clique
          weight += w(edge(i, k)) + w(edge(j, k))
          enqueue(k, clique)
            
      if weight > maximum_weight
        maximum_weight = weight
        maximum_clique = clique
```

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