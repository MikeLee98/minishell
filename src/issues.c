// ISSUES





// marioro2@c1r11s2:~/minishell$ export a="ls -l"
// marioro2@c1r11s2:~/minishell$ a
// a: command not found
// marioro2@c1r11s2:~/minishell$ $a
// total 104
// drwxr-xr-x 2 marioro2 2025_lisbon    25 dez 22 16:53 includes
// drwxrwxr-x 5 marioro2 2025_lisbon    83 dez 22 17:34 libft
// -rw-r--r-- 1 marioro2 2025_lisbon  5420 dez 22 16:53 Makefile
// -rwxr-xr-x 1 marioro2 2025_lisbon 93016 dez 22 17:34 minishell
// drwxr-xr-x 4 marioro2 2025_lisbon    38 dez 22 17:34 objects
// drwxr-xr-x 4 marioro2 2025_lisbon    38 dez 22 16:53 src
// -rw-r--r-- 1 marioro2 2025_lisbon   631 dez  3 20:59 valgrind.supp
// marioro2@c1r11s2:~/minishell$ echo ola >$a
// bash: $a: ambiguous redirect
// marioro2@c1r11s2:~/minishell$
// flags separadas
// investigar export de variaveis com espacos
// split por espacos no export para comandos





// Regarding Prompt,

// NUMBER 1:
// CTRL+C signal (130) is being overwritten somewhere in the code.

// minishell$ a^C
// minishell$ echo $?

// TOKENS:
// [0] Type: WORD            Value: echo
// [1] Type: WORD            Value: $?

// TOKENS (after expansion):
// [0] Type: WORD            Value: echo
// [1] Type: WORD            Value: 0

// TOKENS (after quote removal):
// [0] Type: WORD            Value: echo
// [1] Type: WORD            Value: 0

// COMMANDS:
// [0] Args:
//     [0] = echo
//     [1] = 0

// 0
// minishell$





// Regarding Child Processes, 

// NUMBER 1:
// When the sleep command is sent, and CTRL+C is pressed, a double shell is being displayed, 
// instead of only one. That would be the correct behaviour of bash, and ours is doing:

// minishell$ sleep 3

// TOKENS:
// [0] Type: WORD            Value: sleep
// [1] Type: WORD            Value: 3

// TOKENS (after expansion):
// [0] Type: WORD            Value: sleep
// [1] Type: WORD            Value: 3

// TOKENS (after quote removal):
// [0] Type: WORD            Value: sleep
// [1] Type: WORD            Value: 3

// COMMANDS:
// [0] Args:
//     [0] = sleep
//     [1] = 3

// ^C
// minishell$ minishell$

// NUMBER 2:
// When the sleep command is sent, and CTRL+\ is pressed, the following error message, "^\Quit (core dumped)", 
// is not being displyed before a new prompt appears. Also, the new prompt should appear after that message in 
// a new line. That would be the correct behaviour of bash, and ours is doing:

// minishell$ sleep 3

// TOKENS:
// [0] Type: WORD            Value: sleep
// [1] Type: WORD            Value: 3

// TOKENS (after expansion):
// [0] Type: WORD            Value: sleep
// [1] Type: WORD            Value: 3

// TOKENS (after quote removal):
// [0] Type: WORD            Value: sleep
// [1] Type: WORD            Value: 3

// COMMANDS:
// [0] Args:
//     [0] = sleep
//     [1] = 3

// ^\minishell$





// Regarding Heredoc, 

// NUMBER 1:
// When the cat << command is sent, and CTRL+C is pressed, the following characters should be 
// printed in the previour line, before the new prompt, ">^C", and the new prompt should not 
// have any adittional new characters, even though they appear to be in INSERT mode and if you 
// just start writing they disappear. Also, sometimes two "minishell$ " prompts appear instead 
// of just once. That would be the correct behaviour of bash, and ours is doing:

// minishell$ cat << EOF

// TOKENS:
// [0] Type: WORD            Value: cat
// [1] Type: REDIR_HEREDOC   Value: <<
// [2] Type: WORD            Value: EOF

