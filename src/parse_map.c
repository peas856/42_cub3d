/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trhee <trhee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 18:20:45 by trhee             #+#    #+#             */
/*   Updated: 2021/06/15 18:26:05 by trhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_xpm(t_all *s, unsigned int **adr, char *file)
{
	int			fd;
	void		*img;
	int			tab[5];

	if (ft_filecheck(file, ".xpm") != 0)
		return (-1);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	close(fd);
	img = mlx_xpm_file_to_image(s->mlx.ptr, file, &tab[0], &tab[1]);
	if (img == NULL)
		return (-1);
	*adr = (unsigned int *)mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4]);
	free(img);
	return (0);
}

int				ft_texture(t_all *s, unsigned int **adr, char *line, int *i)
{
	char		*file;
	int			j;

	if (*adr != NULL)
		return (-7);
	(*i) += 2;
	ft_spaceskip(line, i);
	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	if (!(file = malloc(sizeof(char) * (*i - j + 1))))
		return (-8);
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		file[j++] = line[(*i)++];
	file[j] = '\0';
	j = ft_xpm(s, adr, file);
	free(file);
	return (j == -1 ? -9 : 0);
}

int				ft_slablen(t_all *s, char *line)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == ' ')
			count++;
		else if (line[i] == 'N' || line[i] == 'S' || \
		line[i] == 'W' || line[i] == 'E')
			count++;
		i++;
	}
	if (count < s->map.x)
		return (s->map.x);
	return (count);
}

char			*ft_slab(t_all *s, char *line, int *i)
{
	char		*slab;
	int			j;

	if (!(slab = malloc(sizeof(char) * (ft_slablen(s, line) + 1))))
		return (NULL);
	j = 0;
	while (line[*i] != '\0')
	{
		if ((line[*i] == '0' || line[*i] == '1' || line[*i] == 'N')
			|| (line[*i] == 'E' || line[*i] == 'S' || line[*i] == 'W'))
			slab[j++] = line[*i];
		else if (line[*i] == ' ')
			slab[j++] = '*';
		else
		{
			free(slab);
			return (NULL);
		}
		(*i)++;
	}
	slab[j] = '\0';
	return (slab);
}

int				ft_map(t_all *s, char *line, int *i)
{
	char		**tmp;
	int			j;

	s->err.m = 1;
	if (!(tmp = malloc(sizeof(char *) * (s->map.y + 2))))
		return (-11);
	j = -1;
	while (++j < s->map.y)
		tmp[j] = s->map.tab[j];
	if ((tmp[s->map.y] = ft_slab(s, line, i)) == NULL)
	{
		free(tmp);
		return (-12);
	}
	tmp[s->map.y + 1] = NULL;
	if (s->map.y > 0)
		free(s->map.tab);
	s->map.tab = tmp;
	s->map.y++;
	s->map.x = ft_slablen(s, line);
	return (0);
}
