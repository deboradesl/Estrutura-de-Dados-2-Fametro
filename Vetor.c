#include <stdio.h>
#include <stdlib.h>

int* criarVetor(int n) {
   
    int* vetor = (int*)malloc(n * sizeof(int));
    return vetor;
}

void imprimirVetor(int* vetor, int n) {
    printf("Elementos do vetor:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void liberarVetor(int* vetor) {
    free(vetor);
}

int main() {
    int n;
    int* meuVetor;

    printf("Digite o tamanho do vetor (n): ");
    scanf("%d", &n);

    meuVetor = criarVetor(n);

    if (meuVetor == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1; // Retorna um código de erro
    }

    printf("Digite os %d elementos do vetor:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &meuVetor[i]);
    }

    imprimirVetor(meuVetor, n);

    liberarVetor(meuVetor);
    printf("Memória liberada com sucesso.\n");

    return 0; 
}
    