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
    cout<<endl<<" i am child1 with pid"<<getpid()<<" and ppid"<<getppid()<<endl;

    char red[100]={'\0'};

    close(pip[1]);
    int b=read(pip[0],red,sizeof(red));
    red[b]='\0';
    reverse(red,b-1);
    close(pip2[0]);
write(pip2[1],red,b);


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
int pip3[2];
if(pipe(pip3)==-1){

    cerr<<"error cant pipe"<<endl;
    exit(100);
}

int pid2=fork();
if(pid2==0){
    cout<<endl<<" i am child2 with pid"<<getpid()<<" and ppid"<<getppid()<<endl;

close(pip3[1]);
char arrx[100]={'\0'};

int l=read(pip3[0],arrx,sizeof(arrx));
arrx[l]='\0';
int fd= open("./file.txt",O_CREAT|O_WRONLY,0666);
if(fd==-1){

    cerr<<"file opening error"<<endl;
    exit(100);
}
write(fd,arrx,l);
close(fd);
exit(100);




}else{
    close(pip3[0]);
write(pip3[1],res,b);
cout<<endl<<" i am parent with pid"<<getpid()<<" and ppid"<<getppid()<<endl;
wait(NULL);





}


}


}