#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"

/*** pai ***/
#define PI (3.1415926535897932384626433832)


void rotation(struct vector *vec)
{
  double tmp_x = vec->x;
  double tmp_y = vec->y;
  double rotate_matrix[2][2];
  rotate_matrix[0][0] = cos(-PI/2);
  rotate_matrix[0][1] = -sin(-PI/2);
  rotate_matrix[1][0] = sin(-PI/2);
  rotate_matrix[1][1] = cos(-PI/2);

  vec->x = rotate_matrix[0][0] * tmp_x + rotate_matrix[0][1] * tmp_y;
  vec->y = rotate_matrix[1][0] * tmp_x + rotate_matrix[1][1] * tmp_y;
}
