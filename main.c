#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

int main(void) {
	char buffer[1024];
			
	const char *whitelist[] = {"ls", "pwd", "clean", "date", "exit"};
	int whitelist_size = sizeof(whitelist) / sizeof(whitelist[0]);
	
	signal(SIGINT, SIG_IGN);

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

		int allowed = 0;
		for (int i = 0; i < whitelist_size; i++) {
			if (strcmp(buffer, whitelist[i]) == 0) {
				allowed = 1;
				break;
				}
		}
			if (!allowed) {
				printf("ERREUR: la commande %s est refusée \n", buffer);

			FILE *log_file = fopen("sentry.log", "a");

			if (log_file != NULL) {
				fprintf(log_file, "[ALERTE SECURITY] Tentative d'exécution de la commande : %s\n", buffer);
				fclose(log_file);
			} 
			else {
				printf("ERREUR SYSTÈME: Impossible d'écrire dans sentry.log\n");
			}

			continue;
		}

	pid_t pid;

	pid = fork();

		if (pid < 0) {
			printf ("Erreur \n");
		}
		else if (pid == 0) {
			execlp (buffer, buffer, NULL);
			fprintf(stderr, "SENTRY-h: %s commande introuvable \n", buffer);
			exit(127);
		}
		else {
			wait(NULL);
		}
	}

	return 0;
}
