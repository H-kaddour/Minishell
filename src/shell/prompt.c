/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 05:29:55 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/07 20:55:49 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	color_desicision(t_data *data, char **clr)
{
	if (data->chk_dolla == 0)
		*clr = CLR1;
	else
		*clr = CLR1ERR;
}

static void	get_me_env_addresses(t_data *data, char **path_h, char **path_pw)
{
	t_env	*pwd;
	t_env	*home;

	pwd = getenv_addr(data, "PWD");
	if (pwd)
		*path_pw = pwd->value;
	else
		*path_pw = data->pwd_of_mysys;
	home = getenv_addr(data, "HOME");
	if (home)
		*path_h = home->value;
	else
		*path_h = getenv("HOME");
}

static void	no_home_path_or_not_in_home(t_data *data, char *clr1, char *path)
{
	char	*tmp;

	tmp = ft_strjoin(path, CLR2);
	data->prompt = ft_strjoin(clr1, tmp);
	free(tmp);
	return ;
}

static void	home_path_and_dir_path(t_data *data, char *clr1, \
		char *home, char *pwd)
{
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	if (ft_strlen(pwd) > ft_strlen(home))
	{
		len = ft_strlen(home);
		data->prompt = malloc(sizeof(char) * len + 3);
		if (!data->prompt)
			error_malloc();
		data->prompt[i++] = '~';
		while (pwd[len])
			data->prompt[i++] = pwd[len++];
		data->prompt[i] = 0;
		tmp = ft_strjoin(data->prompt, CLR2);
		free(data->prompt);
		data->prompt = ft_strjoin(clr1, tmp);
		free(tmp);
	}
	else if (ft_strlen(pwd) == ft_strlen(home))
		no_home_path_or_not_in_home(data, clr1, "~");
}

void	prompt_changer(t_data *data)
{
	char	*path_h;
	char	*path_pw;
	char	*clr1;

	color_desicision(data, &clr1);
	get_me_env_addresses(data, &path_h, &path_pw);
	if (!path_h)
	{
		no_home_path_or_not_in_home(data, clr1, path_pw);
		return ;
	}
	if (!ft_strncmp(path_pw, path_h, ft_strlen(path_h)))
		home_path_and_dir_path(data, clr1, path_h, path_pw);
	else
		no_home_path_or_not_in_home(data, clr1, path_pw);
}
