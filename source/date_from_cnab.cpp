#include <iostream>
#include <sstream>

#include "header/date_from_cnab.hpp"
#include "header/utility.hpp"


date_from_cnab::date_from_cnab(const char* path)
{
    m_file = fopen(path, "r");
    std::cout << "Date From Cnab initialized with sucess\n" << std::endl;
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