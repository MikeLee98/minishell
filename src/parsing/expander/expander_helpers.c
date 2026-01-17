#include "../../../includes/minishell.h"

char	*append_string(char *result, char *to_add, int free_add)
{
	char	*temp;

	if (!to_add)
	{
		free(result);
		return (NULL);
	}
	temp = ft_strjoin(result, to_add);
	if (free_add)
		free(to_add);
	if (!temp)
	{
		free(result);
		return (NULL);
	}
	free(result);
	return (temp);
}

char	*append_char(char *result, char c)
{
	char	char_str[2];
	char	*temp;

	char_str[0] = c;
	char_str[1] = '\0';
	temp = ft_strjoin(result, char_str);
	if (!temp)
	{
		free(result);
		return (NULL);
	}
	free(result);
	return (temp);
}
