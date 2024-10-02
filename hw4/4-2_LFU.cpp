#include <iostream>
#include <vector>
using namespace std;

int main(){
	int line;
	int k;
	int data_size;
	int data;
	int how_many_set;
	
	cin>>line;
	cin>>k;
	cin>>data_size;
	
	how_many_set = line/k;
	int cache[line];
	int visit[line];
	int miss = 0;
	for(int i = 0;i < line;i++){
		visit[i] = -1;
		cache[i] = 0;
	}
	
	for(int i = 0;i < data_size;i++){
		int min = 1000000000;
		int index;
		int hit_flag = 0;
		
		cin>>data;

		for(int j = 0;j < line;j++){
			if(visit[j] != -1 && cache[j] == data){
				hit_flag = 1;
				index = j;
				break;				
			}
		}
		
		if(hit_flag == 0){
			for(int j = (i%how_many_set)*k;j < ((i%how_many_set)+1)*k;j++){
				if(visit[j] == -1){
					min = visit[j];
					index = j;
					break;
				}
				
				if(visit[j] < min && visit[j] != -1){
					min = visit[j];
					index = j;
				}
			}
		
			cache[index] = data;

			visit[index] = 1;
			miss++;
		}
		else{
			visit[index]++;
		}
	}
	cout<<"Total Cache Misses:"<<miss;
	return 0;
}
