/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:49:51 by mario             #+#    #+#             */
/*   Updated: 2025/08/02 17:49:23 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	line = NULL;
	ft_read_to_buffer(fd, &line, buffer);
	if (line)
	{
		while (line[i] && line[i] != '\n')
			i++;
		if (line[i] == '\n')
			i++;
		line[i] = '\0';
	}
	ft_trim_buffer(buffer);
	return (line);
}
