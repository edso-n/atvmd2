#include <stdio.h>
#include <stdlib.h>


void fatores(int n, int fat[5]){
    //por se tratar de valores de 1 a 105, esses são os primos possíveis
    int primos[] = {2, 3, 5, 7, 11}; 
    int i = 0;
    int j = 0; 

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

int contador_de_divisoresprimos(int fat[5]){
    int aux = 0; // Quantidade de fatores encontrados
    int r2 = 0,r3 = 0,r5 = 0,r7 = 0,r11 = 0;
    
    printf("Fatores encontrados: ");
    
    for(int i = 0; i < 5; i++){
        if(fat[i] != 0){
            printf("%d ", fat[i]);
            aux += 1;
        }
    }
    
    printf("\nEsse número tem %d fatores primos\n\n", aux);
    
    for (int j=0; j<5; j++){
        
        if(fat[j] == 2){
            r2 += 1;
        }
        if(fat[j] == 3){
            r3 += 1;
        }
        if(fat[j] == 5){
            r5 += 1;
        }
        if(fat[j] == 7){
            r7 += 1;
        }
        if(fat[j] == 11){
            r11 += 1;
        }
        
    }
    printf("Que podem ser escritos como 2^(%d) * 3^(%d) * 5^(%d) * 7^(%d) * 11^(%d)\n\n", r2,r3,r5,r7,r11);
    
    int lista_expoentes[5] = {r2, r3, r5, r7, r11}, tal_de_n;
    for(int h=0; h<5; h++){
        lista_expoentes[h] += 1;
    }
    for(int a=0; a<5; a++){
        printf("%d ", lista_expoentes[a]);
        tal_de_n *= lista_expoentes[a];
    }
    printf("%d ", tal_de_n);
    printf("\n\n");

    return aux;
}

int soma_de_divisore(int fat[5]){
    int soma = 0;
    for(int i=0; i<5; i++){
        soma += fat[i];
    }
    printf("A soma de fatores é %d\n\n", soma);
    return soma;
}

//int tal_de_n()

int main(){
    int n;
    int lista_fatores[5] = {0};
    
    printf("Digite um inteiro N (sendo 1 <= N <= 105): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 105) {
        printf("Entrada inválida. O valor deve ser entre 1 e 105.\n");
        return 1;
    }

    printf("N: %d\n\n", n);

    // Chamei a função 'fatores' passando o array para ser preenchido
    fatores(n, lista_fatores); 
    
    // Chamei a função 'contador_de_divisores' para contar os fatores preenchidos
    int num_fatores = contador_de_divisoresprimos(lista_fatores);
    

    int somafatores = soma_de_divisore(lista_fatores);
    return 0;
}