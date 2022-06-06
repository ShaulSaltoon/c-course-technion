#include <stdio.h>
#include <stdbool.h>
#define N 10
// declaration:
// input functions:
int total_counter();
int subsequence_counter(bool digit);
void histogram(int i, int a[]);

void sequential(int n, int a[], int b[][N]);

void main_input(int a[], int b[][N], int *c, int *s_c);
// output functions:
void frequencies(int n, int a[], int t);
void sequential_print(int a[], int b[][N]);
void main_output(int a[], int b[][N], int n, int s);

int main()
{
    int a[N] = {0};
    int matrix[N][N] = {{0}};
    int total_count = 0, subsequence_count = 0;
    int *c, *s_c;
    c = &total_count;
    s_c = &subsequence_count;
    main_input(a, matrix, c, s_c);
    main_output(a, matrix, total_count, subsequence_count);
    return 1;
}
// input functions:
int total_counter()
{
    static int count = 0;
    count++;
    return count;
}
int subsequence_counter(bool digit)
{

    static int max = 0, count = 0;
    if (digit)
        count++;
    else
    {
        if (count > max)
            max = count;
        count = 0;
    }
    return max;
}
void histogram(int n, int a[])
{
    a[n]++;
}

void sequential(int j, int a[], int matrix[][N])
{

    for (int i = 0; i < N; i++)
    {
        if (a[i] == 0)
            continue;
        matrix[i][j] = matrix[i][j] + a[i];
    }
}

void main_input(int a[], int matrix[][N], int *c, int *s_c)
{
    bool temp = false;
    char n = 'a';
    printf("Enter a sequence of characters:\n");
    while (scanf("%1c", &n) != EOF)
    {
        if (n < 58 && n >= 48)
        {
            printf("%d", n - 48);
            *c = total_counter();
            temp = true;
            sequential(n - 48, a, matrix);
            histogram(n - 48, a);
        }
        *s_c = subsequence_counter(temp);
        temp = false;
    }
}
void main_output(int a[], int matrix[][N], int n, int s)
{
    printf("Number of digits: %d\n", n);
    printf("Longest digit subsequence: %d\n", s);
    printf("Frequencies: ");
    for (int i = 0; i < N; i++)
    {

        frequencies(i, a, n);
    }
    printf("\n");
    sequential_print(a, matrix);
}
void frequencies(int i, int a[], int total)
{
    printf("%.2f ", a[i] / (double)total);
}
void sequential_print(int a[], int matrix[][N])
{
    printf("Sequential:\n");

    for (int i = -1; i < N; i++)
    {
        if (i == -1)
        {
            printf(" ");
        }
        else if (a[i] == 0)
            continue;
        for (int j = -1; j < N; j++)
        {
            if (j == -1 && i != -1)
            {
                printf("%d ", i);
                continue;
            }
            if (j != -1)
            {
                if (a[j] == 0)
                    continue;
            }

            if (i == -1 && j != -1)
            {
                printf("%d ", j);
                continue;
            }
            if (i != -1 && j != -1)
            {
                printf("%d ", matrix[i][j]);
            }
        }
        printf("\n");
    }
}