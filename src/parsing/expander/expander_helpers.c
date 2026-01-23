#include "../../../includes/minishell.h"

char	*get_env_value(char *var_name)
{
	char	*value;

	if (!var_name || !var_name[0])
		return (ft_strdup(""));
	else if (ft_strncmp(var_name, "?", 2) == 0)
		return (ft_itoa(shell()->exit_code));
	else if (ft_strlen(var_name) == 1 && !ft_isalnum(var_name[0])
		&& var_name[0] != '_')
		return (ft_strdup(""));
	value = ft_getenv(shell()->env, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

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
