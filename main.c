#include <stdio.h>
#include <string.h>

int main(void) {
	char buffer[1024];

	while(1) {
		printf("[SENTRY-sh]$");
		fflush(stdout);
		
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
			break;
		}

		size_t len = strlen(buffer);

		if (len > 0 && buffer [len -1] == '\n') {
	       		buffer [len - 1] = '\0';
		}	
	}

	return 0;
}
