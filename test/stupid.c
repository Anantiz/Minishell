#include <stdlib.h>
#include <stdio.h>
int	main(int argc, char **argv){int x;
printf("\033[32mtst:%d\033[0m\n",
x=(argc==1?0:atoi(argv[1])));return x;}