// ISSUES





/*
Regarding Child Processes, 

NUMBER 2:
When the sleep command is sent, and CTRL+\ is pressed, the following error message, "^\Quit (core dumped)", 
is not being displyed before a new prompt appears. Also, the new prompt should appear after that message in 
a new line. That would be the correct behaviour of bash, and ours is doing:

minishell$ sleep 3

TOKENS:
[0] Type: WORD            Value: sleep
[1] Type: WORD            Value: 3

TOKENS (after expansion):
[0] Type: WORD            Value: sleep
[1] Type: WORD            Value: 3

TOKENS (after quote removal):
[0] Type: WORD            Value: sleep
[1] Type: WORD            Value: 3

COMMANDS:
[0] Args:
    [0] = sleep
    [1] = 3

^\minishell$
*/





/*
Regarding Heredoc, 

NUMBER 1:
When the cat << command is sent, and CTRL+C is pressed, the following characters should be 
printed in the previour line, before the new prompt, ">^C", and the new prompt should not 
have any adittional new characters, even though they appear to be in INSERT mode and if you 
just start writing they disappear. Also, sometimes two "minishell$ " prompts appear instead 
of just once. That would be the correct behaviour of bash, and ours is doing:

minishell$ cat << EOF

TOKENS:
[0] Type: WORD            Value: cat
[1] Type: REDIR_HEREDOC   Value: <<
[2] Type: WORD            Value: EOF

TOKENS (after expansion):
[0] Type: WORD            Value: cat
[1] Type: REDIR_HEREDOC   Value: <<
[2] Type: WORD            Value: EOF

TOKENS (after quote removal):
[0] Type: WORD            Value: cat
[1] Type: REDIR_HEREDOC   Value: <<
[2] Type: WORD            Value: EOF

COMMANDS:
[0] Args:
    [0] = cat
        Redir: REDIR_HEREDOC EOF (hd_expand: 1)

> a
> b
> c
> 
minishell$ ^C

Note: In the example above, the "^C" should appear after the last '>' character, 
and the string "minishell$ " should have nothing after it.

Here's another example:

minishell$ cat << heredoc

TOKENS:
[0] Type: WORD            Value: cat
[1] Type: REDIR_HEREDOC   Value: <<
[2] Type: WORD            Value: heredoc

TOKENS (after expansion):
[0] Type: WORD            Value: cat
[1] Type: REDIR_HEREDOC   Value: <<
[2] Type: WORD            Value: heredoc

TOKENS (after quote removal):
[0] Type: WORD            Value: cat
[1] Type: REDIR_HEREDOC   Value: <<
[2] Type: WORD            Value: heredoc

COMMANDS:
[0] Args:
    [0] = cat
        Redir: REDIR_HEREDOC heredoc (hd_expand: 1)

> a
minishell$ ^C

Note: In the example above, the "^C" should appear after the character 'a', in 
the string "> a", and the string "minishell$ " should have nothing after it.

Here's the last case:

minishell$ minishell$ cat << heredoc

TOKENS:
[0] Type: WORD            Value: cat
[1] Type: REDIR_HEREDOC   Value: <<
[2] Type: WORD            Value: heredoc

TOKENS (after expansion):
[0] Type: WORD            Value: cat
[1] Type: REDIR_HEREDOC   Value: <<
[2] Type: WORD            Value: heredoc

TOKENS (after quote removal):
[0] Type: WORD            Value: cat
[1] Type: REDIR_HEREDOC   Value: <<
[2] Type: WORD            Value: heredoc

COMMANDS:
[0] Args:
    [0] = cat
        Redir: REDIR_HEREDOC heredoc (hd_expand: 1)

> 
minishell$ minishell$

Note: In the example above, the "^C" should appear after the last '>' character, 
and the string "minishell$ " should only appear once.

NUMBER 2:
When the cat << command is sent, and CTRL+D is pressed, the following error message, 
"bash: warning: here-document at line NUMBER delimited by end-of-file (wanted `DELIMITER')", 
where NUMBER changes according to the current heredoc line in that instance, and DELIMITER 
changes according to the current heredoc delimiter, is not being displyed before a new prompt 
appears. Also, the new prompt should appear after that message in a new line. That would be the 
correct behaviour of bash, and ours is doing:

minishell$ cat << current_delimiter

TOKENS:
[0] Type: WORD            Value: cat
[1] Type: REDIR_HEREDOC   Value: <<
[2] Type: WORD            Value: current_delimiter

TOKENS (after expansion):
[0] Type: WORD            Value: cat
[1] Type: REDIR_HEREDOC   Value: <<
[2] Type: WORD            Value: current_delimiter

TOKENS (after quote removal):
[0] Type: WORD            Value: cat
[1] Type: REDIR_HEREDOC   Value: <<
[2] Type: WORD            Value: current_delimiter

COMMANDS:
[0] Args:
    [0] = cat
        Redir: REDIR_HEREDOC current_delimiter (hd_expand: 1)

> a
> b
> c
> 
a
b
c
minishell$

Note: The warning should appear in the next line right after the last '>' character 
that was displayed. In this case, something like this:

(...)
> b
> c
> 
bash: warning: here-document at line NUMBER delimited by end-of-file (wanted `DELIMITER')
a
b
(...)
*/





/*
For minishell_tester_LucasKuhn:
cd minishell
git clone https://github.com/LucasKuhn/minishell_tester.git minishell_tester_LucasKuhn
cd minishell_tester_LucasKuhn
./tester

———————————— builtins ————————————

Test  40: ❌ cd $PWD hi 
mini exit code = 0
bash exit code = 1
mini error = ()
bash error = ( too many arguments)

———————————— redirects ————————————

Test  73: ❌ cat <"./test_files/infile" | echo hi 
mini exit code = 141
bash exit code = 0

Test  75: ❌ cat <"./test_files/infile_big" | echo hi 
mini exit code = 141
bash exit code = 0

Test  96: ❌ echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye 
mini exit code = 1
bash exit code = 0

———————————— extras ————————————

Test 133: ✅⚠️  $PWD 
mini error = ( Permission denied)
bash error = ( Is a directory)

Test 141: ✅⚠️  ./test_files 
mini error = ( Permission denied)
bash error = ( Is a directory)
*/





/*
For minishell_tester_zstenger93:
cd minishell
git clone https://github.com/zstenger93/42_minishell_tester.git minishell_tester_zstenger93
cd minishell_tester_zstenger93
vim tester.sh
	# Change if you store the tester in another PATH
	export MINISHELL_PATH=../
	export EXECUTABLE=minishell
	RUNDIR=/home/msdmrf/Documents/42lisboa/migusant/common/minishell/minishell_tester_zstenger93

# Change the shell_loop() function to respect the GitHub Repository Instructions
static void	shell_loop(void)
{
	char	*input;
	char	*tmp;
	int		validation_result;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			input = readline("minishell$ ");
		else
		{
			input = get_next_line(STDIN_FILENO);
			if (input)
			{
				tmp = input;
				input = ft_strtrim(tmp, "\n");
				free(tmp);
			}
		}
		if (!input)
			break ;
		validation_result = validate_input(input);
		if (validation_result == 1)
		{
			free(input);
			break ;
		}
		else if (validation_result == 2)
		{
			free(input);
			continue ;
		}
		if (!*input)
		{
			free(input);
			continue ;
		}
		if (isatty(STDIN_FILENO))
			add_history(input);
		process_and_execute(input);
		free(input);
	}
}
*/