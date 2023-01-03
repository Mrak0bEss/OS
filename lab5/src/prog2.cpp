#include <stdio.h>         //g++ prog2.cpp -L. -ldl -o main2 -Wl,-rpath -Wl,.
#include <stdlib.h>
#include <dlfcn.h>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
    void* h = NULL;
    float (*Intgr)(float A, float B,float e);
    int* (*Prim)(int A,int B);
    int lib;
    printf("0 for change libs, 1 for re1.cpp, 2 for re2.cpp, 3 for exit:\n");
    scanf("%d", &lib);
    while ((lib != 1)&&(lib != 2))
    {
        printf("Input error, try again:\n");
        scanf("%d", &lib);
    }
    if (lib == 1)
    {
        h = dlopen("./libd1.so", RTLD_LAZY);
    }
    if (lib == 2)
    {
        h = dlopen("./libd2.so", RTLD_LAZY);
    }
    Intgr= (float(*)(float, float,float))dlsym(h, "Intgr");
    Prim = (int*(*)(int,int))dlsym(h, "Prim");
    unsigned command;
    printf("1 for Integrate 2 for Eratosphen:\n");
    char c1 = '1', c2 = '1';
    scanf("%d", &command);
    while (1)
    {
        if (command == 0)
        {
            if (lib == 1)
            {
                dlclose(h);
                h = dlopen("./libd2.so", RTLD_LAZY);
                Intgr = (float(*)(float, float,float))dlsym(h, "Intgr");
                Prim= (int*(*)(int,int))dlsym(h, "Prim");
                lib = 2;
                printf("re1 changed on re2\n");
                scanf("%d", &command);
                continue;
            }
            else
            {
                dlclose(h);
                h = dlopen("./libd1.so", RTLD_LAZY);
                Intgr  = (float(*)(float, float,float))dlsym(h, "Intgr");
                Prim = (int*(*)(int,int))dlsym(h, "Prim");
                lib = 1;
                printf("re2 changed on re1\n");
                scanf("%d", &command);
                continue;
            }
        }
        if (command == 1)
        {
            char c1 = '1', c2 = '1';
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
            int a,b;
            
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
    dlclose(h);
    return 0;
}