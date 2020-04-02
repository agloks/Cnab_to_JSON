#ifndef DATE_FROM_CNAB_HPP
#define DATE_FROM_CNAB_HPP
#include <map>

class date_from_cnab {
    public:
        date_from_cnab(const char* path);
        ~date_from_cnab();

        std::map<std::string, std::string> m_map_values;

        void fill_member(std::string& member, int& initPos, int& length);
        void jumpLine(const int& quanty);
    private:
        FILE* m_file;
};

#endif