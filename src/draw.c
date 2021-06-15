#include "cub3d.h"

void	ft_ray(t_all *s)
{
	double	angle;
	double	dist;
	double	camerax;

	s->mapx = (int)(s->pos.x);
	s->mapy = (int)(s->pos.y);
	camerax = (2 * s->ray.i / (double)s->win.x) - 1;
	angle = 33 * camerax * M_PI / 180;
	s->ray.x = s->dir.x * cos(angle) - s->dir.y * sin(angle);
	s->ray.y = s->dir.y * cos(angle) + s->dir.x * sin(angle);
	dist = hypot(s->ray.x, s->ray.y);
	s->ray.x /= dist;
	s->ray.y /= dist;
}

void	ft_dir(t_all *s)
{
	s->ray.deltadistx = fabs(1 / s->ray.x);
	s->ray.deltadisty = fabs(1 / s->ray.y);
	if (s->ray.x >= 0)
	{
		s->ray.stepX = 1;	
		s->ray.sidedistx = (s->mapx + 1.0 - s->pos.x) * s->ray.deltadistx;
	}
	else
	{
		s->ray.stepX = -1;
		s->ray.sidedistx = (s->pos.x - s->mapx) * s->ray.deltadistx;
	}
	if (s->ray.y >= 0)
	{
		s->ray.stepY = 1;
		s->ray.sidedisty = (s->mapy + 1 - s->pos.y) * s->ray.deltadisty;
	}	
	else
	{
		s->ray.stepY = -1;
		s->ray.sidedisty = (s->pos.y - s->mapy) * s->ray.deltadisty;
	}
}

void	ft_hit(t_all *s)
{
	s->hit.h = 0;
	while (s->hit.h == 0)
	{
		if (s->ray.sidedistx < s->ray.sidedisty)
		{
			s->ray.sidedistx += s->ray.deltadistx;
			s->mapx += s->ray.stepX;
			s->hit.side = 0;
		}
		else
		{
			s->ray.sidedisty += s->ray.deltadisty;
			s->mapy += s->ray.stepY;
			s->hit.side = 1;
		}
		if (s->map.tab[s->mapy][s->mapx] == '1')
			s->hit.h = 1;
	}
}
