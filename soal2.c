#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 100

typedef struct {
    char nama[101];
    int bobot;
    int nilai;
} Item;

Item items[MAXN];
int N, W;

// best solution
int bestValue = 0;
int bestWeight = 1e9;
char bestSet[MAXN][101];
int bestCount = 0;

// helper: sort string array
int cmpstr(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
}

// compare lexicographically
int isLexSmaller(char a[][101], int na, char b[][101], int nb) {
    for (int i = 0; i < na && i < nb; i++) {
        int cmp = strcmp(a[i], b[i]);
        if (cmp != 0) return cmp < 0;
    }
    return na < nb;
}

// DFS
void dfs(int idx, int totalW, int totalV, char chosen[][101], int count) {
    if (totalW > W) return;

    // check better solution
    if (totalV > bestValue ||
        (totalV == bestValue && totalW < bestWeight) ||
        (totalV == bestValue && totalW == bestWeight &&
         isLexSmaller(chosen, count, bestSet, bestCount))) {

        bestValue = totalV;
        bestWeight = totalW;
        bestCount = count;

        for (int i = 0; i < count; i++)
            strcpy(bestSet[i], chosen[i]);
    }

    if (idx == N) return;

    // pilih item
    strcpy(chosen[count], items[idx].nama);
    dfs(idx + 1,
        totalW + items[idx].bobot,
        totalV + items[idx].nilai,
        chosen,
        count + 1);

    // tidak pilih
    dfs(idx + 1, totalW, totalV, chosen, count);
}

int main() {
    scanf("%d %d", &N, &W);

    for (int i = 0; i < N; i++) {
        scanf("%s %d %d",
              items[i].nama,
              &items[i].bobot,
              &items[i].nilai);
    }

    char chosen[MAXN][101];

    dfs(0, 0, 0, chosen, 0);

    // sort hasil akhir alfabetis
    qsort(bestSet, bestCount, sizeof(bestSet[0]), cmpstr);

    printf("MAX_VALUE %d\n", bestValue);
    for (int i = 0; i < bestCount; i++) {
        printf("ITEM %s\n", bestSet[i]);
    }

    return 0;
}
