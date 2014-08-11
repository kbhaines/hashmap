#include <stdio.h>

int func(int n) {

    int i,j,k, r = 0;

    for (i = 1; i <= n; i++)
        for (j = 1; j <=i; j++) 
            for (k = j; k <= (i+j); k++)
                r += 1;

    return r;
}

int predict2(int n) {
    int i, r = 0;
    double r0, n0 = (double)n - 1;
    double c =(double)(n*n*n - n)/2;

    for (i=1; i < n; i++)
        r += (i*(i+1)/2);

    r0 = (((n0*n0*n0 / 3) + ((n0*n0) / 2) + n0 / 6)+ ( n0*(n0+1)/2)) / 2;
    printf("%f  %d ", r0, r);

    return (int)(c - r0);
}

int predict(int n) {
    return (n*(n+1)*(2*n+1))/6 + n*(n+1)/2;
}

int main(int argc, char **argv) {

    int n;

    for ( n = 3; n< 10; n++) {
        printf("N is %d, predict: %d, result %d\n", n, predict(n), func(n));
    }
}
