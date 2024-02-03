ANTOINE:

Dereferencing '$' without issues
Expending a variable that does not exist should return an empty string

`export` need to sort in alphabetical order while env just prints in chronological order
Fix export such that PATH= clears the variable but PATH don't, also check again abou using variables direclty as export args

BUG:
	in ZSH:	env -i ./minishell

TO DO:

	Environment variables:
		`SHLVL`
		`_`
	Add them if they don't exist, and give them appropriate value

	OLDPWD, handle it like PATH
	Have a environment variable that you keep updated if it exist
	but also your `our_oldpwd` that you always keep track of (and that you init with OLDPWD)
	the environment variable has priority over `our_oldpwd`
