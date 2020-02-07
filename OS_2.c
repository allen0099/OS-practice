#include <stdio.h>
#include <zconf.h>

int main() {
    int a[3][3];
    int b[2];
    int max = -INT_MAX;
    printf("輸入 3 x 3 矩陣：");
    for (int i = 0; i <= 8; i++) {
        scanf("%d", &a[i / 3][i % 3]);
        if (a[i / 3][i % 3] > max) {
            max = a[i / 3][i % 3];
            b[0] = i / 3 + 1;
            b[1] = i % 3 + 1;
        }
    }
    printf("矩陣為：\n");

    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; ++j) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    printf("矩陣的最大值：%d 在 第 %d 列第 %d 行", max, b[0], b[1]);
    return 0;
}
//0 19 2 3 4 5 6 10 2
// 1 42 6 171 3 4 636 1 3