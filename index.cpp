#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>
using namespace std;

void reverse(char arr1[], int size){

char *n= new char[size+1];
for(int i=size-1;i>=0;i--){

n[size-1-i]=arr1[i];

}
n[size]='\0';
for(int i=0;i<=size;i++){
arr1[i]=n[i];

}


}

int main(){

int pip[2], pip2[2];
if(pipe(pip)==-1|| pipe(pip2)==-1){

    cout<<endl<<"error cant create pipe"<<endl;
exit(101);
}
int pid= fork();
if(pid==0){
    char red[100]={'\0'};

    close(pip[1]);
    int b=read(pip[0],red,sizeof(red));
    red[b]='\0';
    reverse(red,b-1);
    close(pip2[0]);
write(pip2[1],red,sizeof(red));


}
else{
char arr1[]="message from parent";
close(pip[0]);

write(pip[1],arr1,sizeof(arr1));
close(pip2[1]);
char res[100]={'\0'};
int b=read(pip2[0],res,sizeof(res));
res[b]='\0';
cout<<endl<<endl<<"inside parent "<<res;



}


}