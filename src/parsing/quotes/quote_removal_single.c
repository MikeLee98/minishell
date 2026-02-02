/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal_single.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:37:44 by migusant          #+#    #+#             */
/*   Updated: 2026/02/02 15:48:41 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	copy_single_quoted(char *dest, char *src, int *j, int *i)
{
	(*i)++;
	while (src[*i] && src[*i] != '\'')
		dest[(*j)++] = src[(*i)++];
	if (src[*i] == '\'')
		(*i)++;
}
