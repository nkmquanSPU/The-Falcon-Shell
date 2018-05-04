#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

void help_message();

int main(int argc, char* argv[])
{
	FILE *file_ptr;
	char help_flag[256] = "-h";
	char exit[256] = "exit";
	char pwd[256] = "pwd";
	char cd[256] = "cd";
	char setpath[256] = "setpath";
	char help[256] = "help";
	char path[256];
	char file_name[256];
	char *cmd;	
	char *current_directory;
	char directory[256];
	current_directory = directory;
	char buffer[256];
	char temp[256];
	char new_data[256];
	
	int i, j = 0;
	int count = 0;
	int index;
	
	if (argc == 1) //if user enter './flash' and hit Enter
	{			
		
		printf("falsh> ");	
		
		//erase values of temp and buffer before give them new ones 
		memset(temp, 0, 255); 
		memset(buffer, 0, 255); 
		fgets(buffer, 256, stdin); //get input from user. This may contains whitespaces				
		stpcpy(temp, buffer); //copy value of buffer to temp
		cmd = buffer;
		
		//this loop eliminate whitespaces in buffer
		// and put all the chars into cmd
		for (i = 0; i < strlen(buffer); i++)          
		{
			if (buffer[i] != ' ')                           
				cmd[j] = buffer[i];                     
			else
				j--;
			j++;
		}
		cmd[j - 1] = 0; //add NULL to the end cmd
		j = 0;
		
		//printf("%s ", cmd);
		//printf("%lu\n", strlen(cmd));
		//return 0;
		
		//while the user's cmd is not 'exit'
		// get user's cmd and perform it.		
		while(strcmp(cmd, exit) != 0) 
		{
			if(strcmp(cmd, pwd) == 0) 
			{	
				/*
				Get the current working directory.
				Put it into the array of char which current_directory is pointing to.
				*/
				getcwd(current_directory, 256);
				
				//print the current working directory
				//printf("Current directory: %s\n", getcwd(current_directory, 256));
				printf("Current directory: %s\n", directory, 256);
				//current_directory = NULL;
			}			
		    	else if((cmd[0] == 'c') && (cmd[1] == 'd'))			
			{					
				if(strlen(cmd) > 2) //if user enter [dir] [dir] ...
				{	
					//empty the array of char that contains the previous specified directory
					memset(directory, 0, 255); 
						
					i = 0; j = 0;
					
					//extract the [dir] [dir] ... from input														
					for (i = 2; i < strlen(cmd); i++)
					{						                          
						directory[j] = cmd[i]; //update the directory with user's input
						j++;						
					}										
					directory[j + 1] = 0; //add NULL to the end of new directory					
					j = 0;
					
					chdir(current_directory); //change the current directory to new directory
					//printf("%s\n", cmd);						
				}
				else
				{
					//if [dir] are not provided, change to user’s home directory
					chdir(getenv("HOME"));					
				}
				
				//printf("%s\n", cmd);
				
			} //setpath command			
			else if((cmd[0] == 's') && 
				(cmd[1] == 'e') &&
				(cmd[2] == 't') &&
				(cmd[3] == 'p') &&
				(cmd[4] == 'a') &&
				(cmd[5] == 't') &&
				(cmd[6] == 'h'))	
			{
				if (strlen(cmd) > 8)
				{	
					//the PATH when falsh launches contains only /bin.
					setenv("PATH", "/bin", 1);
					printf("\nOriginal PATH: %s\n", getenv("PATH"));
					char *env_name;
					//char *env_value;
					
					//empty the array of char that contains the previous specified path
					memset(path, 0, 255); 
						
					i = 0; j = 0;
					
					//extract the [dir] [dir] ... from input														
					for (i = 7; i < strlen(cmd); i++)
					{						                          
						path[j] = cmd[i]; //update the path with user's input
						j++;						
					}										
					path[j + 1] = 0; //add NULL to the end of new path					
					j = 0;
										
					//adds the env_name to the environment with the value path
					//overwrite the path
					//setenv(env_name, path, 1);
					setenv("PATH", path, 1);
					if (env_name != NULL)
						printf("%s is set.\n", getenv("PATH"));	
							
					setenv("PATH", path, 1);
					//setenv("PATH", path, 1);
					printf("PATH now contains: %s\n\n", getenv("PATH"));
				}
			}
			else if(strcmp(cmd, help) == 0) //help command
			{
				help_message(); //print out help message
			}
			else if((cmd[0] == 'c') && //Redirection: command > file_name
				(cmd[1] == 'o') &&
				(cmd[2] == 'm') &&
				(cmd[3] == 'm') &&
				(cmd[4] == 'a') &&
				(cmd[5] == 'n') &&
				(cmd[6] == 'd'))								
			{
				//printf("This is temp: %s\n", temp);
				//return 0;
				
				//erase values of new_data and file_name before give them new ones
				memset(new_data, 0, 255); 
				memset(file_name, 0, 255); 
				
				if(strlen(cmd) == 7) //missing filename argument
				{
					printf("	Filename is missing.");
					printf("	Cannot run the command.\n");
				}
				else
				{					
					//find the index of '>' in user's input
					char *ptr = NULL;					
					
					ptr = strchr(temp, '>');  //returns the pointer to the first occurrence of '>'
					
					if(ptr != NULL) 
						index = ptr - temp; //get the index of '>'
													
					//printf("%d", index);
					//return 0;
					ptr = NULL;
					//get new data from user for the file
					i = 0; j = 0;
					for(i = 8; i < index - 1; i++)
					{
						new_data[j] = temp[i];
						j++;
					}
					new_data[j + 1] = 0; //add NULL to the end of new path	
					
					i = 0; j = 0;
					//extract file name from user														
					for (i = index + 2; i < strlen(temp) - 1; i++)
					{						                          
						file_name[j] = temp[i]; //update the path with user's input
						j++;						
					}										
					file_name[j + 1] = 0; //add NULL to the end of new path					
					j = 0;					
					
					//printf("%s\n", new_data);
					//printf("%d\n", strlen(new_data));
					
					//printf("%s\n", file_name);
					//printf("%d\n", strlen(file_name));
					
					//return 0;
					/*
					file_ptr = fopen(file_name, "r");
					if(file_ptr == NULL) //if error occurs
					{	
						printf("	Error: %s\n", strerror(errno));
						printf("	Cannot run the command.\n");						
					}					
					*/
						
					//file_ptr = fopen(file_name, "r");
					int filedesc = open(file_name, O_WRONLY | O_APPEND | O_CREAT);
					
					//open and write fileno(stdout) to file_name
					int std_out = dup(STDOUT_FILENO);
					open(file_name, O_WRONLY, stdout);						
					
					//open and append fileno(stderr) to file_name
					int std_err = dup(STDERR_FILENO);
					open(file_name, O_APPEND, stderr);						
					
					//redirect the output of stdout to file_name.out
					dup2(std_out, STDOUT_FILENO);
					close(std_out);
					
					//redirect the output of stderr to file_name.err
					dup2(std_err, STDERR_FILENO);
					close(std_err);
					
				}																
			}
			else //if user enter an invalid command
			{
				printf("Command not found.\n");
			}
						
			printf("falsh> ");
			
			//erase values of temp and buffer before give them new ones 
			memset(temp, 0, 255); 
			memset(buffer, 0, 255); 
			
			fgets(buffer, 256, stdin); //get input from user. This may contains whitespaces
			stpcpy(temp, buffer); //copy value of buffer to temp
		    	cmd = buffer;
			
			//this loop eliminate whitespaces in buffer
			// and put all the chars into cmd
			for (i = 0; i < strlen(buffer); i++)          
			{
				if (buffer[i] != ' ')                           
					cmd[j] = buffer[i];                     
				else
					j--;
				j++;
			}
			cmd[j -1] = 0; //add NULL to the end cmd
			j = 0;				
		}			
		
		return 0;
	}
	else if(strcmp(argv[1], help_flag) == 0) //if user enter './falsh -h'
	{	
		help_message();	
		return 0;					
	}	
	
	return 0;
}

/*
This function list all built-in commands with short, user-friendly descriptions.
Parameter: None
Return: None 
*/
void help_message()
{
	printf("\n");
	printf("These are the built-in commands of falsh shell.\n"); 
	printf("Type './falsh -h' to see this list.\n");
	printf("\n");
	printf("	exit - exit the program.\n");
	printf("	Usage: exit\n");
	printf("\n");
	printf("	pwd - print the current working directory.\n");
	printf("	Usage: pwd\n");
	printf("\n");
	printf("	cd - change directory.\n");
	printf("	Usage: cd\n");
	printf("\n");
	printf("	setpath - sets the path, user must provide at least one argument (directory).\n");
	printf("	Usage: setpath <dir> [dir] … [dir]\n");
	printf("\n");
	
}
