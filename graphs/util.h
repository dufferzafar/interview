#include <vector>
#include <list>
#include <iostream>
#include <utility>

typedef int item;
typedef std::vector<item> row;
typedef std::vector<row> matrix;

void print_graph(matrix adj) {
    for (int i = 1; i < adj.size(); ++i)
    {
        std::cout << i << " -> ";
        for(row::iterator it = adj[i].begin(); it != adj[i].end(); ++it)
        {
            std::cout << *it << " | ";
        }
        std::cout << std::endl;
    }
}
