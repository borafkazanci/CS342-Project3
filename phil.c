#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>

pthread_t tid[5];
pthread_mutex_t mutex;
bool loop = true;
int phils[5];
 
int rand1_5(){
  return rand() % 5 + 1;
}

int rand1_10(){
  return rand() % 10 + 1;
}

void think(int p){
  int time = rand1_10();
  sleep(time);
}

void eat(int p){
  int time = rand1_5();
  sleep(time);
}

void hold(int p){
  
}

void release(int p){
  
}

void philosopher(void* data){
  int i = (int*) data;
  printf("Phil: %d\n", i);
  while(loop){
		think(i);
		hold(i);
		eat(i);
		release(i);
  }
}

int main(){

  if (pthread_mutex_init(&mutex, NULL) != 0){
    perror("\n mutex init is failed \n");
    exit(-1);
  }

	for(int i = 0; i < 5; i++){
		if(pthread_create(&(tid[i]), NULL, philosopher, (int *) i) != 0){
			perror("\n thread creation is failed \n");
    	exit(-1);
		}
	}

	for(int i = 0; i < 5; i++){
		pthread_join(tid[i], NULL);		
	}
	pthread_mutex_destroy(&mutex);
  return 0;
}