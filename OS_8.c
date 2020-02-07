#include <stdio.h>
#include <stdlib.h>

typedef struct p {
    int *pages;
    int len;
} Data;

Data *read_file(Data *data) {
    FILE *pFile;
    pFile = fopen("page.txt", "r");
    data->pages = (int *) malloc(sizeof(int));
    data->len = 0;
    while (fscanf(pFile, "%d", (data->pages + data->len)) != EOF) {
        data->len++;
        data->pages = (int *) realloc(data->pages, sizeof(int) * (data->len + 1));
    }
    return data;
}

int main() {
    int no_of_frames, no_of_pages, frames[10], pages[30], temp[10], flag1, flag2, flag3, i, j, k, pos, max, faults = 0;

    Data *data = read_file((Data *) malloc(sizeof(Data)));

    printf("Length of frames: ");
    scanf("%d", &no_of_frames);

    no_of_pages = data->len;

    printf("Refence strings: ");
    for (int i = 0; i < data->len; ++i) {
        printf("%d ", *(data->pages + i));
        pages[i] = *(data->pages + i);
    }

    for (i = 0; i < no_of_frames; ++i) {
        frames[i] = -1;
    }

    for (i = 0; i < no_of_pages; ++i) {
        flag1 = flag2 = 0;

        for (j = 0; j < no_of_frames; ++j) {
            if (frames[j] == pages[i]) {
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            for (j = 0; j < no_of_frames; ++j) {
                if (frames[j] == -1) {
                    faults++;
                    frames[j] = pages[i];
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0) {
            flag3 = 0;

            for (j = 0; j < no_of_frames; ++j) {
                temp[j] = -1;

                for (k = i + 1; k < no_of_pages; ++k) {
                    if (frames[j] == pages[k]) {
                        temp[j] = k;
                        break;
                    }
                }
            }

            for (j = 0; j < no_of_frames; ++j) {
                if (temp[j] == -1) {
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }

            if (flag3 == 0) {
                max = temp[0];
                pos = 0;

                for (j = 1; j < no_of_frames; ++j) {
                    if (temp[j] > max) {
                        max = temp[j];
                        pos = j;
                    }
                }
            }

            frames[pos] = pages[i];
            faults++;
        }

        printf("\n");

        for (j = 0; j < no_of_frames; ++j) {
            printf("%d\t", frames[j]);
        }
    }

    printf("\n\nTotal Page Faults = %d\n", faults);

    return 0;
}