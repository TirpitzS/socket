#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include "err.h"

#define MAXLINE 4096
/*
void sig_child(int signo)
{
	pid_t pid;
	int stat;
	while ((pid = waitpid(-1, &stat, WNOHANG)) >= 0)
	{
		//printf("child %d terminated\n", pid);
		return;
	}
}
*/

void ProcessTask(void *arg)
{
	int n;
	int connect = *(int *)arg;
	char buf[4096] = {0};
	n = read(connect, buf, sizeof(buf));
	printf("%s\n", buf);
	n = write(connect, buf, sizeof(buf));
	close(connect);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	int ss = -1;
	int conn = -1;
	//int n
	int t = 0;
	struct sockaddr_in serv;
  char buf[MAXLINE];
	pid_t pid;

	/*signal(SIGCHLD, SIG_IGN);*/
	if ((ss = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	 err_exit(1,"create socket error");
	bzero(&serv, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(22222);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	if ((t = bind(ss, (struct sockaddr *) &serv, sizeof(serv))) < 0)
    err_exit(1, "bind error");
	listen(ss, 10);
	/*
	while(1)
	{
		if ((conn = accept(ss, (struct sockaddr *)NULL, NULL))< 0)
      return -1;
		pid = fork();
		if (pid < 0)
			err_sys("fork error");
		else if (pid == 0)
		{
			close(ss);
			read(conn, buf, sizeof(buf));
			printf("request:%s\n", buf);
			write(conn, buf, sizeof(buf));
			close(conn);
			exit(0);
		}
		else{
    	close(conn);
		}
	}*/
	while(1)
	{
		conn = accept(ss, (struct sockaddr *)NULL, NULL);
		if (conn < 0)
			continue;
		if ((pthread_create(&newthread, NULL, ProcessTask, &conn)) != 0)
			continue;
	}
	close(ss);
}
