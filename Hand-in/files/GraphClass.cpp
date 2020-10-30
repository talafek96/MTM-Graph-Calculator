#include "GraphClass.h"
#include <vector>

namespace mtm
{
    graph::graph(const std::string& data)
    {
        GraphParser parser(data);
        parser.evaluate();
        vertices = parser.vertices;
        edges = parser.edges;
    }

    graph::graph(const std::set<std::string>& vertices, const std::set<std::pair<std::string, std::string>>& edges) :
    vertices(vertices), edges(edges) { }

    graph graph::operator+(const graph& other) const
    {
        graph result;
        result.edges = edges;
        result.vertices = vertices;
        result.edges.insert(other.edges.begin(), other.edges.end());
        result.vertices.insert(other.vertices.begin(), other.vertices.end());
        return result;
    }

    graph graph::operator-(const graph& other) const
    {
        graph result = *this;
        for(auto vertex : other.vertices)
        {
            if(vertices.count(vertex))
            {
                result.vertices.erase(vertex); 
                for(auto edge : edges)
                {
                    if((edge.first == vertex) || (edge.second == vertex))
                    {
                        result.edges.erase(edge);
                    }
                }
            }
        }
        return result;
    }

    graph graph::operator^(const graph& other) const
    {
        graph result;
        for(auto vertex : vertices)
        {
            if(other.vertices.count(vertex))
            {
                result.vertices.insert(vertex);
            }
        }
        for(auto edge : edges)
        {
            if(other.edges.count(edge))
            {
                result.edges.insert(edge);
            }
        }
        return result;
    }

    graph graph::operator!() const
    {
        graph result;
        result.vertices = vertices;
        for(auto vertex1 : vertices)
        {
            for(auto vertex2 : vertices)
            {
                std::pair<std::string, std::string> p = {vertex1, vertex2};
                if((vertex1 != vertex2) && !edges.count(p))
                {
                    result.edges.insert(p);
                }
            }
        }
        return result;
    }
    
    graph graph::operator*(const graph& other) const
    {
        graph result;
        for(auto vertex1 : vertices)
        {
            for(auto vertex2 : other.vertices)
            {
                std::string new_vertex = ('['+vertex1+';'+vertex2+']');
                result.vertices.insert(new_vertex);
            }
        }
        for(auto edge1 : edges)
        {
            for(auto edge2 : other.edges)
            {
                std::pair<std::string, std::string> new_edge =
                {('['+edge1.first+';'+edge2.first+']'), ('['+edge1.second+';'+edge2.second+']') };
                result.edges.insert(new_edge);
            }
        }
        return result;
    }

    std::ostream& operator<<(std::ostream& out, const graph& G)
    {
        for(auto vertex : G.vertices)
        {
            out << vertex << std::endl;
        }
        out << '$';
        for(auto edge : G.edges)
        {
            out << std::endl << edge.first << ' ' << edge.second;
        }
        return out;
    }

    void graph::save(const graph& G, const std::string& filename)
    {
        std::ofstream fd(filename, std::ios_base::binary);
        if(!fd)
        {
            throw CannotWriteToFile(filename);
        }
        unsigned num_vertices = G.vertices.size();
        unsigned num_edges = G.edges.size();
        fd.write(reinterpret_cast<char*>(&num_vertices), sizeof(num_vertices));
        fd.write(reinterpret_cast<char*>(&num_edges), sizeof(num_edges));
        for(auto vertex : G.vertices)
        {
            unsigned vertex_strlen = vertex.size();
            fd.write(reinterpret_cast<char*>(&vertex_strlen), sizeof(vertex_strlen));
            fd.write(vertex.c_str(), vertex_strlen);
        }
        for(auto edge : G.edges)
        {
            unsigned first_strlen = edge.first.size();
            unsigned second_strlen = edge.second.size();
            fd.write(reinterpret_cast<char*>(&first_strlen), sizeof(unsigned));
            fd.write(edge.first.c_str(), first_strlen);
            fd.write(reinterpret_cast<char*>(&second_strlen), sizeof(unsigned));
            fd.write(edge.second.c_str(), second_strlen);
        }
    }

