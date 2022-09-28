typedef struct s_cmds
{
    char    *path;
    char    **args;
    int     in;
    int     out;
    int     is_exec;
    struct s_cmds *next;
} t_cmds;

typedef struct s_data
	char	**lines;
    char    *tokens;
	int		**here_fds;
	int		*infiles;
	int		*outfiles;
} t_data;

// t_cmds *node(data, i , j)
// {
//     t_cmds *ptr;
//     s_content ptr3;
//     ptr1 = malloc(t_cmds);
//     ptr1->path = data->lines[i];
//     ptr1->args = data->lines[i][j];
//     ptr1->in = data->infile[i];
//     ptr1->out = data->outfile[i];
//     ptr1->is_exec = /*chi haja*/
//     ptr1->next = NULL;
//     .
//     .
//     .

// }