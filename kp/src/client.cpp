#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<cstring>
#include<string.h>
using namespace std;

int main()
{   

    fflush(stdout); 
    
    int wfd = open("mypipe", O_WRONLY);// Открываем файл конвейера
	if(wfd < 0){
		perror("open");
	}
    
    
    
    char buf[10];
    char* name = (char*)malloc(20*sizeof(char));
    char cmd;
    cmd ='n';
    //ОТПРАВКА ИМЕНИ НА СЕРВЕР
        //name[0]=0;
        string name1;
		printf("Please Enter name ");
        
		fflush(stdout);    // Обновляем буфер
        getline(cin,name1);
        int s = name1.length();
        write(wfd, &cmd,sizeof(char)); // Записываем в buf со стандартного ввода (клавиатура)
		if(s > 0 ){
            name[s-1]='\0';
            int nfd = open("name", O_WRONLY);// Открываем файл конвейера
	        if(nfd < 0){
		    perror("open");
	        }
    
			write(nfd, name1.c_str(), sizeof(string));  // Запись в файл конвейера
		}else if(s <= 0){
			perror("read");
		}

    
    //cout<<name1<<" -1"<<endl;
    printf("Search of enemy, wait of enemy or exit? Enter (s,w,e)\n");

    cin >> cmd;
    //ВЫБОР РЕЖИМА ИГРЫ
    if (cmd  == 's')
    {   
        char answ='n';
        while(answ != 'y')
        {
        int nfd = open(name1.c_str(), O_WRONLY);// Открываем файл конвейера
	    if(nfd < 0)
        {
		perror("open");
	    }
        write(nfd, &cmd,sizeof(char));
        string enemy;
        cout<<"enter enemy"<<endl;
        cin >> enemy;
		write(nfd, enemy.c_str(), sizeof(string)); 
        close(wfd);
        close(nfd);
        nfd =open(name1.c_str(), O_RDONLY);
        if(nfd < 0)
        {
		perror("open");
	    }
        
        read(nfd,&answ,sizeof(char));
        if (answ=='y')
        {
            cout<<"Player "<<enemy<<" want to play with you"<<endl;
            system("clear");
            cout <<"Playing. Your name - "<<name1<<". Enemy name - "<<enemy<<"."<<endl;
            string fight_address='&'+name1;
            //cout<<fight_address;
            int playingfd=open(fight_address.c_str(),O_RDWR);
            int ships[5][5];
            int seaofenemy[5][5];
            for (int i =0; i <5;i++)
            {
                for (int j =0; j<5;j++)
                {
                    ships[i][j]=0;
                    seaofenemy[i][j]=0;
                        
                }
            }

            char x;
            char y1;
            int y;
            cout<< "Введите наличие однопалубных кораблей. формат ввода - A 3 , D 0 - координаты однопалубных кораблей. всего их 3 шт. клеток 5, с 0 по 4 и с A по E"<<endl;
            
            for (int i = 0;i<3;i++)
            {
                while (1)
                {
                cin>>x>>y1;
                if ((x - 65 >=0) and (x - 65 <5) and (y1 >= '0')and(y1 < '5'))
                {
                    break;
                }
                else {
                    cout<<"Ошибка\n";
                }
                }
                y = y1 - 48;
                ships[x-65][y] = 1;
            }
            cout<< "Введите наличие однопалубных кораблей. формат ввода - C 3 D 4, B 0 B 1 - координаты координаты начала и конца двупалубных караблей кораблей. всего их 2 шт. клеток 5, с 0 по 4 и с A по E"<<endl;
            char d1;
            char z;
            int d;
            for (int i = 0;i<2;i++)
            {

                while (1)
                {
                cin >> x >> y1 >> z >> d1;
                if ((x - 65 >=0) and (x - 65 <5) and (y1 >= '0')and(y1 < '5')and (z - 65 >=0) and (z - 65 <5) and (d1 >= '0')and(d1 < '5'))
                {
                    break;
                }
                else {
                    cout<<"Ошибка\n";
                }
                }
                y = y1 - 48;
                d = d1 - 48;
                ships[x - 65][y] = 2;
                ships[z - 65][d] = 2;
            }
            for (int i =0; i <5;i++)
                                {
                                    for (int j =0; j<5;j++)
                                    {
                                        cout<<ships[i][j]<<" ";
                                        if (j == 4)
                                        {
                                            cout<<endl;
                                        }
                                    }
                                }
            write(playingfd, &ships,sizeof(int)*25);
            close(playingfd);
            system("clear");
            char stat;
            char res;
            int count;
            //playingfd=open(fight_address.c_str(),O_RDONLY);
            while(1)
            {
                int turn;
                
                cout<<"waiting..."<<endl;
                sleep(2);
                playingfd=open(fight_address.c_str(),O_RDONLY);
                read(playingfd,&stat,sizeof(char));
                
                //cout<<stat<<endl;
                if (stat == 'l')
                {
                    cout<<"Поражение"<<endl;
                    
                    break;
                }
                if (stat == 'w')
                {
                    
                    break;
                }
                read(playingfd,&seaofenemy,sizeof(int)*25);
                read(playingfd,&ships,sizeof(int)*25);
                close(playingfd);
                cout<<"Поле врага\n";
                for (int i =0; i <5;i++)
                                {
                                    for (int j =0; j<5;j++)
                                    {
                                        cout<<seaofenemy[i][j]<<" ";
                                        if (j == 4)
                                        {
                                            cout<<endl;
                                        }
                                    }
                                }
                cout<<"Ваше поле\n";
                for (int i =0; i <5;i++)
                                {
                                    for (int j =0; j<5;j++)
                                    {
                                        cout<<ships[i][j]<<" ";
                                        if (j == 4)
                                        {
                                            cout<<endl;
                                        }
                                    }
                                }
                cout<<"Введите точку для удара по противнику. Пример - В 0."<<endl;
                cin >> x >>y;
                int x1 = x - 65;
                playingfd=open(fight_address.c_str(), O_WRONLY);
                write(playingfd, &x1,sizeof(int));
                write(playingfd, &y,sizeof(int));
                close(playingfd);
                //cout<<"отослал\n";
                playingfd=open(fight_address.c_str(), O_RDONLY);
                read(playingfd,&res,sizeof(char));
                read(playingfd,&count,sizeof(int));
                close(playingfd);
                if (res == 'k')
                {
                    cout<<"Корабль уничтожен\n";
                    cout<<"Осталось кораблей противника - "<< count<<endl;
                }
                if (res == 'd')
                {
                    cout<<"Корабль задет\n";
                }
                if (res == 'p')
                {
                    cout<<"Промах\n";
                }
                if (res == 'w')
                {
                    cout<<"Победа!"<<endl;
                    
                }
                
                
            }
        }
        else
        {
            cout<<"Player "<<enemy<<" will not play with you"<<endl;
            cout <<"Want to exit or retry? (Enter e/r)"<<endl;
            char cntnue;
            cin >> cntnue;
            if (cntnue == 'e')
            {
                cout<<"EXIT\n";
                break;
            } 
        }
        }
        /// 
        ///
        remove(name1.c_str());
    }
    if (cmd  == 'w')
    {
        int nfd = open(name1.c_str(), O_WRONLY);// Открываем файл конвейера
	    if(nfd < 0)
        {
		perror("open");
	    }
        write(nfd, &cmd,sizeof(char));
        char acs;
        //write(1, "enter acsess\n", sizeof("enter acsess\n"));
        cout << "Enter acsess"<<endl;
        string adress_of_me=name1;
        adress_of_me.push_back('&');
        if(mkfifo(adress_of_me.c_str(), 0644) < 0)
            {    // Создаем файл именованного канала
    	        perror("mkfifo");
            }
        int pfd = open(adress_of_me.c_str(),O_RDONLY );
        if(pfd < 0)
        {
		perror("open");
	    }
        //НАДО ДОБВАИТЬ ВЫВОД ЛОГИНА ПРИГЛАШАЮЩЕГО И ДАЛЬНЕЙШЕЕ ВЗАИМОДЕЙСТВИЕ
        char* enemy=(char*)malloc(sizeof(string));
        read(pfd, enemy,sizeof(string) );
        close(pfd);
        string em;
        em = enemy;
        cout<<"Pleyer "<<enemy<<" want to play, yes or now (enter y,n)"<<endl;
        cin >>acs;
        pfd = open(adress_of_me.c_str(),O_WRONLY );
        write (pfd, &acs,sizeof(char));
        if (acs =='y')
        {
            system("clear");
            cout <<"Playing. Your name - "<<name1<<". Enemy name - "<<em<<".\nWaiting..."<<endl;
            string fight_address='&'+name1;
            //cout<<fight_address;
            int playingfd=open(fight_address.c_str(),O_RDONLY);
            int ships[5][5];
            char o;
            read(playingfd,&o,sizeof(char));
            close(playingfd);
            int seaofenemy[5][5];
            for (int i =0; i <5;i++)
            {
                for (int j =0; j<5;j++)
                {
                    ships[i][j]=0;
                    seaofenemy[i][j]=0;
                        
                }
            }
            int y;
            char y1;
            char x;
            cout<< "Введите наличие однопалубных кораблей. формат ввода - A 3 , D 0 - координаты однопалубных кораблей. всего их 3 шт. клеток 5, с 0 по 4 и с A по E"<<endl;
            
            for (int i = 0;i<3;i++)
            {

                while (1)
                {
                cin>>x>>y1;
                if ((x - 65 >=0) and (x - 65 <5) and (y1 >= '0')and(y1 < '5'))
                {
                    break;
                }
                else {
                    cout<<"Ошибка\n";
                }
                }
                y = y1 - 48;
                ships[x-65][y] = 1;
            }
            cout<< "Введите наличие однопалубных кораблей. формат ввода - C 3 D 4, B 0 B 1 - координаты координаты начала и конца двупалубных караблей кораблей. всего их 2 шт. клеток 5, с 0 по 4 и с A по E"<<endl;
            int d;
            char d1;
            char z;
            for (int i = 0;i<2;i++)
            {
                while (1)
                {
                cin >> x >> y1 >> z >> d1;
                if ((x - 65 >=0) and (x - 65 <5) and (y1 >= '0')and(y1 < '5')and (z - 65 >=0) and (z - 65 <5) and (d1 >= '0')and(d1 < '5'))
                {
                    break;
                }
                else {
                    cout<<"Ошибка\n";
                }
                }
                y = y1 - 48;
                d = d1 - 48;
                ships[x - 65][y] = 2;
                ships[z - 65][d] = 2;
            }
            playingfd= open(fight_address.c_str(),O_WRONLY);
            write(playingfd, &ships,sizeof(int)*25);
            close(playingfd);
            system("clear");
            char stat;
            char res;
            int count;
            
            while(1)
            {
                int turn;
                
                cout<<"waiting..."<<endl;
                sleep(2);
                playingfd=open(fight_address.c_str(),O_RDONLY);
                
                read(playingfd,&stat,sizeof(char));
                
                //cout<<stat<<endl;
                if (stat == 'l')
                {
                    cout<<"Поражение"<<endl;
                
                    break;
                }
                if (stat == 'w')
                {
                    
                    break;
                }
                read(playingfd,&seaofenemy,sizeof(int)*25);
                read(playingfd,&ships,sizeof(int)*25);
                //read(playingfd,&turn,sizeof(int));
                close(playingfd);
                cout<<"Поле врага" << endl;
                for (int i =0; i <5;i++)
                                {
                                    for (int j =0; j<5;j++)
                                    {
                                        cout<<seaofenemy[i][j]<<" ";
                                        if (j == 4)
                                        {
                                            cout<<endl;
                                        }
                                    }
                                }
                cout<<"Ваше поле" << endl;
                for (int i =0; i <5;i++)
                                {
                                    for (int j =0; j<5;j++)
                                    {
                                        cout<<ships[i][j]<<" ";
                                        if (j == 4)
                                        {
                                            cout<<endl;
                                        }
                                    }
                                }
                cout<<"Введите точку для удара по противнику. Пример - A 0."<<endl;
                cin >> x >>y;
                int x1=x-65;
                playingfd=open(fight_address.c_str(),O_WRONLY);
                write(playingfd, &x1,sizeof(int));
                write(playingfd, &y,sizeof(int));
                close(playingfd);
                playingfd=open(fight_address.c_str(),O_RDONLY);
                read(playingfd,&res,sizeof(char));
                read(playingfd,&count,sizeof(int));
                close(playingfd);
                if (res == 'k')
                {
                    cout<<"Корабль уничтожен\n";
                    cout<<"Осталось кораблей противника - "<< count<<endl;
                }
                if (res == 'd')
                {
                    cout<<"Корабль задет\n";
                }
                if (res == 'p')
                {
                    cout<<"Промах\n";
                }
                if (res == 'w')
                {
                    cout<<"Победа!"<<endl;
                
                    
                }
                
                
            }
        }    
    
		//write(nfd, enemy, strlen(enemy)-1); 
        remove(name1.c_str());
        remove(adress_of_me.c_str());
    }
    if (cmd  == 'e')
    {
        int nfd = open(name1.c_str(), O_WRONLY);// Открываем файл конвейера
	    if(nfd < 0)
        {
		perror("open");
	    }
        write(nfd, &cmd,sizeof(char));
        cout<<"EXIT\n";
        remove(name1.c_str());
      
    }
    remove(name1.c_str());
	
}