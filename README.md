ANTOINE:

Dereferencing '$' without issues
Expending a variable that does not exist should return an empty string

FIXED:
`cd` and `pwd` need to have predictable behavior when the PATH or any other Environment variable is deleted
When you delete all environment variable, you still need to keep a Basic PWD and PATH

`export` need to sort in alphabetical order while env just prints in chronological order
Fix export such that PATH= clears the variable but PATH don't, also check again abou using variables direclty as export args

FIXED:
`exit` has to take into account any situation where the value isn't a valid int (overflow, char etc...)

When there is:
	A | B | C ...
The last command will somehow never terminate and will wait for someone to close the pipe

TO DO:
	Si PATH n'existe pas au depart, cree un PATH basic en hidden, il sera pas print, mais existe qd meme et tu peu le delete stv


LORIS: