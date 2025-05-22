// Bibliotecas necessárias para o programa
#include <stdio.h>    // Para funções de entrada/saída
#include <stdlib.h>   // Para funções de alocação de memória
#include <string.h>   // Para funções de manipulação de strings

// Estrutura que representa um nó da pilha
typedef struct no{
    float valor;          // Valor armazenado no nó
    struct no *proximo;   // Ponteiro para o próximo nó
}No;

// Estrutura para pilha de operadores
typedef struct no_op {
    char operador;
    struct no_op *proximo;
} NoOp;

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

// Função para empilhar operador
NoOp* empilhar_op(NoOp *pilha, char op) {
    NoOp *novo = malloc(sizeof(NoOp));
    if(novo) {
        novo->operador = op;
        novo->proximo = pilha;
        return novo;
    }
    return NULL;
}

// Função para desempilhar operador
NoOp* desempilhar_op(NoOp **pilha) {
    NoOp *remover = NULL;
    if(*pilha) {
        remover = *pilha;
        *pilha = remover->proximo;
    }
    return remover;
}

// Função para verificar precedência dos operadores
int precedencia(char op) {
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
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

// Função para converter expressão infixa para posfixa
void converter_para_posfixa(char *infixa, char *posfixa) {
    NoOp *pilha = NULL;
    int j = 0;
    
    for(int i = 0; infixa[i] != '\0'; i++) {
        // Se for número ou ponto decimal, copia para saída
        if((infixa[i] >= '0' && infixa[i] <= '9') || infixa[i] == '.') {
            while((infixa[i] >= '0' && infixa[i] <= '9') || infixa[i] == '.') {
                posfixa[j++] = infixa[i++];
            }
            posfixa[j++] = ' ';
            i--;
        }
        // Se for parêntese de abertura, empilha
        else if(infixa[i] == '(') {
            pilha = empilhar_op(pilha, infixa[i]);
        }
        // Se for parêntese de fechamento
        else if(infixa[i] == ')') {
            while(pilha && pilha->operador != '(') {
                posfixa[j++] = pilha->operador;
                posfixa[j++] = ' ';
                NoOp *temp = desempilhar_op(&pilha);
                free(temp);
            }
            if(pilha && pilha->operador == '(') {
                NoOp *temp = desempilhar_op(&pilha);
                free(temp);
            }
        }
        // Se for operador
        else if(infixa[i] == '+' || infixa[i] == '-' || 
                infixa[i] == '*' || infixa[i] == '/') {
            while(pilha && pilha->operador != '(' && 
                  precedencia(pilha->operador) >= precedencia(infixa[i])) {
                posfixa[j++] = pilha->operador;
                posfixa[j++] = ' ';
                NoOp *temp = desempilhar_op(&pilha);
                free(temp);
            }
            pilha = empilhar_op(pilha, infixa[i]);
        }
    }
    
    // Desempilha operadores restantes
    while(pilha) {
        if(pilha->operador != '(') {
            posfixa[j++] = pilha->operador;
            posfixa[j++] = ' ';
        }
        NoOp *temp = desempilhar_op(&pilha);
        free(temp);
    }
    
    posfixa[j] = '\0';
}

// Função principal do programa
int main() {
    int opcao;
    char exp[100];
    
    do {
        printf("\nEscolha uma opção:\n");
        printf("1 - Calcular expressão em notação polonesa\n");
        printf("2 - Converter expressão matemática para notação polonesa\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado
        
        switch(opcao) {
            case 1:
                printf("Digite a expressao em notacao polonesa (ex: 1 2 + 3 * 4 +): ");
                fgets(exp, sizeof(exp), stdin);
                exp[strcspn(exp, "\n")] = 0;
                
                float resultado = resolver_expressao(exp);
                printf("Resultado: %f\n", resultado);
                break;
                
            case 2:
                printf("Digite a expressão matemática (ex: (1 + 2) * 3 + 4): ");
                fgets(exp, sizeof(exp), stdin);
                exp[strcspn(exp, "\n")] = 0;
                
                char posfixa[100];
                converter_para_posfixa(exp, posfixa);
                printf("Expressão em notação polonesa: %s\n", posfixa);
                break;
                
            case 0:
                printf("Saindo...\n");
                break;
                
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    
    return 0;
}
