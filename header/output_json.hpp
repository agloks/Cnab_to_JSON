#ifndef OUTPUT_JSON_HPP
#define OUTPUT_JSON_HPP

#include <iostream>

template<typename T>
class output_json{
    public:
        output_json(const char* path);
        ~output_json();

        T* m_obj_map;
        void writeFileFields(const std::string& property, const std::string& value);
        void writeComma();
        void openCurly();
        void closeCurly();
        void erasePatchEndObject(int begin);
        void erasePatchEndJson(int begin);
    private:
        FILE* m_file;
        fpos_t m_pos_file;
};

//fwrite @text const char*, @size of element, @quanty element, @file stream
template<typename T>
output_json<T>::output_json(const char* path)
{
    this->m_file = fopen(path, "w+");
    fwrite("[", sizeof(char), 1, this->m_file);
    std::cout << "Ok, is working output_json" << std::endl;

    this->m_pos_file = ftell(this->m_file);
};

template<typename T>
output_json<T>::~output_json()
{
    this->erasePatchEndJson(5);
    fwrite("]", sizeof(char), 1, this->m_file);
    fclose(m_file);
};

template<typename T>
void output_json<T>::writeFileFields(const std::string& property, const std::string& value)
{
    std::string a = std::string("\"") + property + std::string("\":\"") + value + std::string("\"") ;
    fwrite(a.c_str(), sizeof(char), a.length(), this->m_file);
    
    this->m_pos_file = ftell(this->m_file);
};

template<typename T>
void output_json<T>::openCurly()
{
    std::string a("{");
    fwrite(a.c_str(), sizeof(char), a.length(), this->m_file);

    this->m_pos_file = ftell(this->m_file);
};

template<typename T>
void output_json<T>::closeCurly()
{
    std::string a("}");
    fwrite(a.c_str(), sizeof(char), a.length(), this->m_file);

    this->m_pos_file = ftell(this->m_file);
};

template<typename T>
void output_json<T>::writeComma()
{
    fwrite(",\n", sizeof(char), 2, this->m_file);

    this->m_pos_file = ftell(this->m_file);
};


template<typename T>
void output_json<T>::erasePatchEndObject(int begin)
{
    char buffer[2];
    sprintf(buffer, "%c", 127);
    fseek(this->m_file, this->m_pos_file - begin, SEEK_SET);
    fwrite(buffer, sizeof(char), 1, this->m_file);
    sprintf(buffer, "%c", '\"');
    fwrite(buffer, sizeof(char), 1, this->m_file);
};

template<typename T>
void output_json<T>::erasePatchEndJson(int begin)
{
    char buffer[2];
    sprintf(buffer, "%c", '\"');
    fseek(this->m_file, this->m_pos_file - begin, SEEK_SET);
    fwrite(buffer, sizeof(char), 1, this->m_file);
    sprintf(buffer, "%c", '}');
    fwrite(buffer, sizeof(char), 1, this->m_file);
};

#endif