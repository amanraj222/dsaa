#include<bits/stdc++.h>
using namespace std;

class Heap {
    public:
    int arr[101];
    int size;

    Heap() {
        arr[0]=0;
        size=0;
    }
    void insert(int value) {
        //value insert kro end mee
        size=size+1;
        int index=size;
        arr[index]=value;

        //iss value ko place at correct position
        while(index>1) {
            int parentIndex=index/2;
            if(arr[index] > arr[parentIndex]) {
                swap(arr[index],arr[parentIndex]);
                index=parentIndex;
            }
            else {
                break;
            }
        }
    }
    int delete1() {
        int ans=arr[1];
        //replace root node value with last node data
        arr[1]=arr[size];
        size--;

        //place root node ka data on its correct position
        int index=1;
        while(index < size) {
            int left=2*index;
            int right=2*index+1;

            int largest=index;
            if(left < size && arr[largest] < arr[left]) {
                largest=left;
            }
            if(right < size && arr[largest] < arr[right]) {
                largest=right;
            }
            if(largest == index) {
                break;
            }
            else {
                swap(arr[index], arr[largest]);
                index=largest;
            }
        }
        return ans;

    }
};

int main() {
    Heap h;
    h.insert(50);
    h.insert(30);
    h.insert(70);
    h.insert(40);
    h.insert(80);
    h.insert(100);

    for(int i=0;i<=h.size;i++) {
        cout<<h.arr[i]<<" ";
    }
    cout<<"\n";
    int a=h.delete1();
    cout<<a<<"\n";

    for(int i=0;i<=h.size;i++) {
        cout<<h.arr[i]<<" ";
    }


}