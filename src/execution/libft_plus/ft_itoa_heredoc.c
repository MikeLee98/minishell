#include "../../../includes/minishell.h"

static int intlen(long n)
{
    int len;

    len = 0;
    if (n <= 0)
        len++;
    while (n != 0)
    {
        n /= 10;
        len++;
    }
    return (len);
}

void ft_itoa_heredoc(int n, char *buffer)
{
    long nb;
    int len;

    nb = n;
    len = intlen(nb);
    buffer[len] = '\0';
    if (nb < 0)
    {
        buffer[0] = '-';
        nb = -nb;
    }
    if (nb == 0)
    {
        buffer[0] = '0';
        return ;
    }
    while (nb > 0)
    {
        buffer[--len] = '0' + (nb % 10);
        nb /= 10;
    }
}