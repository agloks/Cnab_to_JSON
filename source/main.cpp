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
    if(argv[1] == NULL)
        throw std::runtime_error("ARGUMENT TO CONFIG NOT DEFINED");
    if(argv[2] == NULL )
        throw std::runtime_error("ARGUMENT TO CNAB NOT DEFINED");

    read_from_config rfc(argv[1]);
    date_from_cnab dfc(argv[2]);

    utility::print_map<std::map<std::string, std::string>, std::string, std::string>(rfc.m_values_on_item_segments);
    utility::print_map_vector<std::map<std::string, std::vector<std::string>>>(rfc.m_items_on_segments);

    return 0;
}