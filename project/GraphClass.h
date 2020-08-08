#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <set>
#include <utility>
#include <fstream>
#include "Exception.h"
#include "GraphParser.h"

namespace mtm
{
    class graph
    {
    private:
        std::set<std::string> vertices;
        std::set<std::pair<std::string, std::string>> edges;

        static std::string readVertex(std::ifstream& fd);
        static std::pair<std::string, std::string> readEdge(std::ifstream& fd);
        static bool isVertexNameValid(const std::string& vertex);

    public:
        graph() = default;
        graph(const std::string& data);
        graph(const std::set<std::string>& vertices, const std::set<std::pair<std::string, std::string>>& edges);
        graph(const graph& other) = default;
        ~graph() = default;

        static void save(const graph& G, const std::string& filename);
        static graph load(const std::string& filename);

        graph operator+(const graph& other) const;
        graph operator^(const graph& other) const;
        graph operator-(const graph& other) const;
        graph operator*(const graph& other) const;
        graph operator!() const;
        friend std::ostream& operator<<(std::ostream& out, const graph& G);
    };
    std::ostream& operator<<(std::ostream& out, const graph& G);
}
#endif