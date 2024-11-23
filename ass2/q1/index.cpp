#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string>
using namespace std;

int isprime(int p,int q){

if(p<=1){
return false;


}
else if(q<=1){
return true;

}
else{

return (p%q!=0)&&isprime(p,q-1);


}



}
int findnp(int num){

int temp= ++num;

while(!isprime(temp,temp-1)){

temp++;



}
return temp;




}
int main(){

int servsocket=socket(AF_INET,SOCK_STREAM,0);
if(servsocket==-1){

perror("socket");
exit(101);

}

sockaddr_in serveradd;
serveradd.sin_family=AF_INET;
serveradd.sin_addr.s_addr=INADDR_ANY;
serveradd.sin_port=htons(8080);

if(bind(servsocket,(const sockaddr*)&serveradd,sizeof(serveradd))==-1){

cout<<endl<<"error cant bind";
exit(101);

}

if(listen(servsocket,5)==-1){

cout<<endl<<"cant listen";
exit(101);

}

fd_set currentsocket, readysocket;
FD_ZERO(&currentsocket);
FD_SET(servsocket,&currentsocket);

while(true){

// since select is destructive, so make a copy

readysocket=currentsocket;



sockaddr_in clientadd;
socklen_t clientaddsize;
if(select(FD_SETSIZE,&readysocket,NULL,NULL,NULL)<0){

cerr<<endl<<"error selecting";
exit(100);

}
//going trhough all possible fds
for(int i=0;i<FD_SETSIZE;i++){

    if(FD_ISSET(i,&readysocket)){
        if(i==servsocket){
cout<<endl<<"new connection request";
            //means that there is a new connection
            int clsocket=accept(servsocket,( sockaddr*)&clientadd,&clientaddsize);
            if(clsocket==-1){

                    cerr<<endl<<"error accepting client connection";
                    exit(101);

            }
              FD_SET(clsocket,&currentsocket);  

            string mesg="hi welcome to the server";

            send(clsocket,mesg.c_str(),mesg.length(),0);

        }else{

cout<<endl<<"older connection became ready";
            char arr1[100];
        
recv(i,arr1,sizeof(arr1),0);

int num= stoi(string(arr1));
cout<<"so the given no is"<<num;

int np=findnp(num);
cout<<endl<<"here"<<np;
string res=to_string(np);
cout<<endl<<"computeed result"<<res;
send(i,res.c_str(),res.length(),0);
FD_CLR(i,&currentsocket);
close(i);




        }


    }


}


}





}