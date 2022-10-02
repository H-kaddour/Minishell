/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:52:18 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/02 04:30:50 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_env_of_export(t_env *env)
{
	while (env)
	{
		if (!env->value)
			printf("declare -x %s\n", env->sec);
		else
			printf("declare -x %s=\"%s\"\n", env->sec, env->value);
		env = env->next;
	}
}

int	dup_opt_equal(t_data *data, t_env *env, char *cmd)
{
	int	i;
	int	hold;

	if (data->chk_export_plus == 1)
		hold = ft_strcspn(cmd, "+");
	else
		hold = ft_strcspn(cmd, "=");
	if (check_existence(data, cmd, hold, env))
		return (0);
	env->sec = malloc(sizeof(char) * hold + 1);
	if (!env->sec)
		return (0);
	dup_opt_equal_helper(&env, cmd, &hold);
	i = 0;
	env->value = malloc(sizeof(char) * ft_strlen(&cmd[hold]) + 1);
	if (!env->value)
		return (0);
	while (cmd[hold])
		env->value[i++] = cmd[hold++];
	env->value[i] = 0;
	return (1);
}

void	export_cmd_helper(t_data *data, t_env **trav_e, t_cmd *trav_c, int i)
{
	int		chk;
	t_env	*head;

	head = 0;
	if (!check_export_error(data, trav_c->cmd[i]))
	{
		chk = if_exist_or_not(data, trav_c->cmd[i]);
		if (chk == 1)
			head = node_allocate();
		if (!check_if_equal_or_wrd(trav_c->cmd[i]))
			chk = dup_opt_wrd(data, head, trav_c->cmd[i]);
		else
			chk = dup_opt_equal(data, head, trav_c->cmd[i]);
		if (chk == 1)
		{
			trav_e[0]->next = head;
			trav_e[0] = trav_e[0]->next;
		}
	}
	else
	{
		data->chk_dolla = 1;
		printf("minishell: export: '%s': not a valid identifier\n", \
				trav_c->cmd[i]);
	}
}

void	export_cmd(t_data *data)
{
	int		i;
	t_env	*trav_e;
	t_cmd	*trav_c;

	i = 1;
	trav_e = data->l_env;
	trav_c = data->v_cmd;
	if (!trav_c->cmd[i])
		print_env_of_export(trav_e);
	else
	{
		while (trav_e->next)
			trav_e = trav_e->next;
		while (trav_c->cmd[i])
		{
			data->chk_export_plus = 0;
			export_cmd_helper(data, &trav_e, trav_c, i);
			i++;
		}
	}
	sort_env(data);
}
