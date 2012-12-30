#include "unp.h"

int main(int argc, char **argv)
{
	int 	sockfd;
	struct	sockaddr_in	cliaddr;

	if (argc != 2)
	{
		err_quit("usage: udpclit <IPADDRESS>");
	}

	memset(&cliaddr, 0, sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &cliaddr.sin_addr);

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	dg_cli(stdin, sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

	exit(0);
}
