#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <map>
#include"pthread.h"
#include<cstring>
#include<vector>
#include<cstdio>
#include <sys/mman.h>
#include <algorithm>
#include <stdlib.h>

using namespace std;


vector <string> spisok;
map <string, int> mp;


int main()
{
    char y = 's';
    if(mkfifo("mypipe", 0644) < 0){    // Создаем файл именованного канала
		//perror("mkfifo");
	}
	int fd = open("mypipe", O_RDONLY);    // Открываем файл конвейера. Дескриптор файла - fd
		if(fd < 0){
		perror("open");
	}
    
    char buf[10];
    int i=0;
    
    pthread_t *id;
    id = (pthread_t*)malloc(sizeof(int)*(100));
    
    while(1)
    {
        
        fflush(stdin);
		
		// Считываем данные из файла конвейера
		if(read(fd, &buf[0], sizeof(char))){
            if (buf[0] == 'n')
            {   
                if(mkfifo("name", 0644) < 0)
                {    // Создаем файл именованного канала
		            //perror("mkfifo");
	            }
                string name;
                char* nm=(char*)malloc(sizeof(string));
	                int nfd = open("name", O_RDONLY);    // Открываем файл конвейера. Дескриптор файла - fd
		            if(nfd < 0){
		            perror("open");
	            }
                string nm1;
                ssize_t s = read(nfd, nm, sizeof(string));
                nm1 = nm;
                printf("client %d ",i);
                cout << nm1<<endl;
                spisok.push_back(nm1);
                mp[nm1]=2;
                int fdmap[2];
                pipe(fdmap);
                write (fdmap[1], &spisok,sizeof(string)*100);
                close (nfd);
                int fd[2];
                pipe(fd);
                write (fd[1], nm1.c_str(),sizeof(string));
                /// 
                /// 




                int pid = fork();
                if (pid == 0)
                {
                    char* name=(char*)malloc(sizeof(string));
                    string nm;
                    //map <char*, int> mp;
                    
                    
                    //nm = name;
                    read(fd[0],name,sizeof(string));
                    //close(fd);
                    nm = name;
                    //name[strlen(name)-1]='\0';
                    cout<<"playing client name " <<nm<<" \n";
                    
                    while (1)
                    {
                    if(mkfifo(name, 0644) < 0){    // Создаем файл именованного канала
	            	    
	                }
                    int ffd = open(name, O_RDONLY);    // Открываем файл конвейера. Дескриптор файла - fd
		            if(ffd < 0){
		                perror("open");
	                }
                    
                    
                    char command;
                    //name[strlen(name)-1]='\0';
                    nm = name;
                    read(ffd, &command,sizeof(char));
                    cout <<"player "<<nm<<" choose command "<<command<<endl;
                    if (command == 's')
                    {
                        
                        char* enemy=(char*)malloc(sizeof(string));
                        read(ffd, enemy,sizeof(string) );
                        close(ffd);
                        string em = enemy;
                        em.push_back('&');
                        cout <<"player "<<nm<<" choose enemy "<<enemy<<" check"<<endl;
                        int chk_enmy= open(enemy, O_WRONLY);// Открываем файл конвейера
	                    if(chk_enmy < 0)
                        {
		                    cout<<"Enemy "<<enemy<< " not exist"<<endl;
                            int ffd = open(name, O_WRONLY);
                            char n ='n';
                            write(ffd,&n,sizeof(char));  
                            close(ffd);
	                    }
                        else 
                        {
                            char accss='y';
                            if(mkfifo(em.c_str(), 0644) < 0)
                            {    // Создаем файл именованного канала
	                	        perror("mkfifo");
	                        }
                            int enmy= open(em.c_str(), O_WRONLY );
                            if(enmy < 0)
                            {
		                        cout<<"file "<<em<< " not exist"<<endl;
                                int ffd = open(name, O_WRONLY);
                                char n ='n';
                                write(ffd,&n,sizeof(char));  
                                close(ffd);

	                        }
                            write(enmy,name ,sizeof(string));
                            close(enmy);
                            enmy= open(em.c_str(), O_RDONLY );
                            read(enmy,&accss,sizeof(char));
                            
                            int ffd = open(name, O_WRONLY);  
                            if (accss == 'y')
                            {
                                cout<<"Player "<<enemy<<" enter acsses"<<endl;
                                write(ffd,&accss,sizeof(char));  
                                close(ffd);
                                em.pop_back();
                                string player2='&'+em;
                                string player1='&'+nm;
                            
                                //cout <<em<<endl;
                                if(mkfifo(player1.c_str(), 0644) < 0)
                                {    // Создаем файл именованного канала
	                	            perror("mkfifo");
	                            }
                                if(mkfifo(player2.c_str(), 0644) < 0)
                                {    // Создаем файл именованного канала
	                	            perror("mkfifo");
	                            }
                               // cout << player1<<" "<<player2<<endl;
                                int player1fd=open(player1.c_str(),O_RDONLY);
                                
                                int sea1[5][5];
                                int sea2[5][5];
                                memset(sea1,0,25);
                                memset(sea2,0,25);
                                int sea2for1[5][5];
                                int sea1for2[5][5];
                                for (int i =0; i <5;i++)
                                {
                                    for (int j =0; j<5;j++)
                                    {
                                        sea2for1[i][j]=0;
                                    }
                                }
                                for (int i =0; i <5;i++)
                                {
                                    for (int j =0; j<5;j++)
                                    {
                                        sea1for2[i][j]=0;
                                    }
                                }
                                read(player1fd, &sea1,sizeof(int)*25);
                                for (int i =0; i <5;i++)
                                {
                                    for (int j =0; j<5;j++)
                                    {
                                        cout<<sea1[i][j]<<" ";
                                        if (j == 4)
                                        {
                                            cout<<endl;
                                        }
                                    }
                                }
                                int player2fd=open(player2.c_str(),O_WRONLY);
                                char q='q';
                                write(player2fd,&q,sizeof(char));
                                close(player2fd);
                                player2fd=open(player2.c_str(),O_RDONLY);
                                read(player2fd, &sea2,sizeof(int)*25);
                                for (int i =0; i <5;i++)
                                {
                                    for (int j =0; j<5;j++)
                                    {
                                        cout<<sea2[i][j]<<" ";
                                        if (j == 4)
                                        {
                                            cout<<endl;
                                        }
                                    }
                                }
                                close(player1fd);
                                close(player2fd);
                                
                                int counter1=5;
                                int counter2=5;
                                char retrn='g';
                                int count=1;
                                char status1, status2;
                                status1='p';
                                status2='p';
                                cout<<"start\n";
                                while (1)
                                {
                                    count++;
                                    
                                    int x,y;
                                    if (count % 2 ==0)
                                    {   
                                        cout<<"start 1"<<endl;
                                        player1fd=open(player1.c_str(),O_WRONLY);
                                        cout<<status1<<endl;
                                        write(player1fd,&status1,sizeof(char));
                                        write(player1fd,&sea2for1,sizeof(int)*25);
                                        write(player1fd,&sea1,sizeof(int)*25);///
                                        //write(0,&status1,sizeof(char));
                                        if ((status1=='l')||(status1=='w'))
                                        {
                                            if (status1=='w')
                                            {
                                                player2fd=open(player2.c_str(),O_WRONLY);
                                                write(player2fd,&status2,sizeof(char));
                                                close(player2fd);
                                            }
                                            cout<<"End of game"<<endl;
                                            break;
                                        }
                                        cout<<"отослал 1\n";
                                        close(player1fd);
                                        player1fd=open(player1.c_str(),O_RDONLY);
                                        read(player1fd,&x,sizeof(int));
                                        read(player1fd,&y,sizeof(int));
                                        cout<<x<<" "<<y<<endl;
                                        close(player1fd);
                                        
                                            if (sea2[x][y]==1)
                                            {
                                                //cout << " NUM - "<<sea2[x][y]<<endl;
                                                counter2--;
                                                sea2[x][y]=4;
                                                sea2for1[x][y]=4;
                                                retrn = 'k';
                                                count--;
                                            }else
                                            if (sea2[x][y]==2)
                                            {
                                                count--;
                                                sea2[x][y]=4;
                                                sea2for1[x][y]=4;
                                                retrn = 'd';
                                                if ((x != 0 && x != 4)&&(y != 0 && y != 4))
                                                {
                                                if ((sea2[x-1][y]==0 || sea2[x-1][y]==4)&&(sea2[x][y-1]==0 || sea2[x][y-1]== 4)&&(sea2[x+1][y]==0 || sea2[x+1][y]== 4)&&(sea2[x][y+1]==0 || sea2[x][y+1]== 4))
                                                {
                                                    counter2--;
                                                    retrn = 'k';   
                                                }
                                                }else if((x == 0)&&(y != 0 && y != 4))
                                                {
                                                    if ((sea2[x][y-1]==0 || sea2[x][y-1]==4)&&(sea2[x+1][y]==0 || sea2[x+1][y]== 4)&&(sea2[x][y+1]==0 || sea2[x][y+1]== 4))
                                                {
                                                    counter2--;
                                                    retrn = 'k';   
                                                }
                                                }else if((x == 0)&&(y == 0))
                                                {
                                                    if ((sea2[x+1][y]==0 || sea2[x+1][y]== 4)&&(sea2[x][y+1]==0 || sea2[x][y+1]==4))
                                                {
                                                    counter2--;
                                                    retrn = 'k';   
                                                }
                                                }else if((x == 0)&&(y == 4))
                                                {
                                                    if ((sea2[x][y-1]==0 || sea2[x][y-1]== 4 )&&(sea2[x+1][y]==0) || sea2[x+1][y]== 4)
                                                {
                                                    counter2--;
                                                    retrn = 'k';   
                                                }
                                                }else if((x == 4)&&(y != 0 && y != 4))
                                                {
                                                    if ((sea2[x-1][y]==0 || sea2[x-1][y]== 4)&&(sea2[x][y-1]==0 || sea2[x][y-1]== 4)&&(sea2[x][y+1]==0 || sea2[x][y+1]== 4))
                                                {
                                                    counter2--;
                                                    retrn = 'k';   
                                                }
                                                }else if((x == 4)&&(y == 0))
                                                {
                                                    if ((sea2[x-1][y]==0 || sea2[x-1][y]== 4)&&(sea2[x][y+1]==0 || sea2[x][y+1] == 4))
                                                {
                                                    counter2--;
                                                    retrn = 'k';   
                                                }
                                                }else if((x == 4)&&(y == 4))
                                                {
                                                    if ((sea2[x-1][y]==0 ||  sea2[x-1][y] == 4)&&(sea2[x][y-1]==0 || sea2[x][y-1] == 4))
                                                {
                                                    counter2--;
                                                    retrn = 'k';   
                                                }
                                                }else if((y == 0)&&(x != 0 && x != 4))
                                                {
                                                    if ((sea2[x-1][y]==0 || sea2[x-1][y]==4)&&(sea2[x+1][y]==0 || sea2[x+1][y]== 4 )&&(sea2[x][y+1]==0 || sea2[x][y+1]== 4))
                                                {
                                                    counter2--;
                                                    retrn = 'k';   
                                                }
                                                }else if((y == 4)&&(x != 0 && x != 4))
                                                {
                                                    if ((sea2[x-1][y]==0 || sea2[x-1][y]== 4)&&(sea2[x][y-1]==0 || sea2[x][y-1]== 4 )&&(sea2[x+1][y]==0 || sea2[x+1][y]== 4))
                                                {
                                                    counter2--;
                                                    retrn = 'k';   
                                                }
                                                }
                                            }else 
                                            {
                                                retrn = 'p';
                                                sea2[x][y]=8;
                                                sea2for1[x][y]=8;
                                            }
                                        
                                        /*player1fd=open(player1.c_str(),O_RDONLY);
                                        char trsh;
                                        if (int err=read(player1fd,&trsh,sizeof(char)) != 0)
                                        {
                                            cout<<"err\n";
                                        }
                                        close(player1fd);*/
                                        player1fd=open(player1.c_str(),O_WRONLY);
                                        if (counter2==0)
                                        {
                                            retrn='w';
                                            write(player1fd,&retrn,sizeof(char));
                                            write(player1fd,&counter2,sizeof(int));

                                            status2='l';
                                            status1='w';
                                            write(player2fd,&status2,sizeof(char));
                                            
                                        }else
                                        {
                                            write(player1fd,&retrn,sizeof(char));
                                            write(player1fd,&counter2,sizeof(int));

                                            cout<< retrn<<" "<<counter2<< " "<<count<<endl;
                                            sleep(1);
                                        }
                                        close(player1fd);
                                       
                                    }
                                    else
                                    {
                                        cout<<"start 2"<<endl;
                                        player2fd=open(player2.c_str(),O_WRONLY);
                                        write(player2fd,&status2,sizeof(char));
                                        write(player1fd,&sea1for2,sizeof(int)*25);
                                        write(player1fd,&sea2,sizeof(int)*25);
                                        close(player2fd);

                                        if ((status2=='l')||(status2=='w'))
                                        {
                                            if (status2=='w')
                                            {
                                                player1fd=open(player1.c_str(),O_WRONLY);
                                                write(player1fd,&status1,sizeof(char));
                                                close(player1fd);
                                            }
                                            cout<<"End of game"<<endl;
                                            break;
                                        }
                                        write(0,&status2,sizeof(char));
                                        cout<<"отослал 2\n";
                                        player2fd=open(player2.c_str(),O_RDONLY);
                                        read(player2fd,&x,sizeof(int));
                                        read(player2fd,&y,sizeof(int));
                                        close(player2fd);
                                        cout<<x<<" "<<y<<endl;
                                        
                                        
                                            if (sea1[x][y]==1)
                                            {
                                                counter1--;
                                                sea1[x][y]=4;
                                                sea1for2[x][y]=4;
                                                retrn = 'k';
                                                count--;
                                                //cout << " NUM - "<<sea2[x][y]<<endl;
                                            }else
                                            if (sea1[x][y]==2)
                                            {
                                                sea1[x][y]=4;
                                                sea1for2[x][y]=4;
                                                retrn = 'd';
                                                count--;
                                                if ((x != 0 && x != 4)&&(y != 0 && y != 4))
                                                {
                                                if ((sea1[x-1][y]==0 || sea1[x-1][y]==4)&&(sea1[x][y-1]==0 || sea1[x][y-1]== 4)&&(sea1[x+1][y]==0 || sea1[x+1][y]== 4)&&(sea1[x][y+1]==0 || sea1[x][y+1]== 4))
                                                {
                                                    counter1--;
                                                    retrn = 'k';   
                                                }
                                                }else if((x == 0)&&(y != 0 && y != 4))
                                                {
                                                    if ((sea1[x][y-1]==0 || sea1[x][y-1]==4)&&(sea1[x+1][y]==0 || sea1[x+1][y]== 4)&&(sea1[x][y+1]==0 || sea1[x][y+1]== 4))
                                                {
                                                    counter1--;
                                                    retrn = 'k';   
                                                }
                                                }else if((x == 0)&&(y == 0))
                                                {
                                                    if ((sea1[x+1][y]==0 || sea1[x+1][y]== 4)&&(sea1[x][y+1]==0 || sea1[x][y+1]==4))
                                                {
                                                    counter1--;
                                                    retrn = 'k';   
                                                }
                                                }else if((x == 0)&&(y == 4))
                                                {
                                                    if ((sea1[x][y-1]==0 || sea1[x][y-1]== 4 )&&(sea1[x+1][y]==0) || sea1[x+1][y]== 4)
                                                {
                                                    counter1--;
                                                    retrn = 'k';   
                                                }
                                                }else if((x == 4)&&(y != 0 && y != 4))
                                                {
                                                    if ((sea1[x-1][y]==0 || sea1[x-1][y]== 4)&&(sea1[x][y-1]==0 || sea1[x][y-1]== 4)&&(sea1[x][y+1]==0 || sea1[x][y+1]== 4))
                                                {
                                                    counter1--;
                                                    retrn = 'k';   
                                                }
                                                }else if((x == 4)&&(y == 0))
                                                {
                                                    if ((sea1[x-1][y]==0 || sea1[x-1][y]== 4)&&(sea1[x][y+1]==0 || sea1[x][y+1] == 4))
                                                {
                                                    counter1--;
                                                    retrn = 'k';   
                                                }
                                                }else if((x == 4)&&(y == 4))
                                                {
                                                    if ((sea1[x-1][y]==0 ||  sea1[x-1][y] == 4)&&(sea1[x][y-1]==0 || sea1[x][y-1] == 4))
                                                {
                                                    counter1--;
                                                    retrn = 'k';   
                                                }
                                                }else if((y == 0)&&(x != 0 && x != 4))
                                                {
                                                    if ((sea1[x-1][y]==0 || sea1[x-1][y]==4)&&(sea1[x+1][y]==0 || sea1[x+1][y]== 4 )&&(sea1[x][y+1]==0 || sea1[x][y+1]== 4))
                                                {
                                                    counter1--;
                                                    retrn = 'k';   
                                                }
                                                }else if((y == 4)&&(x != 0 && x != 4))
                                                {
                                                    if ((sea1[x-1][y]==0 || sea1[x-1][y]== 4)&&(sea1[x][y-1]==0 || sea1[x][y-1]== 4 )&&(sea1[x+1][y]==0 || sea1[x+1][y]== 4))
                                                {
                                                    counter1--;
                                                    retrn = 'k';   
                                                }
                                                }
                                            }else 
                                            {
                                                retrn = 'p';
                                                sea1[x][y]=8;
                                               sea1for2[x][y]=8; 
                                            }
                                        
                                            player2fd=open(player2.c_str(),O_WRONLY);
                                            
                                            
                                            if (counter1==0)
                                            {
                                                retrn='w';
                                                write(player2fd,&retrn,sizeof(char));
                                                write(player2fd,&counter1,sizeof(int));
                                                status1='l';
                                                status2='w';
                                                player2fd=open(player2.c_str(),O_WRONLY);
                                                write(player1fd,&status1,sizeof(char));
                                                close(player1fd);
                                                
                                            }else
                                            {

                                                write(player2fd,&retrn,sizeof(char));
                                                write(player2fd,&counter1,sizeof(int));
                                                cout<< retrn<<" "<<counter1<<" "<<count<<endl;

                                              
                                                
                                                
                                            }
                                            close(player2fd);
                                            sleep(1);
                                            
                                        }
                                    
                                    
                                    
                                }
                                remove(player1.c_str());
                                remove(player2.c_str());
                                remove(name);
                                remove(em.c_str());
                                
                            }
                            else 
                            {
                                cout<<"Player "<<enemy<<" not  enter acsses"<<endl;
                                write(ffd,&accss,sizeof(char));  
                                close(ffd);
                                remove(name);
                            }
                        }
                        
                    }
                    if (command == 'w')
                    {
                        cout<<"Player "<<name<<" entering acsses"<<endl;
                    }
                    if (command == 'e')
                    {
                        cout<<"Player "<<name<<" exit"<<endl;
                        break;
                    }
                    }
                }
                
                i++;
            }
		}else{
            

		}
        

    }
    
    close(fd);
}