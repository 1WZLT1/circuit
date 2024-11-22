#include <stdio.h>
#include <math.h>

/**************************************************/
/*RCD*/
/*功率计算公式*/
/* L = uH(漏感)  I = A*/
#define W_Algorithm(L,I) 0.5f * L * ( I * I)
/*电容计算公式*/
/*C = uF*/
#define C_Algorithm(W,V) W * 2.0f / (V * V)

/*电阻的取值*/
/*R越大代表其放电时间就越久*/
/*T(放电时间) = R * C*/
/*T = 开关的频率 * 占空比*/
#define R_Algorithm(T,C) R = 1/T * C
 
/*二极管的取值*/
/*耐压高过vcc*/
/*电流等于电感的输出电流*/
/*开关速度越快越好*/
/**************************************************/

/**************************************************/
/*反激电路*/
/*匝数比*/
/*N = (输入的最小电压 / 输出电压 + 压降) * (最大占空比 / 1 - 最大占空比)*/
#define N_Algorithm(Vi,Vo,Vf,D) ((Vi * 0.85f * sqrt(2) / Vo + Vf) * (D / (1.0f - D)))
/*源边电感值*/
/*Lp(源边电感 mh) = (n)效率 * pow(D)(占空比) * pow(vin)(最小电压) / 2 * Fsw(开关频率) * Po(输出频率)*/
#define Lp_Algorithm(n,D,Vi,Fsw,Po) (((n * pow(D,2) * pow(Vi * 0.85f * sqrt(2),2) ) / (2.0f * Fsw * Po))) * 1000.0f
/*磁芯选择*/
/*EE10 5w  Ae 11mm2*/
/*EE13 8w  Ae 16mm2*/
/*EE16 10w Ae 19.5mm2*/
/*EE19 14w Ae 22.3mm2*/
/*EE19 20w Ae 40.8mm2*/
/*原边峰值电流*/
/*Ipk(峰值电流A) = 2 * Po(功率)/n(效率)*Vin(最小电压输入)*D(占空比)*/
#define Ipk_Algorithm(Po,n,Vin,D) (2 * Po) / (n * (Vin * 0.85f) * D) 
/*原边匝数*/
/*Np(原边匝数) = (Lp(原边电感) * Ipk(原边峰值电流)) / ((Bm(最大磁通密度) * Ae(磁芯截面积)) */
#define Np_Algorithm(Lp,Ipk,Bm,Ae) ((Lp * Ipk) / (Bm * Ae)) * 1000.0f 
/*副边匝数*/
#define Ns_Algorithm(Np,N) Np/N
/*副边反推原边匝数*/
#define Ns_Np_Algorithm(Ns,N) Ns * N
/**************************************************/
int main()
{
    float Lp  = Lp_Algorithm(0.75f,0.4f,220.0f,65000.0f,10.0f);
    float Ipk = Ipk_Algorithm(10.0f,0.75f,220.0f,0.4f);
    float Np  = Np_Algorithm(Lp,Ipk,0.25f,40.8f); 
    printf("Lp:%lf",Lp);
    printf("Ipk:%lf",Ipk);
    printf("Np:%lf",Np);
    
    while(1);
}