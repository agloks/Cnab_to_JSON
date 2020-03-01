#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <regex>

#ifndef BUFFER_SIZE_LINE
#define BUFFER_SIZE_LINE 256
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
            std::cout << "Key: " << elem.first << "  "
                    << "Value: " << elem.second << std::endl;
        });
    };

    int position_subtext(std::string pattern, std::string& text);

    void debug();
};

#endif