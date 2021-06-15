/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trhee <trhee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 18:19:52 by trhee             #+#    #+#             */
/*   Updated: 2021/06/15 18:41:34 by trhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw(t_all *s)
{
	t_ray	ray;
	t_hit	hit;

	ray.x = 0;
	ray.y = 0;
	ray.i = 0;
	ray.stepx = 0;
	ray.stepy = 0;
	hit.h = 0;
	hit.side = 0;
	s->ray = ray;
	s->hit = hit;
	ft_screen(s);
	mlx_put_image_to_window(s->mlx.ptr, s->win.ptr, s->img.ptr, 0, 0);
	free(s->img.ptr);
	free(s->img.adr);
}

int		ft_cubed(t_all s, char *cub)
{
	t_pos	pos;
	t_dir	dir;

	pos.x = 0;
	pos.y = 0;
	dir.x = 0;
	dir.y = 0;
	s.pos = pos;
	s.dir = dir;
	s.mlx.ptr = mlx_init();
	if (ft_parse(&s, cub) == -1)
		return (ft_close(&s, 0));
	s.win.ptr = mlx_new_window(s.mlx.ptr, s.win.x, s.win.y, "cub3D");
	ft_draw(&s);
	mlx_hook(s.win.ptr, 2, 0, ft_key, &s);
	mlx_hook(s.win.ptr, 17, 0, ft_close, &s);
	mlx_loop(s.mlx.ptr);
	return (1);
}

void	ft_declare(t_all s, char *cub)
{
	t_map	map;
	t_tex	tex;

	map.tab = NULL;
	tex.n = NULL;
	tex.s = NULL;
	tex.e = NULL;
	tex.w = NULL;
	map.x = 0;
	map.y = 0;
	tex.c = NONE;
	tex.f = NONE;
	s.map = map;
	s.tex = tex;
	ft_cubed(s, cub);
}

void	ft_init(char *cub)
{
	t_mlx	mlx;
	t_win	win;
	t_img	img;
	t_err	err;
	t_all	s;

	mlx.ptr = NULL;
	win.ptr = NULL;
	img.ptr = NULL;
	img.adr = NULL;
	win.x = 0;
	win.y = 0;
	err.n = 0;
	err.m = 0;
	err.pos = -1;
	s.mlx = mlx;
	s.win = win;
	s.img = img;
	s.err = err;
	ft_declare(s, cub);
}

int		main(int ac, char **av)
{
	if (ac == 2 && !ft_filecheck(av[1], ".cub"))
		ft_init(av[1]);
	else
		write(2, "Error : Invalid arg\n", 20);
	return (0);
}
