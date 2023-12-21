#include "includes/minishell.h"

int	main()
{
	t_s_token	token;

	token.token_type = CMD;
	char **args = {"cat", "-e", NULL};
	token.text_data.cmd_args = args;

	t_s_token	token_2;

	token_2.token_type = FILE;
	token.text_data.file_path = "File path";


	if (token.token_type == FILE)
	{
		print(token.text_data.file_path);
	}
	else if (token.token_type)
}