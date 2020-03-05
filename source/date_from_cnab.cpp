#include <iostream>
#include <sstream>

#include "header/date_from_cnab.hpp"
#include "header/utility.hpp"


date_from_cnab::date_from_cnab(const char* path)
{
    m_file = fopen(path, "r");
    std::cout << "Date From Cnab initialized with sucess\n" << std::endl;
    // int a = 34;
    // int b = 72;
    // int c = 1;
    // int d = 4;
    
    // this->fill_member(this->m_id, a, b);
    // this->fill_member(this->m_div, c, d);

    // std::cout << "value ->m_* = " << this->m_id << std::endl;
    // std::cout << "value ->m_* = " << this->m_div << std::endl;
};

date_from_cnab::~date_from_cnab()
{
    fclose(m_file);
};

void date_from_cnab::fill_member(std::string& member, int& initPos, int& length)
{
    member = utility::string_from_fgetc(this->m_file, length - initPos - 1, initPos);
};

void date_from_cnab::jumpLine(const int& quanty)
{
    std::cout << "jumo line date_from... " << quanty << std::endl;
    utility::jump_lines(this->m_file, quanty);
}

/*
fgetc = get only an unique char.
fscanf = get the words with custom pattern, it stop when found new black space. 
fgets = get whole line or delimiter by number size.
fseek = move pointer for determined position of file. # remimber that start desire is (pos - 1);
ftell = storage current position of cursor present in instance object file
*/