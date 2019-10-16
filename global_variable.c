//*****************************************
// last update 2019.08.20 by Kenta Shibuta
//*****************************************

#include <stddef.h>//20190215
#include "global_variable.h"
//#include "malloc.h"//20190215

/*** １要素当たりの節点数 ***/
#define NODE (4)
/*** １要素に隣接する要素数 ***/
#define ELEMENT (4)
/*** pai ***/
#define PI (3.1415926535897932384626433832)

/*******表面張力関連*******/
double sigma;
double  *l_k; // 辺要素

/****界面の外向き法線方向ベクトル****/
double **normal_vectors;
/****曲率**********/
double *kappa;

/*** variable ***/
int nan_flag;//非数の検知用

/*
 * 移流項をガウス積分で作成するための材料
 * 20181226
 */
double gauss_vxe, gauss_vye;
double gauss_Ax, gauss_Ay;
double gauss_advec_x;
double gauss_advec_y;

/*
 * 拡散項をガウス積分で作成するための材料
 * 20181228
 */
double gauss_div_x;
double gauss_div_y;

//質量項をガウス積分で解く．//20181228
double gauss_mass;

/*** newmark-beta method parameters ***/
//20181203
double beta;
double rbeta;
double Gamma;
double rgamma;
double gamma_h;
double rgamma_h;

/*** analysis parameters ***/
double L_x, L_y;       // タンクの寸法  [m]
double L_y_water, L_y_air;  //液体層の寸法, 気体層の寸法 [m] 20190521
double *rho;            // 液体の密度    [kg/m^3] 20190521_ポインタ変数に変更
double *nu;             // 液体の動粘性  [m^2/s]  20190521_ポインタ変数に変更
int * cell_matel;       //材料番号 20190521
double g;              // 重力加速度    [m/s^2]
double A;                    // 加振振幅      [-]
double f;                    // 振動数        [Hz]
double omega;                // 角速度        [rad/s]
double Omega_T;              // 角度          [rad]
int input_force;             // 
double Omega_dt;
/*****2019.0627_解析領域*******/
double rc, rl, all_domain_r;
int nc, nl, r_divide;
int nc_1, nl_1;

/*** mesh parameters ***/
//int nnode, nelement;         // 総節点数，総要素数
int x_element, y_element;    // x,y方向の要素数
int y_element_water, y_element_air;  //液体層と気体層の要素数 20190521
int x_node, y_node;          // x,y方向の節点数
double *x, *y;               // 物理空間の座標
double *gx, *gy;             // 要素の重心座標
double *delta;               // 要素面積
double *deltagauss;          // ガウスの要素面積
int **nbool;                 // グローバルな節点番号と局所節点番号の関係
int **nbool3;                // 要素間の関係
int *ncod_x;                 // x方向の速度なし
int *ncod_y;                 // y方向の速度なし

/*** メッシュの分割方法 ***/
int method_of_division; // 等分割1 不当分割2
int unequal_division_para_1; // 物質1の不当分割パラメータ
int unequal_division_para_2; // 物質2の不当分割パラメータ

double xi[NODE], eta[NODE];  // 計算空間の座標

double *xb, *yb;             // 座標の保存
double *xb1, *yb1;           // 

/*** physical parameters ***/
double *u, *v;               // 速度
double *ua, *va;             // 流体の加速度 [m/s^2]
double *p;                   // 圧力

double ue, ve;               // 平均速度
double *uu, *vv;             // 速度の足し込み変数
double *ub, *vb;             // 速度の保存
double *u1, *v1;             // 速度の予測子

//20181203
double *aax, *aay;           // 流体の加速度の足し込み変数
double *uab, *vab;           // 流体の加速度の保存
double *ua1, *va1;           // 流体の加速度の予測子

double dddu, dddv;           // 速度場の拡散項
double aaau, aaav;           // 速度場の移流項
double btdu, btdv;           // 速度場のBTD項
double bodyu, bodyv;         // 速度場の体積力項
double bndu, bndv;           // 速度場の境界項

double anb1, anb2;           // 移流マトリックスベース
double bmb1, bmb2, bmb3;     // BTDマトリックスベース

double dndxi[NODE], dndet[NODE], dndzt[NODE];  // 共変基底ベクトル

double *Div;                 // 速度のダイバージェンス
double *Faig;                // 修正速度ポテンシャル

double div_error, div_max;   // 反復計算の誤差と最大誤差
double del_error, vel_max;   // 陽的反復を打ち切るための速度誤差と最大誤差
double error1;               // Poisson方程式の収束条件
double error2;               // 座標決定の収束条件
const double ram1 = 1.0;     // 収束緩和係数
int ncal_num = 0;                // Poisoon方程式の計算回数
const int ncal_max = 100000000;   // Poisoon方程式の最大計算回数
int mcal_num = 0;                // 座標更新の計算回数
const int mcal_max = 100;    // 座標更新の最大計算回数

/*** time parameters ***/
int nstep;                   // 時間ステップ
double dt, time_max;         // 時間刻み幅，解析時間
double rdt;                  // 時間刻み幅の逆数
double increment_dt;         // ωΔt の刻み量

double ntime;                        // nステップの時間
double sample_time; int sample_num;  // サンプリング時間とサンプリングステップ
double nblk_time;   int nblk;        // 情報データの出力間隔時間，ステップ数

/*** matrix ***/
double *fm, *fhh;            // 質量集中化行列
double *fm_rho;              //20190521
double *sx1, *sx2;           // x方向の余因子成分(A11, A12)
double *sy1, *sy2;           // y方向の余因子成分(A21, A22)
double **cx, **cy;           // 勾配行列
double em[NODE][NODE];       // 質量行列
double am1[NODE][NODE], am2[NODE][NODE];                  // 移流部分行列
double dm1[NODE][NODE], dm2[NODE][NODE], dm3[NODE][NODE], dm4[NODE][NODE];

/*** ALE Method parameters ***/
int **nbool1d;               // 界面における線分要素と節点の関係
double *wx, *wy;             // メッシュ移動速度
double *wax, *way;           // メッシュの加速度
double *h;                   // 界面高さ
double *hb;                  // 界面高さの保存
double *hh;                  // 
double *vh;
double *vhh;                 //
double *vhb;                 //

double wxe, wye;             // メッシュの平均移動速度
double *wxb, *wyb;           // メッシュ移動速度の保存
double *waxb, *wayb;         // メッシュ移動加速度の保存

double am1d[NODE/2];         // 
double em1d[NODE/2][NODE/2]; // 
double *fm1d;                //

//double *dll;                 // 線分の長さ
double ue_n, ue_m;
double aaa, mmm, btd;

/*** Newmark-beta method parameters ***/
double *u_0, *v_0;
double *wx_0, *wy_0;
double *x_0, *y_0;
double *h_0;
double *ub1, *vb1;
double *vhb1;

/*** file name ***/
int file_number;
int file_count;
int mode_type;
char name[20];

