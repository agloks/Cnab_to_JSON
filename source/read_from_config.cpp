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

char* lineHeader(FILE* p_file, int lines[])
{
    char* temp = (char*)malloc(BUFFER_SIZE_LINE);
    int init_line = lines[0];
    int end_line = lines[1];
    utility::jump_lines(p_file, lines[0]);
    
    while(init_line++ < end_line )
    {
        fgets(temp, BUFFER_SIZE_LINE, p_file);
        std::cout << "in line header -> " << *temp << std::endl;
    }
    return temp;
}


void read_from_config::_fill_values()
{
    std::cout << "m_path in _fill_values == " << this->m_path << std::endl;
    FILE* file = fopen(this->m_path, "rb+");
    t_msi linesFound = findLines(file);

    if(file == NULL)
        perror("Can't to open file");
    
    utility::print_map<t_msi>(linesFound);

    fclose(file);
}