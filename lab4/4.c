#include <stdio.h>
#include <stdlib.h>

int strMatch(char str[], char pattern[], int m, int n)
{
    int count = 0;
    for (int i = 0; i <= m - n; i++)
    {
        int j = 0;
        while (j < n && str[i + j] == pattern[j])
        {
            count++;
            j++;
        }
        if (j == n)
            return count;  // Full match
        count++;
    }
    return count;  // Pattern not found
}

void main()
{
    FILE *fp = fopen("str.txt", "w");
    if (!fp)
    {
        printf("Error opening file.\n");
        return;
    }

    int m = 1000;
    char str[1000];

    // Fill string with 'a'
    for (int i = 0; i < m; i++)
        str[i] = 'a';

    for (int i = 100; i <= m; i += 100)
    {
        // Create pattern of size i
        char pattern[i];
        for (int j = 0; j < i; j++)
            pattern[j] = 'a';

        fprintf(fp, "%d\t", i);

        // Best Case: complete match
        int best = strMatch(str, pattern, m, i);
        fprintf(fp, "%d\t", best);

        // Worst Case: last character doesn't match
        pattern[i - 1] = 'b';
        int worst = strMatch(str, pattern, m, i);
        fprintf(fp, "%d\t", worst);
        for(int j=0;j<i;j++)
            pattern[j] = (char)(97 + rand() % 2);
        
        int avg=strMatch(str, pattern, m, i);
        fprintf(fp, "%d\n", avg);

    }

    fclose(fp);
}
