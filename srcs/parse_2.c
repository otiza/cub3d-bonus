/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:55:52 by otaouil           #+#    #+#             */
/*   Updated: 2021/03/15 11:33:29 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

extern struct s_all	data;

char	*ft_slab(t_all *s, char *line, int i, int x)
{
	char	*slab;
	int		j;

	if (!(slab = malloc(sizeof(char) * x + 1)))
		return (NULL);
	j = 0;
	while (j < x)
	{
		if (j >= ft_slablen(line) || line[i] == ' ')
			slab[j++] = '3';
		else if ((line[i] == '0' || line[i] == '1' || line[i] == 'N'
			|| (line[i] == '2' && (++s->map.spr))) || (line[i] == 'E'
			|| line[i] == 'S' || line[i] == 'W' || line[i] == '3'))
			slab[j++] = line[i];
		else
		{
			free(slab);
			return (NULL);
		}
		(i)++;
	}
	slab[j] = '\0';
	return (slab);
}

int		ft_map(t_all *s, char *line)
{
	char	**tmp;
	int		j;

	s->err.m = 1;
	if (!(tmp = malloc(sizeof(char *) * (s->map.y + 2))) || s->err.l == 1)
		return (-11);
	j = -1;
	if (s->map.x < ft_slablen(line))
		s->map.x = ft_slablen(line);
	while (++j < s->map.y)
	{
		tmp[j] = ft_slab(s, s->map.tab[j], 0, s->map.x);
		free(s->map.tab[j]);
	}
	if ((tmp[s->map.y] = ft_slab(s, line, 0, s->map.x)) == NULL)
	{
		free(tmp);
		return (-12);
	}
	tmp[s->map.y + 1] = NULL;
	if (s->map.y > 0)
		free(s->map.tab);
	s->map.tab = tmp;
	s->map.y++;
	return (1);
}

int		ft_mapcheck(t_all *s)
{
	int		i;
	int		j;

	i = -1;
	while (++i < s->map.y && (j = -1))
	{
		while (++j < s->map.x)
			if (s->map.tab[i][j] == '0' || s->map.tab[i][j] == 'N' ||
				s->map.tab[i][j] == 'E' || s->map.tab[i][j] == 'S' ||
				s->map.tab[i][j] == 'W' || s->map.tab[i][j] == '2')
			{
				if (i == 0 || j == 0 || i == s->map.y - 1 ||
					j == s->map.x - 1 ||
					s->map.tab[i][j + 1] == '\0' ||
					s->map.tab[i + 1][j] == '\0' ||
					s->map.tab[i + 1][j] == '3' ||
					s->map.tab[i][j + 1] == '3' ||
					s->map.tab[i - 1][j] == '\0' ||
					s->map.tab[i][j - 1] == '\0' ||
					s->map.tab[i - 1][j] == '3' ||
					s->map.tab[i][j - 1] == '3')
					return (-1);
			}
	}
	return (1);
}

int		ft_parcheck(t_all *s)
{
	if (s->win.x <= 0 || s->win.y <= 0)
		return (ft_strerror(-14));
	else if ((s->tex.n == NULL || s->tex.s == NULL || s->tex.e == NULL)
			|| (s->tex.w == NULL || s->tex.i == NULL))
		return (ft_strerror(-15));
	else if (s->tex.c == NONE || s->tex.f == NONE)
		return (ft_strerror(-16));
	else if (s->err.p == 0)
		return (ft_strerror(-17));
	else if (s->err.p > 1)
		return (ft_strerror(-18));
	else if (ft_mapcheck(s) == -1)
		return (ft_strerror(-19));
	return (1);
}
