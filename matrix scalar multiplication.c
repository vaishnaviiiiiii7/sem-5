#include <stdio.h>
#include <limits.h>

void print_optimal_parenthesization(int s[][100], int i, int j) {
if (i == j) {
printf("A%d", i);
} else {
printf("(");
print_optimal_parenthesization(s, i, s[i][j]);
print_optimal_parenthesization(s, s[i][j] + 1, j);
printf(")");
}
}

void matrix_chain_order(int p[], int n) {
int m[100][100];
int s[100][100];

for (int i = 1; i <= n; i++) {
m[i][i] = 0;
}

for (int L = 2; L <= n; L++) {
for (int i = 1; i <= n - L + 1; i++) {
int j = i + L - 1;
m[i][j] = INT_MAX;

for (int k = i; k <= j - 1; k++) {
int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
if (q < m[i][j]) {
m[i][j] = q;
s[i][j] = k;
}
}
}
}

printf("M Table:\n");
for (int i = 1; i <= n; i++) {
for (int j = 1; j <= n; j++) {
printf("%d ", m[i][j]);
}
printf("\n");
}

printf("\nS Table:\n");
for (int i = 1; i <= n; i++) {
for (int j = 1; j <= n; j++) {
printf("%d ", s[i][j]);
}
printf("\n");
}

printf("\nOptimal parenthesization: ");
print_optimal_parenthesization(s, 1, n);
printf("\n");
printf("The optimal ordering of the given matrices requires %d scalar multiplications.\n", m[1][n]);
}

int main() {
int n;
printf("Enter the number of matrices: ");
scanf("%d", &n);

int p[n + 1];
printf("Enter dimensions of matrices (e.g., A1 A2 A3): ");
for (int i = 0; i <= n; i++) {
scanf("%d", &p[i]);
}

matrix_chain_order(p, n);

return 0;
}
