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

int N = 10, n = 0, salida = 0, entrada = 0;
int* arr = new int[N];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int main(){

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
        sleep(2);
        pthread_mutex_unlock(&mutex);
    }
}

