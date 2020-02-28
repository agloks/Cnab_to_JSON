#include <iostream>

#include "header/date_from_cnab.hpp"
#include "header/read_from_config.hpp"

/*
@argv[1] == path to file
*/
int main(int argc, char* argv[])
{
    // date_from_cnab myfile(argv[1]);
    
    if(argv[2] != NULL)
        read_from_config test(argv[2]);

    return 0;
}