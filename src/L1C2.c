#include "stdlib.h"
#include<stdio.h>
#include<string.h>
#include <unistd.h>
int main(int argv, char *args[])
{

    short n1 =0;
    short n = strlen(*args);
        char stringAr1[n];
        sprintf(stringAr1,"%s",args[0]);
            for (short i =0;i<n;i++)
            {
                if ((stringAr1[i] == 32) &&(stringAr1[i+1] == 32))
                {
                     for (short j = i;j<n-1;j++)
                    {
                    stringAr1[j]=stringAr1[j+1];
                    
                    }
                    n1++;
                }
            }
            if (n1 !=0)
            {
            n = n - n1-1;
            stringAr1[n]='\0';
            }
        
         fflush(stdout);
         
   
          printf("%s",stringAr1);

}