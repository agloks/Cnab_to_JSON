#ifndef READ_FROM_CNAB_HPP
#define READ_FROM_CNAB_HPP
#include<map>
#include<vector>

typedef std::map<std::string, int> t_msi;

class read_from_config {
    public:
        read_from_config(const char* path);
        ~read_from_config();
    
        std::string m_value;
        
        std::map<std::string, std::vector<std::map<std::string, std::string>>> m_all_items;
        std::map<std::string, std::vector<std::string>> m_items_on_segments;
    private:
        const char* m_path;
        void _fill_values();
        void lineInstrucao(FILE* p_file, t_msi& lhs_map);
        void lineHeader(FILE* p_file, t_msi& lhs_map);
        void lineSegmentoA(FILE* p_file, t_msi& lhs_map);
        void lineSegmentoB(FILE* p_file, t_msi& lhs_map);
        void lineSubHeader(FILE* p_file, t_msi& lhs_map);
};

#endif