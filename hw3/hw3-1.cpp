#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore.h>
using namespace std;

static mutex io_mutex;
// static int a = 0;
static sem_t s[100];
void count(int index) {
  int num = 1000000;
  while (num--) {}
  sem_wait(&s[index]);
  {
    lock_guard<mutex> lock(io_mutex);
	  // while (a < index){}
    cout << "I'm thread " << index << ", local count: 1000000\n";
    // a++;
    if(index < 99)sem_post(&s[index+1]);
    else sem_post(&s[0]);
  }
}

int main(void) {
  thread t[100];
  for (int i = 0; i < 100; i++){
  	if(i==0)sem_init(&s[i],0,1);
  	else sem_init(&s[i],0,0);
  }
  for (int i = 0; i < 100; i++)
    t[i] = thread(count, i);
  for (int i = 0; i < 100; i++)
    t[i].join();
}
