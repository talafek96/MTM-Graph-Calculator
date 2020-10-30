#include "graph.h"

using namespace mtm;
graph* create()
{
    graph* new_graph;
    try
    {
        new_graph = new graph;
    }
    catch(const std::exception& e)
    {
        std::cout << "Error: " << e.what() << '\n';
    }
    return new_graph;
}

void destroy(graph* graph)
{
    if(!graph)
    {
        return;
    }
    delete graph;
}

graph* addVertex(graph* graph, const char* v)
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
    catch(const Exception& e)
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

graph* addEdge(graph* graph, const char* v1, const char* v2)
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
    catch(const Exception& e)
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

void disp(graph* graph)
{
    if(!graph)
    {
        std::cout << "Error: nullptr input.\n";
        return;
    }
    std::cout << *graph << '\n';
}

graph* graphUnion(graph* graph_in1, graph* graph_in2, graph* graph_out)
{
    if(!graph_in1 || !graph_in2 || !graph_out)
    {
        std::cout << "Error: nullptr input.\n";
        return nullptr;
    }
    *graph_out = graph_in1->unite(*graph_in2);
    return graph_out;
}
graph* graphIntersection(graph* graph_in1, graph* graph_in2, graph* graph_out)
{
    if(!graph_in1 || !graph_in2 || !graph_out)
    {
        std::cout << "Error: nullptr input.\n";
        return nullptr;
    }
    *graph_out = graph_in1->intersection(*graph_in2);
    return graph_out;
}
graph* graphDifference(graph* graph_in1, graph* graph_in2, graph* graph_out)
{
    if(!graph_in1 || !graph_in2 || !graph_out)
    {
        std::cout << "Error: nullptr input.\n";
        return nullptr;
    }
    *graph_out = graph_in1->difference(*graph_in2);
    return graph_out;
}
graph* graphProduct(graph* graph_in1, graph* graph_in2, graph* graph_out)
{
    if(!graph_in1 || !graph_in2 || !graph_out)
    {
        std::cout << "Error: nullptr input.\n";
        return nullptr;
    }
    *graph_out = graph_in1->product(*graph_in2);
    return graph_out;
}
graph* graphComplement(graph* graph_in, graph* graph_out)
{
    if(!graph_in || !graph_out)
    {
        std::cout << "Error: nullptr input.\n";
        return nullptr;
    }
    *graph_out = graph_in->complement();
    return graph_out;
}