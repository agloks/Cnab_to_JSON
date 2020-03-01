#include "header/utility.hpp"

std::string utility::convert_to_string(char* arr)
{
    std::string pointer_to_string;
    std::stringstream ss;

    ss << arr;
    ss >> pointer_to_string;

    return pointer_to_string;
};

std::string utility::convert_to_string_by_arr(const char *arr)
{
    std::string pointer_to_string;
    while(*arr++ != '\0')
    {
        pointer_to_string.push_back(*arr);
    }

    return pointer_to_string;
};

std::string utility::convert_to_string_by_pointer(char* ptr_c, int size)
{
    std::string pointer_to_string;
    int increment = 0;
    while(size--)
        pointer_to_string.push_back(*(ptr_c + increment++));

    return pointer_to_string;
};

void utility::jump_lines(FILE* p_file, const int& jump)
{
    char t[BUFFER_SIZE_LINE];
    for(int k = 0; k < jump; k++)
        fgets(t, BUFFER_SIZE_LINE, p_file);
};


int utility::position_subtext(std::string pattern, std::string& text)
{
    auto const regex_pattern = std::regex(pattern);
    auto search_results = std::smatch{};
    bool const result = std::regex_search(text, search_results, regex_pattern);
    if(result) 
        return search_results.prefix().length();
    return -1;
};

void utility::debug()
{
    std::cout << "can't understand it" << std::endl;
}