#include "../../../includes/minishell.h"

void setup_exec_signals(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}
