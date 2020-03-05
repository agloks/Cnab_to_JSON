#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <regex>

#ifndef BUFFER_SIZE_LINE
#define BUFFER_SIZE_LINE 242
#endif

namespace utility {
    std::string convert_to_string(char* arr);

    std::string convert_to_string_by_arr(const char* arr);

    std::string convert_to_string_by_pointer(char* ptr_c, int size);

    void jump_lines(FILE* p_file, const int& jump);

    template<typename T, typename S = std::string, typename I = int>
    void print_map(const T& mapa)
    {
        std::for_each(mapa.begin(), mapa.end(), [&](std::pair<S, I> elem){
            std::cout << "Key: " << elem.first << " "
                    << "Value: " << elem.second << std::endl;
        });
    };

    template<typename T>
    void print_map_vector(const T& mapa)
    {
        auto it_map = mapa.begin();
        for(int k = 0; k < mapa.size(); k++)
        {
            std::cout << it_map->first << " -> \n ";
            for(auto x: it_map++ -> second)
            {
                std::cout << "\t" << x << std::endl;
            }
        }
    };

    template<typename T, typename MP>
    void print_map_vector_map(const T& mapa)
    {
        auto it_map = mapa.begin();
        for(int k = 0; k < mapa.size(); k++)
        {
            std::cout << it_map->first << "-->" << std::endl;;
            for(auto x: it_map++ -> second)
            {                
                utility::print_map<MP, std::string, std::string>(x);
            }
        }
    };

    int position_subtext(std::string pattern, std::string& text);

    std::string string_from_fgetc(FILE* p_file, const int& len, const int& begin);
    std::vector<std::string> split(const std::string& s, char seperator);
    void isEnd(std::string& str);
    void debug();
};

#endif