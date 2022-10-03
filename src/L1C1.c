#include "stdlib.h"
#include<stdio.h>
#include<string.h>
#include <unistd.h>

int main(int argv, char *args[])
{
 
        int a = strlen(*args);
        char stringAr[a];
        sprintf(stringAr,"%s",args[0]);
      
        int i =0;
        while(i<a)
        {
           
            if ((stringAr[i] >64) &&(stringAr[i] < 91))
            {
                
                stringAr[i] = stringAr[i]+32;
                
                
            }
            i++;
        }
     
      fflush(stdout);
       printf("%s", stringAr);
      

    
        
}