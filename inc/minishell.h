/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:18:26 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/30 10:35:07 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "../ft_fprintf/ft_fprintf.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "exe.h"

# define F_NO_SUCH_FILE -2
# define F_PERMISSION_DENIED -3

typedef struct s_cmds
{
	char			*path;
	char			**args;
	int				in;
	int				out;
	int				is_exec;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_data
{
	char	**lines;
	char	*tokens;
	char	**s_tokens;
	int		**here_fds;
	int		**infiles;
	int		**outfiles;
}	t_data;

typedef struct s_cord
{
	int	i;
	int	j;
	int	*sync;
}	t_cord;

/*************************** PARSER *************************/
void	check_expand(t_data	*data);
t_cmds	*ft_parser(char *line);
int		ft_strptr(char **ptr);
void	fill_here_fds(t_data *data);
void	fill_infiles(t_data *data);
void	fill_outfiles(t_data *data);
/************************** LEXER ***************************/
char	*ft_tokenize(char **lines);
char	**ft_lexer(char *line, char *set);
int		is_seperator_char(char c);
int		find_until_not(char *str_trim, int *i, char o);
void	count_until_not(char *trim_line, int i, int *len, char o);
void	find_string(char *str_trim, int *i);
void	count_string(char *trim_line, int i, int *len);
/************************** EXPAND ***************************/
char	*expand(char *arg);
/************************** ERROR ****************************/
int		ft_syntax_error(char **lines, char *token);
int		ft_check_redir_filename(char **lines, char *tokens);
int		count_dup(char *str_trim, char o);
/************************** REDIRECTIONS *********************/
int		find_op(char *tokens, char c);
int		*ft_open_hdocs(char **lines, char *tokens, int *sync);
int		*ft_open_infiles(char **lines, char *tokens, int *sync);
int		*ft_open_outfiles(char **lines, char *tokens, int *sync);
int		setup_last_io(int *last_io, char *token, t_data *data, int cmd_idx);
/************************* FILLUP ***************************/
char	**ft_fill_args(char **lines, char *tokens, int *sync);
void	skip_quote1(char *str_trim, int *i, char q);
void	skip_quote(char *str_trim, int *i, char q);
void	skip_quote_len(char *trim_line, int i, int *len, char q);
char	*unquote_arg(char *str);
/************************ PATH *****************************/
char	*get_cmd_path(t_cmds *cmds);
/************************ FREE *******************************/
void	cleanup(t_data *data);
void	ft_free_all(t_cmds *cmds);
void	free_2d_int(int **str);
void	free_2d_char(char **str);
#endif
