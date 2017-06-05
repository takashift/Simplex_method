#include <iostream>  // for cout
#include <stdio.h>   // for printf()

#define N_ROW 4      // 行数
#define N_COL 6      // 列数
#define N_VAR 5      // 求めたい変数の数
#define N_PUX 2      // 目的関数のxの数

using namespace std;

/*
 * 計算クラス
 */
class Calc
{
    // 各種変数
    double min, p, d;
    int i, j, x, y, flag;
    
public:
    void calcLinearProgramming();   // 線形計画法
};

/*
 * 線形計画法
 */
void Calc::calcLinearProgramming()
{
    flag = 0;
    
    // 係数行列
    // { x1, x2, s1, s2, s3, 定数}
    static double a[N_ROW][N_COL] = {
        { 1,  2,  1,  0,  0, 14},
        { 1,  1,  0,  1,  0,  8},
        { 3,  1,  0,  0,  1, 18},
        {-2, -1,  0,  0,  0,  0}
    };
    
    printf("  -x1  -x2  定数\n");
    
    while (1) {
        // タブロー出力
        for (i = 0; i < N_ROW; i++) {
            for (j = 0; j < N_COL; j++){
                if (a[i][j] >= 0 && a[i][j] < 10)
                    printf(" ");
                printf(" %.1f", a[i][j]);
                if (j == N_PUX-1)
                    j += N_COL - N_PUX - 1;
            }
            printf("\n");
        }
        printf("\n");
        
        // 列選択
        min = 9999;
        for (i = 0; i < N_COL - 1; i++) {
            if (a[N_ROW - 1][i] < min) {
                min = a[N_ROW - 1][i];
                y = i;
            }
        }
        
        // min が0以上になったら終了
        if (min >= 0){
            flag = -1;
            break;
        }
        // 選んだ列の値が全て0以下だったら終了
        else if (flag == N_ROW) break;
        
        // 行選択
        min = 9999;
        for (i = 0; i < N_ROW - 1; i++) {
            p = a[i][N_COL - 1] / a[i][y];
            if (a[i][y] > 0 && p < min) {
                min = p;
                x = i;
            }
            // 値が0以下だったらカウントする
            else if(a[i][y] <= 0 && p < min) {
                flag++;
            }
        }
        
        // ピボット係数
        p = a[x][y];
        
        // ピボット係数を p で除算
        for (i = 0; i < N_COL; i++)
            a[x][i] = a[x][i] / p;
        
        // ピボット列の掃き出し
        for (i = 0; i < N_ROW; i++) {
            if (i != x) {
                d = a[i][y];
                for (j = 0; j < N_COL; j++)
                    a[i][j] = a[i][j] - d * a[x][j];
            }
        }
    }
    
    // 結果出力
    // 選んだ列の値が全て０以下なら「解無し」
    if(flag != -1){
        printf("解無し\n");
    }
    
    for (i = 0; i < N_VAR; i++) {
        flag = -1;
        for (j = 0; j < N_ROW; j++) {
            if (a[j][i] == 1) {
                flag = j;
            } else if (flag != -1 && a[j][i] != 0) {
                flag = -1;
                break;
            }
        }
        if (flag != -1)
            printf("x%d = %8.4f\n", i, a[flag][N_COL - 1]);
        else
            printf("x%d = %8.4f\n", i, 0.0);
    }
    printf("z  = %8.4f\n", a[N_ROW - 1][N_COL - 1]);
}

/*
 * メイン処理
 */
int main()
{
    try
    {
        // 計算クラスインスタンス化
        Calc obiCalc;
        
        // 線形計画法
        obiCalc.calcLinearProgramming();
    }
    catch (...) {
        cout << "例外発生！" << endl;
        return -1;
    }
    return 0;
}
