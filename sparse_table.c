#include <stdio.h>

#define max(a, b) ((a) > (b)) ? (a) : (b)

int n;
int a[280198];
int Lg[280199];
int sp_table[20][280198];

void init_sp_table() { // init sparse table

  for (int i = 0; i < n; ++i) 
    sp_table[0][i] = a[i];

  Lg[1] = 0;
  for (int i = 2; i <= n; ++i) 
    Lg[i] = Lg[i / 2] + 1;

  for (int l = 1; (1 << l) < n; ++l) {
    for (int i = 0; i + (1 << l) - 1 < n; ++i) 
      sp_table[l][i] = max(sp_table[l - 1][i], sp_table[l - 1][i + (1 << l)]);
  }
}

int query(int l, int r) { // get max in range [l..r]
  int k = Lg[r - l + 1];
  return max(sp_table[k][l], sp_table[k][r - (1 << k) + 1]);
}
int main() {
  n = 5;
  // a[] = { 1, 23, 5, 6, 7}
  a[0] = 1, a[1] = 23, a[2] = 5, a[3] = 6, a[4] = 7;
  init_sp_table();
  printf("%d\n", query(1, 3));
  printf("%d\n", query(2, 4));
  printf("%d\n", query(0, 4));
  return 0;
}
