#include "cub3d.h"
// 맵 형식이 .cub로 끄타는지 확인 맞으면 0 리턴
int		ft_cubcheck(char *av)
{
	int		len;

	len = ft_strlen(av);
	if (len - 4 < 0)
		len = 0;
	else
		len = len - 4;
	return (ft_strcmp(av + len, ".cub"));
}
// 문자열 비교 같으면 0 리턴 
int		ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
// 벽으로 둘러쌓여있는지 체크, map.y 와 map.x에 뭐가 들어있는지 체크 
int		ft_mapcheck(t_all *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < s->map.y)
	{
		j = 0;
		while (j < s->map.x)
		{
			if (s->map.tab[i][j] != '1' && i == 0)
				return (-1);
			else if (s->map.tab[i][j] != '1' && i == s->map.y - 1)
				return (-1);
			else if (s->map.tab[i][j] != '1' && j == 0)
				return (-1);
			else if (s->map.tab[i][j] != '1' && j == s->map.x - 1)
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_parcheck(t_all *s)
{
	if (s->win.x <= 0 || s->win.y <= 0)
		return (ft_strerror(-14));   //("Error : No resolution specified)
	else if ((s->tex.n == NULL || s->tex.s == NULL || s->tex.e == NULL)
			|| (s->tex.w == NULL || s->tex.i == NULL))
		return (ft_strerror(-15));   //"Error : Missing texture  , n, w, s, w -> 도어남북 
	else if (s->tex.c == NONE || s->tex.f == NONE)
		return (ft_strerror(-16));  //  c, f-> 아마 실링, 플루어 "Error : Missing floor/ceiling color
	else if (s->err.p == 0)
		return (ft_strerror(-17));  //"Error : No starting position 
	else if (s->err.p > 1)
		return (ft_strerror(-18));   // "Error : Multiple starting positions
	else if (ft_mapcheck(s) == -1)
		return (ft_strerror(-19));  // "Error : Map isn't surrounded by walls
	return (1);
}
