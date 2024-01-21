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
	write(1, "\nINTERECEPT SIGINT\n", 20);
	fflush(stdout);
}

void	register_signals(void)
{
	signal(SIGINT, our_sig_handl);
}

void	*kill_child(void *pid_)
{
	int pid = *(int*)pid_;
	sleep(1);
	printf("Killing child\n");
	kill(pid, SIGSEGV);
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
		// sleep(4);
		// printf("Child Wake-up:\tg_sig: %d\n", our_g_sig);fflush(stdout);
		// exit(our_g_sig);
		/* yes*/
		execve("/bin/yes", (char *[]){"yes", NULL}, NULL);
	}
	else
	{
		pthread_t pthread;
		pthread_create(&pthread, NULL, kill_child, (void *)&pid);
		int ret = 0;
		int wstatus = 0;
		ret = waitpid(pid, &wstatus, 0);
		if (our_g_sig == SIGINT)
		{
			printf("Relaying SIGINT to child\n");fflush(stdout);
			kill(pid, SIGINT);
			ret = waitpid(pid, &wstatus, 0);
		}
		printf("Parent:\tRet: %d\tpid: %d\tWstatus: %d\tparent_g_sig: %d\n\n", ret, pid,wstatus, our_g_sig);fflush(stdout);

		if (WIFEXITED(wstatus))
            printf("Child exited normally with status: %d\n", WEXITSTATUS(wstatus));
        else if (WIFSIGNALED(wstatus))
            printf("Child exited due to signal: %d\n", WTERMSIG(wstatus));
	}
    printf("Parent exited normally\n");
	return (0);
}
