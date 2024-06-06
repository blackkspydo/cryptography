/**
 * Write a program to simulate diffie-hellman key exchange algorithm
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to compute (base^exp) % mod
long long int power(long long int base, long long int exp, long long int mod)
{
    long long int result = 1;
    base = base % mod;
    while (exp > 0)
    {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

int main()
{
    long long int P, G, x, a, y, b, ka, kb;

    // Both the persons will be agreed upon the public keys P and G
    printf("Enter the value of P (a prime number): ");
    scanf("%lld", &P);
    printf("The value of P : %lld\n", P);

    printf("Enter the value of G (a primitive root for P): ");
    scanf("%lld", &G);
    printf("The value of G : %lld\n\n", G);

    // Alice will choose the private key a
    printf("Enter the value of a (a private key): ");
    scanf("%lld", &a);
    printf("The private key a for Alice : %lld\n", a);
    x = power(G, a, P); // gets the generated key
    printf("The public key x for Alice : %lld\n", x);

    // Bob will choose the private key b
    printf("\nEnter the value of b (a private key): ");
    scanf("%lld", &b);
    printf("The private key b for Bob : %lld\n", b);
    y = power(G, b, P); // gets the generated key
    printf("The public key y for Bob : %lld\n", y);

    ka = power(y, a, P); // Secret key for Alice
    kb = power(x, b, P); // Secret key for Bob

    printf("Secret key for the Alice is : %lld\n", ka);
    printf("Secret Key for the Bob is : %lld\n", kb);

    if (ka == kb)
    {
        printf("Since keys are same, the exchange is successful.\n");
    }
    else
    {
        printf("Since keys are different, the exchange is unsuccessful.\n");
    }

    return 0;
}
