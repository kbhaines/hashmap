#include <stdio.h>

int func(int n) {

    int i,j,k, r = 0;

    for (i = 1; i <= n-1; i++)
        for (j = i+1; j <=n; j++) 
            for (k = 1; k <= j; k++)
                r += 1;

    return r;
}

int predict2(int n) {
    int i, r = 0;
    int c = (n*n*n - n)/2;

    for (i=1; i < n; i++)
        r += (i*(i+1)/2);
    return c - r;
}

int predict(int n) {
    int i, r = 0;
    for (i=1; i < n; i++)
        r += ((n*(n+1)/2) - (i*(i+1)/2));
    return r;
}

int main(int argc, char **argv) {

    int n;

    for ( n = 3; n< 10; n++) {
        printf("N is %d, predict: %d, result %d\n", n, predict2(n), func(n));
    }
}
