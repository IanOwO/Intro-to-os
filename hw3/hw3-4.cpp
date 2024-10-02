#include <iostream>
#include <cstdint>
#include <vector>
#include <string.h>
#include <thread>

using namespace std;

int n, m;
vector<uint64_t> subsets;
uint64_t one = static_cast<uint64_t>(1), global_count = 0;

int cur_thread = 0; // thread that has created

int par1[8];
uint64_t par2[8];

int countlist[8];

void solve(int index, uint64_t current,int sol_idx,int tid) {
    if (index == m) {
        if (current == (one << n) - 1){
	        countlist[tid]++;
	    }
    }
    else if(sol_idx != index) {
        solve(index + 1, current, sol_idx, tid);
        solve(index + 1, current | subsets[index], sol_idx, tid);
    }
    else if(sol_idx == index){
        par1[cur_thread] = index+1;
        par2[cur_thread] = current;
        par1[cur_thread+1] = index+1;
        par2[cur_thread+1] = (current | subsets[index]);
        cur_thread+=2;
        return;
	}
}

int main(int argc, char* argv[]) {
	int thread_num;
	
	for (int i = 0;i < argc;i++){
		if(strcmp(argv[i],"-t") == 0){
			thread_num = atoi(argv[i+1]);
			break;
		}
	}

	int sol_idx; // the time to create thread
	switch(thread_num){
	case 1:
		sol_idx = -1;
		break;
	case 2:
		sol_idx = 0;
		break;
	case 4:
		sol_idx = 1;
		break;
	case 8:
		sol_idx = 2;
		break;
	default:
		cout<<"thread num err"<<endl;
		return 0;
	}
	
    cin >> n >> m;

    subsets.resize(m);
    for (int i = 0; i < m; i++) {
        int p, temp;
        cin >> p;
        for (int j = 0; j < p; j++) {
            cin >> temp;
            subsets[i] |= (one << temp);
        }
    }
	
    solve(0, 0, sol_idx, 0);
    thread t[8];
    if(thread_num > 1){
		for (int i = 0; i < thread_num; i++)
			t[i] = thread(solve, par1[i], par2[i],sol_idx,i);
		for (int i = 0; i < thread_num; i++){
			t[i].join();
			global_count += countlist[i];
		}
    }
    else global_count += countlist[0];
	
    cout << global_count << endl;
    return 0;
}
