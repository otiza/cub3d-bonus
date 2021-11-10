/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:44:29 by otaouil           #+#    #+#             */
/*   Updated: 2021/03/07 19:11:03 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		ft_namecheck(char *arg, char *ext)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
		i++;
	if ((i > 4 && arg[i - 1] == ext[2] && arg[i - 2] == ext[1])
		&& (arg[i - 3] == ext[0] && arg[i - 4] == '.'))
		return (1);
	return (0);
}

int		ft_strcheck(char *arg, char *str)
{
	int	i;

	i = 0;
	while (arg[i] == str[i])
	{
		if (arg[i] == '\0' && str[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int		ft_unpress(int key, void *param)
{
	if (key == W)
		((t_all*)param)->ply.wlkdir = 0;
	else if (key == D)
		((t_all*)param)->ply.wlkdir2 = 0;
	else if (key == A)
		((t_all*)param)->ply.wlkdir2 = 0;
	else if (key == S)
		((t_all*)param)->ply.wlkdir = 0;
	else if (key == RIGHT)
		((t_all*)param)->ply.trndir = 0;
	else if (key == LEFT)
		((t_all*)param)->ply.trndir = 0;
	else
		return (1);
	return (0);
}

int		ft_press(int key, void *param)
{
	if (key == ESC)
		ft_close(param, 1);
	if (key == W)
		((t_all*)param)->ply.wlkdir = +1;
	if (key == S)
		((t_all*)param)->ply.wlkdir = -1;
	if (key == D)
		((t_all*)param)->ply.wlkdir2 = 1;
	else if (key == A)
		((t_all*)param)->ply.wlkdir2 = -1;
	else if (key == RIGHT)
		((t_all*)param)->ply.trndir = 1;
	else if (key == LEFT)
		((t_all*)param)->ply.trndir = -1;
	return (0);
}
