#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H
//套接字错误
enum SocketError{
    SOCKET_CREATE_ERROR     =-1,//创建套接字时的错误
    SOCKET_BIND_ERROR       =-2,//绑定套接字地址信息时的错误
    SOCKET_LISTEN_ERROR     =-3,//服务器端打开监听时的错误
    SOCKET_ACCEPT_ERROR     =-4,//服务器端接收请求时的错误
    SOCKET_CONNECT_ERROR    =-5,//客户端发送连接请求时的错误
    SOCKET_PARSE_IP_ERROR   =-6,//套接字解析IP地址时的错误
    SOCKET_PARSE_PORT_ERROR =-7 //套接字解析端口号时的错误
};
//打印套接字错误信息并换行
//input@socket_error:套接字错误码
extern void println_socket_error(enum SocketError socket_error);
//创建一个TCP服务器端套接字
//input@port:端口号
//input@queue_size:等待队列长度
//output:
//  成功时返回tcp_socket的文件描述符
//  失败时返回(<0)enum SocketError
extern int tcp_server_socket(char const* port,int queue_size);
//得到发送连接请求的客户端套接字文件描述符
//input@server_socket:服务器端套接字文件描述符
//output:
//  成功时返回client socket的文件描述符
//  失败时返回(<0)enum SocketError
extern int tcp_server_accept(int server_socket);
//创建一个TCP客户端套接字
//input@server_ip:服务器端的IPv4地址
//input@server_port:服务器端口号
//output:
//  成功时返回tcp_socket的文件描述符
//  失败时返回(<0)enum SocketError
extern int tcp_client_socket(char const* server_ip,char const* server_port);
//创建一个TCP服务器端
//input@port:端口号
//input@queue_size:等待队列长度
//input@func:服务器端业务逻辑函数
//output:
//  成功时返回0
//  失败时返回(<0)enum SocketError
extern int tcp_server(
    char const* port
    ,int queue_size
    ,void(*func)(int server_socket,int queue_size)
);
//创建一个TCP客户端
//input@server_ip:服务器端的IPv4地址
//input@server_port:服务器端口号
//input@func:客户端业务逻辑函数
//output:
//  成功时返回0
//  失败时返回(<0)enum SocketError
extern int tcp_client(
    char const* server_ip
    ,char const* server_port
    ,void(*func)(int client_socket)
);
#endif//TCP_SOCKET_H
