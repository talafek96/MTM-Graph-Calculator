#include "graph.h"

mtm::graph* create()
{
    mtm::graph* new_graph;
    try
    {
        new_graph = new mtm::graph;
    }
    catch(const std::exception& e)
    {
        std::cout << "Error: " << e.what() << '\n';
    }
    return new_graph;
}

void destroy(mtm::graph* graph)
{
    if(!graph)
    {
        return;
    }
    delete graph;
}

mtm::graph* addVertex(mtm::graph* graph, const char* v)
{
    if(!graph || !v)
    {
        std::cout << "Error: nullptr input.\n";
        return nullptr;
    }
    try
    {
        graph->addVertex(v);
    }
    catch(const mtm::Exception& e)
    {
        std::cout << e.what() << '\n';
        return nullptr;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
        return nullptr;
    }
    return graph;
}

mtm::graph* addEdge(mtm::graph* graph, const char* v1, const char* v2)
{
    if(!graph || !v1 || !v2)
    {
        std::cout << "Error: nullptr input.\n";
        return nullptr;
    }
    try
    {
        graph->addEdge(v1, v2);
    }
    catch(const mtm::Exception& e)
    {
        std::cout << e.what() << '\n';
        return nullptr;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
        return nullptr;
    }
    return graph;
}

void disp(mtm::graph* graph)
{
    if(!graph)
    {
        std::cout << "Error: nullptr input.\n";
        return;
    }
    std::cout << *graph << '\n';
}

mtm::graph* graphUnion(mtm::graph* graph_in1, mtm::graph* graph_in2, mtm::graph* graph_out)
{
    if(!graph_in1 || !graph_in2 || !graph_out)
    {
        std::cout << "Error: nullptr input.\n";
        return nullptr;
    }
    *graph_out = *graph_in1 + *graph_in2;
    return graph_out;
}
mtm::graph* graphIntersection(mtm::graph* graph_in1, mtm::graph* graph_in2, mtm::graph* graph_out)
{
    if(!graph_in1 || !graph_in2 || !graph_out)
    {
        std::cout << "Error: nullptr input.\n";
        return nullptr;
    }
    *graph_out = *graph_in1 ^ *graph_in2;
    return graph_out;
}
mtm::graph* graphDifference(mtm::graph* graph_in1, mtm::graph* graph_in2, mtm::graph* graph_out)
{
    if(!graph_in1 || !graph_in2 || !graph_out)
    {
        std::cout << "Error: nullptr input.\n";
        return nullptr;
    }
    *graph_out = *graph_in1 - *graph_in2;
    return graph_out;
}
mtm::graph* graphProduct(mtm::graph* graph_in1, mtm::graph* graph_in2, mtm::graph* graph_out)
{
    if(!graph_in1 || !graph_in2 || !graph_out)
    {
        std::cout << "Error: nullptr input.\n";
        return nullptr;
    }
    *graph_out = *graph_in1 * *graph_in2;
    return graph_out;
}
mtm::graph* graphComplement(mtm::graph* graph_in, mtm::graph* graph_out)
{
    if(!graph_in || !graph_out)
    {
        std::cout << "Error: nullptr input.\n";
        return nullptr;
    }
    *graph_out = !*graph_in;
    return graph_out;
}
