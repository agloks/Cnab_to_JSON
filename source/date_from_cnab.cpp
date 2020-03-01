#include <iostream>
#include <sstream>

#include "header/date_from_cnab.hpp"
#include "header/utility.hpp"

#ifndef BUFFER_SIZE_LINE
#define BUFFER_SIZE_LINE 256
#endif

date_from_cnab::date_from_cnab(const char* path)
{
    m_file = fopen(path, "rb");
    std::cout << "Date From Cnab initialized with sucess\n" << std::endl;
    utility::debug();
    
    this->m_agencia = new char[BUFFER_SIZE_LINE];
    this->m_id = new char[BUFFER_SIZE_LINE];
    this->m_div = new char[BUFFER_SIZE_LINE];
    this->m_valor = new char[BUFFER_SIZE_LINE];
    this->m_conta = new char[BUFFER_SIZE_LINE];
}

date_from_cnab::~date_from_cnab()
{
    delete []this->m_id;
    delete []this->m_conta;
    delete []this->m_agencia;
    delete []this->m_valor;
    delete []this->m_div;

    fclose(m_file);
}

bool date_from_cnab::fill_id(int& initPos, int& endPos)
{
    return false;
}

/*
fgetc = get only an unique char.
fscanf = get the words with custom pattern, it stop when found new black space. 
fgets = get whole line or delimiter by number size.
fseek = move pointer for determined position of file.
ftell = storage current position of cursor present in instance object file
*/