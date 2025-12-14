#include "../../../includes/minishell.h"

static void    free_env_array(char **array)
{
    int i;

    if (!array)
        return;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

static void sort_array(char **arr)
{
    int     i;
    int     j;
    char    *tmp;

    i = 0;
    while (arr[i])
    {
        j = i + 1;
        while (arr[j])
        {
            if (ft_strcmp(arr[i], arr[j]) > 0)
            {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

static char    *join_key_value(char *key, char *value)
{
    char    *tmp;
    char    *res;

    tmp = ft_strjoin(key, "=");
    if (!tmp)
        return (NULL);
    res = ft_strjoin(tmp, value);
	free(tmp);
	if (!res)
		return (NULL);
    return (res);
}

static char    **env_to_array(t_env *env)
{
    char    **array;
    int     count;
    int     i;
	t_env   *head;

	head = env;
    count = 0;
    while (env)
    {
        count++;
        env = env->next;
    }
    array = malloc(sizeof(char *) * (count + 1));
    if (!array)
        return (NULL);
    i = 0;
	env = head;
    while (env)
    {
        array[i] = join_key_value(env->key, env->value);
		if (!array[i])
		{
			free_env_array(array);
			return (NULL);
		}
        i++;
        env = env->next;
    }
    array[i] = NULL;
    return (array);
}

void print_export(t_env *env)
{
	char	**array;
	int i;
	char *value;

	array = env_to_array(env);
	if (!array)
		return ;
	sort_array(array);
	i = 0;
    while (array[i])
    {
		value = ft_strchr(array[i], '=');
        if (value)
        {
            *value = '\0';
            if (ft_strcmp(array[i], "_") != 0)
            	ft_printf("declare -x %s=\"%s\"\n", array[i], value + 1);
            *value = '=';
        }
        else if (ft_strcmp(array[i], "_") != 0)
            ft_printf("declare -x %s\n", array[i]);
		i++;
    }
	free_env_array(array);
}
