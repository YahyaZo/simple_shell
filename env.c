#include "shell.h"

/**
 * _execvep - Execute shell command and its arguments by searching in PATH
 * @commands: The command and its arguments as an array of strings
 * @envp: The environment variables
 * @status: The pointer to an int where the status will be stored
 */
void _execvep(char **commands, char **envp, int *status)
{
	char *full_path = NULL;
	int pid;


	if (access(commands[0], X_OK) == 0)
	{
		pid = fork();

		if (pid == 0)
			execve(commands[0], commands, envp);
		else
			wait_child_process(status);
	}
	else if (_locate(commands[0], &full_path))
	{
		pid = fork();

		if (pid == 0)
			execve(full_path, commands, envp);
		else
			wait_child_process(status);

		free(full_path);
	}
	else
	{
		*status = 127;
		write_error(commands[0]);
	};
}

/**
 * _locate - Searches for the full path of a cmd in the PATH env variable
 * @command: The command to search for
 * @full_path: search for path
 *
 * Return: void
 */
int _locate(char *command, char **full_path)
{
	char *token, *path_env;
	int found = 0;



	path_env = _getenv("PATH");

	if (path_env != NULL)
	{
		char *path_env_copy = strdup(path_env);

		token = strtok(path_env_copy, ":");

		while (token != NULL && !found)
		{
			*full_path = malloc(strlen(token) + strlen(command) + 2);
			if (*full_path != NULL)
			{
				strcpy(*full_path, token);
				strcat(*full_path, "/");
				strcat(*full_path, command);


				if (access(*full_path, X_OK) == 0)
				{

					found = 1;
				}

				if (!found)
					free(*full_path);
			}

			token = strtok(NULL, ":");
		}

		free(path_env_copy);
	}

	return (found);
}

/**
 * wait_child_process - Waits for a child proc to end and get its exit status
 * @status: Pointer to the status variable to store the exit status
 *
 * Return: void
 */
void wait_child_process(int *status)
{
	int child_status;

	if (wait(&child_status) == -1)
	{
		perror("wait");
		exit(EXIT_FAILURE);
	}

	if (WIFEXITED(child_status))
	{
		*status = WEXITSTATUS(child_status);
	}
}
/**
 * _getenv - Searches for an environment variable and returns its value
 * @path: The name of the environment variable to search for
 *
 * Return: Ptr to the value of the environment variable, or NULL if not found
 */
char *_getenv(const char *path)
{
	int i;
	int path_length = _strlen((char *) path);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (!strncmp(path, environ[i], path_length))
		{
			if (environ[i][path_length] == '=')
			{
				return (environ[i] + path_length + 1);
			}
		}
	}

	return (NULL);
}
/**
 * print_env_var - Prints the environment variables to stdout
 *
 * Return: void
 */
void print_env_var(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}
