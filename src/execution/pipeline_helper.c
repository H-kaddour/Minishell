/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:22:17 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/07 11:00:29 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pipeline_parent_helper(t_data *data, int status, t_cmd *p_trav, \
		t_cmd *trav)
{
	exit_status(&data->chk_dolla, status);
	if (p_trav)
		close(p_trav->tab_pipe[1]);
	close(trav->tab_pipe[0]);
}
