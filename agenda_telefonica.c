#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dia;
    int mes;
} Data;

typedef struct {
    char nome[41];
    char telefone[16];
    char celular[16];
    char email[41];
    Data dataAniversario;
} Contato;

struct elemento {
    Contato info;
    struct elemento* prox;
};
typedef struct elemento Elemento;

Elemento* cria_agenda();
Elemento* insere_contato(Elemento* lista);
void lista_contatos(Elemento* lista);
Elemento* busca_contato(Elemento* lista, char* nome);
Elemento* remove_contato(Elemento* lista);
Elemento* atualiza_contato(Elemento* lista);
void libera_agenda(Elemento* lista);
void limpa_buffer();

int main() {
    Elemento* agenda = cria_agenda();
    int opcao;
    
    do {
        printf("\n=== AGENDA TELEFONICA ===\n");
        printf("1. Inserir Contato\n");
        printf("2. Listar Contatos\n");
        printf("3. Buscar Contato\n");
        printf("4. Editar Contato\n");
        printf("5. Remover Contato\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpa_buffer();
        
        switch(opcao) {
            case 1:
                agenda = insere_contato(agenda);
                break;
            case 2:
                lista_contatos(agenda);
                break;
            case 3:
                {
                    char nome_busca[41];
                    printf("Digite o nome para buscar: ");
                    fgets(nome_busca, 41, stdin);
                    nome_busca[strcspn(nome_busca, "\n")] = '\0'; // Remove o \n
                    
                    Elemento* encontrado = busca_contato(agenda, nome_busca);
                    if (encontrado != NULL) {
                        printf("\n=== CONTATO ENCONTRADO ===\n");
                        printf("Nome: %s\n", encontrado->info.nome);
                        printf("Telefone: %s\n", encontrado->info.telefone);
                        printf("Celular: %s\n", encontrado->info.celular);
                        printf("Email: %s\n", encontrado->info.email);
                        printf("Aniversario: %02d/%02d\n", 
                               encontrado->info.dataAniversario.dia,
                               encontrado->info.dataAniversario.mes);
                    } else {
                        printf("Contato nao encontrado!\n");
                    }
                }
                break;
            case 4:
                agenda = atualiza_contato(agenda);
                break;
            case 5:
                agenda = remove_contato(agenda);
                break;
            case 6:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
        
    } while(opcao != 6);
    
    libera_agenda(agenda);
    return 0;
}

Elemento* cria_agenda() {
    return NULL;
}

Elemento* insere_contato(Elemento* lista) {
    Elemento* novo = (Elemento*)malloc(sizeof(Elemento));
    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return lista;
    }
    
    printf("\n=== NOVO CONTATO ===\n");
    printf("Nome: ");
    fgets(novo->info.nome, 41, stdin);
    novo->info.nome[strcspn(novo->info.nome, "\n")] = '\0';
    
    printf("Telefone: ");
    fgets(novo->info.telefone, 16, stdin);
    novo->info.telefone[strcspn(novo->info.telefone, "\n")] = '\0';
    
    printf("Celular: ");
    fgets(novo->info.celular, 16, stdin);
    novo->info.celular[strcspn(novo->info.celular, "\n")] = '\0';
    
    printf("Email: ");
    fgets(novo->info.email, 41, stdin);
    novo->info.email[strcspn(novo->info.email, "\n")] = '\0';
    
    printf("Dia do aniversario: ");
    scanf("%d", &novo->info.dataAniversario.dia);
    printf("Mes do aniversario: ");
    scanf("%d", &novo->info.dataAniversario.mes);
    limpa_buffer();
    
    novo->prox = NULL;

    if (lista == NULL) {
        return novo;
    }

    Elemento* atual = lista;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    
    atual->prox = novo;
    return lista;
}

void lista_contatos(Elemento* lista) {
    if (lista == NULL) {
        printf("\nAgenda vazia!\n");
        return;
    }
    
    printf("\n=== LISTA DE CONTATOS ===\n");
    Elemento* atual = lista;
    int contador = 1;
    
    while (atual != NULL) {
        printf("\n--- Contato %d ---\n", contador++);
        printf("Nome: %s\n", atual->info.nome);
        printf("Telefone: %s\n", atual->info.telefone);
        printf("Celular: %s\n", atual->info.celular);
        printf("Email: %s\n", atual->info.email);
        printf("Aniversario: %02d/%02d\n", 
               atual->info.dataAniversario.dia,
               atual->info.dataAniversario.mes);
        atual = atual->prox;
    }
}

Elemento* busca_contato(Elemento* lista, char* nome) {
    Elemento* atual = lista;
    
    while (atual != NULL) {
        if (strcmp(atual->info.nome, nome) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    
    return NULL;
}

Elemento* remove_contato(Elemento* lista) {
    if (lista == NULL) {
        printf("Agenda vazia!\n");
        return lista;
    }
    
    char nome_remover[41];
    printf("Digite o nome do contato a ser removido: ");
    fgets(nome_remover, 41, stdin);
    nome_remover[strcspn(nome_remover, "\n")] = '\0';
    
    Elemento* anterior = NULL;
    Elemento* atual = lista;
   
    while (atual != NULL && strcmp(atual->info.nome, nome_remover) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    
    if (atual == NULL) {
        printf("Contato nao encontrado!\n");
        return lista;
    }
 
    if (anterior == NULL) {
        
        lista = atual->prox;
    } else {
        
        anterior->prox = atual->prox;
    }
    
    printf("Contato '%s' removido com sucesso!\n", atual->info.nome);
    free(atual);
    return lista;
}

Elemento* atualiza_contato(Elemento* lista) {
    if (lista == NULL) {
        printf("Agenda vazia!\n");
        return lista;
    }
    
    char nome_atualizar[41];
    printf("Digite o nome do contato a ser atualizado: ");
    fgets(nome_atualizar, 41, stdin);
    nome_atualizar[strcspn(nome_atualizar, "\n")] = '\0';
    
    Elemento* encontrado = busca_contato(lista, nome_atualizar);
    
    if (encontrado == NULL) {
        printf("Contato nao encontrado!\n");
        return lista;
    }
    
    printf("\n=== EDITANDO CONTATO: %s ===\n", encontrado->info.nome);
    printf("Novo telefone (atual: %s): ", encontrado->info.telefone);
    fgets(encontrado->info.telefone, 16, stdin);
    encontrado->info.telefone[strcspn(encontrado->info.telefone, "\n")] = '\0';
    
    printf("Novo celular (atual: %s): ", encontrado->info.celular);
    fgets(encontrado->info.celular, 16, stdin);
    encontrado->info.celular[strcspn(encontrado->info.celular, "\n")] = '\0';
    
    printf("Novo email (atual: %s): ", encontrado->info.email);
    fgets(encontrado->info.email, 41, stdin);
    encontrado->info.email[strcspn(encontrado->info.email, "\n")] = '\0';
    
    printf("Novo dia do aniversario (atual: %d): ", encontrado->info.dataAniversario.dia);
    scanf("%d", &encontrado->info.dataAniversario.dia);
    printf("Novo mes do aniversario (atual: %d): ", encontrado->info.dataAniversario.mes);
    scanf("%d", &encontrado->info.dataAniversario.mes);
    limpa_buffer();
    
    printf("Contato atualizado com sucesso!\n");
    return lista;
}

void libera_agenda(Elemento* lista) {
    Elemento* atual = lista;
    Elemento* proximo;
    
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

void limpa_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}