//*****************************************
// last update 2019.08.20 by Kenta Shibuta
//*****************************************

/*** 使い方 ***/
// int **f = (int *)malloc2d(sizeof(int), row, col);
// free(f);
/**************/
#include <stddef.h>//20190215
#include <stdlib.h>
#include "malloc.h"

// メモリ領域が連続な2次元配列
void *malloc2d(size_t size, int row, int col)
{
    char **a, *b;
    int  t = size * col;
    int i;
    
    // インデックスと要素を一気に確保
    a = (char**)malloc((sizeof(*a) + t) * row);
     
    if (a) {
        // [インデックス, インデックス, ..., 要素, 要素, 要素, ...]
        // と整列させるため要素の開始位置をずらす
        b = (char*)(a + row);
 
        // 各行の先頭アドレスを与える
        for (i = 0; i < row; i++) {
            a[i] = b;
            b += t; // 要素のサイズ×列の長さの分だけずらす
        }
 
        return a;
    }
     
    return NULL;
}


// メモリ領域が連続な3次元配列
void *malloc3d(size_t size, int i, int j, int k)
{
    char ***a, **b, *c;
    int  t = size * k;
    int idx1, idx2;
    
    // インデックスと要素を一気に確保
    a = (char***)malloc((sizeof(*a) + sizeof(**a) * j + t * j) * i);
 
    if (a) {
        b = (char**)(a + i);
        c = (char*)(b + i * j);
 
        for (idx1 = 0; idx1 < i; idx1++) {
            a[idx1] = b;
            for (idx2 = 0; idx2 < j; idx2++) {
                b[idx2] = c;
                c += t;
            }
            b += j;
        }
 
        return a;
    }
     
    return NULL;
}

// メモリ領域が連続な4次元配列
void *malloc4d(size_t size, int i, int j, int k, int l)
{
    char ****a, ***b, **c, *d;
    int  t = size * l;
    int idx0, idx1, idx2;
    
    // インデックスと要素を一気に確保
    a = (char****)malloc((sizeof(*a) + sizeof(**a) * j + sizeof(***a) * j * k + t * j * k) * i);
    if (a) {
        b = (char***)(a + i);
        c = (char **)(b + i * j);
        d = (char  *)(c + i * j * k);
        for (idx0 = 0; idx0 < i; idx0++) {
            a[idx0] = b;
            for (idx1 = 0; idx1 < j; idx1++) {
                b[idx1] = c;
                for (idx2 = 0; idx2 < k; idx2++) {
                    c[idx2] = d;
                    d += t;
                }
                c += k;
            }
            b += j;
        }
 
        return a;
    }
    return NULL;
}

// メモリ領域が連続な5次元配列
void *malloc5d(size_t size, int i, int j, int k, int l, int m)
{
  char *****a, ****b, ***c, **d, *e;
  int t = size * m;
  int idx0, idx1, idx2, idx3;

  // インデックスと要素を一気に確保
  a = (char*****)malloc((sizeof(*a) + sizeof(**a) * j + sizeof(***a) * j * k + sizeof(****a) * j * k * l + t * j * k * l) * i);
  if(a) {
    b = (char****)(a + i);
    c = (char ***)(b + i * j);
    d = (char  **)(c + i * j * k);
    e = (char   *)(d + i * j * k * l);
    for(idx0=0; idx0<i; idx0++) {
      a[idx0] = b;
      for(idx1=0; idx1<j; idx1++) {
	b[idx1] = c;
	for(idx2=0; idx2<k; idx2++) {
	  c[idx2] = d;
	  for(idx3=0; idx3<l; idx3++) {
	    d[idx3] = e;
	    e += t;
	  }
	  d += l;
	}
	c += k;
      }
      b += j;
    }
    
    return a;
  }
  return NULL;
}


void delete_int1d(int *p)
{
  if(p != NULL) {
    free(p);
    p = NULL;
  }
}

void delete_int2d(int **p)
{
  if(p != NULL) {
    free(p);
    p = NULL;
  }
}

void delete_double1d(double *p)
{
  if(p != NULL) {
    free(p);
    p = NULL;
  }
}

void delete_double2d(double **p)
{
  if(p != NULL) {
    free(p);
    p = NULL;
  }
}

void delete_double3d(double ***p)
{
  if(p != NULL) {
    free(p);
    p = NULL;
  }
}

void delete_double4d(double ****p)
{
  if(p != NULL) {
    free(p);
    p = NULL;
  }
}

void delete_double5d(double *****p)
{
  if(p != NULL) {
    free(p);
    p = NULL;
  }
}
