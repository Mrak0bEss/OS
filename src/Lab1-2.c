#include "unistd.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int main()
{
	int fd1[2];
    int fd2[2];
    int fd3[2];
	pipe(fd1);
    int tr = 0;
     pipe(fd2);
     pipe(fd3);
    char s[100];
    
    int n =0;
    printf("Enter text (} - sign of the end):\n");
    for (int i =0; i<=100;i++)
    {
        scanf("%c", &s[i]);
        if (s[i]!='}')
        {
            n++;
        }else 
        {
            
            break;
        }
    }
  
    write(fd1[1],&n,sizeof(int));
    write(fd1[1],s,sizeof(char)*n);

    int child1=fork();
    
    
    
    if (child1 == -1)
    {
        printf("fork 1 error\n");
        return -1;
    } else if (child1 == 0 )
    {
        printf("child 1 is working\n");
        int a;
        read(fd1[0], &a, sizeof(int));
        char stringAr[a];
        read(fd1[0], stringAr, sizeof(char)*a);
        for (int i =0;i<a;i++)
        {
            if ((stringAr[i] >64) &&(stringAr[i] < 91))
            {
                stringAr[i] = stringAr[i]+32;
            }
        }

    
        write(fd2[1],&a,sizeof(int));
        write(fd2[1],stringAr,sizeof(char)*a);
        
    }else{
    int child2=fork();
        if (child2 == -1)
        {
            printf("fork 2 error\n");
            return -1;
        } else if (child2 == 0)
        {
            printf("child 2 is working\n");
            int a1;
            int n1 =0;
            read(fd2[0],&a1,sizeof(int));
           
            char stringAr1[a1];
            read(fd2[0], stringAr1, sizeof(char)*a1);
          
            for (int i =0;i<a1;i++)
            {
                if ((stringAr1[i] == 32) &&(stringAr1[i+1] == 32))
                {
                     for (int j = i;j<a1-1;j++)
                    {
                    stringAr1[j]=stringAr1[j+1];
                    
                    }
                    n1++;
                }
            }
            a1=a1-n1;
             close(fd2[0]);
             close(fd2[1]);
           
          
           write(fd3[1],&a1,sizeof(int));
           write(fd3[1],stringAr1,sizeof(char)*a1);
        } 
        if (child2 >0)
        {
            int final;
            read(fd3[0],&final,sizeof(int));
            char finalString[final];
            read(fd3[0],finalString,sizeof(char)*final);
            for(int i =0;i<final;i++)
            {
                printf("%c", finalString[i]);
            }
            printf("\n");
            close(fd3[0]);
            close(fd3[1]);
        }
    }
}