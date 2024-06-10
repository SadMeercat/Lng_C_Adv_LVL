#include <stdio.h>

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

unsigned long long binomial_coefficient(int N, int M) {
    if (M > N) return 0;
    if (M == 0 || M == N) return 1;
    unsigned long long numerator = factorial(N);
    unsigned long long denominator = factorial(M) * factorial(N - M);
    return numerator / denominator;
}

int main() {
    int N, M;
    printf("Введите N и M: ");
    scanf("%d %d", &N, &M);

    unsigned long long result = binomial_coefficient(N, M);
    printf("%llu\n", result);

    return 0;
}
