/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 05:04:12 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/06 05:07:10 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_parsing_red(t_cmd *parse)
{
	t_red		*red;

	red = parse->redirect;
	while (red)
	{
		if (red->file)
			free(red->file);
		if (red->determiner)
			free(red->determiner);
		free(red);
		red = red->next;
	}
}

void	free_parsing_cmd(t_data *data)
{
	t_cmd		*parse;
	int			i;

	parse = data->v_cmd;
	while (parse)
	{
		i = 0;
		while (parse->cmd[i])
		{
			free(parse->cmd[i]);
			i++;
		}
		free(parse->cmd);
		if (parse->redirect)
			free_parsing_red(parse);
		free(parse->tab_pipe);
		free(parse);
		parse = parse->next;
	}
	data->v_cmd = 0;
}
