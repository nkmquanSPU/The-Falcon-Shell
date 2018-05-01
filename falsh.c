#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[])
{
	char help_flag[256] = "-h";
	char exit_cmd[256] = "exit";
	char cmd[256];
	
	if (argc == 1) //if user enter ./flash and hit Enter
	{
		//get the next command (cmd) from user
		//fgets(cmd, 256, stdin);
		
		scanf("%s", &cmd);
		while(strcmp(cmd, exit_cmd) != 0)
		{
			printf("%s \n",cmd);
			scanf("%s", &cmd);
		}			
		
		return 0;
	}
	else
	{
		//if user enter ./falsh -h
		if(strcmp(argv[1], help_flag) == 0) 
		{
			printf("exit - exit the program.\n");
			printf("Usage: exit\n");
			printf("pwd - print the current working directory.\n");
			printf("Usage: pwd\n");
			printf("cd - change directory.\n");
			printf("Usage: cd\n");
			printf("setpath - sets the path, user must provide at least one argument (directory).\n");
			printf("Usage: setpath <dir> [dir] … [dir]\n");
		
			return 0;
		}	
		else if (strcmp(argv[1], exit_cmd) == 0) //if user enter exit
			return 0;
	}
	
	return 0;
}
