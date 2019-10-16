/********************************************
 *   2d sloshing simulation by ALE Method   *
 *   2014.06. () by Yusuke Kajiyama   *
 ********************************************/

/*** １要素当たりの節点数 ***/
#define NODE (4)
/*** １要素に隣接する要素数 ***/
#define ELEMENT (4)


/*** pai ***/
#define PI (3.1415926535897932384626433832)

/*******表面張力関連*******/
extern double sigma;
extern double  *l_k;

/****界面の外向き法線方向ベクトル****/
extern double **normal_vectors;
/****曲率**********/
extern double *kappa;

/*** variable ***/
extern int nan_flag;//非数の検知用

/*
 * 移流項をガウス積分で作成するための材料
 * 20181226
 */
extern double gauss_vxe, gauss_vye;
extern double gauss_Ax, gauss_Ay;
extern double gauss_advec_x;
extern double gauss_advec_y;

/*
 * 拡散項をガウス積分で作成するための材料
 * 20181228
 */
extern double gauss_div_x;
extern double gauss_div_y;

//質量項をガウス積分で解く．//20181228
extern double gauss_mass;

/*** newmark-beta method parameters ***/
extern double beta;
extern double rbeta;
extern double Gamma;
extern double rgamma;
extern double gamma_h;
extern double rgamma_h;

/*** analysis parameters ***/
extern double L_x, L_y;       // タンクの寸法
extern double L_y_water, L_y_air;  //液体層の寸法, 気体層の寸法 [m] 20190521
extern double *rho;            // 液体の密度
extern double *nu;             // 液体の動粘性
extern int * cell_matel;       //材料番号 20190521
extern double g;              // 重力加速度
extern double A;                    // 加振振幅      [-]
extern double f;                    // 振動数        [Hz]
extern double omega;                // 角速度        [rad/s]
extern double Omega_T;              // 角度          [rad]
extern int input_force;             // 
extern double Omega_dt;//
/*****2019.0627_解析領域*******/
extern double rc, rl, all_domain_r;
extern int nc, nl, r_divide;
extern int nc_1, nl_1;

/*** mesh parameters ***/
//extern int nnode, nelement;         // 総節点数，総要素数
extern int x_element, y_element;    // x,y方向の要素数
extern int y_element_water, y_element_air;  //液体層と気体層の要素数 20190521
extern int x_node, y_node;          // x,y方向の節点数
extern double *x, *y;               // 物理空間の座標
extern double *gx, *gy;             // 要素の重心座標
extern double *delta;               // 要素面積
extern double *deltagauss;          // ガウスの要素面積
extern int **nbool;                 // グローバルな節点番号と局所節点番号の関係
extern int **nbool3;                // 要素間の関係
extern int *ncod_x;                 // x方向の速度なし
extern int *ncod_y;                 // y方向の速度なし

/*** メッシュの分割方法 ***/
extern int method_of_division; // 等分割1 不当分割2
extern int unequal_division_para_1; // 物質1の不当分割パラメータ
extern int unequal_division_para_2; // 物質2の不当分割パラメータ

extern double xi[NODE], eta[NODE];  // 計算空間の座標

extern double *xb, *yb;             // 座標の保存
extern double *xb1, *yb1;           // 
/*** physical parameters ***/
extern double *u, *v;               // 速度
extern double *ua, *va;             // 流体の加速度 [m/s^2]
extern double *p;                   // 圧力

extern double ue, ve;               // 平均速度
extern double *uu, *vv;             // 速度の足し込み変数
extern double *ub, *vb;             // 速度の保存
extern double *u1, *v1;             // 速度の予測子

extern double *aax, *aay;           // 流体の加速度の足し込み変数
extern double *uab, *vab;           // 流体の加速度の保存
extern double *ua1, *va1;           // 流体の加速度の予測子

extern double dddu, dddv;
extern double aaau, aaav;           // 速度場の移流項
extern double btdu, btdv;
extern double bodyu, bodyv;         // 速度場の体積力項
extern double bndu, bndv;           // 速度場の境界項

extern double anb1, anb2;           // 移流マトリックスベース
extern double bmb1, bmb2, bmb3;     // BTDマトリックスベース

extern double dndxi[NODE], dndet[NODE], dndzt[NODE];  // 共変基底ベクトル

extern double *Div;                 // 速度のダイバージェンス
extern double *Faig;                // 修正速度ポテンシャル

extern double div_error, div_max;   // 反復計算の誤差と最大誤差
extern double del_error, vel_max;   // 座標の更新の誤差と最大誤差
extern double error1;               // Poisson方程式の収束条件
extern double error2;               // 座標決定の収束条件
extern const double ram1;           // 収束緩和係数
extern int ncal_num;                // Poisson方程式の計算回数
extern const int ncal_max;          // Poisson方程式の最大計算回数
extern int mcal_num;                // 座標更新の計算回数
extern const int mcal_max;          // 座標更新の最大計算回数

/*** time parameters ***/
extern int nstep;                   // 時間ステップ
extern double dt, time_max;         // 時間刻み幅，解析時間
extern double rdt;                  // 時間刻み幅の逆数
extern double increment_dt;         // ωΔt の刻み量

extern double ntime;                        // nステップの時間
extern double sample_time; int sample_num;  // サンプリング時間とサンプリングステップ
extern double nblk_time;   int nblk;        // 情報データの出力間隔時間，ステップ数

/*** matrix ***/
extern double *fm, *fhh;            // 質量集中化行列
double *fm_rho;              //20190521
extern double *sx1, *sx2;           // x方向の余因子成分(A11, A12)
extern double *sy1, *sy2;           // y方向の余因子成分(A21, A22)
extern double **cx, **cy;           // 勾配行列
extern double em[NODE][NODE];       // 質量行列
extern double am1[NODE][NODE], am2[NODE][NODE];                  // 移流部分行列
extern double dm1[NODE][NODE], dm2[NODE][NODE], dm3[NODE][NODE], dm4[NODE][NODE];

/*** ALE Method parameters ***/
extern int **nbool1d;               // 界面における線分要素と節点の関係
extern double *wx, *wy;             // メッシュ移動速度
extern double *wax, *way;           // メッシュの加速度
extern double *h;                   // 界面高さ
extern double *hb;                  // 界面高さの保存
extern double *hh;                  // 
extern double *vh;
extern double *vhh;                 //
extern double *vhb;                 //

extern double wxe, wye;             // メッシュの平均移動速度
extern double *wxb, *wyb;           // メッシュ移動速度の保存
extern double *waxb, *wayb;         // メッシュ移動加速度の保存

extern double am1d[NODE/2];         // 
extern double em1d[NODE/2][NODE/2]; // 
extern double *fm1d;                //

//extern double *dll;                 // 線分の長さ
extern double ue_n, ue_m;
extern double aaa, mmm, btd;

/*** Newmark-beta method parameters ***/
extern double *u_0, *v_0;
extern double *wx_0, *wy_0;
extern double *x_0, *y_0;
extern double *h_0;
extern double *ub1, *vb1;
extern double *vhb1;

/*** file name ***/
extern int file_number;
extern int file_count;
extern int mode_type;
extern char name[20];

