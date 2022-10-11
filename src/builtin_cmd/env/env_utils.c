/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:39:18 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/11 15:56:45 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	compare(char *one, char *two)
{
	int	i;
	int	len;

	i = 0;
	if (ft_strlen(one) > ft_strlen(two))
		len = ft_strlen(one);
	else
		len = ft_strlen(two);
	while (i < len)
	{
		if (one[i] > two[i])
			return (1);
		else if (one[i] < two[i])
			return (0);
		i++;
	}
	return (0);
}

void	sort_env(t_data *data)
{
	t_env	*trav;
	char	*hold_s;
	char	*hold_v;

	trav = data->l_env;
	if (!trav)
		return ;
	while (trav->next)
	{
		if (compare(trav->sec, trav->next->sec))
		{
			hold_s = trav->sec;
			hold_v = trav->value;
			trav->sec = trav->next->sec;
			trav->value = trav->next->value;
			trav->next->sec = hold_s;
			trav->next->value = hold_v;
			trav = data->l_env;
		}
		else
			trav = trav->next;
	}
}

t_env	*node_allocate(void)
{
	t_env	*node;

	node = (t_env *) malloc(sizeof(t_env));
	if (!node)
		error_malloc();
	node->sec = 0;
	node->value = 0;
	node->next = 0;
	return (node);
}

static void	env_double_ptr_helper(t_data *data, int i)
{
	int		j;
	int		k;
	t_env	*trav;

	i = 0;
	trav = data->l_env;
	while (trav)
	{
		data->env_exec[i] = malloc(sizeof(char) * \
			ft_strlen(trav->sec) + ft_strlen(trav->value) + 1);
		if (!data->env_exec[i])
			error_malloc();
		j = 0;
		k = 0;
		while (trav->sec[k])
			data->env_exec[i][j++] = trav->sec[k++];
		data->env_exec[i][j++] = '=';
		k = 0;
		while (trav->value[k])
			data->env_exec[i][j++] = trav->value[k++];
		data->env_exec[i][j] = 0;
		free_implementation(data, data->env_exec[i]);
		i++;
		trav = trav->next;
	}
	data->env_exec[i] = 0;
}

char	**env_double_ptr(t_data *data)
{
	t_env	*trav;
	int		i;

	i = 0;
	trav = data->l_env;
	while (trav)
	{
		trav = trav->next;
		i++;
	}
	data->env_exec = malloc(sizeof(char *) * i + 1);
	if (!data->env_exec)
		error_malloc();
	env_double_ptr_helper(data, i);
	free_implementation(data, data->env_exec);
	return (data->env_exec);
}