// TOKENS (after expansion):
// [0] Type: WORD            Value: cat
// [1] Type: REDIR_HEREDOC   Value: <<
// [2] Type: WORD            Value: EOF

// TOKENS (after quote removal):
// [0] Type: WORD            Value: cat
// [1] Type: REDIR_HEREDOC   Value: <<
// [2] Type: WORD            Value: EOF

// COMMANDS:
// [0] Args:
//     [0] = cat
//         Redir: REDIR_HEREDOC EOF (hd_expand: 1)

// > a
// > b
// > c
// > 
// minishell$ ^C

// Note: In the example above, the "^C" should appear after the last '>' character, 
// and the string "minishell$ " should have nothing after it.

// Here's another example:

// minishell$ cat << heredoc

// TOKENS:
// [0] Type: WORD            Value: cat
// [1] Type: REDIR_HEREDOC   Value: <<
// [2] Type: WORD            Value: heredoc

// TOKENS (after expansion):
// [0] Type: WORD            Value: cat
// [1] Type: REDIR_HEREDOC   Value: <<
// [2] Type: WORD            Value: heredoc

// TOKENS (after quote removal):
// [0] Type: WORD            Value: cat
// [1] Type: REDIR_HEREDOC   Value: <<
// [2] Type: WORD            Value: heredoc

// COMMANDS:
// [0] Args:
//     [0] = cat
//         Redir: REDIR_HEREDOC heredoc (hd_expand: 1)

// > a
// minishell$ ^C

// Note: In the example above, the "^C" should appear after the character 'a', in 
// the string "> a", and the string "minishell$ " should have nothing after it.

// Here's the last case:

// minishell$ minishell$ cat << heredoc

// TOKENS:
// [0] Type: WORD            Value: cat
// [1] Type: REDIR_HEREDOC   Value: <<
// [2] Type: WORD            Value: heredoc

// TOKENS (after expansion):
// [0] Type: WORD            Value: cat
// [1] Type: REDIR_HEREDOC   Value: <<
// [2] Type: WORD            Value: heredoc

// TOKENS (after quote removal):
// [0] Type: WORD            Value: cat
// [1] Type: REDIR_HEREDOC   Value: <<
// [2] Type: WORD            Value: heredoc

// COMMANDS:
// [0] Args:
//     [0] = cat
//         Redir: REDIR_HEREDOC heredoc (hd_expand: 1)

// > 
// minishell$ minishell$

// Note: In the example above, the "^C" should appear after the last '>' character, 
// and the string "minishell$ " should only appear once.

// NUMBER 2:
// When the cat << command is sent, and CTRL+D is pressed, the following error message, 
// "bash: warning: here-document at line NUMBER delimited by end-of-file (wanted `DELIMITER')", 
// where NUMBER changes according to the current heredoc line in that instance, and DELIMITER 
// changes according to the current heredoc delimiter, is not being displyed before a new prompt 
// appears. Also, the new prompt should appear after that message in a new line. That would be the 
// correct behaviour of bash, and ours is doing:

// minishell$ cat << current_delimiter

// TOKENS:
// [0] Type: WORD            Value: cat
// [1] Type: REDIR_HEREDOC   Value: <<
// [2] Type: WORD            Value: current_delimiter

// TOKENS (after expansion):
// [0] Type: WORD            Value: cat
// [1] Type: REDIR_HEREDOC   Value: <<
// [2] Type: WORD            Value: current_delimiter

// TOKENS (after quote removal):
// [0] Type: WORD            Value: cat
// [1] Type: REDIR_HEREDOC   Value: <<
// [2] Type: WORD            Value: current_delimiter

// COMMANDS:
// [0] Args:
//     [0] = cat
//         Redir: REDIR_HEREDOC current_delimiter (hd_expand: 1)

// > a
// > b
// > c
// > 
// a
// b
// c
// minishell$

// Note: The warning should appear in the next line right after the last '>' character 
// that was displayed. In this case, something like this:

// (...)
// > b
// > c
// > 
// bash: warning: here-document at line NUMBER delimited by end-of-file (wanted `DELIMITER')
// a
// b
// (...)