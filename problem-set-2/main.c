#include <stdio.h>

int iter;
void rec(int val);
int main() {
    printf("Hello, World!\n");

    iter = 0;
    rec(27);

    printf("%d", iter);

    return 0;
}

void rec(int val) {
    if(val  > 1) {
        iter++;
        rec(val/3);
        rec(val/3);
    }
}