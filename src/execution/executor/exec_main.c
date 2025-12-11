#include "../../../includes/minishell.h"

cmd[0]:		command = "ls"
         	args = ["ls", "-l", NULL]
redir[0]:	redirs -> lista com <, >, >>, << (heredoc)
         	next == pipe para próximo comando

cmd[1]:  	command = "grep"
         	args = ["grep", "txt", NULL]
redir[1]:   redirs -> lista com <, >, >>, << (heredoc)
		 	next == NULL
