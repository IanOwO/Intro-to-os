#include <iostream>
#include <mutex>
#include <thread>
#include <string.h>
using namespace std;

int n, global_count = 0;
mutex globol_count_mutex;
int thread_num;

int countlist[8];

bool is_prime(int num) {
    if (num == 1) return false;

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void func(int st,int iter, int tid){
	for (int i = st; i <= iter; i++) {
	    if (is_prime(i)) {
	    	countlist[tid]++;
	    }
	}
}

int main(int argc, char* argv[]) {
    cin >> n;

	for (int i = 0;i < argc;i++){
		if(strcmp(argv[i],"-t") == 0){
			thread_num = atoi(argv[i+1]);
			break;
		}
	}
	
	int seperate = n/thread_num;
	if(n%thread_num != 0){
		seperate++;
	}
	
	thread t[8];
	for (int i = 0; i < thread_num; i++){
		int prod = i*seperate;
    	t[i] = thread(func, prod + 1, prod + seperate, i);
    	if(i+1+1 == thread_num){
    		t[i+1] = thread(func, prod + seperate + 1, n, i + 1);
    		break;
    	}
    }
    
	for (int i = 0; i < thread_num; i++){
    	t[i].join();
    	global_count += countlist[i];
    }

    cout << global_count << endl;
    return 0;
}
