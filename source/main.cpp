#include <iostream>

#include "header/output_json.hpp"
#include "header/utility.hpp"
#include "header/read_from_config.hpp"
#include "header/data_from_cnab.hpp"

/*
@argv[1] == path to config
@argv[2] == path to file
@argv[3] == path to output file
*/

void header_bloc(read_from_config& obj_rfc, data_from_cnab& obj_dfc, const int& lines)
{
    int initPos = 0;
    int lengthPos = 0;

    for(auto k: obj_rfc.m_all_items["header"])
    {
        for(auto members: k)
        {
            // std::cout << "hi from header_bloc" << lines << std::endl;
            std::vector<std::string> splitedValue = utility::split(k[members.first], ',');

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

void subheader_bloc(read_from_config& obj_rfc, data_from_cnab& obj_dfc, const int& lines)
{
    int initPos = 0;
    int lengthPos = 0;

    for(auto k: obj_rfc.m_all_items["subheader"])
    {
        for(auto members: k)
        {
            // std::cout << "hi from subheader_bloc" << lines << std::endl;
            std::vector<std::string> splitedValue = utility::split(k[members.first], ',');

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

void segmento_a(read_from_config& obj_rfc, data_from_cnab& obj_dfc, const int& lines)
{
    int initPos = 0;
    int lengthPos = 0;

    for(auto k: obj_rfc.m_all_items["segmento_a"])
    {
        for(auto members: k)
        {
            // std::cout << "hi from segmento_a" << lines << std::endl;
            std::vector<std::string> splitedValue = utility::split(k[members.first], ',');

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
    int linhasJumpA =  obj_rfc.m_all_items["instrucao"][0]["__BLOCO_TRANSACAO_LINHAS_A"].at(2) - '0';
    std::cout << "linhasJumpA = " << obj_rfc.m_all_items["instrucao"][0]["__BLOCO_TRANSACAO_LINHAS_A"].at(2) << std::endl;
    obj_dfc.jumpLine(linhasJumpA);
}

void segmento_b(read_from_config& obj_rfc, data_from_cnab& obj_dfc, const int& lines)
{
    int initPos = 0;
    int lengthPos = 0;

    for(auto k: obj_rfc.m_all_items["segmento_b"])
    {
        for(auto members: k)
        {
            // std::cout << "hi from segmento_b" << lines << std::endl;
            std::vector<std::string> splitedValue = utility::split(k[members.first], ',');

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
    int linhasJumpB = obj_rfc.m_all_items["instrucao"][0]["__BLOCO_TRANSACAO_LINHAS_B"].at(2) - '0';
    std::cout << "linhasJumpB = " << linhasJumpB << std::endl;
    obj_dfc.jumpLine(linhasJumpB);
}


const std::string convertBRL(const std::string& value)
{
    std::string send = value.substr(3, value.length());
    while((*send.begin()) == '0')
        send.erase(send.begin());
    return send;
}

const std::string converteNomeDoFavorecido(const std::string& value)
{
    std::string temp_send = value;

    while((*temp_send.begin()) == ' ')
        temp_send.erase(temp_send.begin());

    int pos_to_del = 0;
    if((pos_to_del = utility::position_subtext("[a-zA-Z](\\s){2,40}", temp_send)) != -1)
    {
        std::cout << temp_send.substr(0, pos_to_del - 1) << std::endl;
        temp_send.erase(pos_to_del + 1);
    }

    return temp_send;
}

int main(int argc, char* argv[])
{       
    if(argv[1] == NULL)
        throw std::runtime_error("ARGUMENT TO CONFIG NOT DEFINED");
    if(argv[2] == NULL )
        throw std::runtime_error("ARGUMENT TO CNAB NOT DEFINED");

    read_from_config rfc(argv[1]);
    data_from_cnab dfc(argv[2]);
    output_json<std::map<std::string, std::string>> outJson(argv[3]);

    utility::print_map_vector_map<std::map<std::string, std::vector<std::map<std::string, std::string>>>, std::map<std::string, std::string>>(rfc.m_all_items);
    
    int e = 1;

    header_bloc(rfc, dfc, e);
    subheader_bloc(rfc, dfc, e);

    int loop = 1;
    while(loop)
    {
        segmento_a(rfc, dfc, e);
        segmento_b(rfc, dfc, e);
        if(dfc.m_map_values["__VALOR"].substr(0, 3) != "BRL")
            loop = 0;
        if(loop) 
        {
            outJson.openCurly();
            for(auto i: dfc.m_map_values)
            {
                std::cout << i.first << " and " << i.second << std::endl;
                if(i.first == "__VALOR") {
                    std::cout << "BRL CONVERT == " << convertBRL(i.second) << std::endl;
                    i.second = convertBRL(i.second);
                }
                if(i.first == "__NOME_FAVORECIDO") {
                    i.second = converteNomeDoFavorecido(i.second);
                }
                outJson.writeFileFields(i.first, i.second);
                outJson.writeComma();
            }
            outJson.erasePatchEndObject(4);
            outJson.closeCurly();
            outJson.writeComma();
        }
    }
    
    utility::print_map<std::map<std::string, std::string>, std::string, std::string>(dfc.m_map_values);

    return 0;
}
