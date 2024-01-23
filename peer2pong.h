#ifndef PEER2PONG_H
# define PEER2PONG_H
# define BUFF_SIZE 8
# define FD_SIZE 4096

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

typedef struct s_list
{
	int	played;
	int game[2];
	struct s_list *next;
}	t_list;

char	**ft_split(char const *s, char c);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_bzero(char *s, size_t n);
void	ft_strdel(char **as);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strnew(size_t size);
int		get_next_line(const int fd, char **line);

#endif