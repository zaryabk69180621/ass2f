#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
using namespace std;
#define IP "127.0.0.1"
int isprime(int p,int q){

if(p<=1){
return false;


}
else if(q<=1){
return true;

}
else{

return (p%q!=0)&&isprime(p,q-1);


}}
int main(){
int clientsock= socket(AF_INET,SOCK_STREAM,0);
sockaddr_in serverad;
serverad.sin_family=AF_INET;
serverad.sin_addr.s_addr=inet_addr(IP);
serverad.sin_port=htons(8080);
int servsocl=connect(clientsock,(const sockaddr*)&serverad,sizeof(serverad));
char mesg[100];
recv(clientsock,mesg,sizeof(mesg),0);
cout<<endl<<"the mesg frome server is "<<mesg;

int n;
cout<<endl<<"enter the orime number"<<endl;
cin>>n;
if(!isprime(n,n-1)){

    cout<<endl<<"entered number is not prime";
    exit(100);
}
send(clientsock,to_string(n).c_str(),to_string(n).length(),0);

char res[100];
recv(clientsock,res,sizeof(res),0);
cout<<endl<<"inside client the recievd next prime is "<<res;

}