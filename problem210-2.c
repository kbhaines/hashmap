#include <stdio.h>

int func(int n) {

    int i,j,k, r = 0;

    for (i = 1; i <= n; i++)
        for (j = 1; j <=i; j++) 
            for (k = j; k <= (i+j); k++)
                r += 1;

    return r;
}

int func3(int n) {
    int i,j,k,l;
    int r = 0;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= i; j++)
            for (k = j; k <= (i+j); k++)
                for (l = 1; l <= (i+j-k); l++)
                    r+=1;

    return r;
}

int func4(int n) {
    int i,j,k;
    int r = 0;

    for (i = 1; i <= n; i++)
        for (j = i+1; j <= n; j++)
            for (k = i+j-1; k <= n; k++)
                r+=1;

    return r;
}

int predict3(int n) {
    long p1 = (n*(n+1)/2);
    long r;
    r = p1*p1 + (n*(n+1)*(2*n+1)) / 6;
    return (int) (r/2);
}

int predict(int n) {
    return (n*(n+1)*(2*n+1))/6 + n*(n+1)/2;
}

int main(int argc, char **argv) {

    int n;
    for ( n = 3; n<= 20; n++) {
        printf("N is %d, predict: %d, result %d\n", n, predict3(n), func4(n));
    }
}
