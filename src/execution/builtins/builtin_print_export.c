#include "../../../includes/minishell.h"

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

void print_export(t_env *env)
{
	char	**envp;
	int i;
	char *value;

	envp = env_to_array(env);
	if (!envp)
		return ;
	sort_array(envp);
	i = 0;
    while (envp[i])
    {
		value = ft_strchr(envp[i], '=');
        if (value)
        {
            *value = '\0';
            if (ft_strcmp(envp[i], "_") != 0)
            	ft_printf("declare -x %s=\"%s\"\n", envp[i], value + 1);
            *value = '=';
        }
        else if (ft_strcmp(envp[i], "_") != 0)
            ft_printf("declare -x %s\n", envp[i]);
		i++;
    }
	free_env_array(envp);
}
