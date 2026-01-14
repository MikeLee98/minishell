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

// empty double quotes should create an empty token and be expanded as space
// input:
// echo "" a
// output esperado:
//  a
// output atual:
// a

// input:
// ""
// output esperado:
// command not found
// output atual:
// Error: Failed to parse tokens.