    bool graph::isVertexNameValid(const std::string& vertex)
    {
        GraphLexer lexer(vertex);
        for(lexer.fetchNextToken(); lexer.getCurrentToken().type != Type::end; lexer.fetchNextToken())
        {
            switch(lexer.getCurrentToken().type)
            {
                case Type::end:
                {
                    return true;
                }
                case Type::variable:
                {
                    break;
                }
                default:
                {
                    return false;
                }
            }
        }
        return true;
    }

    graph graph::load(const std::string& filename)
    {
        std::ifstream fd(filename, std::ios_base::binary);
        if(!fd)
        {
            throw CannotReadFromFile(filename);
        }
        unsigned num_vertices, num_edges;
        std::string vertex;
        std::pair<std::string, std::string> edge;
        graph result;
        fd.read(reinterpret_cast<char *>(&num_vertices), sizeof(num_vertices));
        if(fd.fail())
        {
            throw CorruptFile();
        }
        fd.read(reinterpret_cast<char *>(&num_edges), sizeof(unsigned));
        if(fd.fail())
        {
            throw CorruptFile();
        }

        for(unsigned i = 0; i < num_vertices; i++)
        {
            vertex = readVertex(fd);
            if(!isVertexNameValid(vertex))
            {
                throw FileIllegalVertexName(vertex);
            }
            if(result.vertices.count(vertex))
            {
                throw FileDuplicateVertex(vertex);
            }
            result.vertices.insert(vertex);
        }
        for(unsigned i = 0; i < num_edges; i++)
        {
            edge = readEdge(fd);
            if((!result.vertices.count(edge.first) || !result.vertices.count(edge.second))
            || edge.first == edge.second || result.edges.count(edge))
            {
                throw FileInvalidEdge(edge);
            }
            result.edges.insert(edge);
        }

        if(fd.peek() != EOF)
        {
            throw CorruptFile();
        }
        return result;
    }

    std::string graph::readVertex(std::ifstream& fd)
    {
        std::string vertex;
        unsigned vertex_strlen;
        fd.read(reinterpret_cast<char *>(&vertex_strlen), sizeof(vertex_strlen));
        if(fd.fail())
        {
            throw CorruptFile();
        }

        char* buffer = new char[vertex_strlen + 1];
        fd.read(buffer, vertex_strlen);
        if(fd.fail())
        {
            delete[] buffer;
            throw CorruptFile();
        }
        buffer[vertex_strlen] = '\0';

        vertex = std::string(buffer);

        delete[] buffer;

        return vertex;
    }

    std::pair<std::string, std::string> graph::readEdge(std::ifstream& fd)
    {
        std::pair<std::string, std::string> edge;

        edge.first = readVertex(fd);
        edge.second = readVertex(fd);

        return edge;
    }

    void graph::addVertex(const std::string& v)
    {
        if(!isVertexNameValid(v))
        {
            throw IllegalVertexName();
        }
        if(vertices.count(v))
        {
            throw DuplicateVertex();
        }
        vertices.insert(v);
    }

    void graph::addEdge(const std::string& v1, const std::string& v2)
    {
        std::pair<std::string, std::string> edge = { std::string(v1), std::string(v2) };
        if(!isVertexNameValid(v1) || !isVertexNameValid(v2))
        {
            throw IllegalVertexName();
        }
        if((!vertices.count(v1) || !vertices.count(v2))
        || v1 == v2 || edges.count(edge))
        {
            throw IllegalEdgeName();
        }
        edges.insert(edge);
    }

    graph graph::unite(const graph& other) const
    {
        return *this + other;
    }
    graph graph::intersection(const graph& other) const
    {
        return *this ^ other;
    }
    graph graph::difference(const graph& other) const
    {
        return *this - other;
    }
    graph graph::product(const graph& other) const
    {
        return *this * other;
    }
    graph graph::complement() const
    {
        return !(*this);
    }
}