#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <set>
#include <utility>

namespace mtm
{
    class graph
    {
    private:
        std::set<std::string> vertices;
        std::set<std::pair<std::string, std::string>> edges;
    public:
        graph() = default;
        graph(const std::string& data);
        graph(const std::set<std::string>& vertices, const std::set<std::pair<std::string, std::string>>& edges);
        graph(const graph& other) = default;
        ~graph() = default;

        static void save(const graph& G, const std::string& filename);
        static graph load(const std::string& filename);

        graph operator+(const graph& other);
        graph operator^(const graph& other);
        graph operator-(const graph& other);
        graph operator*(const graph& other);
        graph operator!();
        friend std::ostream& operator<<(std::ostream& out, graph G);
    };
    std::ostream& operator<<(std::ostream& out, graph G);
}
#endif