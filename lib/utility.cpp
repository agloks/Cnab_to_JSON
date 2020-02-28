#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

#ifndef BUFFER_SIZE_LINE
#define BUFFER_SIZE_LINE 256
#endif


namespace utility {

    template <typename T>
    std::string convert_to_string(T arr)
    {
        std::string pointer_to_string;
        std::stringstream ss;
        
        ss << arr;
        ss >> pointer_to_string;

        return pointer_to_string;
    };

    std::string convert_to_string_by_pointer(char* ptr_c, int size)
    {
        std::string pointer_to_string;
        int increment = 0;
        while(size--)
            pointer_to_string.push_back(*(ptr_c + increment++));

        return pointer_to_string;
    };

    void jump_lines(FILE* p_file, const int& jump)
    {
        char t[BUFFER_SIZE_LINE];
        for(int k = 0; k < jump; k++)
            fgets(t, BUFFER_SIZE_LINE, p_file);
    };

    template<typename T, typename S = std::string, typename I = int>
    void print_map(const T& mapa)
    {
        std::for_each(mapa.begin(), mapa.end(), [&](std::pair<S, I> elem){
            std::cout << "Key: " << elem.first << "  "
                      << "Value: " << elem.second << std::endl;
        });
    };
};