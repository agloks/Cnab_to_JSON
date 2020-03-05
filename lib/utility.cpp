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

std::string utility::string_from_fgetc(FILE* p_file, const int& len, const int& begin)
{
    std::string send;
    fpos_t pos_save = ftell(p_file);
    fseek(p_file, begin, SEEK_CUR);
    for(int k = 0; k <= len; k++)
    {
        send.push_back(fgetc(p_file));
    }

    fseek(p_file, pos_save, SEEK_SET);
    return send;
};

void utility::isEnd(std::string& str)
{
    int pos = 0;
    // while(pos = utility::position_subtext(pattern, str) != -1)
    // {
    //     std::cout << "i'm clear_all_space " << pos << std::endl;
    //     str.replace(pos-1, pos+1, "");
    // };
    std::for_each(str.begin(), str.end(), [&](int a)
    {
        if(EOF == a)
            str.replace(pos, pos+1 , "");
        ++pos;
    });
}

std::vector<std::string> utility::split(const std::string& s, char seperator)
{
    std::vector<std::string> output;
    std::string::size_type prev_pos = 0, pos = 0;

    while((pos = s.find(seperator, pos)) != std::string::npos)
    {
        std::string substring( s.substr(prev_pos, pos-prev_pos) );
        output.push_back(substring);
        prev_pos = ++pos;
    }

    output.push_back(s.substr(prev_pos, pos-prev_pos)); // Last word
    return output;
}

void utility::debug()
{
    std::cout << "can't understand it" << std::endl;
};