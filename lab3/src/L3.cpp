#include"stdio.h"
#include"pthread.h"
#include<unistd.h>
#include<string.h>
#include<iostream>
#include<math.h>
#include<complex>


using namespace std;

pthread_mutex_t mutex;

void *func(void* arg)
{
   // pthread_mutex_lock(&mutex);
    complex <int> *data = (complex <int >*)arg;
    complex <int> k = (0, 0);
    int m = (real)(data[0]);
    for( int i =1;i<=m;i++)
    {
      
        k = k + data[i]*data[i+m];
    }
   
    complex <int> *p = (complex<int>*)calloc(1,sizeof(int));
    *p = k;
   
  //  pthread_mutex_unlock(&mutex);    
    pthread_exit(p);
    
}


int main()
{
    int n,m,p,b;
    int numOfThr;
    cout << "Введите количество потоков:\n";
    cin>> numOfThr;
    cout << "Размеры матрицы 1: ";
    cin >>n>>m;
    cout << "\nРазмеры матрицы 2: ";
    cin>>p>>b;
    if (m != p)
    {
        cout<<"Каоличество столбцов первой матрицы не соответсвукт количеству строк второй\n";
        return 0;
    }
    complex <int> matr[n][m];
    complex <int> matr2[p][b];
    for (int i =0; i<n;i++)
    {
        for (int j =0; j<m;j++)
        {
            cin >> matr[i][j];
        }
    }
    for (int i =0; i<p;i++)
    {
        for (int j =0; j<b;j++)
        {
            cin >> matr2[i][j];
        }
    }
    int count  = 0;
    complex <int>* data = NULL;
    pthread_t *id;
    id = (pthread_t*)malloc(sizeof(int)*(numOfThr));
    int numOfcout =0;
    for (int i =0; i<n;i++)
    {
        for (int j =0; j<b;j++)
        {
            data = (complex<int>*)malloc((m*p*2+2)*sizeof(int));
            data[0]=m;
            for (int k = 0; k < m;k++)
            {
                data[k+1]=matr[i][k];
                
            }
            for (int k = 0; k < m;k++)
            {
                data[k+m+1]=matr2[k][j];
                
            }
            
            pthread_create(&id[count++], NULL,func, (void*)(data));
            if (count == numOfThr)
            {
                for (int i =0; i<count;i++)
              {   
                void *k;
                pthread_join(id[i], &k);
    
                complex <int> *p=(complex<int>*)k;
                cout<<real(*p);
                if (imag(*p)>=0)
                {
                    cout<<'+';
                } 
                cout<<imag(*p)<<'i';
                cout<<' ';
                numOfcout++;
                if ((numOfcout) % b == 0)
                {
                    cout<<'\n';
                }   
                
              }
              count = 0;
            }
        }
       
    }
    if (count< numOfThr)
    {
    for (int i =0; i<count;i++)
        {   
                    
            void *k;
            pthread_join(id[i], &k);
    
            complex <int> *p=(complex<int>*)k;
            cout<<real(*p);
            if (imag(*p)>=0)
            {
                cout<<'+';
            } 
            cout<<imag(*p)<<'i';
            cout<<' ';
            numOfcout++;
            if ((numOfcout) % b == 0)
            {
                cout<<'\n';
            }   
        }
    }
  

}