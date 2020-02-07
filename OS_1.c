#include <stdio.h>
#include <zconf.h>

int main(int a) {
    if (a == 82) {
        return 0;
    } else {
        printf("%d * %d = %d\n", (a - 1) % 9 + 1, (a - 1) / 9 + 1, ((a - 1) % 9 + 1) * ((a - 1) / 9 + 1));
        return main(a + 1);
    }
}
