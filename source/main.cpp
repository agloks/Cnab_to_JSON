#include <iostream>

#include "header/utility.hpp"
#include "header/read_from_config.hpp"
#include "header/date_from_cnab.hpp"


/*
@argv[1] == path to config
@argv[2] == path to file
*/
int main(int argc, char* argv[])
{    
    if(argv[1] != NULL)
        read_from_config test(argv[1]);
    if(argv[2] != NULL )
        date_from_cnab myfile(argv[2]);

    utility::debug();

    return 0;
}