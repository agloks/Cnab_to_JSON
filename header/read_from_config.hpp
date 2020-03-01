#ifndef READ_FROM_CNAB_HPP
#define READ_FROM_CNAB_HPP
#include<map>

typedef std::map<std::string, int> t_msi;

class read_from_config {
    public:
        read_from_config(const char* path);
        ~read_from_config();
    
        std::string m_header;
        std::string m_conta;
        std::string m_agencia;
        std::string m_id;
        std::string m_nome_favorecido;
        std::string m_valor;
        std::string m_div;
        std::map<std::string, std::string> m_items_on_segments;
        std::map<std::string, std::string> m_values_on_item_segments;
    private:
        const char* m_path;
        void _fill_values();
        void lineHeader(FILE* p_file, t_msi& lhs_map);
        void lineSegmentoA(FILE* p_file, t_msi& lhs_map);
        void lineSegmentoB(FILE* p_file, t_msi& lhs_map);
};

#endif