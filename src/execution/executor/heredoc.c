#include "../../../includes/minishell.h"

int open_temp_heredoc_file(char *delimiter)
{
    char    filename[64];
    int     fd;
    char    *line;

    ft_memset(filename, 0, 64);
    ft_strcpy(filename, "/tmp/minishell_heredoc_");
    ft_itoa(getpid(), filename + ft_strlen(filename));
    fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0)
        return (-1);
    while (1)
    {
        ft_printf("> ");
        line = get_next_line(0);
        if (!line)
            break;
        if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
        {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    lseek(fd, 0, SEEK_SET);
    unlink(filename);
    return (fd);
}
