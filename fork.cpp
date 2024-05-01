#include<iostream>
#include<unistd.h>
using namespace std;
int main(void){
        int a=10;
        if(fork() == 0){
                cout<<++a;   
         }
         cout<<--a;
        return 0;
}
