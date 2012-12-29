#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>
#include <unistd.h>

#define MAX 100
#define SERV_PORT 6677

void echo_to(int fd);
void send_to(FILE *fp, int fd);

int max(int a, int b);
