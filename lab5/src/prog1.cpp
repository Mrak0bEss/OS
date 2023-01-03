#include <stdio.h>    //g++ prog1.cpp -L. -ld1 -o main1 -Wl,-rpath -Wl,.
#include <vector>        //g++ prog1.cpp -L. -ld2 -o main2 -Wl,-rpath -Wl,.
#include<iostream>
using namespace std;


extern "C" float Intgr(float A, float B, float e);
//extern "C" float inintergal(float A, float B,float e);
extern "C" int *Prim(int A, int B);   

int main()
{
    int command;
    printf("1 for integrate, 2 for Eratosphen, 3 for break:\n");
    scanf("%d", &command);
    while (1)
    {
        if (command == 1)
        {
        
            
                float a, b,e;
                scanf("%f%f%f", &a, &b, &e);
                if ((a < 1)||(b < 1))
                {
                    printf("Input error\n");
                }
                else
                {
                printf("%lf\n", Intgr(a,b,e));
                }
            
        }
        if (command == 2)
        {
            int a;
            int b;
            
            cin >> a >> b;
            //int arr[10000]; 
            int *arr = Prim(a,b);
            for (int i = a; i <= b; ++i)
            {
                //printf("%d ",arr[i]);
                if (arr[i]==1)
                {
                    printf("%d ",i);
                }
                
            }
            printf("\n");
            
        }
        if (command == 3)
        {
            break;
        }
        scanf("%d", &command);
    }
    return 0;
}
/*
 g++ -fPIC -c re1.cpp -o d1.o
 g++ -shared d1.o -o libd1.so
 g++ -fPIC -c re2.cpp -o d2.o
 g++ -shared d2.o -o libd2.so
 g++ prog1.cpp -L. -ld1 -o main1 -Wl,-rpath -Wl,.
 g++ prog1.cpp -L. -ld2 -o main2 -Wl,-rpath -Wl,.
*/