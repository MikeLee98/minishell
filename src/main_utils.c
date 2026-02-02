/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:18:33 by migusant          #+#    #+#             */
/*   Updated: 2026/02/02 16:10:38 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	get_unclosed_quote_type(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (!str[i])
				return (quote);
			i++;
		}
		else
			i++;
	}
	return (0);
}

static void	print_unclosed_quote_error(char quote)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(quote, 2);
	ft_putstr_fd("'\n", 2);
}

int	validate_input(char *input)
{
	char	unclosed_quote;

	if (!input)
	{
		printf("exit\n");
		return (1);
	}
	unclosed_quote = get_unclosed_quote_type(input);
	if (unclosed_quote)
	{
		print_unclosed_quote_error(unclosed_quote);
		return (2);
	}
	return (0);
}
