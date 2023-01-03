#include<cmath>
#include<vector>
#include <cstdlib>
#include<iostream>
using namespace std;
//extern "C" float inintergal(float A, float B,float e);
extern "C" float Intgr(float A, float B,float e);         
extern "C" int *Prim(int A, int B);       

float Intgr(float A, float B,float e)
{
    cout<<"Вычисление интеграла\n";
    float h,S,x;
    S=0;
    for(float i=A;i<=B;i=i+e)
    {
        S=S+sin(i);
    }
    h=(B-A)/((B-A)/e);
    S=h*S;
    return S;
}


int* Prim(int A, int B)
{
    cout<<"Решето Эратосфена\n";
    int *a= (int*)malloc(sizeof(int)*1000);
    for (int i = 2; i <= B; i++) {
        a[i] = 1;
       

    }
 
    for (int i = 2; i <= sqrt(B); i++)
    {
        if (a[i] == 1)          
        {
            for (int j = 2; i * j <= B; j++) {
                a[i * j] = 0;  
                
            }
        }
    }
    return a;
}