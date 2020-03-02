#include <iostream>
#include <sstream>

#include "header/read_from_config.hpp"
#include "header/utility.hpp"

#ifndef BUFFER_SIZE_LINE
#define BUFFER_SIZE_LINE 256
#endif

read_from_config::read_from_config(const char* path):
    m_path(path)
    {
    std::cout << "Read From config initialized with sucess\n" << std::endl;
 
    this->_fill_values();    
    }

read_from_config::~read_from_config()
{}

t_msi findLines(FILE* p_file)
{
    char temp[BUFFER_SIZE_LINE];
    std::string temp_string;
    int line = 0;
    t_msi linesFound;
     
    while(fgets(temp, BUFFER_SIZE_LINE, p_file) != NULL)
    {
        temp_string = utility::convert_to_string(temp);
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
bool setMembers(const std::string p_string, std::map<std::string, std::string>& p_map, T& member)
{
    std::map<std::string, std::string>::iterator it = p_map.find(p_string);
    if(it == p_map.end())
        return false;
    
    member = it->second;
    return true;
}

void read_from_config::lineHeader(FILE* p_file, t_msi& lhs_map)
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
        temp_string_patch = utility::convert_to_string(temp);
        temp_string_full = utility::convert_to_string_by_arr(temp);
        int position_substring = utility::position_subtext(pattern_regex, temp_string_full);
        
        // std::cout << "begin line header -> " << temp_string_patch << std::endl;
        if(position_substring != -1) {
            std::string cut_full_result = temp_string_full.substr(position_substring, temp_string_full.size());
            this->m_values_on_item_segments[temp_string_patch] = cut_full_result;
            this->m_items_on_segments["header"].push_back(temp_string_patch);
            // std::cout << "cut full result -> " << cut_full_result << std::endl;
        }
    }

    fseek(p_file, SEEK_SET, SEEK_SET);
}

void read_from_config::lineSegmentoA(FILE* p_file, t_msi& lhs_map)
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
        temp_string_patch = utility::convert_to_string(temp);
        temp_string_full = utility::convert_to_string_by_arr(temp);
        int position_substring = utility::position_subtext(pattern_regex, temp_string_full);
        
        // std::cout << "begin line segmento_a -> " << temp_string_patch << std::endl;
        if(position_substring != -1) {
            std::string cut_full_result = temp_string_full.substr(position_substring, temp_string_full.size());
            this->m_values_on_item_segments[temp_string_patch] = cut_full_result;
            this->m_items_on_segments["segmento_a"].push_back(temp_string_patch);
            // std::cout << "cut full result -> " << cut_full_result << std::endl;
        }
    }

    fseek(p_file, SEEK_SET, SEEK_SET);
}

void read_from_config::lineSegmentoB(FILE* p_file, t_msi& lhs_map)
{
    char temp[BUFFER_SIZE_LINE];
    int init_line = lhs_map["segmento_b"] + 1;
    std::string temp_string_patch;
    std::string temp_string_full;
    std::string pattern_regex = "\\[[0-9]{1,4}.[0-9]{1,4}\\]";
    utility::jump_lines(p_file, init_line);
    
    while(fgets(temp, BUFFER_SIZE_LINE, p_file))
    {
        temp_string_patch = utility::convert_to_string(temp);
        temp_string_full = utility::convert_to_string_by_arr(temp);
        int position_substring = utility::position_subtext(pattern_regex, temp_string_full);
        
        // std::cout << "begin line segmento_b -> " << temp_string_patch << std::endl;
        if(position_substring != -1) {
            std::string cut_full_result = temp_string_full.substr(position_substring, temp_string_full.size());
            this->m_values_on_item_segments[temp_string_patch] = cut_full_result;
            this->m_items_on_segments["segmento_b"].push_back(temp_string_patch);
            // std::cout << "cut full result -> " << cut_full_result << std::endl;
        } else {
            //TODO: doesn't working, need to fix.
            const std::string error("FILE CONFIG CORROMPID IN LINE\n" + temp_string_full);
            throw std::runtime_error(error).what();
        }
    }

    fseek(p_file, SEEK_SET, SEEK_SET);
}

void read_from_config::_fill_values()
{
    FILE* file = fopen(this->m_path, "rb");
    t_msi linesFound = findLines(file);

    if(file == NULL)
        perror("Can't to open file");
    
    // utility::print_map<t_msi>(linesFound);
    this->lineHeader(file, linesFound);
    this->lineSegmentoA(file, linesFound);
    this->lineSegmentoB(file, linesFound);
    // utility::print_map<std::map<std::string,std::string>, std::string, std::string>(this->m_values_on_item_segments);

    bool sucess = false;
    if(sucess = setMembers<std::string>("__ID", this->m_values_on_item_segments, this->m_id))
        // std::cout << "sucess set __ID with = " << this->m_id << std::endl;
    if(sucess = setMembers<std::string>("__AGENCIA", this->m_values_on_item_segments, this->m_agencia))
        // std::cout << "sucess set __AGENCIA with = " << this->m_agencia << std::endl;
    if(sucess = setMembers<std::string>("__CONTA", this->m_values_on_item_segments, this->m_conta))
        // std::cout << "sucess set __CONTA with = " << this->m_conta << std::endl;
    if(sucess = setMembers<std::string>("__HEADER", this->m_values_on_item_segments, this->m_header))
        // std::cout << "sucess set __HEADER with = " << this->m_header << std::endl;
    if(sucess = setMembers<std::string>("__DIGITO_VERIFICADOR", this->m_values_on_item_segments, this->m_div))
        // std::cout << "sucess set __DIGITO_VERIFICADOR with = " << this->m_div << std::endl;
    if(sucess = setMembers<std::string>("__NOME_FAVORECIDO", this->m_values_on_item_segments, this->m_nome_favorecido))
        // std::cout << "sucess set __NOME_FAVORECIDO with = " << this->m_nome_favorecido << std::endl;

    fclose(file);
}