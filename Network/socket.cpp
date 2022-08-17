#if 0

//Server
int main()
{
    //Create
    int fd=socket(AF_INET,SOCK_STREAM,0);
    //Bind
    bind(fd,...);
    //Listen
    listen(fd,128);
    //Accept
    accept(fd,...);
    ...
}

//Client
int main(){
    //Create
    fd = socket(AF_INET,SOCK_STREAM, 0);
    //Call Connection
    connect(fd, ...);
    ...
}
#endif