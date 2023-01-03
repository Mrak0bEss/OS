#include "unistd.h"
#include "stdio.h"
//#include "string.h"
#include <cstring>
//#include <iostream>
#include <sys/mman.h>
//using namespace std;

int main()
{
	int fd1[2];
    int fd2[2];
    int fd3[2];
	pipe(fd1);
    pipe(fd2);
    pipe(fd3);
    
    //char *s=malloc(sizeof(char) * 100);
    
    int n =0;
    fflush(stdin);
    fflush(stdout);
   // char *hello="Enter text({ - end)\n";
    //write(1,hello, strlen(hello));
    /*for (int i =0; i<=100;i++)
    {
        read(0,&s[i],sizeof(char));
        if (s[i]!='}')
        {
            n++;
        }else 
        {
            s[i]=='\0';
            break;
        }
    }*/ 
    char s[3];
    //getline(cin, s);
    //nt n1=s.length();
    int n1=3;
    char *t = (char*)mmap( NULL, n1*sizeof(char),
 PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );

    for (int i = 0; i < n1; i++)
    {
        t[i] = s[i];
    }
    int child1=fork();
    
    
    
    if (child1 == -1)
    {
        //char *er1="fork 1 error\n";
        //write(1,er1,strlen(er1));
        return -1;
    } else if (child1 == 0 )
    {
        //char *wk1="child1 work\n";
        
    }else{
    int child2=fork();
        if (child2 == -1)
        {
            //char *er2="fork 2 error\n";
            //write(1,er2,strlen(er2));
            return -1;
        } else if (child2 == 0)
        {
            
           
            fflush(stdin);
           
            //char *wk2="child2 work\n";
            
            
        } 
        if (child2 >0)
        {
            
            fflush(stdin);
            char *final= munmap(t, n1*sizeof(char));
            printf("\n %s", final);
            // << final;
            
        }
    }
}