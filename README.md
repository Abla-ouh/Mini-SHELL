
      
<h2 align="center">Want to explore some cute shells [ 🐚 ] ? Then, dive into the Occean.</h2>
<h1 align="center">WHAT IS IT, MINISHELL !? </h1>

<blockquote align="center"> Where There is a SHELL, There is a Way</blockquote>

<p align="center">
<img alt="GitHub code size in bytes" src="https://cameronnokes.com/images/bash.png" />
</p>

---
- It was the first group project in my 42 cursus.
- 42 project, recoding our own little **bash**. A program capable of parsing (which I have done ) a prompt and launching executables with arguments, along with a few built-in functions.
-  The objective of this project is to create a simple shell to learn some advanced programming techniques like processes creation and control, file descriptors, signals and pipes, etc.
---
# WHY?

The existence of **shells** is linked to the very existence of IT.

At the time, all developers agreed that *communicating with a computer using aligned 1/0 switches was seriously irritating.* 

It was only logical that they came up with the idea of creating a software to **communicate with a computer using interactive lines of commands in a language somewhat close to the human language.** 

Thanks to **Minishell**, you’ll be able to travel through time and come back to problems people faced when ~~Windows~~ didn’t exist.

![shell](https://miro.medium.com/max/688/1*GuB5q_bWOSZa-8sDg1lEDA.png)
---
## Built-in functions to implement :

| Command | Description  |
|--- |--- |
| **echo** | Echo the STRING(s) to standart output. **-n** flag: do not output the trailing newline. |
| **cd** | Change the shell working directory	(with a relative or absolute path). |
| **pwd** | Print name of current/working directory. |
| **export** | Set export attribute for shell variables. |
| **unset** | Unset values of shell variables. |
| **env** | Print the environment. |
| **exit** | Cause the shell to exit with the exit status specified. |
---
## Using Only :

Only the following functions are allowed to be used in this project:

| Function | Description | Function | Description |
|----------|-------------|----------|-------------|
|readline | read a line from the terminal |lstat | get file status | 
|rl_clear_history | clear the history list by deleting all of the entries | fstat | get file status by fd |
|rl_on_new_line | tell the update routines that we have moved onto a new line | unlink | remove a specified file |
|rl_replace_line | replace the contents of rl_line_buffer with text | execve | execute program |
|rl_redisplay | change what's displayed on the screen | dup | duplicate a file descriptor |
|add_history | save the line in a history list of lines | dup2 | duplicate a file descriptor |
|printf | format and print data | pipe | create pipe |
|malloc | allocate dynamic memory | opendir | open a directory |
|free | free dynamic memory | readdir | read a directory |
|write | write to a file descriptor | closedir | close a directory |
|access | check user's permissions for a file | strerror | return string describing error number |
|open | open and can create a file | perror | print a system error message |
|read | read from a file descriptor | isatty | test whether a file descriptor refers to a terminal |
|close | close a file descriptor | ttyname | return name of a terminal |
|fork | create a child process | ttyslot | find the slot of the current user's terminal in some file |
|wait | wait for process to change state | ioctl | control device |
|waitpid | wait for process to change state | getenv | get an environment variable |
|wait3 | wait for process to change state | tcsetattr | control asynchronous communications ports |
|wait4 | wait for process to change state | tcgetattr | control asynchronous communications ports |
|signal | ANSI C signal handling | tgetent | termcap database emulation |
|sigaction | examine and change a signal action | tgetflag |  termcap database emulation |
|kill | send signal to a process | tgetnum |  termcap database emulation |
|exit | cause normal process termination | tgetstr | termcap database emulation |
|getcwd | get current working directory | tgoto | termcap database emulation |
|chdir | change working directory | tputs | curses interfaces to terminfo database |
|stat | get file status by pathname |
---
> **FOR MORE INFORMATION, CHECK THE SUBJECT :** [**MINISHELL SUBJECT**](https://cdn.intra.42.fr/pdf/pdf/65828/en.subject.pdf)
---
## About this repo:

 1. Clone the repo. 
 2. Execute `make` command. 
 3. Execute `./bin/minishell`  
 4. You will get prompted. then, it's our shell, have fun with it.

## Useful ressources :

- https://mywiki.wooledge.org/BashParserhttp://aosabook.org/en/bash.html
- https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
- https://tldp.org/LDP/Bash-Beginners-Guide/html/index.html
- https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY (Unix processes)
- https://youtu.be/uHH7nHkgZ4w (Pipes)
- https://youtu.be/EqndHT606Tw (fd, dup, dup2)
---
###  the most highlighted learned skill from this project is "How to fix memory leaks, and memory management".
                                                   We struggled but we learned :) 
