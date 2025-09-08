// Auto‑test Warshall’s Algorithm on Best & Worst Cases
#include <stdio.h>
#include <stdlib.h>

#define MAXN 100     // maximum n we’ll test
#define STEP 10      // step size for n

static int graph[MAXN+1][MAXN+1];
static int ct;

// The core Warshall’s transitive‑closure loop.
//  Increments ct each time it computes graph[i][j] = graph[i][j] || graph[k][j].
void warshall(int n) {
    ct = 0;
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
           
            if (graph[i][k]) {
                for (int j = 1; j <= n; j++) {
                    // this is one “update check”
                    graph[i][j] = graph[i][j] && graph[k][j];
                    ct++;
                }
            }
        }
    }
}

int main(void) {
    FILE *fptr = fopen("warshall.dat", "a");
    if (!fptr) {
        perror("warshall.dat");
        return 1;
    }

    // Loop over sizes n = 10, 20, …, MAXN
    for (int n = STEP; n <= MAXN; n += STEP) {
        int best_ct, worst_ct;

        // ——— BEST CASE: graph already fully transitively closed ———
        // Fill graph so every possible reachability is already present.
        // Easiest: complete graph (except self‑loops optional).
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                graph[i][j] = 1;  

        warshall(n);
        best_ct = ct;

        // ——— WORST CASE: directed chain 1→2→3→…→n ———
        // Only graph[i][i+1] = 1, all else 0.
        // for (int i = 1; i <= n; i++)
        //     for (int j = 1; j <= n; j++)
        //         graph[i][j] = 0;
        // for (int i = 1; i < n; i++)
        //     graph[i][i+1] = 1;
          for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                graph[i][j] = 0; 
        warshall(n);
        worst_ct = ct;

        // Log: n, best‑case count, worst‑case count
        fprintf(fptr, "%d\t%d\t%d\n", n, best_ct, worst_ct);
    }

    fclose(fptr);
    return 0;
}
