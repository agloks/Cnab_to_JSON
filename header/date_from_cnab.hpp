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
    private:
        const char* m_path;
        void _fill_values();
};

#endif