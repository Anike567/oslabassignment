#include<stdio.h>

int fact(int num){
    if(num < 1){
        return 1;
    }
    return num*fact(num-1);
}
int main(void){
    int n;
    printf("Enter the number to find factorial \n");
  
    scanf("%d",&n);
    printf("%d\n",fact(n));
    return 1;
}