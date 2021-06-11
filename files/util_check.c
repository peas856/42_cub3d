#include "cub3d.h"

int		ft_filecheck(char *av, char *s)
{
	int		len;

	len = 0;
    while (av[len] != '\0')
        len++;
	if (len - 4 < 0)
		len = 0;
	else
		len = len - 4;
	return (ft_strcmp(av + len, s));
}

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

int		ft_mapcheck(t_all *s)   // check 필요 
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
			if (s->map.tab[i][j] == '0')
			{
				if (i == 0 || j == 0 || j == s->map.x - 1 || i == s->map.y - 1)
					return (-1);
				if (s->map.tab[i - 1][j - 1] == '*'|| s->map.tab[i - 1][j] == '*'|| s->map.tab[i - 1][j + 1] == '*'||
				s->map.tab[i][j - 1] == '*'|| s->map.tab[i][j + 1] == '*'|| s->map.tab[i + 1][j - 1] == '*'||
				s->map.tab[i + 1][j] == '*'|| s->map.tab[i + 1][j + 1] == '*')
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_parcheck(t_all *s)
{
	if (s->win.x <= 0 || s->win.y <= 0)
		return (ft_strerror(-14));
	else if ((s->tex.n == NULL || s->tex.s == NULL || s->tex.e == NULL)
			|| (s->tex.w == NULL))
		return (ft_strerror(-15));
	else if (s->tex.c == NONE || s->tex.f == NONE)
		return (ft_strerror(-16));
	else if (ft_mapcheck(s) == -1)
		return (ft_strerror(-19));
	return (1);
}
