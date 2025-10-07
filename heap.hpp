#include <vector>
#include <algorithm>

struct Heap{
    int size;
    std::vector<int> pq;
    bool (*comp)(int, int);
    void heapify_down(int i){
        while(2*i+1<size){
            if(!comp(pq[i], pq[2*i+1])){
                std::swap(pq[i], pq[2*i+1]);
                i=2*i+1;
            }
            else if(2*i+2<size && !comp(pq[i], pq[2*i+2])){
                std::swap(pq[i], pq[2*i+2]);
                i=2*i+2;
            }
            else break;
        };
    }
    void buildheap(){
        for(int i=size/2-1;i>=0;i--){
            heapify_down(i);
        }
    }

};
