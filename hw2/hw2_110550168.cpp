#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;
#define pii pair<int,int>

int main(){
	map<int,pii> output;

	priority_queue<pii,vector<pii>,greater<pii> > pq;
	vector<priority_queue<pii,vector<pii>,greater<pii>>> process;
	vector<pii> process_mode;
	int n;int m; // # of queue and process
	cin>>n>>m;
	int mode;int quantium;
	for(int i = 0;i < n;i++){
		cin>>mode>>quantium;
		process.push_back(pq);
		process_mode.push_back(make_pair(mode,quantium));
	}

	queue<pii> task;
	map<int,int> bust_list;
	int arrival;int bust;
	for(int i = 0;i < m;i++){
		cin>>arrival>>bust;
		task.push(make_pair(arrival,bust));
		bust_list[arrival]=bust;
	}
	// cout<<"------seperate line--------\n";
	int totaltime = 0;
	for(int i = 0;i < n;i++){
		if(i > 0 && process[i].empty() && ((i + 1)!=n)) continue;
			
		if(process_mode[i].first == 0){
		// pq to <time into pq, arrival>
			if(i == 0){
				while(!task.empty()){
					pii task_cur = task.front();
					task.pop();
					if(totaltime < task_cur.first)totaltime=task_cur.first;
					output[task_cur.first] = make_pair(totaltime-task_cur.first,0);
					totaltime+=bust_list[task_cur.first];
					output[task_cur.first].second = totaltime-task_cur.first;
				}
			}
			else{
				pii task_cur;
				while(!process[i].empty()){
					task_cur = process[i].top();
					process[i].pop();
					
					pii task_input = make_pair(100000000,100000000);
					if(!task.empty()){
						task_input = task.front();
					}
					
					if(bust_list[task_cur.second] + totaltime > task_input.first){
						bust_list[task_cur.second] -= (task_input.first - totaltime);
						totaltime = task_input.first;
						if(i + 1 == n)process[i].push(make_pair(totaltime,task_cur.second));
						else{
							if(process_mode[i+1].first == 0)process[i+1].push(make_pair(totaltime,task_cur.second));
							else if(process_mode[i+1].first == 1)process[i+1].push(make_pair(bust_list[task_cur.second],task_cur.second));
							else if(process_mode[i+1].first == 2)process[i+1].push(make_pair(totaltime,-task_cur.second));
						}
					}
					else{
						totaltime += bust_list[task_cur.second];
						output[task_cur.second].second += totaltime;
						output[task_cur.second].first += totaltime;
					}
					if(totaltime == task_input.first){
						i = -1;
						break;
					}
					else if(process[i].empty() && totaltime < task_input.first){
						break;
					}
				}
			}	
		}
		else if(process_mode[i].first == 1){
		// pq with item <bust,arrival>
			// pii task_cur; (86,88)
			if(i == 0){
				// if(!task.empty()) (86,88)
				pii task_cur = make_pair(task.front().second,task.front().first);
				task.pop();
				process[i].push(task_cur);
				if(totaltime < task_cur.second) totaltime=task_cur.second;
				output[task_cur.second] = make_pair(-task_cur.first-task_cur.second,-task_cur.second);
				
				//cout<<"curtime:"<<totaltime<<endl;
				while(!task.empty() || !process[i].empty()){
					//cout<<"curtime:"<<totaltime<<endl;
					if(!process[i].empty()){
						task_cur = process[i].top();
						process[i].pop();
					} 
					else if(process[i].empty() && n == 1){
						break;
					}
					pii task_input = make_pair(100000000,100000000);
					if(!task.empty()){
						task_input = task.front();
					}
					//cout<<"task_cur  :"<<task_cur.second<<","<<task_cur.first<<"    curtime:"<<totaltime<<endl;
					//cout<<"task_input:"<<task_input.first<<","<<task_input.second<<"    curtime:"<<totaltime<<endl;
					//cout<<"-----"<<endl;
					if(bust_list[task_cur.second] + totaltime > task_input.first){
						bust_list[task_cur.second] -= (task_input.first - totaltime);
						task_cur.first -= (task_input.first - totaltime);
						totaltime = task_input.first;
						if(n == 1){
							process[i].push(task_cur); // need modify
						}
						else if(bust_list[task_cur.second] > task_input.second){
							if(n > 1 && process_mode[i+1].first == 0)process[i+1].push(make_pair(totaltime,task_cur.second)); // still need modify
							else if(n > 1 && process_mode[i+1].first == 1)process[i+1].push(task_cur);
							else if(n > 1 && process_mode[i+1].first == 2)process[i+1].push(make_pair(totaltime,-task_cur.second));
						}
						else if(bust_list[task_cur.second] <= task_input.second){
							if(n > 1) process[i].push(task_cur);
						}
						
						process[i].push(make_pair(task_input.second,task_input.first));
						output[task_input.first] = make_pair(-task_input.first-task_input.second,-task_input.first);
						task.pop();
					}
					else if(bust_list[task_cur.second] + totaltime < task_input.first){
						totaltime += bust_list[task_cur.second];
						output[task_cur.second].second += totaltime;
						output[task_cur.second].first += totaltime;
						if(task_input.first != 100000000 && task_input.second != 100000000){
							if(n == 1 && process[i].empty()){
								process[i].push(make_pair(task_input.second,task_input.first));
								output[task_input.first] = make_pair(-task_input.first-task_input.second,-task_input.first);
								task.pop();
								if(totaltime < task_input.first) totaltime = task_input.first;
							}

							//if(totaltime == task_input.first) break;
						}
						
					}
					else if(bust_list[task_cur.second] + totaltime == task_input.first){
						totaltime += bust_list[task_cur.second];
						output[task_cur.second].second += totaltime;
						output[task_cur.second].first += totaltime;
						if(task_input.first != 100000000 && task_input.second != 100000000){
							if(n == 1 && process[i].empty()){
								process[i].push(make_pair(task_input.second,task_input.first));
								output[task_input.first] = make_pair(-task_input.first-task_input.second,-task_input.first);
								task.pop();
								if(totaltime < task_input.first) totaltime = task_input.first;
							}
	
							process[i].push(make_pair(task_input.second,task_input.first));
							output[task_input.first] = make_pair(-task_input.first-task_input.second,-task_input.first);
							task.pop();
						}
						
					}
					if(process[i].empty() && n > 1)break;
				}
			}
			/*else{
				pii task_cur;
				while(!process[i].empty()){
					task_cur = process[i].top();
					process[i].pop();

					pii task_input = make_pair(10000000,10000000);
					if(!task.empty()){
						task_input = task.front();
					}
					
					if(bust_list[task_cur.second] + totaltime > task_input.first){
						bust_list[task_cur.second] -= (task_input.first - totaltime);
						task_cur.first -= (task_input.first - totaltime);
						process[i].push(task_cur);
						i=-1;
						break;
						
					}
					else{
						totaltime += task_cur.first;
						output[task_cur.second].second += totaltime;
						output[task_cur.second].first += totaltime;
						if(task_input.first != 10000000 && task_input.second != 10000000){
							if(process[i].empty()) i=-1;
						}
					}
				}
			}*/
			else{
				pii task_cur;
				while(!process[i].empty()){
				// cout<<"totaltime:"<<totaltime<<endl;
					task_cur = process[i].top();
					process[i].pop();
					
					pii task_input = make_pair(100000000,100000000);
					if(!task.empty()){
						task_input = task.front();
					}
					
					if(bust_list[task_cur.second] + totaltime > task_input.first){
						bust_list[task_cur.second] -= (task_input.first - totaltime);
						task_cur.first -= (task_input.first - totaltime);
						totaltime = task_input.first;
						if(i + 1 == n)process[i].push(task_cur);
						else{
							if(process_mode[i+1].first == 0)process[i+1].push(make_pair(totaltime,task_cur.second));
							else if(process_mode[i+1].first == 1)process[i+1].push(task_cur);
							else if(process_mode[i+1].first == 2)process[i+1].push(make_pair(totaltime,-task_cur.second));
						}
					}
					else{
						totaltime += bust_list[task_cur.second];
						output[task_cur.second].second += totaltime;
						output[task_cur.second].first += totaltime;
					}
					if(totaltime == task_input.first){
						i = -1;
						break;
					}
					else if(process[i].empty() && totaltime < task_input.first){
						break;
					}
				}
			}
			
		}
		else if(process_mode[i].first == 2){
		// pq with <time into pq,-arrival>, another array store bust time
			if(i == 0){
				pii task_cur = task.front();
				task.pop();
				process[i].push(make_pair(task_cur.first,-task_cur.first));
				totaltime = task_cur.first;
				output[task_cur.first] = make_pair(-task_cur.first-task_cur.second,-task_cur.first);
				
				pii task_input; // pii with <arrival,bust>
				while(!task.empty() || !process[i].empty()){
					if(!process[i].empty()){
						task_cur = process[i].top();
						process[i].pop();
					}
					
					if(bust_list[-task_cur.second] <= process_mode[i].second){
						totaltime += bust_list[-task_cur.second];
						bust_list[-task_cur.second] -= bust_list[-task_cur.second];
						output[-task_cur.second].first += totaltime;
						output[-task_cur.second].second += totaltime;
					}
					else{
						totaltime += process_mode[i].second;
						bust_list[-task_cur.second] -= process_mode[i].second;
						if(n == 1)process[i].push(make_pair(totaltime,task_cur.second));
						else if(n > 1 && process_mode[i+1].first == 0)process[i+1].push(make_pair(totaltime,-task_cur.second));
						else if(n > 1 && process_mode[i+1].first == 1)process[i+1].push(make_pair(bust_list[-task_cur.second],-task_cur.second));
						else if(n > 1 && process_mode[i+1].first == 2)process[i+1].push(make_pair(totaltime,task_cur.second));
					}
					while(!task.empty()){
						task_input = task.front();
						if(task_input.first <= totaltime){
							process[i].push(make_pair(task_input.first,-task_input.first));
							output[task_input.first] = make_pair(-task_input.first-task_input.second,-task_input.first);
							task.pop();
						}
						else if(totaltime < task_input.first && n == 1 && process[i].empty()){
							process[i].push(make_pair(task_input.first,-task_input.first));
							output[task_input.first] = make_pair(-task_input.first-task_input.second,-task_input.first);
							task.pop();
							totaltime = task_input.first;
							break;
						}
						else break;
					}
					if(process[i].empty() && n > 1)break;
				}
			}
			else{
				pii task_cur;
				while(!process[i].empty()){
					task_cur = process[i].top();
					process[i].pop();

					pii task_input = make_pair(100000000,100000000);
					if(!task.empty()){
						task_input = task.front();
					}
					
					int use_time;
					if(process_mode[i].second > task_input.first - totaltime)use_time = task_input.first - totaltime;
					else use_time = process_mode[i].second;
					
					if(bust_list[-task_cur.second] <= use_time){
						totaltime += bust_list[-task_cur.second];
						bust_list[-task_cur.second] -= bust_list[-task_cur.second];
						output[-task_cur.second].first += totaltime;
						output[-task_cur.second].second += totaltime;
					}
					else{
						totaltime += use_time;
						bust_list[-task_cur.second] -= use_time;
						if(i + 1 == n)process[i].push(make_pair(totaltime,task_cur.second));
						else{
							if(process_mode[i+1].first == 0)process[i+1].push(make_pair(totaltime,-task_cur.second));
							else if(process_mode[i+1].first == 1)process[i+1].push(make_pair(bust_list[-task_cur.second],-task_cur.second));
							else if(process_mode[i+1].first == 2)process[i+1].push(make_pair(totaltime,task_cur.second));
						}
					}
					
					if(totaltime == task_input.first){
						i = -1;
						break;
					}
					else if(process[i].empty() && totaltime < task_input.first){
						break;
					}
				}
			}
		}
		
		if(!task.empty() && (i + 1) == n)i = -1; // new add, not sure if is right, need double check
	}
	
	int total_wait = 0;
	int total_turnaround = 0;
	for(map<int,pii>::iterator it = output.begin();it != output.end();it++){
		cout<< it->second.first <<" "<< it->second.second <<"\n";
		total_wait += it->second.first;
		total_turnaround += it->second.second;
	}
	cout<<total_wait<<"\n"<<total_turnaround<<"\n";
	return 0;
}
