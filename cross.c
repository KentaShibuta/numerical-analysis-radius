#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double solv_cross(double x_1, double y_1, double x_2, double y_2)
{
  //vector_1 coross vector_2
  //     (vector_1 cross vector_2)
  //        ^
  //        |
  //        |
  //        |
  //        ----------> vector_2
  //       /
  //      /
  //     /
  //   vector_1
  //
  //
  double cross_v1_v2 = (x_1 * y_2) - (x_2 * y_1);
  return cross_v1_v2;
}

double solv_norm(double x, double y)
{
  return sqrt(x*x + y*y);
}

double solv_sin(double cross, double norm_1, double norm_2)
{
  return (cross / (norm_1 * norm_2));
}	  
