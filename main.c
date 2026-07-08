#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
	char buffer[1024];

	while(1) {
		printf("[SENTRY-sh]$");
		fflush(stdout);
		
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
			break;
		}

		size_t len = strlen(buffer);

		if (len > 0 && buffer[len -1] == '\n') {
	       		buffer[len - 1] = '\0';
		}

		if (strcmp(buffer, "exit") == 0) {
			printf("Fermeture de session sécurisée \n");
				break;
		}

	pid_t pid;

	pid = fork();

		if (pid < 0) {
			printf ("Erreur \n");
		}
		else if (pid == 0) {
			printf ("Processus enfant \n");
			return 0;
		}
		else {
			printf ("Processus parent \n");
		}
	}

	return 0;
}
