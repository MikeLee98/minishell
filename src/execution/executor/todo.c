//remove builtin_needs_parent
//corrigir o ft_exit
//verificar exit codes
//escrever para o stderror com ft_putstr_fd
//transformar builtins em ints
//exits para falhas de malloc
//concatenar values no export key+=value

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

// marioro2@c1r11s2:~/minishell$ export a=">"
// marioro2@c1r11s2:~/minishell$ echo ola >$a
// -----------------> cria ficheiro > com "ola" detro

// >export key ----> env 0 
// >export key= ----> env key=
// >export key=1 ----> env key=1

// >export key ----> export key
// >export key= ----> env key=""
// >export key=1 ----> env key="1"