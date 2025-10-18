#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h> // Incluído para abs() se não for C++

// *** Funções Auxiliares de Teoria dos Números ***

// Algoritmo de Euclides para calcular o Máximo Divisor Comum (MDC)
int algoritmo_euclides(int a, int b)
{
    printf("\n--- Chamando Algoritmo de Euclides ---\n");
    int resto;
    // O algoritmo continua enquanto o divisor (b) não for zero
    while (b != 0)
    {
        resto = a % b;
        printf("  %d mod %d = %d\n", a, b, resto); // Mostra o passo da divisão
        a = b;      // O divisor antigo (b) se torna o novo dividendo (a)
        b = resto;  // O resto se torna o novo divisor (b)
    }
    // O MDC é o último valor não nulo de 'a'
    return a;
}

// Algoritmo de Fatoração de Pollard's Rho (método heurístico para encontrar um fator não trivial)
int fatorarPollardRho(int n)
{
    // x e y são os pontos da sequência. d é o MDC.
    int x = 2, y = 2, d = 1; 
    printf("\n--- Fatoracao de %d (Pollard's Rho) ---\n", n);

    // Loop principal: continua até que d > 1 (fator encontrado) ou d = n (falha provável)
    while (d == 1)
    {
        // Funções de iteração: usamos f(x) = (x^2 + 1) mod n
        // 'x' avança um passo
        x = (x * x + 1) % n;
        // 'y' avança dois passos (o 'coelho')
        y = ((y * y + 1) % n); 
        y = ((y * y + 1) % n); 
        
        // Calcula o MDC de |x-y| e n. 
        // Se d > 1, d é um fator de n.
        d = algoritmo_euclides(abs(x - y), n);
        printf("  x = %d, y = %d, mdc(|x-y|, n) = %d\n", x, y, d);
    }

    // Caso de falha (não encontrou fator, n é primo ou falha do rho)
    if (d == n)
    {
        printf("  Fator nao encontrado, ou n e primo. Tentativa falhou.\n");
        return -1;
    }
    else
    {
        // Fator encontrado com sucesso.
        printf("  Fator encontrado: %d\n", d);
        return d;
    }
}

// Algoritmo Estendido de Euclides para encontrar o Inverso Modular
int inversoModular(int a, int m) // Encontra 'x' tal que a*x ≡ 1 (mod m)
{
    // Variáveis para manter os originais e garantir que o resultado seja em (mod m)
    int orig_a = a;
    int orig_m = m;

    // Apenas para fins didáticos: mostra o MDC primeiro
    algoritmo_euclides(a, m);

    // Variáveis para os coeficientes de Bezout: x0 e x1
    // (r, x, y) inicia como (m, 1, 0) e (a, 0, 1) se olharmos a tabela
    int x0 = 0, x1 = 1; 
    int q, t;

    // Algoritmo Estendido: encontra x e y tais que a*x + m*y = mdc(a,m)
    while (m != 0)
    {
        q = a / m; // Quociente
        
        // Atualiza 'a' e 'm' (como no Euclides normal)
        t = m;
        m = a % m;
        a = t;

        // Atualiza os coeficientes x0 e x1: x_novo = x_ant - q * x_antigo_do_m
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // Se o mdc(a, m) não for 1, o inverso não existe
    if (a != 1)
    {
        printf("\n  Inverso modular nao existe (MDC != 1).\n");
        return -1; 
    }

    // x1 é o coeficiente de Bezout que multiplica 'a'.
    // Devemos garantir que o inverso seja positivo (0 < x < orig_m)
    if (x1 < 0)
        x1 += orig_m;

    printf("\n  Substituindo, o inverso de %d em mod %d e %d\n", orig_a, orig_m, x1);
    return x1;
}

// Funções de mapeamento para o Cifra
int converte_letra_em_numero(char mensagem) // Converte caractere em código numérico
{
    if (islower((unsigned char)mensagem))
        mensagem = toupper((unsigned char)mensagem);

    // ' ' (Espaço) -> 00
    if (mensagem == ' ')
        return 0; 

    // 'A' -> 11, 'B' -> 12, ..., 'Z' -> 36 (Total de 26 letras)
    if (mensagem >= 'A' && mensagem <= 'Z')
        return mensagem - 'A' + 11; 

    return -1; // Caractere não suportado
}

char converter_numero_em_letra(int codigo) // Converte código numérico em caractere
{
    if (codigo == 0)
        return ' ';
    if (codigo >= 11 && codigo <= 36)
        return (char)('A' + (codigo - 11));
    return '?'; // Código desconhecido
}

// Teste de Primalidade Simples
int primo(int num)
{ 
    if (num < 2)
        return 0; // 0 e 1 não são primos
    // Testa divisores até a raiz quadrada de num
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return 0; // Encontrou um divisor, não é primo
    }
    return 1; // É primo
}

