/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:50:06 by mario             #+#    #+#             */
/*   Updated: 2025/08/02 17:49:04 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_gnl_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_gnl_strjoin(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*str;

	i = 0;
	j = 0;
	len = ft_gnl_strlen(s1) + ft_gnl_strlen(s2);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (free(s1), NULL);
	while (s1 && s1[i])
		str[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

int	ft_check_newline(char *buffer)
{
	int	i;

	i = -1;
	while (buffer[++i])
	{
		if (buffer[i] == '\n')
			return (1);
	}
	return (0);
}

void	ft_read_to_buffer(int fd, char **line, char *buffer)
{
	int	bytes_read;

	bytes_read = 0;
	if (buffer[0])
		*line = ft_gnl_strjoin(*line, buffer);
	while (!ft_check_newline(buffer))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 1)
			break ;
		buffer[bytes_read] = '\0';
		*line = ft_gnl_strjoin(*line, buffer);
	}
	if (bytes_read == -1)
	{
		free(*line);
		*line = NULL;
		buffer[0] = '\0';
	}
}

void	ft_trim_buffer(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[i])
		buffer[j++] = buffer[i++];
	buffer[j] = '\0';
}
