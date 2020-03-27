#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>

#include "list.h"
#include "proc.h"
#include "connect.h"

#define TCP "/proc/net/tcp"
#define UDP "/proc/net/udp"
#define TCP6 "/proc/net/tcp6"
#define UDP6 "/proc/net/udp6"

int main(int argc, char** argv){
	int opt, index = 0;
	int c;
	const char *optionstring = "t:u:h";
	static struct option long_options[] = {
		{"tcp", optional_argument, NULL, 't'},
		{"udp", optional_argument, NULL, 'u'},
		{"help", no_argument, NULL, 'h'},
		{0, 0, 0, 0}
	};
	
	list* pList = addPID();

	while(1){
		c = getopt_long(argc, argv, optionstring, long_options, NULL);
		if(c == -1){
			printf("Error in getopt.");
			exit(0);
		}

		switch(c){
			case 't':
				printf("List of TCP services:\n ");
				clist *c = newCList();
				parse(TCP, "ip4", c);
				parse(TCP6, "ip6", c);
				puts("PROTOCOL     LOCAL    LOCAL_PORT     FOREGIN    FORE_PORT    INODE   \n");
				printf("%s       %s    %ld     %s     %ld    %ld\n", "TCP", c->connect->local, c->connect->local_port, c->connect->foregin, c->connect->fore_port, c->connect->inode);
				break;

			case 'u':
				printf("List of UDP services:\n ");

				parse(UDP, "ip4", c);
				parse(UDP6, "ip6", c);
				puts("PROTOCOL     LOCAL    LOCAL_PORT     FOREGIN    FORE_PORT    INODE   \n");
				printf("%s       %s    %ld     %s     %ld    %ld\n", "UDP", c->connect->local, c->connect->local_port, c->connect->foregin, c->connect->fore_port, c->connect->inode);
				break;

			case 'h':
				puts("Usage:\n");
				puts("-t --tcp <service name> : List the states of all the TCP services or the corresponding TCP services.\n");
				puts("-u --udp <service name> : List the states of all the UDP services or the corresponding UDP services.\n");
				puts("-h --help : Show the manual.");

				break;

		}

	}
}

