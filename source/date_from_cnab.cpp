#include <iostream>
#include <sstream>

#include "header/date_from_cnab.hpp"

date_from_cnab::date_from_cnab(const char* path):
    m_path(path)
{
    this->m_agencia = new char[BUFFER_SIZE_LINE];
    this->m_id = new char[BUFFER_SIZE_LINE];
    this->m_div = new char[BUFFER_SIZE_LINE];
    this->m_valor = new char[BUFFER_SIZE_LINE];
    this->m_conta = new char[BUFFER_SIZE_LINE];
    
    this->_fill_values();
}

date_from_cnab::~date_from_cnab()
{
    delete []this->m_id;
    delete []this->m_conta;
    delete []this->m_agencia;
    delete []this->m_valor;
    delete []this->m_div;
}

template <typename T>
std::string convert_to_string(T arr)
{
    std::string pointer_to_string;
    std::stringstream ss;
    
    ss << arr;
    ss >> pointer_to_string;

    return pointer_to_string;
}

/*
fgetc = get only an unique char.
fscanf = get the words with custom pattern, it stop when found new black space. 
fgets = get whole line or delimiter by number size.
fseek = move pointer for determined position of file.
ftell = storage current position of cursor present in instance object file
*/

void date_from_cnab::_fill_values()
{
    std::cout << "m_path in _fill_values == " << this->m_path << std::endl;
    FILE* file = fopen(this->m_path, "rw+");
    
    fgets(this->m_agencia, BUFFER_SIZE_LINE, file);
    const_cast<const char*>(this->m_agencia);
    
    std::cout << "\ngoing to see value in m_agencia == \n" 
              << this->m_agencia << std::endl;

    // std::cout << "*THIS-M_AGENCIA ===== " << convert_to_string<char *>(this->m_agencia) << std::endl; 
    fclose(file);
}