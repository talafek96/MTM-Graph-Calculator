#include "graph.h"
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
        return (*this)^(!other);
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
        out << '&';
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
        int num_vertices = G.vertices.size();
        int num_edges = G.edges.size();
        fd.write((char*)&num_vertices, sizeof(int));
        fd.write((char*)&num_edges, sizeof(int));
        for(auto vertex : G.vertices)
        {
            int vertex_strlen = vertex.size();
            fd.write((char*)&vertex_strlen, sizeof(int));
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
        unsigned num_vertices, num_edges, first_strlen, second_strlen;
        std::string vertex;
        std::pair<std::string, std::string> edge;
        char* buffer;
        graph result;
        fd.read(reinterpret_cast<char *>(&num_vertices), sizeof(num_vertices));
        fd.read(reinterpret_cast<char *>(&num_edges), sizeof(unsigned));

        for(unsigned i = 0; i < num_vertices; i++)
        {
            vertex = readVertex(fd);
            if(!isVertexNameValid(vertex))
            {
                throw FileIllegalVertexName(vertex);
            }
            result.vertices.insert(vertex);
        }
        for(unsigned i = 0; i < num_edges; i++)
        {
            edge = readEdge(fd);
            if(!result.vertices.count(edge.first) || !result.vertices.count(edge.second))
            {
                throw FileInvalidEdge(edge);
            }
            result.edges.insert(edge);
        }
        if(!fd.eof())
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
        unsigned left_size, right_size;

        fd.read(reinterpret_cast<char *>(&left_size), sizeof(left_size));
        char* left_buffer = new char[left_size + 1];
        fd.read(left_buffer, left_size);
        if(fd.fail())
        {
            delete[] left_buffer;
            throw CorruptFile();
        }
        left_buffer[left_size] = '\0';
        edge.first = std::string(left_buffer);
        delete[] left_buffer;

        fd.read(reinterpret_cast<char *>(&right_size), sizeof(right_size));
        char* right_buffer = new char[right_size + 1];
        fd.read(right_buffer, right_size);
        if(fd.fail())
        {
            delete[] right_buffer;
            throw CorruptFile();
        }
        right_buffer[right_size] = '\0';
        edge.second = std::string(right_buffer);
        delete[] right_buffer;

        return edge;
    }
}