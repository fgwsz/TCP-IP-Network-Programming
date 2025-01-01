#include<stdlib.h>//atoi()
#include<stdio.h>//printf()
#include<string.h>//memset()
#include<sys/socket.h>//socket() bind() listen() accept()
#include<netinet/in.h>//sockaddr_in{} sockaddr{}
#include<unistd.h>//close()
#include<arpa/inet.h>//htonl() htons() inet_aton()
#include"tcp_socket.h"
void println_socket_error(enum SocketError socket_error){
    switch(socket_error){
        case SOCKET_CREATE_ERROR    :{printf("socket() error!\n"  );break;}
        case SOCKET_BIND_ERROR      :{printf("bind() error!\n"    );break;}
        case SOCKET_LISTEN_ERROR    :{printf("listen() error!\n"  );break;}
        case SOCKET_ACCEPT_ERROR    :{printf("accept() error!\n"  );break;}
        case SOCKET_PARSE_IP_ERROR  :{printf("parse ip error!\n"  );break;}
        case SOCKET_PARSE_PORT_ERROR:{printf("parse port error!\n");break;}
    }
}
int tcp_server_socket(char const* port,int queue_size){
    int server_socket;
    if((server_socket=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))==-1){
        return SOCKET_CREATE_ERROR;
    }
    struct sockaddr_in server_address;
    memset(&server_address,0,sizeof(server_address));
    server_address.sin_family=AF_INET;
    server_address.sin_addr.s_addr=htonl(INADDR_ANY);
    int server_port=atoi(port);
    if(server_port<=0||server_port>65535){
        close(server_socket);
        return SOCKET_PARSE_PORT_ERROR;
    }
    server_address.sin_port=htons(server_port);
    if(
        bind(
            server_socket
            ,(struct sockaddr*)&server_address
            ,sizeof(server_address)
        )==-1
    ){
        close(server_socket);
        return SOCKET_BIND_ERROR;
    };
    if(listen(server_socket,queue_size)==-1){
        close(server_socket);
        return SOCKET_LISTEN_ERROR;
    }
    return server_socket;
}
int tcp_server_accept(int server_socket){
    struct sockaddr_in client_address;
    socklen_t client_address_length=sizeof(client_address);
    int client_socket=accept(
        server_socket
        ,(struct sockaddr*)&client_address
        ,&client_address_length
    );
    if(client_socket==-1){
        return SOCKET_ACCEPT_ERROR;
    }
    return client_socket;
}
int tcp_client_socket(char const* server_ip,char const* server_port){
    int client_socket;
    if((client_socket=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))==-1){
        return SOCKET_CREATE_ERROR;
    }
    struct sockaddr_in server_address;
    memset(&server_address,0,sizeof(server_address));
    server_address.sin_family=AF_INET;
    if(!inet_aton(server_ip,&(server_address.sin_addr))){
        close(client_socket);
        return SOCKET_PARSE_IP_ERROR;
    }
    int port=atoi(server_port);
    if(port<=0||port>65535){
        close(client_socket);
        return SOCKET_PARSE_PORT_ERROR;
    }
    server_address.sin_port=htons(port);
    if(
        connect(
            client_socket
            ,(struct sockaddr*)&server_address
            ,sizeof(server_address)
        )==-1
    ){
        close(client_socket);
        return SOCKET_CONNECT_ERROR;
    };
    return client_socket;
}
int tcp_server(
    char const* port
    ,int queue_size
    ,void(*func)(int server_socket,int queue_size)
){
    int server_socket=tcp_server_socket(port,queue_size);
    if(server_socket<0){
        println_socket_error(server_socket);
        return server_socket;
    }
    (*func)(server_socket,queue_size);
    close(server_socket);
    return 0;
}
int tcp_client(
    char const* server_ip
    ,char const* server_port
    ,void(*func)(int client_socket)
){
    int client_socket=tcp_client_socket(server_ip,server_port);
    if(client_socket<0){
        println_socket_error(client_socket);
        return client_socket;
    }
    (*func)(client_socket);
    close(client_socket);
    return 0;
}
