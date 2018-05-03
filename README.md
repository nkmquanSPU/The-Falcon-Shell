#The Falcon Shell
This program mimics basic behaviour of a shell:
```sh
while true
	read user input
	if input is built-in command
		handle it
	else if user input is program in path
		fork child process
		wait for child process to complete
	else
		error
``` 

## Built-in Commands:
`falsh [-h]`
*The optional -h flag prints the help message and immediately exits.
*After invoking falsh, it runs until the user types the exit command.

`exit` – exit the program
*Usage: `exit`

`pwd` – print the current working directory
*Usage: `pwd`

`cd` – change directory
*Usage: `cd`

`setpath` – sets the path, user must provide at least one argument (directory)
*Usage: Usage: `setpath <dir> [dir] … [dir]`

`help` – list all built-in commands with short, user-friendly descriptions.
*Usage: `help`

## Redirection:
when the user invokes `command > filename`, redirect `command`'s standard output to
`<filename>.out` and standard error to `<filename>.err`.

## Other Commands:
Any non-built-in command will be executed if it is in one of the directories specified
in the user’s path.
