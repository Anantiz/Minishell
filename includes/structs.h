#include <stddef.h>

/* ################################ */
/* 				ENUM 				*/
/* ################################ */

typedef enum e_token_type
{
	FILE,
	CMD,
	OP,
	VAR,
}t_e_token_type;

typedef enum t_e_op_type
{
	PIPE,
	SEMICOLON,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}t_e_op_type;


/* ################################ */
/* 				TOKENS 				*/
/* ################################ */

typedef struct s_file
{
	char	*file_path;
}t_s_file;

typedef struct s_cmd
{
	char	**args;
}t_s_cmd;

typedef struct s_op
{
	t_e_op_type	op_type;
}t_s_op;

typedef struct s_var
{
	// A chercher dans ENVP
	char	*var_name;
}t_s_var;

/* ############################## */

union u_token
{
	t_s_file	file;
	t_s_cmd		cmd;
	t_s_op		op;
	t_s_var		var;
};

/* Liste Chainée */
typedef struct s_token
{
	t_e_token_type	token_type;
	union u_token	data;

	struct s_token	*next;
}t_s_token;


/* ################################ */
/* 			Main struct 			*/
/* ################################ */

typedef struct s_shell_data
{
	// Shall be initialized at boot then edited when required
	int 		argc;
	char		**env;
	char		**argv;

	// get_line_history	*history;

	t_s_token	*token_list;
}t_shell_data;
