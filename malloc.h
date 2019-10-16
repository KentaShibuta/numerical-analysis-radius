#ifndef _MALLOC_H_
#define _MALLOC_H_

// メモリ領域が連続な2次元配列
void *malloc2d(size_t size, int row, int col);

// メモリ領域が連続な3次元配列
void *malloc3d(size_t size, int i, int j, int k);

// メモリ領域が連続な4次元配列
void *malloc4d(size_t size, int i, int j, int k, int l);

// メモリ領域が連続な5次元配列
void *malloc5d(size_t size, int i, int j, int k, int l, int m);

// 領域の開放
void delete_int1d(int *p);
void delete_int2d(int **p);
void delete_double1d(double *p);
void delete_double2d(double **p);
void delete_double3d(double ***p);
void delete_double4d(double ****p);
void delete_double5d(double *****p);

#endif  // _MALLOC_H_
