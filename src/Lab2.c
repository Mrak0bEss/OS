#include "unistd.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int main()
{
	int fd1[2];
    int fd2[2];
 
	pipe(fd1);
    pipe(fd2);
    
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
        char *args[] ={stringAr,NULL};
        
        dup2(fd1[1],1);
        dup2(fd1[0],0);
        fflush(stdout);
        
        execv("./L1C1",args);
    }else{
    int child2=fork();
        if (child2 == -1)
        {
            printf("fork 2 error\n");
            return -1;
        } else if (child2 == 0)
        {
            sleep(1);
            printf("child 2 is working\n");
            
            int a1=0;
            int n1 =0;
            char stringAr1[n];
            
            read(fd1[0], stringAr1, sizeof(char)*n);
            close(fd1[1]);
            close(fd1[0]);
            
            printf("-2- %s", stringAr1);
            char *args[] ={stringAr1,NULL};
            dup2(fd2[1],1);
            dup2(fd2[0],0);
            
            execv("./L1C2",args);
            
        } 
        if (child2 >0)
        {
            sleep(2);
            fflush(stdin);
            
           printf("Father\n");
        
            char finalString[n];
            read(fd2[0],finalString,sizeof(char)*n);
            close(fd2[0]);
            close(fd2[1]);
            int n1 =0;
          
          for (int i =0; i<n;i++)
            {
              
                if (finalString[i]!='\0')
                {
                    n1++;
                }
            }
            n=n1;
            fflush(stdout);
        printf("Finally text : ");
            for(int i =0;i<n;i++)
            {
               printf("%c", finalString[i]);
            }
            printf("\n");
            
        }
    }
}