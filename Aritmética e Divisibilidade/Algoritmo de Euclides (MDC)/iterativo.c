#include <stdio.h>
#include <time.h>

int mdc_usando_mod(int a, int b)
{
    // tratando o caso em que ambos sao zero
    if (a == 0 && b == 0)
    {
        return 0;
    }

    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mdc_usando_subtracao(int a, int b)
{
    // Garante que 'a' serja sempre positivo
    if (a < 0)
    {
        a = -a;
    }

    // Garante que 'b' serja sempre positivo
    if (b < 0)
    {
        b = -b;
    }

    // tratando o caso em que ambos sao zero
    if (a == 0 && b == 0)
    {
        return 0;
    }

    while (a != b)
    {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    return a;
}

int mdc_usando_divisao_inteira(int a, int b)
{
    // tratando o caso em que ambos sao zero
    if (a == 0 && b == 0)
    {
        return 0;
    }

    int quociente, resto;
    while (b != 0)
    {
        quociente = a / b;
        resto = a - b * quociente;
        a = b;
        b = resto;
    }
    return a;
}

int mdc_stein(int a, int b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;

    // Remove fatores comuns de 2
    int shift = 0;
    while (((a | b) & 1) == 0)
    {
        a >>= 1;
        b >>= 1;
        shift++;
    }

    // Remove fatores de 2 de a
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
    int a, b;

    printf("Digite dois numeros inteiros: ");
    scanf("%d %d", &a, &b);

    clock_t start, end;
    double cpu_time_used;

    // Testando o algoritmo usando mod
    start = clock();
    int resultado_mod = mdc_usando_mod(a, b);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("MDC (modulo): %d, Tempo: %f segundos\n", resultado_mod, cpu_time_used);

    // Testando o algoritmo usando subtracao
    start = clock();
    int resultado_subtracao = mdc_usando_subtracao(a, b);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("MDC (subtracao): %d, Tempo: %f segundos\n", resultado_subtracao, cpu_time_used);

    // Testando o algoritmo usando divisao inteira
    start = clock();
    int resultado_divisao_inteira = mdc_usando_divisao_inteira(a, b);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("MDC (divisao inteira): %d, Tempo: %f segundos\n", resultado_divisao_inteira, cpu_time_used);

    // Testando o algoritmo de Stein
    start = clock();
    int resultado_stein = mdc_stein(a, b);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("MDC (Stein): %d, Tempo: %f segundos\n", resultado_stein, cpu_time_used);

    return 0;
}