#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "comp.h"

void division_complex(struct complex_ans *ans, double real_1, double img_1, double real_2, double img_2)
{
  // (real_1 + j img_1) / (real_2 + j img_2)
  double bunbo = (real_2 * real_2) + (img_2 * img_2);
  double bunsi_real = (real_1 * real_2) + (img_1 * img_2);
  double bunsi_img = (-1.0 * real_1 * img_2) + (img_1 * real_2);
  // ans = (bunsi_real / bunbo) + j (buisi_img / bunbo)
  ans->ans_real = bunsi_real / bunbo;
  ans->ans_img = bunsi_img / bunbo;
}

void mul_complex(struct complex_ans *ans, double real_1, double img_1, double real_2, double img_2)
{
  ans->ans_real = (real_1 * real_2) - (img_1 * img_2);
  ans->ans_img = (real_1 * img_2) + (img_1 * real_2);
}