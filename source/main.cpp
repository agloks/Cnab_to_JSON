#include <iostream>

#include "header/output_json.hpp"
#include "header/utility.hpp"
#include "header/read_from_config.hpp"
#include "header/date_from_cnab.hpp"


/*
@argv[1] == path to config
@argv[2] == path to file
*/

template<typename O>
void header_bloc(read_from_config& obj_rfc, date_from_cnab& obj_dfc, const int& lines, fpos_t& posFile, O& out)
{
    int initPos = 0;
    int lengthPos = 0;
    std::stringstream sstream;
    for(auto k: obj_rfc.m_all_items["header"])
    {
        for(auto members: k)
        {
            // std::cout << "hi from header_bloc" << lines << std::endl;
            std::vector<std::string> splitedValue = utility::split(k[members.first], ',');
            for(auto x: splitedValue){
                // std::cout << "splited -> " << x << std::endl;
            }
            std::stringstream sstream;
            sstream << splitedValue[0].substr(1, splitedValue[0].size());
            sstream >> initPos;
            sstream.clear();
            sstream << splitedValue[1].substr(0, splitedValue[1].size() - 1);
            sstream >> lengthPos;
            sstream.clear();
            obj_dfc.fill_member(obj_dfc.m_map_values[members.first], initPos, lengthPos);
        }
    }
    obj_dfc.jumpLine(lines);
}

template<typename O>
void subheader_bloc(read_from_config& obj_rfc, date_from_cnab& obj_dfc, const int& lines, fpos_t& posFile, O& out)
{
    int initPos = 0;
    int lengthPos = 0;
    for(auto k: obj_rfc.m_all_items["subheader"])
    {
        for(auto members: k)
        {
            // std::cout << "hi from subheader_bloc" << lines << std::endl;
            std::vector<std::string> splitedValue = utility::split(k[members.first], ',');
            for(auto x: splitedValue){
                // std::cout << "splited -> " << x << std::endl;
            }
            std::stringstream sstream;
            sstream << splitedValue[0].substr(1, splitedValue[0].size());
            sstream >> initPos;
            sstream.clear();
            sstream << splitedValue[1].substr(0, splitedValue[1].size() - 1);
            sstream >> lengthPos;
            sstream.clear();
            obj_dfc.fill_member(obj_dfc.m_map_values[members.first], initPos, lengthPos);
        }
    }
    obj_dfc.jumpLine(lines);
}

template<typename O>
void segmento_a(read_from_config& obj_rfc, date_from_cnab& obj_dfc, const int& lines, fpos_t& posFile, O& out)
{
    int initPos = 0;
    int lengthPos = 0;
    for(auto k: obj_rfc.m_all_items["segmento_a"])
    {
        for(auto members: k)
        {
            // std::cout << "hi from segmento_a" << lines << std::endl;
            std::vector<std::string> splitedValue = utility::split(k[members.first], ',');
            for(auto x: splitedValue){
                // std::cout << "splited -> " << x << std::endl;
            }
            std::stringstream sstream;
            sstream << splitedValue[0].substr(1, splitedValue[0].size());
            sstream >> initPos;
            sstream.clear();
            sstream << splitedValue[1].substr(0, splitedValue[1].size() - 1);
            sstream >> lengthPos;
            sstream.clear();
            obj_dfc.fill_member(obj_dfc.m_map_values[members.first], initPos, lengthPos);
        }
    }
    int a = 1;
    obj_dfc.jumpLine(a);
}

template<typename O>
void segmento_b(read_from_config& obj_rfc, date_from_cnab& obj_dfc, const int& lines, fpos_t& posFile, O& out)
{
    int initPos = 0;
    int lengthPos = 0;
    for(auto k: obj_rfc.m_all_items["segmento_b"])
    {
        for(auto members: k)
        {
            // std::cout << "hi from segmento_b" << lines << std::endl;
            std::vector<std::string> splitedValue = utility::split(k[members.first], ',');
            for(auto x: splitedValue){
                // std::cout << "splited -> " << x << std::endl;
            }
            std::stringstream sstream;
            sstream << splitedValue[0].substr(1, splitedValue[0].size());
            sstream >> initPos;
            sstream.clear();
            sstream << splitedValue[1].substr(0, splitedValue[1].size() - 1);
            sstream >> lengthPos;
            sstream.clear();
            obj_dfc.fill_member(obj_dfc.m_map_values[members.first], initPos, lengthPos);
        }
    }
    int a = 1;
    obj_dfc.jumpLine(a);
}

// template <typename T, typename O>
// void transation_bloc(const T& obj, const int& lines, fpos_t& posFile, O& out)
// {

// }

int main(int argc, char* argv[])
{       
    if(argv[1] == NULL)
        throw std::runtime_error("ARGUMENT TO CONFIG NOT DEFINED");
    if(argv[2] == NULL )
        throw std::runtime_error("ARGUMENT TO CNAB NOT DEFINED");

    read_from_config rfc(argv[1]);
    date_from_cnab dfc(argv[2]);
    output_json<std::map<std::string, std::string>> outJson(argv[3]);

    // utility::print_map<std::map<std::string, std::string>, std::string, std::string>(rfc.m_values_on_item_segments);
    // utility::print_map_vector<std::map<std::string, std::vector<std::string>>>(rfc.m_items_on_segments);
    utility::print_map_vector_map<std::map<std::string, std::vector<std::map<std::string, std::string>>>, std::map<std::string, std::string>>(rfc.m_all_items);
    
    int a = 4;
    fpos_t fpos;
    int e = 1;
    header_bloc<output_json<std::map<std::string, std::string>>>(rfc, dfc, e, fpos, outJson);
    subheader_bloc<output_json<std::map<std::string, std::string>>>(rfc, dfc, e, fpos, outJson);

    int loop = 1;
    while(loop)
    {
        segmento_a<output_json<std::map<std::string, std::string>>>(rfc, dfc, e, fpos, outJson);
        segmento_b<output_json<std::map<std::string, std::string>>>(rfc, dfc, e, fpos, outJson);
        if(dfc.m_map_values["__VALOR"].substr(0, 3) != "BRL")
            loop = 0;
        if(loop) 
        {
            outJson.openCurly();
            for(auto i: dfc.m_map_values)
            {
                std::cout << i.first << "and" << i.second << std::endl;
                outJson.writeFileFields(i.first, i.second);
                outJson.writeComma();
            }
            outJson.erasePatchEndObject(4);
            outJson.closeCurly();
            outJson.writeComma();
        }
    }
    outJson.erasePatchEndJson(5);
    
    utility::print_map<std::map<std::string, std::string>, std::string, std::string>(dfc.m_map_values);

    return 0;
}