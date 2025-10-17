#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Função para encontrar os fatores primos
void fatores(int n, int fat[5]){
    // Por se tratar de valores de 1 a 105, esses são os primos possíveis (até 11)
    int primos[] = {2, 3, 5, 7, 11}; 
    int i = 0; // Índice para primos[]
    int j = 0; // Índice para fat[]

    // A fatoração só funciona corretamente se n <= 105.
    while(n != 1 && i < 5){ 
        if(n % primos[i] == 0){
            n = n / primos[i];
            if (j < 5) { 
                fat[j] = primos[i];
                j++;
            }
        }
        else{
            i++; 
        }
    }
}

// Função que calcula o número de divisores (tal(N)) a partir dos fatores
int calcula_tal_n(int fat[5]){
    int aux = 0; // Contador de fatores (para o print)
    // Contadores para os expoentes (r_primo = alfa)
    int r2 = 0,r3 = 0,r5 = 0,r7 = 0,r11 = 0;
    
    // --- PARTE 1: Exibição e contagem dos fatores ---
    printf("Fatores encontrados: ");
    for(int i = 0; i < 5; i++){
        if(fat[i] != 0){
            printf("%d ", fat[i]);
            aux += 1;
        }
    }
    printf("\nEsse número tem %d fatores primos (contando repetições)\n\n", aux);
    
    // --- PARTE 2: Contagem dos expoentes (alfa) ---
    for (int j=0; j<5; j++){
        if(fat[j] == 2){ r2 += 1; }
        if(fat[j] == 3){ r3 += 1; }
        if(fat[j] == 5){ r5 += 1; }
        if(fat[j] == 7){ r7 += 1; }
        if(fat[j] == 11){ r11 += 1; }
    }
    printf("Fatoração: 2^(%d) * 3^(%d) * 5^(%d) * 7^(%d) * 11^(%d)\n\n", r2,r3,r5,r7,r11);
    
    // --- PARTE 3: Aplicação da fórmula tal(N) = (alfa1+1) * (alfa2+1) * ... ---
    int lista_expoentes[5] = {r2, r3, r5, r7, r11};
    int total_de_divisores = 1; 
    
    printf("Expoentes + 1: ");
    for(int h=0; h<5; h++){
        lista_expoentes[h] += 1; // (alfa + 1)
        printf("%d ", lista_expoentes[h]);
    }
    
    // Multiplica todos os (alfa + 1)
    for(int a=0; a<5; a++){
        total_de_divisores *= lista_expoentes[a];
    }
    
    printf("\n\nO número total de divisores (tal(N)) é: %d\n\n", total_de_divisores);

    return total_de_divisores; // Retorna tal(N)
}

// Função auxiliar para calcular a potência (p^a)
// Mantida como long long internamente para evitar overflow no cálculo
long long power(int base, int exp) {
    long long res = 1;
    for (int i = 0; i < exp; i++) {
        res *= base;
    }
    return res;
}

// Função para calcular a soma dos divisores (sigma(N)) usando a fórmula
int soma_de_divisores_formula(int n) {
    if (n <= 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    // Usamos int para o resultado, pois para N <= 105, sigma(N) caberá em int.
    int resultado_sigma = 1; 
    int temp_n = n;
    int p; 
    int alpha; 

    // O restante do código usa a mesma lógica de fatoração e aplicação da fórmula:
    // sigma = PRODUTÓRIO de (p^(alpha+1) - 1) / (p - 1)
    
    p = 2;
    alpha = 0;
    while (temp_n % p == 0) {
        alpha++;
        temp_n /= p;
    }
    if (alpha > 0) {
        long long termo = (power(p, alpha + 1) - 1) / (p - 1);
        resultado_sigma *= termo;
    }

    for (p = 3; p * p <= temp_n; p = p + 2) {
        alpha = 0;
        while (temp_n % p == 0) {
            alpha++;
            temp_n /= p;
        }
        if (alpha > 0) {
            long long termo = (power(p, alpha + 1) - 1) / (p - 1);
            resultado_sigma *= termo;
        }
    }

    if (temp_n > 1) {
        p = temp_n;
        alpha = 1; 
        
        long long termo = (power(p, alpha + 1) - 1) / (p - 1);
        resultado_sigma *= termo;
    }
    
    printf("O resultado da função sigma(%d) é %d\n\n", n, resultado_sigma);
    return resultado_sigma;
}


void razao_eficiencia(int funcaosigma, int funcaotal){
    // É importante fazer a conversão para float antes da divisão para obter o resultado correto
    float resultado = (float)funcaosigma / funcaotal;
    printf("A razão de eficiência (Sigma(N) / Tal(N)) é de: %.2f\n", resultado);
}

int main(){
    int n, sigma, tal;
    // O array é inicializado com 0s.
    int lista_fatores[5] = {0}; 
    
    printf("Digite um inteiro N (sendo 1 <= N <= 105): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 105) {
        printf("Entrada inválida. O valor deve ser entre 1 e 105.\n");
        return 1;
    }

    printf("\nN: %d\n\n", n);

    // 1. Encontra os fatores e preenche a lista_fatores
    fatores(n, lista_fatores); 
    
    // 2. Calcula tal(N) a partir da lista de fatores
    tal = calcula_tal_n(lista_fatores); 

    // 3. Calcula sigma(N)
    sigma = soma_de_divisores_formula(n);
    
    // 4. Calcula a razão
    razao_eficiencia(sigma, tal);

    printf("/n/n");
    
    return 0;
}