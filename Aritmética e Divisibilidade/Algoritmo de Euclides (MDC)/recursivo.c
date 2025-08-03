#include <stdio.h>
#include <time.h>

long long mdc_mod(long long a, long long b)
{
    if (b == 0)
        return a;
    return mdc_mod(b, a % b);
}

long long mdc_sub(long long a, long long b)
{
    if (a == b)
        return a;
    if (a > b)
        return mdc_sub(a - b, b);
    return mdc_sub(a, b - a);
}

long long mdc_ext(long long a, long long b, long long *x, long long *y)
{
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = mdc_ext(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

int main()
{
    long long a, b;
    printf("=== MDC Recursivo ===\n");
    printf("Digite dois números inteiros: ");
    scanf("%lld %lld", &a, &b);

    clock_t inicio, fim;
    double tempo;

    inicio = clock();
    long long r1 = mdc_mod(a, b);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;
    printf("[1] Recursivo com %%: MDC = %lld | Tempo: %.3f ms\n", r1, tempo);

    inicio = clock();
    long long r2 = mdc_sub(a, b);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;
    printf("[2] Recursivo com subtração: MDC = %lld | Tempo: %.3f ms\n", r2, tempo);

    long long x, y;
    inicio = clock();
    long long r3 = mdc_ext(a, b, &x, &y);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;
    printf("[3] Recursivo estendido: MDC = %lld | x = %lld, y = %lld | Tempo: %.3f ms\n", r3, x, y, tempo);

    return 0;
}
