#include "../../../includes/minishell.h"

// if builtin AND not piped:
//     run_builtin_in_parent()
// else:
//     fork and execve
