#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct no{
    float valor;
    struct no *proximo;
}No;

No* empilhar(No *pilha, float num){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->valor = num;
        novo->proximo = pilha;
        return novo;
    }else{
        printf("Erro ao alocar memoria");
        return NULL;
    }
}

No* desempilhar(No **pilha){
    No *remover = NULL;
    
    if(*pilha){
        remover = *pilha;
        *pilha = remover->proximo;
    }
    else
        printf("Pilha vazia");
    return remover;
}

float operacao(int a, int b, char x){
    switch(x){
        case '+': 
            return a + b;
            break;
        case '-': 
            return a - b;
            break;
        case '*': 
            return a * b;
            break;
        case '/': 
            return a / b;
            break;
        default:
            return 0.0;
        
    }
}
float resolver_expressao(char x[]){
    char *ponteiro;
    float num;
    No *n1, *n2, *pilha = NULL;

    ponteiro = strtok(x, " ");
    while(ponteiro){
        if(ponteiro[0] == '+' || ponteiro[0] == '-' || ponteiro[0] == '*' || ponteiro[0] == '/'){
            n1 = desempilhar(&pilha);
            n2 = desempilhar(&pilha);
            num = operacao(n1->valor, n2->valor, ponteiro[0]);
            pilha = empilhar(pilha, num);
            free(n1);
            free(n2);
        }    
        else{
            num = strtol(ponteiro, NULL, 10);
            pilha = empilhar(pilha, num);

        }

        ponteiro = strtok(NULL, " ");
    }
    n1 = desempilhar(&pilha);
    num = n1->valor;
    free(n1);
    return num;
}

int main(){
    char exp[50] = 


