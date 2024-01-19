// /* TEST */
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
# include <pthread.h>
# include <errno.h>

int our_g_sig = 0;

/* Relay signal value into our sig */
void	our_sig_handl(int sig)
{
	our_g_sig = sig;
	write(1, "SIGINT\n", 7);
	fflush(stdout);
}

void	register_signals(void)
{
	// struct sigaction	sa;

	// sa.sa_handler = our_sig_handl;
	// sa.sa_sigaction = NULL;
	// sigemptyset(&sa.sa_mask);
	// sa.sa_flags = SIGINT;
	// sigaction(SIGINT, &sa, NULL);
	signal(SIGINT, our_sig_handl);
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
	register_signals();
	int pid = fork();

	if (pid == -1)
	{
		perror("fork() error");
		return (1);
	}

	if (pid == 0)
	{
		printf("Child Born\n");
		sleep(15);
		printf("Child received signal :\n\tg_sig: %d\n", our_g_sig);
		fflush(stdout);
	}
	else
	{
		printf("Parent Born\n");

		pthread_t pthread;
		pthread_create(&pthread, NULL, kill_child, (void *)&pid);

		int wstatus = 0;
		int ret = waitpid(pid, &wstatus, 0);\

		printf("Parent\n\tRet: %d\tpid: %d\n\tWstatus: %d\n\tg_sig: %d\n", ret, pid,wstatus, our_g_sig);
		fflush(stdout);
	}
	return (0);
}
