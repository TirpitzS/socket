#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include "err.h"

#define MAXLINE 4096

int main(int argc, char *argv[])
{
	int ss = -1;
	int conn = -1;
	//int n;
	int t = 0;
	struct sockaddr_in serv;
  char buf[MAXLINE];

	if ((ss = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	 err_exit(1,"create socket error");
	bzero(&serv, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(22222);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	if ((t = bind(ss, (struct sockaddr *) &serv, sizeof(serv))) < 0)
    err_exit(1, "bind error");
	listen(ss, 10);
	while(1)
	{
		if ((conn = accept(ss, (struct sockaddr *)NULL, NULL))< 0)
      return -1;
    read(conn, buf, sizeof(buf));
    printf("request:%s\n", buf);
    write(conn, buf, sizeof(buf));
    close(conn);
	}
	close(ss);
}
