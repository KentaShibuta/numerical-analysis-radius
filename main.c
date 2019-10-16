#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "comp.h"
#include "complex.h"
#include "cross.h"
#include "rotation.h"
#include "solver_vec_radi.h"
#include "global_variable.h"

int main(void){
    int nnode = 1001;
    double data[nnode][2];
    FILE *fp;
    char file_name[100]="楕円_a_1_b_3_0_001刻み_2.csv";
    

    printf(">>> read the %s\n", file_name);
    if((fp = fopen(file_name, "r")) == NULL) {
        perror("can't open file");
        return -1;
    }

    int i;

    for(i=0; i<nnode; i++){
        fscanf(fp, "%lf,%lf", &data[i][0], &data[i][1]);
    }

    fclose(fp);

    for(i=0; i<nnode; i++){
        printf("%d %f %f\n", i, data[i][0], data[i][1]);
    }

    /****界面の外向き法線方向ベクトル****/
    //double **normal_vectors;
    /****曲率**********/
    //double *kappa;

    //normal_vectors = (double **)malloc2d(sizeof(double), nnode, 2);
    kappa = (double *)malloc(sizeof(double) * nnode);



    solver_normalvec_radius(nnode, data);

    for(i=0; i<nnode; i++){
        printf("%d %f %f\n", i, data[i][0], kappa[i]);
    }

    free(kappa);

    return 0;
}
