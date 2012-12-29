#include "unp.h"

#define PORT 6677

int main(void)
{
	int	listenfd, newfd;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		 perror("socket error");
		 return -1;
	}

	struct sockaddr_in	cliaddr, servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	socklen_t addlen = sizeof(servaddr);

	if (bind(listenfd, (struct sockaddr *)(&servaddr), addlen) == -1)
	{
		perror("bind error");
		exit -1;
	}

	if (listen(listenfd, 10) == -1)
	{
		perror("listen error");
		exit(-1);
	}
	
	int client[FD_SETSIZE];
	int maxi = 0, i, maxfd = listenfd, sockfd, n, nready;
	char buf[100];

	for (i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;

	fd_set	allset, rset;
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);

	for ( ; ; )
	{
		rset = allset;
		if ((nready = select(maxfd + 1, &rset, NULL, NULL, NULL)) == -1)
		{
			perror("select error");
			exit(-1);
		}

		if (FD_ISSET(listenfd, &rset))
		{
			if ((newfd = accept(listenfd, (struct sockaddr *)&cliaddr, &addlen)) == -1)
			{
				
					perror("accpet error");
					exit(-1);
				
			}	
			printf("new connect\n");

			for (i = 0; i < FD_SETSIZE; i++)
				if (client[i] == -1)
				{
					client[i] = newfd;
					break;
				}

			FD_SET(client[i], &allset);

			if (i > maxi)
				maxi = i;

			if (newfd > maxfd)
				maxfd = newfd;

			if (--nready <= 0)
				continue;
			
		}

		for (i = 0; i <= maxi; i++)
		{
			printf("next for\n");
			if ((sockfd = client[i]) < 0)
				continue;

			if (FD_ISSET(client[i], &rset))
			{
				if ((n = read(sockfd, buf, 100)) < 0)
				{
					perror("read error");
					exit(-1);
				}
				else if (n == 0)
				{
					printf("socket close\n");
					client[i] = -1;
					FD_CLR(sockfd, &allset);
				}
				else 
				{
					if (write(sockfd, buf, n) == -1)
					{
						perror("write error");
						exit(-1);
					}
				}
				if (--nready <= 0)
					break;
			}

		}
	}

}
