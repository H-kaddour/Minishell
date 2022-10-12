/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:38:44 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/12 12:01:56 by hkaddour         ###   ########.fr       */
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
		//free(sp[i]);
		free_implementation(data, sp[i]);
		i++;
	}
	//free(sp);
	//unset kldsjfkds still leak
	//free_implementation(data, sp);
}
