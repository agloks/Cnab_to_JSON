#ifndef DATE_FROM_CNAB_HPP
#define DATE_FROM_CNAB_HPP

class date_from_cnab {
    public:
        date_from_cnab(const char* path);
        ~date_from_cnab();

        std::string m_id;
        std::string m_conta;
        std::string m_agencia;
        std::string m_valor;
        std::string m_div;

        void fill_member(std::string& member, int& initPos, int& endPos);
    private:
        FILE* m_file;
};

#endif