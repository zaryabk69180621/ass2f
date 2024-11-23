#include<iostream>
using namespace std;
void reverse(char arr1[], int size){

char *n= new char[size+1];
for(int i=size-1;i>=0;i--){
cout<<"a";
n[size-1-i]=arr1[i];

}
n[size]='\0';



}
int main(){


char arr1[4]={'a','b','c','\0'};
reverse(arr1,3);


}