#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

using std::cout;
using std::endl;

void agregar(int x);
int sacar();
void imprimir();
void* producir(void*);
void* consumir(void*);

int N = 10, n = 0, salida = 0, entrada = 0;
int* arr = new int[N];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int main(){
    int state1,state2;
    pthread_t thread1,thread2,thread3,thread4,thread5;
    pthread_create(&thread1, NULL, producir, NULL);
    pthread_create(&thread2, NULL, producir, NULL);
    pthread_create(&thread3, NULL, producir, NULL);
    pthread_create(&thread4, NULL, consumir, NULL);
    pthread_create(&thread5, NULL, consumir,NULL);
    
    while(true){
        pthread_mutex_lock(&mutex);
        imprimir();        
        pthread_mutex_unlock(&mutex);
        sleep(5);
    }

	return 0;
}

void agregar(int x){
	if(n < N){
        arr[entrada] = x;
        n++;
        entrada = (entrada+1)%N;
    }else{
    	pthread_cond_wait(&cond,&mutex);
    	agregar(x);
    }
}

int sacar(){
	if(n>0){
		int x = arr[salida];
        salida = (salida+1)%N;
        n--;
        pthread_cond_signal(&cond);
        return x;
	}
	return -1;
}

void imprimir(){
    for(int i = 0; i < n; i++){
        cout << arr[(salida + i)%N] << " ";
    }
    cout << endl;
}

void* producir(void* params){
    srand(time(NULL));
    while(true){
        int x = rand()%100+1;
        pthread_mutex_lock(&mutex);
        agregar(x);
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
}
void* consumir(void* params){
	while(true){
        pthread_mutex_lock(&mutex);
		sacar();
        pthread_mutex_unlock(&mutex);
        sleep(3);	
	}
}

