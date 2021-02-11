#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
 
int e1, e2;
int p, d;
int C1, C2;
FILE *out1, *out2;
 
int gcd(int a, int b)
{
    int q, r1, r2, r;
 
    if (a > b) {
        r1 = a;
        r2 = b;
    }
    else {
        r1 = b;
        r2 = a;
    }
 
    while (r2 > 0) {
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;
    }
 
    return r1;
}
 
int FastExponention(int bit, int n, int* y, int* a)
{
    if (bit == 1)
        *y = (*y * (*a)) % n;
 
    *a = (*a) * (*a) % n;
}
 
int FindT(int a, int m, int n)
{
    int r;
    int y = 1;
 
    while (m > 0)
    {
        r = m % 2;
        FastExponention(r, n, &y, &a);
        m = m / 2;
    }
 
    return y;
}
 
int PrimarityTest(int a, int i)
{
    int n = i - 1;
    int k = 0;
    int m, T;
 
    while (n % 2 == 0) {
        k++;
        n = n / 2;
    }
 
    m = n;
    T = FindT(a, m, i);
    if (T == 1 || T == i - 1)
        return 1;
 
    for (int j = 0; j < k; j++) {
        T = FindT(T, 2, i);
        if (T == 1)
            return 0;
        if (T == i - 1)
            return 1;
    }
 
    return 0;
}
 
int PrimitiveRoot(int p)
{
    int flag;
    for (int a = 2; a < p; a++)
    {
        flag = 1;
        for (int i = 1; i < p; i++) {
            if (FindT(a, i, p) == 1 && i < p - 1) {
                flag = 0;
            }
            else if (flag && FindT(a, i, p) == 1 && i == p - 1) {
                return a;
            }
        }
    }
}
 
int KeyGeneration()
{
    do {
        do
            p = rand() + 256;
        while (p % 2 == 0);
 
    } while (!PrimarityTest(2, p));
    p = 107;
 
    e1 = 2;
    do {
        d = rand() % (p - 2) + 1; // 1 <= d <= p-2
    } while (gcd(d, p) != 1);
 
    d = 67;
    e2 = FindT(e1, d, p);
}
 
int Encryption(int Plaintext)
{
    out1 = fopen("cipher1.txt", "a+");
    out2 = fopen("cipher2.txt", "a+");
 
    int r;
    do {
        r = rand() % (p - 1) + 1; // 1 < r < p
    }
    while (gcd(r, p) != 1);
 
    C1 = FindT(e1, r, p);
    C2 = FindT(e2, r, p) * Plaintext % p;
 
    fprintf(out1, "%d ", C1);
    fprintf(out2, "%d ", C2);
 
    fclose(out1);
    fclose(out2);
}
 
int Decryption(int C1, int C2)
{
    FILE* out = fopen("result.txt", "a+");
    int decipher = C2 * FindT(C1, p - 1 - d, p) % p;
    fprintf(out, "%c", decipher);
    fclose(out);
}
 
int main()
{
    FILE *out, *inp;
 
    // destroy contents of these files (from previous runs, if any)
    out = fopen("result.txt", "w+");
    fclose(out);
 
    out = fopen("cipher1.txt", "w+");
    fclose(out);
    out = fopen("cipher2.txt", "w+");
    fclose(out);
 
    KeyGeneration();
 
    inp = fopen("plain.txt", "r+");
    if (inp == NULL) {
        printf("Error opening Source File.\n");
        exit(1);
    }
 
    while (1)
    {
        char ch = getc(inp);
        if (ch == EOF)
            break;  // M < p
 
        Encryption(toascii(ch));
    }
 
    fclose(inp);
 
    FILE *inp1, *inp2;
    inp1 = fopen("cipher1.txt", "r");
    inp2 = fopen("cipher2.txt", "r");
 
    int C1, C2;
    while (1)
    {
        int ret = fscanf(inp1, "%d", &C1);
        fscanf(inp2, "%d", &C2);
        if (ret == -1)
            break;
 
        Decryption(C1, C2);
    }
 
    fclose(inp1);
    fclose(inp2);
 
    return 0;
}
