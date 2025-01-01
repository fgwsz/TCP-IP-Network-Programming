#include<stdio.h>//printf()
#include<unistd.h>//write() read() close()
#include"tcp_socket.h"
void sent_msg_to_client(int server_socket,int queue_size){
    int client_socket=tcp_server_accept(server_socket);
    if(client_socket<0){
        println_socket_error(client_socket);
        return;
    }
    char message[]="0123456789-----";
    write(client_socket,message,sizeof(message));
    close(client_socket);
}
void recv_msg_from_server(int client_socket){
    char buffer[sizeof(unsigned long long)];
    ssize_t message_length=0;
    printf("Message from server:");
    while(1){
        *(unsigned long long*)(buffer)=0;
        message_length=read(client_socket,buffer,sizeof(buffer));
        if(message_length<0){
            break;
        }
        printf("%s",buffer);
        if(message_length==0){
            break;
        }
    }
    printf("\n");
}
int main(int argc,char* argv[]){
    if(argc!=2&&argc!=3){
        printf("TCP Server Usage:%s <port>\n",argv[0]);
        printf("TCP Client Usage:%s <ip> <port>\n",argv[0]);
        return 1;
    }
    if(argc==2){
        return tcp_server(argv[1],5,&sent_msg_to_client);
    }
    return tcp_client(argv[1],argv[2],&recv_msg_from_server);
}
