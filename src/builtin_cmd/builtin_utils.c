/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:38:44 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/13 09:42:42 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_sp(t_data *data, char **sp)
{
	int	i;

	i = 0;
	free_implementation(data, sp);
	while (sp[i])
	{
		free_implementation(data, sp[i]);
		i++;
	}
}
