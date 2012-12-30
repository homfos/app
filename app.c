#include "unp.h"

void dg_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen)
{
	char buf[100];
	int	n;

	for ( ; ; )
	{
		n = Recvfrom(sockfd, buf, 100, 0, pcliaddr, &clilen);

		Sendto(sockfd, buf, n, 0, pcliaddr, clilen);
	}
	
}

void dg_cli(FILE *fp, int sockfd, const struct sockaddr * servaddr, socklen_t servlen)
{
	int	n;
	char	sendbuf[100],	recvbuf[100];

	while (fgets(sendbuf, 100, fp) != NULL)
	{

		Sendto(sockfd, sendbuf, strlen(sendbuf), 0,servaddr, servlen);
		n = Recvfrom(sockfd, recvbuf, 100, 0, NULL, NULL);

		if (fputs(recvbuf, stdout) == EOF)
		{
			err_quit("fputs error");
		}
	}
}
