ANTOINE:

Dereferencing '$' without issues
Expending a variable that does not exist should return an empty string

`export` need to sort in alphabetical order while env just prints in chronological order
Fix export such that PATH= clears the variable but PATH don't, also check again abou using variables direclty as export args

BUG:

TO DO:

	Environment variables:
		`_` -> Exist but I never update it, idk if it's required by subject ...

	Have a environment variable that you keep updated if it exist
	but also your `our_oldpwd` that you always keep track of (and that you init with OLDPWD)
	the environment variable has priority over `our_oldpwd`


TEST-----------------------------

	`env MY_VAR`
		BASH:	Does nothing
		ME:		Does nothing

	`env MY_VAR=`
		BASH:	Create var with empty val
		ME:		Create var with empty val
			ME:		Does nothing	FIXED

	'echo $dfsdfsf`
		BASH:	Expands bullshit into an empty string
		ME:		Writes the bullshit because I could't find a match

	`export $A_VAR=val`
		BASH:	Expandes A_VAR and use this as the name for a var with value = val
		ME:		SAME

	TEST:	FIXED
		export MY_VAR_A=MY_VAR_B
		export MY_VAR_X=HAHA
		export $MY_VAR_A=$MY_VAR_X

		Results:
			BASH:
				MY_VAR_X=HAHA
				MY_VAR_A=MY_VAR_B
				MY_VAR_B=HAHA
			ME:
				MY_VAR_A=MY_VAR_B
				MY_VAR_X=HAHA
				MY_VAR_B=$MY_VAR_HAHA
		FIXED

TO DO:
	Implement a functioning logic to the get_next_tree() concept


Giga BUG, read line takes too much drug