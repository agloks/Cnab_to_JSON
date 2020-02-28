#include <iostream>

#include "header/date_from_cnab.hpp"

/*
@argv[1] == path to file
*/
int main(int argc, char* argv[])
{
    date_from_cnab myfile(argv[1]);
    
    return 0;
}