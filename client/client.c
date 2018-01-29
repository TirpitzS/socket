#include <stdio.h>
#include <getopt.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include "err.h"

#define MAXLINE (2048)
extern char *optarg;
extern int opterr;

#define USAGE "usage:client -i ip -p port -m msg\ndefault:\nip:0.0.0.0\n:port:22222\nmsg:hello world"

void usage(void)
{
  printf("%s\n", USAGE);
}

int ParameterHandle(const int arg, char **args, char *ip, unsigned short *port, char *msg)
{
  int pp = 22222;
  char c;
  struct option opts[] = {
    {"ip", required_argument, NULL, 'i'},
    {"port", required_argument, NULL, 'p'},
    {"msg", required_argument, NULL, 'm'},
    {"help", required_argument, NULL, 'h'},
    {0,0,0,0}
  };

  while((c = getopt_long(arg,args,"i:p:m:h",opts,NULL)) != -1)
  {
    switch(c)
    {
      case 'i':
        strcpy(ip, optarg);
        break;
      case 'p':
        pp = atoi(optarg);
        if (pp>0&&pp<65536)
          *port = (unsigned )pp;
        break;
      case 'm':
        strcpy(msg, optarg);
        break;
      case 'h':
        usage();
        return -1;
      default:
        break;
    }
  }
  return 0;
}

int main(int argc, char *argv[])
{
  unsigned short port = 22222;
  char ip[16]="0.0.0.0";
  char msg[MAXLINE] = "hello world";
  char res[MAXLINE] = {0};

  struct sockaddr_in serv;
  int sockfd;
  fork();
  if (ParameterHandle(argc, argv, ip, &port, msg) != 0)
    err_exit(1, USAGE);
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    err_exit(1,"create socket error");
  bzero(&serv, sizeof(serv));
  serv.sin_family = AF_INET;
  serv.sin_port = htons(port);
  if (inet_pton(AF_INET, ip, &serv.sin_addr)<0)
    err_exit(1,"error");

  if (connect(sockfd, (struct sockaddr *)&serv, sizeof(serv)) <0)
    err_exit(1,"connect error");

  write(sockfd, msg, MAXLINE);
  bzero(res, sizeof(res));
  read(sockfd, res, MAXLINE);
  printf("responce:%s\n", res);
  close(sockfd);
}
