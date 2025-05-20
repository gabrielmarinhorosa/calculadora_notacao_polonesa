// Bibliotecas necessárias para o programa
#include <stdio.h>    // Para funções de entrada/saída
#include <stdlib.h>   // Para funções de alocação de memória
#include <string.h>   // Para funções de manipulação de strings

// Estrutura que representa um nó da pilha
typedef struct no{
    float valor;          // Valor armazenado no nó
    struct no *proximo;   // Ponteiro para o próximo nó
}No;

// Função para adicionar um elemento no topo da pilha
No* empilhar(No *pilha, float num){
    No *novo = malloc(sizeof(No));    // Aloca memória para novo nó
    if(novo){
        novo->valor = num;            // Atribui o valor ao nó
        novo->proximo = pilha;        // Conecta com a pilha existente
        return novo;
    }else{
        printf("Erro ao alocar memoria");
        return NULL;
    }
}

// Função para remover o elemento do topo da pilha
No* desempilhar(No **pilha){
    No *remover = NULL;
    
    if(*pilha){
        remover = *pilha;             // Guarda referência do nó a remover
        *pilha = remover->proximo;    // Atualiza o topo da pilha
    }
    else
        printf("Pilha vazia");
    return remover;
}

// Função que realiza as operações matemáticas
float operacao(int a, int b, char x){
    switch(x){
        case '+': 
            return a + b;    // Soma
            break;
        case '-': 
            return a - b;    // Subtração
            break;
        case '*': 
            return a * b;    // Multiplicação
            break;
        case '/': 
            return a / b;    // Divisão
            break;
        default:
            return 0.0;
    }
}

// Função que avalia a expressão em notação polonesa
float resolver_expressao(char x[]){
    char *ponteiro;
    float num;
    No *n1, *n2, *pilha = NULL;    // Inicializa pilha vazia

    // Divide a string em tokens usando espaço como separador
    ponteiro = strtok(x, " ");
    while(ponteiro){
        // Verifica se é um operador
        if(ponteiro[0] == '+' || ponteiro[0] == '-' || ponteiro[0] == '*' || ponteiro[0] == '/'){
            n1 = desempilhar(&pilha);    // Remove primeiro operando
            n2 = desempilhar(&pilha);    // Remove segundo operando
            // Realiza a operação e empilha o resultado
            num = operacao(n1->valor, n2->valor, ponteiro[0]);
            pilha = empilhar(pilha, num);
            free(n1);    // Libera memória
            free(n2);
        }    
        else{
            // Converte string para número e empilha
            num = strtol(ponteiro, NULL, 10);
            pilha = empilhar(pilha, num);
        }

        ponteiro = strtok(NULL, " ");    // Pega próximo token
    }
    // Obtém resultado final
    n1 = desempilhar(&pilha);
    num = n1->valor;
    free(n1);
    return num;
}

// Função principal do programa
int main(){
    char exp[50];    // Array para armazenar a expressão
    // Solicita entrada do usuário
    printf("Digite a expressao em notacao polonesa (ex: 1 2 + 3 * 4 +): ");
    fgets(exp, sizeof(exp), stdin);    // Lê a entrada
    exp[strcspn(exp, "\n")] = 0;       // Remove caractere de nova linha
    
    // Calcula e mostra o resultado
    float resultado = resolver_expressao(exp);
    printf("Resultado: %f\n", resultado);
    return 0;
}
