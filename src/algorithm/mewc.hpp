#include "../clique.hpp"
#include "../graph.hpp"

#ifndef MEWC_HPP
#define MEWC_HPP

Clique exactMEWC(Graph g);
Clique constructiveMEWC(Graph g);
Clique localSearchMEWC(Graph g);
Clique graspMEWC(Graph g);

#endif // MEWC_HPP