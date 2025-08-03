#include <stdio.h>
#include <time.h>

long long mdc_modulo(long long a, long long b)
{
    if (a == 0 && b == 0)
        return 0;
    while (b != 0)
    {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long mdc_subtracao(long long a, long long b)
{
    if (a < 0)
        a = -a;
    if (b < 0)
        b = -b;
    if (a == 0 && b == 0)
        return 0;
    while (a != b)
    {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    return a;
}

long long mdc_divisao(long long a, long long b)
{
    if (a == 0 && b == 0)
        return 0;
    long long quociente, resto;
    while (b != 0)
    {
        quociente = a / b;
        resto = a - b * quociente;
        a = b;
        b = resto;
    }
    return a;
}

long long mdc_stein(long long a, long long b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    int shift = 0;
    while (((a | b) & 1) == 0)
    {
        a >>= 1;
        b >>= 1;
        shift++;
    }
    while ((a & 1) == 0)
        a >>= 1;
    while (b != 0)
    {
        while ((b & 1) == 0)
            b >>= 1;
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    return a << shift;
}

int main()
{
    long long a, b;
    printf("Digite dois numeros inteiros: ");
    scanf("%lld %lld", &a, &b);

    clock_t start, end;
    double tempo;

    start = clock();
    long long r1 = mdc_modulo(a, b);
    end = clock();
    tempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("MDC (modulo): %lld | Tempo: %.6f s\n", r1, tempo);

    start = clock();
    long long r2 = mdc_subtracao(a, b);
    end = clock();
    tempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("MDC (subtracao): %lld | Tempo: %.6f s\n", r2, tempo);

    start = clock();
    long long r3 = mdc_divisao(a, b);
    end = clock();
    tempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("MDC (divisao inteira): %lld | Tempo: %.6f s\n", r3, tempo);

    start = clock();
    long long r4 = mdc_stein(a, b);
    end = clock();
    tempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("MDC (Stein): %lld | Tempo: %.6f s\n", r4, tempo);

    return 0;
}