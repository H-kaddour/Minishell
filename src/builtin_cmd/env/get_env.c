/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 23:17:12 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/11 14:39:53 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*get_sec(char *str)
{
	int		i;
	int		eqal;
	char	*ptr;

	i = 0;
	eqal = ft_strcspn(str, "=");
	ptr = malloc(sizeof(char) * eqal + 1);
	if (!ptr)
		error_malloc();
	while (i < eqal)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

static void	allocate_all_nodes(t_data *data)
{
	int		i;
	t_env	*head;
	t_env	*next;
	char	*hold;

	i = 1;
	head = node_allocate();
	data->l_env = head;
	while (data->env[i])
	{
		hold = get_sec(data->env[i]);
		if (!ft_strcmp(hold, "OLDPWD"))
			i++;
		else
		{
			next = node_allocate();
			head->next = next;
			head = head->next;
			i++;
		}
		free_implementation(data, hold);
	}
}

static void	env_shlvl(t_data *data)
{
	t_env	*env;
	t_env	*shlvl;

	env = getenv_addr(data, "SHLVL");
	if (env)
		env_shlvl_helper(data, env);
	else
	{
		shlvl = node_allocate();
		shlvl->sec = ft_strdup("SHLVL");
		shlvl->value = ft_strdup("1");
		if (data->l_env)
		{
			env = data->l_env;
			while (env->next)
				env = env->next;
			env->next = shlvl;
			sort_env(data);
		}
		else
			data->l_env = shlvl;
	}
}

static void	fill_nodes_env(t_data *data, t_env **env, int i)
{
	int	j;
	int	k;

	j = 0;
	while (data->env[i][j] && data->env[i][j] != '=')
		j++;
	env[0]->sec = malloc(sizeof(char) * j + 1);
	if (!env[0]->sec)
		error_malloc();
	j = 0;
	while (data->env[i][j] && data->env[i][j] != '=')
	{
		env[0]->sec[j] = data->env[i][j];
		j++;
	}
	env[0]->sec[j] = 0;
	j++;
	env[0]->value = malloc(sizeof(char) * (ft_strlen(data->env[i]) + 1) - j);
	if (!env[0]->value)
		error_malloc();
	k = 0;
	while (data->env[i][j] && data->env[i][j] != 0)
		env[0]->value[k++] = data->env[i][j++];
	env[0]->value[k] = 0;
	env[0] = env[0]->next;
}

void	get_env(t_data *data)
{
	int		i;
	char	*hold;
	t_env	*env;

	allocate_all_nodes(data);
	i = 0;
	env = data->l_env;
	while (data->env[i])
	{
		hold = get_sec(data->env[i]);
		free_implementation(data, hold);
		if (ft_strcmp(hold, "OLDPWD"))
			fill_nodes_env(data, &env, i);
		i++;
	}
	env_shlvl(data);
}
