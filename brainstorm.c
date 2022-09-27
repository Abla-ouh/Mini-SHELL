typedef struct s_cmds
{
    char    *path;
    char    **args;
    int     in;
    int     out;
    int     is_exec;
    struct s_cmds *next;
} t_cmds;

typedef struct data
	char	**lines;
    char    *tokens;
	int		**here_fds;
	int		*infiles;
	int		*outfiles;
} s_data

t_list *node(data, i , j)
{
    t_cmds ptr;
    s_content ptr3;
    ptr1 = malloc(t_cmds);
    ptr1->content->path = data->lines[i];
    ptr1->content->args = data->lines[i][j];
    ptr1->content->in = data->infile[i];
    ptr1->content->out = data->outfile[i];
    ptr1->content->is_exec = /*chi haja*/
    ptr1->next = NULL;
    .
    .
    .

}