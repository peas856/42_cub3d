#include "cub3d.h"

#define texWidth 64
#define texHeight 64

void	ft_ray(t_all *s)
{
	double	angle;
	double	dist;
	double	cameraX;

	cameraX = (2 * s->ray.i / (double)s->win.x) - 1;
	angle = 33 * cameraX * M_PI / 180;
	s->ray.x = s->dir.x * cos(angle) - s->dir.y * sin(angle);
	s->ray.y = s->dir.y * cos(angle) + s->dir.x * sin(angle);
	dist = hypot(s->ray.x, s->ray.y);
	s->ray.x /= dist;
	s->ray.y /= dist;
}

void	ft_dir(t_all *s)
{
	double	mapX;
	double	mapY;
	
	mapX = floor(s->pos.x);   // mapX, 플레이어의 현재 위치 편의상 정수로 나타내며 1씩 움직임
	mapY = floor(s->pos.y);   // mapY, 플레이어의 현재 위치 편의상 정수로 나타내며 1씩 움직임

	s->ray.deltadistX = fabs(1 / s->ray.x);
	s->ray.deltadistY = fabs(1 / s->ray.y);
	if (s->ray.x >= 0)
	{
		s->ray.stepX = 1;	
		s->ray.sidedistX = (mapX + 1.0 - s->pos.x) * s->ray.deltadistX;
	}
	else
	{
		s->ray.stepX = -1;
		s->ray.sidedistX = (s->pos.x - mapX) * s->ray.deltadistX;
	}
	if (s->ray.y >= 0)
	{
		s->ray.stepY = 1;
		s->ray.sidedistY = (mapY + 1 - s->pos.y) * s->ray.deltadistY;
	}	
	else
	{
		s->ray.stepY = -1;
		s->ray.sidedistY = (s->pos.y - mapY) * s->ray.deltadistY;
	}
		
}

void	ft_ver(t_all *s)
{
	double perpWallDist;
	int hit;
	int side;
	int	mapX;
	int	mapY;

	hit = 0;
	mapX = (int)(s->pos.x);   // mapX, 플레이어의 현재 위치 편의상 정수로 나타내며 1씩 움직임
	mapY = (int)(s->pos.y);   // mapY, 플레이어의 현재 위치 편의상 정수로 나타내며 1씩 움직임
	for (int y = 0; y < s->win.y; y++)
	{
		s->buf[y] = s->tex.f; 
		s->buf[s->win.y - y - 1] = s->tex.c;
	}
	while (hit == 0)
	{
		if (s->ray.sidedistX < s->ray.sidedistY) // 기울기가 1보다 작을 때, x축으로 검사
		{
			s->ray.sidedistX += s->ray.deltadistX;
			mapX += s->ray.stepX; // stepX 는 1, -1 중 하나.
			side = 0; // x면에 부딪혔다면 side = 0
		}
		else  // 기울기가 1보다 클 때, y축 기준으로 검사 
		{
			s->ray.sidedistY += s->ray.deltadistY;
			mapY += s->ray.stepY; // stepY는 1, -1 중 하나.
			side = 1; // y면에 부딪혔다면 side = 1
		}
		if (s->map.tab[mapY][mapX] == '1')
			hit = 1;
	}
	if (side == 0)
		perpWallDist = (mapX - s->pos.x + (1 - s->ray.stepX) / 2) / s->ray.x;
	else
		perpWallDist = (mapY - s->pos.y + (1 - s->ray.stepY) / 2) / s->ray.y;
	int lineHeight = (int)(s->win.y / perpWallDist);
	int drawStart = (-lineHeight / 2) + (s->win.y / 2);
	if (drawStart < 0)
		drawStart = 0;
	int drawEnd = (lineHeight / 2) + (s->win.y / 2);
	if (drawEnd >= s->win.y)
		drawEnd = s->win.y - 1;
	unsigned int	*texNum;
	if (side == 1) // y면에 부딪히면
	{
		if (s->ray.y >= 0)
			texNum = s->tex.n;
		else
			texNum = s->tex.s;
	}
	else
	{
		if (s->ray.x >= 0)
			texNum = s->tex.w;
		else
			texNum = s->tex.e;
	}
	double wallX;
	if (side == 0)
		wallX = s->pos.y + perpWallDist * s->ray.y;
	else
		wallX = s->pos.x + perpWallDist * s->ray.x;
	wallX -= floor(wallX);
	int texX = (int)(wallX * (double)texWidth);
	if (side == 0 && s->ray.x > 0)
		texX = texWidth - texX - 1;
	if (side == 1 && s->ray.y < 0)
		texX = texWidth - texX - 1;
	double step = 1.0 * texHeight / lineHeight;
	double texPos = (drawStart - s->win.y / 2 + lineHeight / 2) * step;\
	for (int i = drawStart; i < drawEnd; i++)
	{
		int texY = (int)texPos & (texHeight - 1);
		texPos += step;
		s->buf[i] = texNum[texHeight * texY + texX];
	}
}

void imageDraw(t_all *s)
{
	int y;
	
	y = 0;
    while (s->ray.i < s->win.x * s->win.y)
	{
        s->img.adr[s->ray.i] = s->buf[y];
		s->ray.i += s->win.x;
		y++;
	}
    s->ray.i -= s->win.x * s->win.y;
}

void	ft_screen(t_all *s)
{
	int		bpp;
	int		sl;
	int		end;

	s->img.ptr = mlx_new_image(s->mlx.ptr, s->win.x, s->win.y);
	s->img.adr = (unsigned int *)mlx_get_data_addr(s->img.ptr, &bpp, &sl, &end);
	while (s->ray.i < s->win.x)
	{
		s->buf = (int *)malloc(sizeof(int) * s->win.y);
		ft_ray(s);
		ft_dir(s);
		ft_ver(s);
		imageDraw(s);
		s->ray.i++;
		free(s->buf);
	}
}