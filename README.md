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

	Joseph_shell:~/Documents/Minishell|☭ ls /bin | grep ls'
==1274474== Invalid read of size 1
==1274474==    at 0x10CDD2: quote_handler (pre_parsing_2.c:26)
==1274474==    by 0x10C9C6: pre_parsing (pre_parsing.c:33)
==1274474==    by 0x10AED8: parse_line (parsing.c:38)
==1274474==    by 0x1098CE: sesion_routine (session_loop.c:84)
==1274474==    by 0x10996D: session_start (session_loop.c:105)
==1274474==    by 0x1095A4: main (main.c:28)
==1274474==  Address 0x4b74217 is 5 bytes after a block of size 2 alloc'd
==1274474==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1274474==    by 0x113B9A: mem_manager_new_node (mem_manager_op.c:32)
==1274474==    by 0x1131EC: safe_as_fuck_malloc (mem_manager.c:33)
==1274474==    by 0x113290: our_malloc (mem_manager.c:59)
==1274474==    by 0x10B5E7: get_op (parsing_utils.c:39)
==1274474==    by 0x10B1EA: ft_strtok (get_token.c:97)
==1274474==    by 0x10AEB6: parse_line (parsing.c:35)
==1274474==    by 0x1098CE: sesion_routine (session_loop.c:84)
==1274474==    by 0x10996D: session_start (session_loop.c:105)
==1274474==    by 0x1095A4: main (main.c:28)
==1274474==
