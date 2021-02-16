#include "./includes/cube.h"
#define READ_SIZE 56 

void	map_error_handler(int error)
{
	if (error < 0)
		printf("Error\n");
	if (error == -1)
		printf("Empty map!\n");
	if (error == -2)
		printf("Inappropriate character in map\n");
}

int ft_strlen(char *s)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char *ft_strjoin_f(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*d;
	int		l1;
	int		l2;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	d = (char *)malloc(sizeof(char) * (l1 + l2 + 1));	
	if (d == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && i < l1 && s1[i])
		d[j++] = s1[i++];
	i = 0;
	while (s2 && i < l2 && s2[i])
		d[l1++] = s2[i++];
	d[l1] = '\0';
	if (s1)
		free(s1);
	return (d);
}
void			ft_bzero(void *s, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

int c_in_s(char c, char *s)
{
	int		i;

	i = 0;
	while (s && s[i])
		if (s[i++] == c)
			return (1);
	return (0);
}

int count_c_in_s(char c, char *s)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s && s[i])
		if (s[i++] == c)
			count++;
	return (count);
}

char *ft_strdup_til_char(char *s, char c, int start)
{
	int		i;
	int		size;
	char	*dup;

	i = start;
	while (s[i] != c && s[i]) 
		i++;
	size = i - start;
	dup = (char *)(malloc(sizeof(char) * (size + 1)));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < size && s[i])
		dup[i++] = s[start++];
	dup[i] = '\0';
	return (dup);
}

void str_to_array(char **src_map, int **dest_array, int max_width, int max_height)  
{
	int i;
	int j;

	j = 0;
	while (i < max_height)
	{
		i = 0;
		while (j < max_width)
		{
			if (src_map[i][j])
				dest_array[i][j] = src_map[i][j];
			else
				dest_array[i][j] = ' ';
			i++;
		}
		j++;
	}
}

void print_array(int **array, int max_width, int max_height)
{
	int x;
	int y;

	x = 0;
	while (x < max_height)
	{
		y = 0;
		while (y < max_width)
		{
			printf("%d", array[x][y]);
			if (y != 23)
				printf(" ");
			else
				printf("\n");
			y++;
		}
		x++;
	}
}

char *file_to_str(char *path_file)
{
	int fd;
	char buf[READ_SIZE + 1];
	char *tmp;
	int r;

	fd = 0;
	fd = open(path_file, O_RDONLY);
	r = READ_SIZE; 
	tmp = NULL;
	if (fd < 0)
		return (NULL);
	while (r == READ_SIZE)
	{
		ft_bzero(buf, READ_SIZE);
		r = read(fd, buf, READ_SIZE);
		buf[READ_SIZE] = '\0';
		if (r > 0)
			tmp = ft_strjoin_f(tmp, buf);
	}
	close(fd);
	return (tmp);
}

int		map_max_width(char **map)
{
	int	max;
	int	i;

	max = 0;
	i = 0;
	while (map[i]) 
	{	
		max = (int)(fmax(ft_strlen(map[i]),max));
		i++;
	}
	printf("max ln - %d\n", max);
	return (max);
}

int	map_max_height(char **map)
{
	int	max;	

	max = 0;
	while (map[max])
		max++;
	printf("max height - %d\n", max);
	return (max);
}

int		pre_parsing(char *map)
{
	int i;

	i = 0;
	if (!map)
		return (-1);
	while (map[i])
	{	
		if(c_in_s(map[i], "\t 012NSEW\n") != 1) 
			return (-2);
		i++;
	}
	return (1);
}

char **split_lines(char *lines)
{
	char **ret;	
	int		j;
	int		k;
	int		n_lines;

	j = 0;
	k = 0;
	n_lines = count_c_in_s('\n', lines); 
	ret = (char **)malloc(sizeof(char *) * (n_lines + 1));
	if (ret == NULL)
		return (NULL);
	while (j < n_lines)
	{
		ret[j] = ft_strdup_til_char(lines, '\n', k); 
		while (lines[k] && lines[k] != '\n') 
			k++;
		if (lines[k] == '\n')
			k++;
		j++;
	}
	ret[n_lines] = 0;
	return (ret);
}

int extract_map_from_file(char *path_file)
{
	char	*tmp;
	char	**map;
	int		**map_tab;
	int		r;
	int		i;
	int		j;

	r = 0;
	tmp = file_to_str(path_file);
	if (!tmp)
		return (-1);
	r = pre_parsing(tmp);	
	map_error_handler(r);
	if (r < 0)
	{	
		free(tmp);
		return (-1);
	}
	map = split_lines(tmp);		
	map_tab = malloc(sizeof(int) * (map_max_width(map) + map_max_height(map)));
	str_to_array(map, map_tab, map_max_width(map), map_max_height(map));
	
	return (1);
}

int main(void)
{
	extract_map_from_file("./map_test.cub");
	return (1);
}
