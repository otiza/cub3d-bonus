/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:28:25 by otaouil           #+#    #+#             */
/*   Updated: 2021/03/14 16:27:26 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

struct s_all	data;

void	ft_draw(void)
{
	plyupdate();
	if ((data.img.ptr = mlx_new_image(data.mlx.ptr,
		data.win.x, data.win.y)) == NULL)
		return ;
	data.img.adr = mlx_get_data_addr(data.img.ptr,
		&data.img.fsh, &data.img.n, &data.img.m);
	render3d();
	sprites();
}

int		ft_init2(char *cub, int bmp)
{
	data.map.x = 0;
	data.map.y = 0;
	data.map.spr = 0;
	data.err.l = 0;
	data.tex.c = NONE;
	data.tex.f = NONE;
	data.mlx.ptr = mlx_init();
	if (config(&data, cub) == -1)
		return (ft_close(&data, 0));
	if ((data.win.ptr = mlx_new_window(data.mlx.ptr, data.win.x,
		data.win.y, "cub3D")) == NULL)
		return (ft_close(&data, 0));
	if (bmp == 1)
		return (ft_bitmap(data));
	
	mlx_loop_hook(data.mlx.ptr, ft_dynamic, 0);
	mlx_loop(data.mlx.ptr);
	return (0);
}

void	ft_init(char *cub, int bmp)
{
	data.mlx.ptr = NULL;
	data.img.ptr = NULL;
	data.img.adr = NULL;
	data.win.x = 0;
	data.win.y = 0;
	data.img.fsh = 0;
	data.err.n = 0;
	data.err.m = 0;
	data.err.p = 0;
	data.map.ts = 64;
	data.map.tab = NULL;
	data.tex.n = NULL;
	data.tex.s = NULL;
	data.tex.e = NULL;
	data.tex.w = NULL;
	data.tex.i = malloc(sizeof(unsigned int *) * 5);
	data.spr = NULL;
	data.rays = NULL;
	ft_init2(cub, bmp);
}

int		main(int ac, char **av)
{
	/*if (ac == 3 && ft_namecheck(av[1], "cub") && ft_strcheck(av[2], "--save"))
		ft_init(av[1], 1);*/
	if (ac == 2 && ft_namecheck(av[1], "cub"))
		ft_init(av[1], 0);
	else
		write(2, "Error : Invalid arguments\n", 26);
	return (0);
}
