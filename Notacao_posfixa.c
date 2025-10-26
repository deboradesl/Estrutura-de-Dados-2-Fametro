#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    double itens[MAX];
    int topo;
} Pilha;

void inicializa(Pilha *p) {
    p->topo = -1;
}

int vazia(Pilha *p) {
    return (p->topo == -1);
}

int cheia(Pilha *p) {
    return (p->topo == MAX - 1);
}

void push(Pilha *p, double valor) {
    if (cheia(p)) {
        printf("Erro: pilha cheia!\n");
        exit(1);
    }
    p->itens[++(p->topo)] = valor;
}

double pop(Pilha *p) {
    if (vazia(p)) {
        printf("Erro: pilha vazia!\n");
        exit(1);
    }
    return p->itens[(p->topo)--];
}

double avaliaRPN(char *expressao) {
    Pilha p;
    inicializa(&p);
    
    char *token = strtok(expressao, " ");
    while (token != NULL) {
       
        if (isdigit(token[0]) || 
            (token[0] == '-' && isdigit(token[1]))) {
            push(&p, atof(token));
        } 
        
        else {
            double b = pop(&p);
            double a = pop(&p);
            double resultado;
            
            switch (token[0]) {
                case '+': resultado = a + b; break;
                case '-': resultado = a - b; break;
                case '*': resultado = a * b; break;
                case '/': 
                    if (b == 0) {
                        printf("Erro: divisão por zero!\n");
                        exit(1);
                    }
                    resultado = a / b; 
                    break;
                default:
                    printf("Erro: operador inválido '%s'\n", token);
                    exit(1);
            }
            push(&p, resultado);
        }
        token = strtok(NULL, " ");
    }

    return pop(&p);
}

int main() {
    char expressao[MAX];
    
    printf("Digite a expressão em notação posfixa (RPN): ");
    fgets(expressao, MAX, stdin);
    
    expressao[strcspn(expressao, "\n")] = '\0';
    
    double resultado = avaliaRPN(expressao);
    printf("Resultado = %.2f\n", resultado);
    
    return 0;
}
