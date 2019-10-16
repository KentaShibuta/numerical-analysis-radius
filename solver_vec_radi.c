#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cross.h"
#include "rotation.h"
#include "vector.h"
#include "complex.h"
#include "comp.h"
#include "cross.h"
#include "global_variable.h"
void solver_normalvec_radius(int num,double data[][2])
//実際は，data[][2]
{
  int i;

  //double normal_vectors[num][2];
  //double kappa[num];

  //printf("num = %d\n", num);

  int j;
  //for(j = 0; j < num; j++){
  //  printf("%f %23.15e %23.15e\n",data[j][0], data[j][0], data[j][1]);
  // }

  double a_x;
  double a_y;
  double b_x;
  double b_y;
  double c_x;
  double c_y;
  double ab_x;
  double ab_y;
  double bc_x;
  double bc_y;
  double ba_x;
  double ba_y;
  

  for(i = 0; i < num; i++){
    //境界上の節点座標値を代入
    if(i == 0){
      a_x = data[num-1][0];
      a_y = data[num-1][1];
    }else{
      a_x = data[i-1][0];
      a_y = data[i-1][1];
    }
    b_x = data[i][0];
    b_y = data[i][1];
    if(i == (num - 1)){
      c_x = data[0][0];
      c_y = data[0][1];
    }else{
      c_x = data[i+1][0];
      c_y = data[i+1][1];
    }

    //節点をつなぐベクトルの生成
    ab_x = b_x - a_x;
    ab_y = b_y - a_y;
    ba_x = a_x - b_x;
    ba_y = a_y - b_y;
    bc_x = c_x - b_x;
    bc_y = c_y - b_y;

    //点接ベクトル
    //gamma_h = 2.0 * (ab_c * bc_c)/(ab_c + bc_c)
    struct complex_ans *mul_comp;
    mul_comp = (struct complex_ans *)malloc(sizeof(struct complex_ans));
    struct complex_ans *div_comp;
    div_comp = (struct complex_ans *)malloc(sizeof(struct complex_ans));
    mul_complex(mul_comp, ab_x, ab_y, bc_x, bc_y);
    division_complex(div_comp, mul_comp->ans_real, mul_comp->ans_img, (ab_x + bc_x), (ab_y + bc_y));

    struct vector *vec;
    vec = (struct vector *)malloc(sizeof(struct vector));

    vec->x = div_comp->ans_real;
    vec->y = div_comp->ans_img;

    rotation(vec);

    //double tmp_vec_x = vec->x;
    //double tmp_vec_y = vec->y;

    //normal_vectors[i][0] = tmp_vec_x / sqrt((tmp_vec_x * tmp_vec_x) + (tmp_vec_y * tmp_vec_y));
    //normal_vectors[i][1] = tmp_vec_y / sqrt((tmp_vec_x * tmp_vec_x) + (tmp_vec_y * tmp_vec_y));

    //曲率を求める
    double cross;
    double norm_ba, norm_bc;
    double vec_add_x, vec_add_y;//ab + bc
    double norm_vec_add;
    double sin;

    cross = solv_cross(bc_x, bc_y, ba_x, ba_y);
    norm_ba = solv_norm(ba_x, ba_y);
    norm_bc = solv_norm(bc_x, bc_y);
    vec_add_x = ab_x + bc_x;
    vec_add_y = ab_y + bc_y;
    norm_vec_add = solv_norm(vec_add_x, vec_add_y);
    sin = solv_sin(cross, norm_ba, norm_bc);
    kappa[i] = (2.0 * sin)/fabs(norm_vec_add);

    free(mul_comp);
    free(div_comp);
    free(vec);

  }

  /*
  FILE *fp;
  fp = fopen( "normal.txt", "a");
  for(i = 0; i < num; i++){
      //printf("%d, %23.15e %23.15e\n", i, data[i][0], data[i][1]);
      fprintf(fp, "%23.15e %23.15e\n", normal_vectors[i][0], normal_vectors[i][1]);			
  }
  fclose(fp);

  fp = fopen( "kappa.txt", "a");
  for(i = 0; i < num; i++){
      //printf("%d, %23.15e %23.15e\n", i, data[i][0], data[i][1]);
      fprintf(fp, "%23.15e\n", kappa[i]);			
  }
  fclose(fp);
  */
}
  
