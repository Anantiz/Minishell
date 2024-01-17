/* TEST */
# define _POSIX_C_SOURCE 199309L
# include <signal.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
#include <pthread.h>

int g_sig = 0;


/* Relay signal value into our sig */
void	our_sig_handl(int sig)
{
	g_sig = sig;
	write(1, "SIGINT\n", 7);
	fflush(stdout);
}

void	register_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = our_sig_handl;
	sa.sa_sigaction = NULL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SIGINT;
	sigaction(SIGINT, &sa, NULL);
}

void	*kill_child(void *pid_)
{
	int pid = *(int*)pid_;
	sleep(1);
	printf("Killing child\n");
	kill(pid, SIGINT);
	return (NULL);
}

int	main()
{

	int pid = fork();
	register_signals();
	if (pid == 0)
	{
		printf("Child Born\n");
		sleep(5);
		printf("Child:\n\tg_sig: %d\n", g_sig);
		fflush(stdout);
	}
	else
	{
		printf("Parent Born\n");
		int wstatus = 0;
		pthread_t pthread;
		pthread_create(&pthread, NULL, kill_child, (void *)&pid);
		int ret = waitpid(pid, &wstatus, 0);
		printf("Parent\n\tRet: %d\tpid: %d\n\tWstatus: %d\n\tg_sig: %d\n", ret, pid,wstatus, g_sig);
		fflush(stdout);
	}
	return (0);
}