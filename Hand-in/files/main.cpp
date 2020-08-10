#include <iostream>
#include <fstream>
#include <string>
#include "CalcParser.h"

using namespace mtm;
void runCalculator(std::istream* in, std::ostream* out, bool print_gcalc = true);

int main(int argc, char *argv[])
{
    std::istream* in;
    std::ostream* out;
    switch(argc)
    {
        case 1:
        {
            in = &std::cin;
            out = &std::cout;
            runCalculator(in, out);
            break;
        }
        case 3:
        {
            std::ifstream input_file(argv[1]);
            if(!input_file)
            {
                std::cerr << "Error: Cannot open the input file." << std::endl;
                return 1;
            }
            std::ofstream output_file(argv[2]);
            if(!output_file)
            {
                std::cerr << "Error: Cannot open the output file." << std::endl;
                return 1;
            }
            in = &input_file;
            out = &output_file;
            runCalculator(in, out, false);
            break;
        }
        default:
        {
            std::cerr << "Error: Syntax error - ./gcalc | ./gcalc [input_file.txt] [output_file.txt]" << std::endl;
            return 1;
        }
    }
    return 0;
}

void runCalculator(std::istream* in, std::ostream* out, bool print_gcalc)
{
    bool quit_flag = false;
    std::string text;
    if(print_gcalc)
    {
        *out << "Gcalc> ";
    }
    while(!quit_flag && std::getline(*in, text))
    {
        CalcParser parser(text, out);
        try
        {
            parser.evaluate();
        }
        catch(const Exception& e)
        {
            *out << e.what() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << '\n';
            quit_flag = true;
        }
        if(!quit_flag)
        {
            quit_flag = parser.quitFlag();
        }
        if(!quit_flag && print_gcalc)
        {
            *out << "Gcalc> ";
        }
    }
}