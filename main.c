#include <stdio.h>

int main(void) {
	char buffer[1024];

	while(1) {
		printf("[SENTRY-sh]$");
		fflush(stdout);
		
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
			break;
		}
	}

	return 0;
}
