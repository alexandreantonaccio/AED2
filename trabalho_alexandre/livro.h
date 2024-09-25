#include "estrutura.c"

Livro* criarLivro(char* isbn, char* titulo, char* autor, char* ano);
void imprimirLivro( Livro* livro, int numLivros);
void inserirLivro( Livro** lista, char* isbn, char* titulo, char* autor, char* ano);
void buscarLivro( Livro* lista, char* chave);
void checkInLivro( Livro* lista, char* chave);
void checkOutLivro( Livro* lista, char* chave);
void impimirBiblioteca( Livro* lista);