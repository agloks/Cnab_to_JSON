#include <iostream>
#include <sstream>

#include "header/data_from_cnab.hpp"
#include "header/utility.hpp"


data_from_cnab::data_from_cnab(const char* path)
{
    m_file = fopen(path, "r");
    std::cout << "Date From Cnab initialized with sucess\n" << std::endl;
};

data_from_cnab::~data_from_cnab()
{
    fclose(m_file);
};

void data_from_cnab::fill_member(std::string& member, int& initPos, int& length)
{
    member = utility::string_from_fgetc(this->m_file, length - initPos - 1, initPos);
};

void data_from_cnab::jumpLine(const int& quanty)
{
    std::cout << "jumo line data_from... " << quanty << std::endl;
    utility::jump_lines(this->m_file, quanty);
}
