#include "unistd.h"
#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main()
{
	
    int n =0;
    char* string =(char*)malloc(sizeof(char)*256);
    
    printf ("Insert your full string: ");
    fgets (string,256,stdin);
    char* ptr = mmap(NULL, sizeof(char)*strlen(string), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);
    if(ptr == MAP_FAILED){
        perror("Not mmap");
    }
    
    for (int i =0; i<strlen(string);i++)
    {
        ptr[i]=string[i];
    }

      
    int child1=fork();
    if (child1 == -1)
    {
        printf("Child1 error\n");
        return -1;
    } else if (child1 == 0 )
    {

        for (int i =0; i<strlen(ptr); i++)
        {
        if ((ptr[i] >64) &&(ptr[i] < 91))
            {
                
                ptr[i] = ptr[i]+32;
                
            }
        }
        
        
    }else{
    int child2=fork();
        if (child2 == -1)
        {
            printf("Child2 error\n");
            return -1;
        } else if (child2 == 0)
        {
           
            
            
        int n1=0;
        int n = strlen(ptr);
        
        for (int i =0;i<n;i++)
            {
                if ((ptr[i] == 32) &&(ptr[i+1] == 32))
                {
                     for (int j = i;j<n;j++)
                    {
                            ptr[j]=ptr[j+1];
                    
                    }
                    n1++;
                }
            }
            if (n1 !=0)
            {
            n = n - n1;
            ptr[n]='\0';
            }
            
            
        } 
        if (child2 >0)
        {
           int status;
            waitpid(child2, &status, WUNTRACED );
          
            printf("%s", ptr);
        
        int errump = munmap(ptr, 1);
        if(errump != 0){
            perror("don't create child2 process");
            exit(EXIT_FAILURE);
        }
        
        }
    }
    
}
