#include <stdio.h>

/*RCD*/
/*功率计算公式*/
/* L = uH(漏感)  I = A*/
#define W_Algorithm(L,I) 0.5f * L * ( I * I)
/*电容计算公式*/
/*C = uF*/
#define C_Algorithm(W,V) W * 2.0f / (V * V)

int main()
{
    float W = W_Algorithm(1000.0f,5.0f);
    float C = C_Algorithm(W,15.8113883f);
    printf("%lf",C);
    while(1);
}
