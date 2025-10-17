#include <stdio.h>
#include <stdlib.h>

// Definição da constante para o limite de anos
#define LIMITE_ANO 50

// Função do algoritmo de Euclides para Máximo Divisor Comum (MDC)
int mdc(int a, int b) {
    while(b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Função para calcular o Mínimo Múltiplo Comum (MMC) de dois números
int mmc(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    // A divisão (a / mdc(a, b)) * b evita overflow se a e b forem grandes, 
    // mas no nosso caso (Ciclos <= 20) é uma questão de boa prática.
    return (a / mdc(a, b)) * b;
}

// Função para calcular o MMC de uma lista de ciclos
int mmc_lista(int *ciclos, int n) {
    if (n <= 0) {
        return 0;
    }

    // Inicializa o resultado com o primeiro ciclo
    int resultado_mmc = ciclos[0];
    
    printf("Iniciando cálculo do MMC. Resultado parcial inicial: %d\n", resultado_mmc);
    
    for(int i = 1; i < n; i++) {
        int proximo_ciclo = ciclos[i];
        
        // Calcula o MMC parcial
        int novo_mmc = mmc(resultado_mmc, proximo_ciclo);
        
        printf("  - MMC(%d, %d) = %d\n", resultado_mmc, proximo_ciclo, novo_mmc);
        
        resultado_mmc = novo_mmc;

        // Otimização e checagem do limite: se o MMC parcial exceder o limite, podemos parar
        if (resultado_mmc > LIMITE_ANO) {
            printf("  - MMC parcial %d excedeu o limite de %d. Parando o cálculo.\n", resultado_mmc, LIMITE_ANO);
            return resultado_mmc; 
        }
    }
    
    return resultado_mmc;
}

int numero_de_chaves() {
    int n;
    printf("Digite um inteiro N (1 <= N <= 10): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 10) {
        fprintf(stderr, "Erro: O número de chaves (N) deve ser entre 1 e 10.\n");
        exit(1);
    }
    printf("N (número de chaves) vale: %d \n", n);
    return n;
}

void ciclos_de_ativa(int *ciclos, int n) { 
    printf("Digite os %d ciclos de ativação (2 <= Ci <= 20): ", n);
    
    for(int i = 0; i < n; i++) {
        if (scanf("%d", &ciclos[i]) != 1 || ciclos[i] < 2 || ciclos[i] > 20) {
            fprintf(stderr, "Erro: Ciclo C%d inválido. Deve ser entre 2 e 20.\n", i + 1);
            exit(1);
        }
    }
    
    printf("Ciclos digitados: ");
    for(int p = 0; p < n; p++) {
        printf("%d ", ciclos[p]);
    }
    printf("\n");
}

int main(){
    int n;
    int ciclos[10]; 
    
    // Leitura do número de chaves (N)
    n = numero_de_chaves();
    
    // Leitura dos ciclos (C1, C2, ..., CN)
    ciclos_de_ativa(ciclos, n);
    
    printf("\n--- Resolução do Problema ---\n");
    
    // 1. Calcular o Mínimo Múltiplo Comum (MMC) de todos os ciclos
    int primeiro_ano_sincronizado = mmc_lista(ciclos, n);
    
    printf("MMC final calculado: %d\n", primeiro_ano_sincronizado);
    
    // 2. Verificar o limite de 50 anos
    printf("Verificando se o MMC é <= %d\n", LIMITE_ANO);
    
    if (primeiro_ano_sincronizado > LIMITE_ANO) {
        // 3. Caso não exista ano válido dentro do limite
        printf("\nRESULTADO FINAL: Nao e possivel\n");
    } else {
        // 3. Caso exista, exibir o primeiro ano sincronizado
        printf("\nRESULTADO FINAL: %d\n", primeiro_ano_sincronizado);
    }
    
    return 0;
}