// Implementação simples do MDC
int mdc(int a, int b)
{
    // Garante que os números sejam positivos para o algoritmo
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    // O mesmo Algoritmo de Euclides
    while (b != 0)
    {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// Exponenciação Modular Rápida (Binary Exponentiation) - Declaração
long long powmod(long long base, long long exp, long long mod);

// Calcula Phi de Euler pela fatoração (usando fatoração por tentativa simples)
int phi_por_fatoracao(int n)
{
    // Fórmula: phi(n) = n * (1 - 1/p1) * (1 - 1/p2) * ...
    int result = n;
    int temp = n; // Copia para não modificar n
    for (int p = 2; p * p <= temp; p++)
    {
        if (temp % p == 0)
        {
            // p é um fator primo
            while (temp % p == 0)
                temp /= p; // Remove todas as ocorrências de p
            // Aplica a fórmula: result = result - result/p
            result -= result / p;
        }
    }
    // Se sobrar um fator primo maior que 1
    if (temp > 1)
        result -= result / temp;
    return result;
}

// Função para aplicar os Teoremas (Fermat/Euler) ou o caso geral
long long verificacao(long long base, long long exp, int n)
{
    printf("\n--- Verificacao para M^e mod n ---\n");
    
    // CASO 1: n é primo -> Pequeno Teorema de Fermat
    if (primo(n))
    {
        long long mod_fermat = n - 1;
        // exp = q*(n-1) + r. Calculamos base^r mod n
        long long q = exp / mod_fermat;
        long long r = exp % mod_fermat;

        printf("  [FERMAT] n=%d e' primo. Reduzindo expoente mod (n-1)=%lld\n", n, mod_fermat);
        printf("  Decomposicao: e = %lld * (%lld) + %lld\n", q, mod_fermat, r);

        printf("  Calculando M^%lld mod %d...\n", r, n);
        return powmod(base, r, n);
    }

    // CASO 2: n é composto E mdc(base, n) = 1 -> Teorema de Euler
    int g = mdc((int)base, n);
    if (g == 1)
    {
        int phi = phi_por_fatoracao(n); // Calcula a função totiente de Euler
        // exp = q*phi(n) + r. Calculamos base^r mod n
        long long q = exp / phi;
        long long r = exp % phi;
        
        printf("  [EULER] mdc(M,n) = 1. Reduzindo expoente mod phi(n)=%d\n", phi);
        printf("  Decomposicao: e = %lld * (%d) + %lld (phi=%d)\n", q, phi, r, phi);
        printf("  Calculando M^%lld mod %d...\n", r, n);
        return powmod(base, r, n);
    }

    // CASO 3: Caso Geral (n composto, mdc(base, n) != 1) -> Não há redução segura de expoente
    // Embora possa haver redução sob certas condições (lambda(n)), o caso geral é calcular C^e mod n.
    int phi = phi_por_fatoracao(n); // Apenas mostra o phi(n) para comparação
    long long q = exp / phi;
    long long r = exp % phi;
    
    printf("  [DIVISAO EUCLIDIANA] mdc(M,n) = %d != 1.\n", g);
    printf("  Decomposicao (Apenas para info): e = %lld * (%d) + %lld\n", q, phi, r);
    printf("  Nao se pode reduzir via Euler. Calculando M^e mod n diretamente...\n");
    return powmod(base, exp, n); // Calcula com o expoente original
}

// Implementação da Exponenciação Modular Rápida
long long powmod(long long base, long long exp, long long mod)
{
    long long res = 1 % mod; // Inicializa o resultado (res)
    base %= mod;             // Reduz a base
    
    // Itera sobre os bits do expoente
    while (exp > 0)
    {
        // Se o bit atual for 1, multiplica no resultado
        if (exp & 1)
            res = (res * base) % mod;

        // Quadrado da base modular
        base = (base * base) % mod;
        
        // Move para o próximo bit do expoente
        exp >>= 1; 
    }
    return res;
}

// Função para testar o Teorema de Euler (para fins didáticos)
int euler(int a, int n)
{
    int g = algoritmo_euclides(a, n);
    if (g != 1)
    {
        printf("Teorema de Euler nao se aplica: mdc(%d,%d) = %d\n", a, n, g);
        return -1;
    }

    int phi = phi_por_fatoracao(n);
    long long r = powmod(a, phi, n);
    printf("Euler: %d^(%d) mod %d = %lld (Deve ser 1)\n", a, phi, n, r);
    return (int)r;
}


// *** Função Principal (Main) ***
int main()
{
    int N1, N2;
    printf("--- Simulacao do Algoritmo RSA ---\n");
    printf("1. Digite dois numeros compostos distintos N1 e N2 (produto de 2 primos distintos, 3 ou 4 digitos):\n");
    
    // Leitura e validação dos números
    if (scanf("%d %d", &N1, &N2) != 2) {
        printf("Erro na leitura.\n");
        return 1;
    }

    if ((N1 < 100 || N1 > 9999) || (N2 < 100 || N2 > 9999) || (N1 == N2))
    {
        printf("  ! Numeros invalidos. Leia as instrucoes.\n");
        return 0;
    }
    printf("  Lidos: N1=%d, N2=%d\n", N1, N2);

    printf("\n***************************************************\n");
    printf("Passo 1: Encontrar p, q e calcular n, phi(n)\n");
    printf("***************************************************\n");
    
    // Fatoração (encontra os fatores primos p e q)
    int p = fatorarPollardRho(N1);
    int q = fatorarPollardRho(N2);
    
    if (p == -1 || q == -1) {
        printf("\nFatoracao falhou para um ou ambos os numeros. Encerrando.\n");
        return 0;
    }

    printf("\n  Fatores Primos: p: %d, q: %d\n", p, q);

    // Cálculo do Módulo e da Função Totiente
    int n = p * q;
    printf("  n (p*q) = %d\n", n);

    int zn = (p - 1) * (q - 1); // phi(n)
    printf("  z(n) = phi(n) = (p-1)*(q-1) = %d\n", zn);

    printf("\n***************************************************\n");
    printf("Passo 2: Encontrar as Chaves (e e d)\n");
    printf("***************************************************\n");

    // Encontrar o expoente público 'e' (coprimo de phi(n))
    int e; 
    for (e = 2; e < zn; e++)
    {
        // Encontra o primeiro 'e' tal que mdc(e, zn) = 1
        if (algoritmo_euclides(e, zn) == 1)
        {
            break;
        }
    }
    printf("\n  Exponente publico 'e' encontrado: %d\n", e);

    // Encontrar o expoente privado 'd' (inverso modular de e mod phi(n))
    int d; 
    d = inversoModular(e, zn);
    
    if (d == -1) {
        printf("  Nao foi possivel encontrar o inverso modular 'd'. Encerrando.\n");
        return 0;
    }

    printf("\n--- Chaves Geradas ---\n");
    printf("  Chave Publica: (n = %d, e = %d)\n", n, e);
    printf("  Chave Privada: (n = %d, d = %d)\n", n, d);

    printf("\n***************************************************\n");
    printf("Passo 3: Cifragem e Decifragem (RSA)\n");
    printf("***************************************************\n");

    printf("\n2. Digite uma mensagem (apenas letras A-Z e espaco): \n");
    char mensagem[101];
    int codificado[101];
    // Leitura da linha inteira
    scanf(" %[^\n]", mensagem); 

    // *** Cifragem: C = M^e mod n ***
    printf("\n--- Cifragem: C = M^e mod n ---\n");
    
    for (int i = 0; mensagem[i] != '\0'; i++)
    {
        int code = converte_letra_em_numero(mensagem[i]);
        if (code < 0)
        {
            printf("  ! Caractere '%c' nao suportado (codigo %d), ignorando.\n", mensagem[i], mensagem[i]);
            continue;
        }

        // Aplica C = M^e mod n, usando a função que testa Fermat/Euler
        long long r = verificacao(code, e, n);
        codificado[i] = (int)r;
        printf("  Cifrado: M='%c' (%d) -> C=%lld\n", mensagem[i], code, r);
    }
    
    printf("\nMensagem cifrada (blocos numericos):\n");
    for (int i = 0; mensagem[i] != '\0'; i++)
    {
        printf("%d ", codificado[i]);
    }
    printf("\n");

    // *** Decifragem: M = C^d mod n ***
    printf("\n--- Decifragem: M = C^d mod n ---\n");
    int decodificado[101];
    char recuperada[101];
    int idx = 0;

    for (int i = 0; mensagem[i] != '\0'; i++)
    {
        // Aplica M = C^d mod n
        long long M = verificacao((long long)codificado[i], (long long)d, n);
        decodificado[i] = (int)M;
        char ch = converter_numero_em_letra(decodificado[i]);
        recuperada[i] = ch;
        
        printf("  Decifrado: C=%d -> M=%lld ('%c')\n", codificado[i], M, ch);
        idx++;
    }
    recuperada[idx] = '\0'; // Finaliza a string

    printf("\n---------------------------------------------------\n");
    printf("Mensagem Recuperada: %s\n", recuperada);
    printf("---------------------------------------------------\n");

    printf("/n/n");

    printf("Edson Pereira - 232025730\n\n");


    return 0;
}