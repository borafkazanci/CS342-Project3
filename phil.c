#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>

#define LEFT (pid - 1) % 5
#define RIGHT (pid + 1) % 5
#define EAT 1
#define THINK 2

pthread_t tid[5];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
bool loop = true;
int phils[5];
 
int rand1_5(){
  return rand() % 5 + 1;
}

int rand1_10(){
  return rand() % 10 + 1;
}

void think(int pid){
  int time = rand1_10();
  sleep(time);
}

void eat(int pid){
  printf("philosopher %d started eating now.\n", pid);
  int time = rand1_5();
  sleep(time);
  printf("philosopher %d finished eating now.\n", pid);
}

void hold(int pid){
  int left = LEFT;
  if (left < 0)
    left += 5;
  
  pthread_mutex_lock(&mutex);

  while(phils[left] == EAT || phils[RIGHT] == EAT)
    pthread_cond_wait(&cond, &mutex);

  phils[pid] = EAT;

  pthread_mutex_unlock(&mutex);
}

void release(int pid){
  pthread_mutex_lock(&mutex);
  phils[pid] = THINK;
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
}

static void *philosopher(void* data){
  int* i = (int *) &data;
  srand(*i);
  printf("Phil: %d\n", *i);
  while(loop){
		think(*i);
		hold(*i);
		eat(*i);
		release(*i);
  }

  pthread_exit(NULL);
}

int main(){
	for(int i = 0; i < 5; i++){
    int* pid = (int *) i;
		if(pthread_create(&(tid[i]), NULL, philosopher, (int *) pid) != 0){
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