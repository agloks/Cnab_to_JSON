#include <iostream>
#include <sstream>

#include "header/read_from_config.hpp"
#include "header/utility.hpp"

#ifndef BUFFER_SIZE_LINE
#define BUFFER_SIZE_LINE 242
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
        if(temp_string == "$INSTRUCAO")
            linesFound[std::string("instrucao")] = line;
        if(temp_string == "$HEADER")
            linesFound[std::string("header")] = line;
        if(temp_string == "$SUBHEADER")
            linesFound[std::string("subheader")] = line;
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

void read_from_config::lineInstrucao(FILE* p_file, t_msi& lhs_map)
{
    char temp[BUFFER_SIZE_LINE];
    int init_line = lhs_map["instrucao"] + 1;
    int end_line = lhs_map["header"];
    std::string temp_string_patch;
    std::string temp_string_full;
    std::string pattern_regex = "=.";
    std::map<std::string, std::string> values_on_items;
  
    utility::jump_lines(p_file, init_line);
    
    while(init_line++ < end_line )
    {
        fgets(temp, BUFFER_SIZE_LINE, p_file);
        temp_string_patch = utility::convert_to_string(temp);
        temp_string_full = utility::convert_to_string_by_arr(temp);
        int position_substring = utility::position_subtext(pattern_regex, temp_string_full);
        
        if(position_substring != -1) {
            std::string cut_full_result = temp_string_full.substr(position_substring, temp_string_full.size());

            values_on_items[temp_string_patch] = cut_full_result;
            this->m_items_on_segments["instrucao"].push_back(temp_string_patch);
        } 
    }

    this->m_all_items["instrucao"].push_back(values_on_items);

    this->m_items_on_segments["instrucao"].clear();
    fseek(p_file, SEEK_SET, SEEK_SET);
}

void read_from_config::lineHeader(FILE* p_file, t_msi& lhs_map)
{
    char temp[BUFFER_SIZE_LINE];
    int init_line = lhs_map["header"] + 1;
    int end_line = lhs_map["subheader"];
    std::string temp_string_patch;
    std::string temp_string_full;
    std::string pattern_regex = "\\[[0-9]{1,4}.[0-9]{1,4}\\]";
    std::map<std::string, std::string> values_on_items;
  
    utility::jump_lines(p_file, init_line);
    
    while(init_line++ < end_line )
    {
        fgets(temp, BUFFER_SIZE_LINE, p_file);
        temp_string_patch = utility::convert_to_string(temp);
        temp_string_full = utility::convert_to_string_by_arr(temp);
        int position_substring = utility::position_subtext(pattern_regex, temp_string_full);
        
        if(position_substring != -1) {
            std::string cut_full_result = temp_string_full.substr(position_substring, temp_string_full.size());
            
            values_on_items[temp_string_patch] = cut_full_result;            
            this->m_items_on_segments["header"].push_back(temp_string_patch);
        }
    }

    this->m_all_items["header"].push_back(values_on_items);

    this->m_items_on_segments["header"].clear();
    fseek(p_file, SEEK_SET, SEEK_SET);
}

void read_from_config::lineSubHeader(FILE* p_file, t_msi& lhs_map)
{
    char temp[BUFFER_SIZE_LINE];
    int init_line = lhs_map["subheader"] + 1;
    int end_line = lhs_map["segmento_a"];
    std::string temp_string_patch;
    std::string temp_string_full;
    std::string pattern_regex = "\\[[0-9]{1,4}.[0-9]{1,4}\\]";
    std::map<std::string, std::string> values_on_items;
  
    utility::jump_lines(p_file, init_line);
    
    while(init_line++ < end_line )
    {
        fgets(temp, BUFFER_SIZE_LINE, p_file);
        temp_string_patch = utility::convert_to_string(temp);
        temp_string_full = utility::convert_to_string_by_arr(temp);
        int position_substring = utility::position_subtext(pattern_regex, temp_string_full);
        
        if(position_substring != -1) {
            std::string cut_full_result = temp_string_full.substr(position_substring, temp_string_full.size());
            
            values_on_items[temp_string_patch] = cut_full_result;
            this->m_items_on_segments["subheader"].push_back(temp_string_patch);
        }
    }

    this->m_all_items["subheader"].push_back(values_on_items);

    this->m_items_on_segments["subheader"].clear();
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
    std::map<std::string, std::string> values_on_items;
  
    utility::jump_lines(p_file, init_line);
    
    while(init_line++ < end_line )
    {
        fgets(temp, BUFFER_SIZE_LINE, p_file);
        temp_string_patch = utility::convert_to_string(temp);
        temp_string_full = utility::convert_to_string_by_arr(temp);
        int position_substring = utility::position_subtext(pattern_regex, temp_string_full);
        
        if(position_substring != -1) {
            std::string cut_full_result = temp_string_full.substr(position_substring, temp_string_full.size());

            values_on_items[temp_string_patch] = cut_full_result;
            this->m_items_on_segments["segmento_a"].push_back(temp_string_patch);
        }
    }

    this->m_all_items["segmento_a"].push_back(values_on_items);

    this->m_items_on_segments["segmento_a"].clear();
    fseek(p_file, SEEK_SET, SEEK_SET);
}

void read_from_config::lineSegmentoB(FILE* p_file, t_msi& lhs_map)
{
    char temp[BUFFER_SIZE_LINE];
    int init_line = lhs_map["segmento_b"] + 1;
    std::string temp_string_patch;
    std::string temp_string_full;
    std::string pattern_regex = "\\[[0-9]{1,4}.[0-9]{1,4}\\]";
    std::map<std::string, std::string> values_on_items;
  
    utility::jump_lines(p_file, init_line);
    
    while(fgets(temp, BUFFER_SIZE_LINE, p_file))
    {
        temp_string_patch = utility::convert_to_string(temp);
        temp_string_full = utility::convert_to_string_by_arr(temp);
        int position_substring = utility::position_subtext(pattern_regex, temp_string_full);
        
        if(position_substring != -1) {
            std::string cut_full_result = temp_string_full.substr(position_substring, temp_string_full.size());
            
            values_on_items[temp_string_patch] = cut_full_result;
            this->m_items_on_segments["segmento_b"].push_back(temp_string_patch);
        } else {
            //TODO: doesn't working, need to fix.
            const std::string error("FILE CONFIG CORROMPID IN LINE\n" + temp_string_full);
            throw std::runtime_error(error).what();
        }
    }
    this->m_all_items["segmento_b"].push_back(values_on_items);

    this->m_items_on_segments["segmento_b"].clear();
    fseek(p_file, SEEK_SET, SEEK_SET);
}

void read_from_config::_fill_values()
{
    FILE* file = fopen(this->m_path, "rb");
    t_msi linesFound = findLines(file);
    
    this->lineInstrucao(file, linesFound);
    this->lineHeader(file, linesFound);
    this->lineSubHeader(file, linesFound);
    this->lineSegmentoA(file, linesFound);
    this->lineSegmentoB(file, linesFound);

    // if(setMembers<std::string>("__VALUE", this->m_values_on_item_segments, this->m_value))

    fclose(file);
}