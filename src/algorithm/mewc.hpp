#include "../model/clique.hpp"
#include "../model/graph.hpp"

#ifndef MEWC_HPP
#define MEWC_HPP

Clique exactMEWC(Graph g);
Clique constructiveMEWC(Graph g);
Clique localSearchMEWC(Graph g);
Clique graspMEWC(Graph g);

#endif // MEWC_HPP