#ifndef DATE_FROM_CNAB_HPP
#define DATE_FROM_CNAB_HPP

class date_from_cnab {
    public:
        date_from_cnab(const char* path);
        ~date_from_cnab();

        char* m_id;
        char* m_conta;
        char* m_agencia;
        char* m_valor;
        char* m_div;

        bool fill_id(int& initPos, int& endPos);
        bool fill_conta(int& initPos, int& endPos);
        bool fill_agencia(int& initPos, int& endPos);
        bool fill_valor(int& initPos, int& endPos);
        bool fill_div(int& initPos, int& endPos);
    private:
        FILE* m_file;
};

#endif