// // /* TEST */
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
# include <string.h>
# include <sys/stat.h>
#include "../includes/libft.h"


#include <stdio.h>

int main(void)
{
    int i, j, n;

    for (i = 0; i < 11; i++) {
        for (j = 0; j < 10; j++) {
            n = 10 * i + j;
            if (n > 108) break;
            printf("\033[%dm %3d\033[m", n, n);
        }
        printf("\n");
    }
    return 0;
}