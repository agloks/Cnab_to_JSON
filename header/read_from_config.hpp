#ifndef READ_FROM_CNAB_HPP
#define READ_FROM_CNAB_HPP

class read_from_config {
    public:
        read_from_config(const char* path);
        ~read_from_config();
    
        char* m_header;
        char* m_conta;
        char* m_agencia;
        char* m_id;
        char* m_nome_favorecido;
        char* m_valor;
        char* m_div;
    private:
        const char* m_path;
        void _fill_values();
};

#endif