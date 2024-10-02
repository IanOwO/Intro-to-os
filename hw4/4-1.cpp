#include <iostream>
#include <vector>
using namespace std;

int main(){
	int cache_size;
	int data_size;
	cin>>cache_size;
	cin>>data_size;
	
	int cache[cache_size];
	int visit[cache_size]={0};
	int miss = 0;
	int data;
	int miss_flag = 1;
	
	for (int i = 0;i < data_size;i++){
		miss_flag = 1;
		cin>>data;
		for(int j = 0;j < cache_size;j++){
			if(cache[j] == data && visit[j]){
				miss_flag = 0;
				break;
			}
		}
		/*cout<<i<<":"<<data<<" missflag:"<<miss_flag<<" => ";
		for(int j = 0;j < cache_size;j++){
			cout<<cache[j]<<" ";
		}
		cout<<endl;*/
		if(miss_flag){
			cache[i%cache_size] = data;
			miss++;
			visit[i%cache_size] = 1;
		}
	}
	cout<<"Total Cache Misses:"<<miss;
	return 0;
}
