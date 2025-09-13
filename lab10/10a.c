// Auto‑test Warshall’s Algorithm on Best & Worst Cases
#include <stdio.h>
#include <stdlib.h>

#define MAXN 1     // maximum n we’ll test
#define STEP 10      // step size for n

static int graph[MAXN+1][MAXN+1];
static int ct;


//  Increments ct each time it computes graph[i][j] = graph[i][j] || graph[k][j].
void warshall(int n) {
    ct = 0;
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
           if (graph[i][k]==1) {
                for (int j = 1; j <= n; j++) {
                    graph[i][j] = graph[i][j] || graph[k][j];
                    ct++;
                }
            }
        }
    }
}


void tester(){
    int n, i, j;
    printf("\nEnter the number of vertices:\n");
    scanf("%d", &n);
    printf("\nEnter the adjacency matrix:\n");
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &graph[i][j]);

    warshall(n);

    printf("\nTransitive closure matrix is:\n");
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
            printf("%d  ", graph[i][j]);
        printf("\n");
    }
    printf("The count for the matrix of %d vertices is %d\n",n,ct);
}

void plotter(){
    FILE *fptr = fopen("warshall.txt", "a");
    if (!fptr) {
        printf("Error opening floyd.txt\n");
        return;
    }

    // Loop over sizes n = 10, 20, …, MAXN
    for (int n = 1; n <= 10; n=n+1) {
        int best_ct, worst_ct;

        // ——— WORST CASE: graph already fully transitively closed ———
        // Fill graph so every possible reachability is already present.
        // Easiest: complete graph (except self‑loops optional).
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++){
                if(i!=j)
                    graph[i][j] = 1;
                else
                    graph[i][j]=0;
        }
                  

        warshall(n);
        best_ct = ct;

        // ——— BEST CASE: directed chain 1→2→3→…→n ———
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                graph[i][j] = 0; 
            
        for (int i = 1; i <=n; i++)
            graph[i][i+1] = 1;

        warshall(n);
        worst_ct = ct;

        // Log: n, best‑case count, worst‑case count
        fprintf(fptr, "%d\t%d\t%d\n", n, best_ct, worst_ct);
    }

    fclose(fptr);
}


void main(void) {
    // tester();
    plotter();
}
