/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trhee <trhee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 18:34:50 by trhee             #+#    #+#             */
/*   Updated: 2021/06/15 18:39:46 by trhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_close(t_all *s, int win)
{
	int	i;

	i = 0;
	while (i < s->map.y)
		free(s->map.tab[i++]);
	free(s->map.tab);
	free(s->tex.n);
	free(s->tex.s);
	free(s->tex.e);
	free(s->tex.w);
	if (win == 1)
		mlx_destroy_window(s->mlx.ptr, s->win.ptr);
	free(s->mlx.ptr);
	exit(0);
	return (1);
}

void	ft_move(t_all *s, double c, int dir)
{
	double orix;
	double oriy;

	orix = s->pos.x;
	oriy = s->pos.y;
	if (dir == 1 && (s->map.tab[(int)floor(oriy)][(int)floor(orix)] != '1'))
	{
		s->pos.x += c * (s->dir.x * SPEED / 100);
		s->pos.y += c * (s->dir.y * SPEED / 100);
	}
	else if (!dir && (s->map.tab[(int)floor(oriy)][(int)floor(orix)] != '1'))
	{
		s->pos.x -= c * (s->dir.y * SPEED / 100);
		s->pos.y += c * (s->dir.x * SPEED / 100);
	}
	if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '1')
	{
		s->pos.x = orix;
		s->pos.y = oriy;
	}
}

void	ft_rotate(t_all *s, double c)
{
	double	dist;

	s->dir.x = s->dir.x * cos(c * ANGLE) - s->dir.y * sin(c * ANGLE);
	s->dir.y = s->dir.x * sin(c * ANGLE) + s->dir.y * cos(c * ANGLE);
	dist = hypot(s->dir.x, s->dir.y);
	s->dir.x /= dist;
	s->dir.y /= dist;
}

int		ft_key(int key, void *arg)
{
	if (key == ESC)
		ft_close(arg, 1);
	else if (key == W)
		ft_move(arg, 1, 1);
	else if (key == A)
		ft_move(arg, -1, 0);
	else if (key == S)
		ft_move(arg, -1, 1);
	else if (key == D)
		ft_move(arg, 1, 0);
	else if (key == LEFT)
		ft_rotate(arg, -1);
	else if (key == RIGHT)
		ft_rotate(arg, 1);
	ft_draw(arg);
	return (1);
}
