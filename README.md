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


BUG:
	If a file fails to open, it kills the whole command line and not just the one function


08/02/24
BUG:
	cat > file1 > file2

	FIXED :HEredoc ferme pas


	IF I have time

	echo "text" > file1 > file2
		Even tho you only write to file2, you will create both

BUGGY INPUT:
	&+$
	wgpb'n o;g'pkf

	pwd-> says (NULL)


# ######################################################################
# ######################################################################
# ######################################################################

# THE SUPER RECAP

	&+$ 	wtf ?

cmd > f1 > f2 done
	Parsing:
		Don't fucking crash pls
	Exec:
		open them all

Pre-parsing:
	Look for invalid input
		-Unclosed quote       done
		-Leading and Trailing pipes		done
		-Trailing redir					done
		-Uneven '&' or "&&&&" and if somehow there is "|||||" , do something with it done
Parsing:
	-remake a split (ls          -l) 'ls' '            -l'
	-Genreally, fix, uninitialized values.
	-Fix :
		2 redir de suite
		redir and empty + pipe marche pas
Exec:
	-Handle erros better (cleaner messages)
	-Heredoc, Expand variables.


Global:
	Clean the code
	Comprendre TOUT le code, pour etre pres a corriger direct