#include <iostream>
#include <sstream>
#include <map>

#include "header/read_from_config.hpp"
#include "lib/utility.cpp"

#ifndef BUFFER_SIZE_LINE
#define BUFFER_SIZE_LINE 256
#endif

typedef std::map<std::string, int> t_msi;

read_from_config::read_from_config(const char* path):
    m_path(path)
    {
    std::cout << "Read From config initialized with sucess" << std::endl;
    // this->m_agencia = new char[BUFFER_SIZE_LINE];
    this->m_id = new char[BUFFER_SIZE_LINE];
    this->m_div = new char[BUFFER_SIZE_LINE];
    this->m_valor = new char[BUFFER_SIZE_LINE];
    this->m_conta = new char[BUFFER_SIZE_LINE];

    this->_fill_values();    
    }

read_from_config::~read_from_config()
{
    delete []this->m_id;
    delete []this->m_conta;
    delete []this->m_agencia;
    delete []this->m_valor;
    delete []this->m_div;
}

/*
fgetc = get only an unique char.
fscanf = get the words with custom pattern, it stop when found new black space. 
fgets = get whole line or delimiter by number size.
fseek = move pointer for determined position of file.
ftell = storage current position of cursor present in instance object file
*/

t_msi findLines(FILE* p_file)
{
    char temp[BUFFER_SIZE_LINE];
    std::string temp_string;
    int line = 0;
    t_msi linesFound;
     
    while(fgets(temp, BUFFER_SIZE_LINE, p_file) != NULL)
    {
        temp_string = utility::convert_to_string<char *>(temp);
        if(temp_string == "$HEADER")
            linesFound[std::string("header")] = line;
        if(temp_string == "$SEGMENTO-A")
            linesFound[std::string("segmento_a")] = line;
        if(temp_string == "$SEGMENTO-B")
            linesFound[std::string("segmento_b")] = line;
        
        ++line;
    }

    fseek(p_file, SEEK_SET, SEEK_SET);
    return linesFound;
}

template<typename T>
bool setMembers(const std::string p_string, t_msi& p_map, T member)
{
    std::map<std::string, int>::iterator it = p_map.find(p_string);
    if(it == p_map.end())
        return false;
    
    member = it->second;
    return true;
}

void lineHeader(FILE* p_file, t_msi& lhs_map, std::map<std::string, std::string>& rhs_map)
{
    char temp[BUFFER_SIZE_LINE];
    int init_line = lhs_map["header"] + 1;
    int end_line = lhs_map["segmento_a"];
    std::string temp_string_patch;
    std::string temp_string_full;
    std::string pattern_regex = "\\[[0-9]{1,4}.[0-9]{1,4}\\]";
    utility::jump_lines(p_file, init_line);
    
    while(init_line++ < end_line )
    {
        fgets(temp, BUFFER_SIZE_LINE, p_file);
        temp_string_patch = utility::convert_to_string<char*>(temp);
        temp_string_full = utility::convert_to_string_by_arr<char>(temp);
        int position_substring = utility::position_subtext(pattern_regex, temp_string_full);
        
        std::cout << "begin line header -> " << temp_string_patch << std::endl;
        if(position_substring != -1) {
            std::string cut_full_result = temp_string_full.substr(position_substring, temp_string_full.size());
            rhs_map[temp_string_patch] = cut_full_result;
            std::cout << "cut full result -> " << cut_full_result << std::endl;
        }
    }

    fseek(p_file, SEEK_SET, SEEK_SET);
}

void lineSegmentoA(FILE* p_file, t_msi& lhs_map, std::map<std::string, std::string>& rhs_map)
{
    char temp[BUFFER_SIZE_LINE];
    int init_line = lhs_map["segmento_a"] + 1;
    int end_line = lhs_map["segmento_b"];
    std::string temp_string_patch;
    std::string temp_string_full;
    std::string pattern_regex = "\\[[0-9]{1,4}.[0-9]{1,4}\\]";
    utility::jump_lines(p_file, init_line);
    
    while(init_line++ < end_line )
    {
        fgets(temp, BUFFER_SIZE_LINE, p_file);
        temp_string_patch = utility::convert_to_string<char*>(temp);
        temp_string_full = utility::convert_to_string_by_arr<char>(temp);
        int position_substring = utility::position_subtext(pattern_regex, temp_string_full);
        
        std::cout << "begin line segmento_a -> " << temp_string_patch << std::endl;
        if(position_substring != -1) {
            std::string cut_full_result = temp_string_full.substr(position_substring, temp_string_full.size());
            rhs_map[temp_string_patch] = cut_full_result;
            std::cout << "cut full result -> " << cut_full_result << std::endl;
        }
    }

    fseek(p_file, SEEK_SET, SEEK_SET);
}

void lineSegmentoB(FILE* p_file, t_msi& lhs_map, std::map<std::string, std::string>& rhs_map)
{
    char temp[BUFFER_SIZE_LINE];
    int init_line = lhs_map["segmento_b"] + 1;
    std::string temp_string_patch;
    std::string temp_string_full;
    std::string pattern_regex = "\\[[0-9]{1,4}.[0-9]{1,4}\\]";
    utility::jump_lines(p_file, init_line);
    
    while(fgets(temp, BUFFER_SIZE_LINE, p_file))
    {
        temp_string_patch = utility::convert_to_string<char*>(temp);
        temp_string_full = utility::convert_to_string_by_arr<char>(temp);
        int position_substring = utility::position_subtext(pattern_regex, temp_string_full);
        
        std::cout << "begin line segmento_b -> " << temp_string_patch << std::endl;
        if(position_substring != -1) {
            std::string cut_full_result = temp_string_full.substr(position_substring, temp_string_full.size());
            rhs_map[temp_string_patch] = cut_full_result;
            std::cout << "cut full result -> " << cut_full_result << std::endl;
        }
    }

    fseek(p_file, SEEK_SET, SEEK_SET);
}

void read_from_config::_fill_values()
{
    std::cout << "m_path in _fill_values == " << this->m_path << std::endl;
    FILE* file = fopen(this->m_path, "rb+");
    t_msi linesFound = findLines(file);
    std::map<std::string, std::string> valuesCamp;

    if(file == NULL)
        perror("Can't to open file");
    
    utility::print_map<t_msi>(linesFound);
    lineHeader(file, linesFound, valuesCamp);
    lineSegmentoA(file, linesFound, valuesCamp);
    lineSegmentoB(file, linesFound, valuesCamp);

    fclose(file);
}