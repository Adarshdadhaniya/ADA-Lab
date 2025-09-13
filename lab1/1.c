#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gcd_modulo(int, int);
int gcd_rept_sub(int, int);
int gcd_cons_intg(int, int);
int is_prime(int);
void generate_primes(int[], int*);

int main() {
    srand(time(NULL));
    int m, n;

    printf("----- BEST CASE (m = 2n) -----\n");
    for (int i = 2; i <= 100; i *= 2) {
        m = 2 * i;
        n = i;
        printf("m = %d, n = %d → Modulo: %d, ReptSub: %d, ConsIntg: %d\n",
            m, n,
            gcd_modulo(m, n),
            gcd_rept_sub(m, n),
            gcd_cons_intg(m, n)
        );
    }

    printf("\n----- AVERAGE CASE (Random m, n) -----\n");
    for (int i = 0; i < 5; i++) {
        m = rand() % 4000 + 1000;
        n = rand() % 4000 + 1;
        printf("m = %d, n = %d → Modulo: %d, ReptSub: %d, ConsIntg: %d\n",
            m, n,
            gcd_modulo(m, n),
            gcd_rept_sub(m, n),
            gcd_cons_intg(m, n)
        );
    }

    printf("\n----- WORST CASE (Random Primes from [1000–5000]) -----\n");
    int primes[1000], count = 0;
    generate_primes(primes, &count);

    for (int i = 0; i < 5; i++) {
        int idx1 = rand() % count;
        int idx2 = rand() % count;
        m = primes[idx1];
        n = primes[idx2];
        printf("m = %d, n = %d → Modulo: %d, ReptSub: %d, ConsIntg: %d\n",
            m, n,
            gcd_modulo(m, n),
            gcd_rept_sub(m, n),
            gcd_cons_intg(m, n)
        );
    }

    return 0;
}

// ----------- GCD Functions ------------

int gcd_modulo(int m, int n) {
    int rem, count = 0;
    while (n != 0) {
        count++;
        rem = m % n;
        m = n;
        n = rem;
    }
    return count;
}

int gcd_rept_sub(int m, int n) {
    if (m == 0 || n == 0) 
        return 0;

    int count = 0;
    while (m != n) {
        count++;
        if (m > n)
            m = m - n;
        else
            n = n - m;
    }
    return count;
}

int gcd_cons_intg(int m, int n) {
    if (m == 0 || n == 0) return 0;

    int min = (m < n) ? m : n;
    int count = 0;
    int gcd = 1;

    while (min != 1) {
        count++;
        if (m % min == 0 && n % min == 0) {
            gcd = min;
            break;
        }
        min--;
    }
    return count;
} 

// ----------- Prime Helpers ------------

int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

void generate_primes(int primes[], int* count) {
    *count = 0;
    for (int i = 1000; i <= 5000; i++) {
        if (is_prime(i)) {
            primes[(*count)++] = i;
        }
    }
}
