/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:21:19 by otaouil           #+#    #+#             */
/*   Updated: 2021/03/14 16:55:07 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

extern struct s_all	data;

int		ft_dynamic(void)
{
	mlx_hook(data.win.ptr, 17, 1L << 2, ft_close, &data);
	mlx_hook(data.win.ptr, 2, 0, ft_press, &data);
	mlx_hook(data.win.ptr, 3, 0, ft_unpress, &data);
	ft_draw();
	mlx_put_image_to_window(data.mlx.ptr, data.win.ptr, data.img.ptr, 0, 0);
	free(data.img.ptr);
	free(data.img.adr);
	return (0);
}

void	bitmap_header(int fd)
{
	int			file_size;
	int			ofbits;

	ofbits = 54;
	file_size = ofbits + (data.win.y * data.win.x * 4);
	write(fd, "BM", 2);
	write(fd, &file_size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &ofbits, 4);
}

void	dib_header(int fd)
{
	int			bsize;
	int			biplan;
	int			imagesize;
	int			i;
	int			bpp;

	i = 16;
	bpp = 32;
	bsize = 40;
	biplan = 1;
	imagesize = (data.win.y * data.win.x);
	write(fd, &bsize, 4);
	write(fd, &data.win.x, 4);
	write(fd, &data.win.y, 4);
	write(fd, &biplan, 2);
	write(fd, &bpp, 2);
	write(fd, "\0\0\0\0", 4);
	write(fd, &imagesize, 4);
	while (i--)
		write(fd, "\0", 1);
}

void	fill_bmp(int *i, int fd)
{
	int			x;
	int			y;

	y = data.win.y;
	while (--y > 0)
	{
		x = -1;
		while (++x < data.win.x)
		{
			write(fd, &i[y * data.win.x + x], 3);
			write(fd, "\0", 1);
		}
	}
}

int		ft_bitmap(t_all s)
{
	int			fd;
	int			winb;

	winb = ((s.win.x * 24 + 31) / 32) * 4;
	ft_draw();
	fd = open("bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	bitmap_header(fd);
	dib_header(fd);
	fill_bmp((int*)data.img.adr, fd);
	close(fd);
	free(data.img.ptr);
	free(data.img.adr);
	ft_close(&data, 0);
	return (1);
}
