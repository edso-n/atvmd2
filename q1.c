#include <stdio.h>
#include <stdlib.h>

int chama_numero(int *n1, int *n2){
    do {
        printf("Digite dois números compostos distintos (3 ou 4 dígitos) -ATENÇÃO! Cada numero N(i) deve ser produto de primos distintos-: \n\n");
        scanf("%d %d", n1, n2); 


        if ((!(*n1 >= 100 && *n1 <= 9999)) || (!(*n2 >= 100 && *n2 <= 9999))) {
            printf("ATENÇÃO! Os números devem ter 3 ou 4 dígitos!\n\n");
        }
        
    } while ((!(*n1 >= 100 && *n1 <= 9999)) || (!(*n2 >= 100 && *n2 <= 9999)));

    return 1;
}

int metodo_polard(){
    return 0;
}

int algoritmo_de_euclides(int n1, int n2){
    if(n2 == 0){        //resto 0
        return n1;
    }
    else{
        algoritmo_de_euclides(n2, n1 % n2); 
    }
}

int main(){

    int n1, n2;

    //chama_numero(&n1, &n2);


    //printf("%d %d", n1, n2);
    printf("\n\n");

    printf("%d\n\n", algoritmo_de_euclides(300, 3));

    return 0;
}