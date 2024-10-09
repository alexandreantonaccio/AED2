typedef struct dicio t_dicio;
t_dicio* criar_dicio();
void inserir_dicio(t_dicio* d,int chave,void* valor);
void* consulta_dicio(t_dicio* d , int chave);
void* remover_dicio(t_dicio* d, int chave);
void destroi_dicio(t_dicio* d);