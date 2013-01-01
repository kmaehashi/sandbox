#include <stdio.h>

#define PATTERN {0x1f, 0x8b, 0x08}
#define PATTERN_STAGES 2
#define BUF_SIZE 10000

int usage(char *this) {
	printf("Usage: %s filename ...\n", this);
	return 1;
}

int find_binary(char *filename) {
	char pattern[] = PATTERN;
	int pattern_stages = PATTERN_STAGES;
	int match_stage = 0;

	FILE *fp = fopen(filename, "rb");
	char data[BUF_SIZE];
	int size = 0;
	int bytes = 0;

	if (fp == NULL) {
		printf("fopen failed: %s\n", filename);
		return 1;
	}

	while ((size = fread(data, sizeof(char), BUF_SIZE, fp)) > 0) {
		int i;
		for (i = 0; i < size; i++) {
			if (data[i] == pattern[match_stage]) {
				if (match_stage++ == pattern_stages) {
					int bytes_match = bytes - pattern_stages;
					printf("%s: match at 0x%x [%d]\n", filename, bytes_match,  bytes_match);
					match_stage = 0;
				}
			} else {
				match_stage = 0;
			}
			bytes++;
		}
	}
	printf("%s: total: %d bytes\n", filename, bytes);
	fclose(fp);
}


int main(int argc, char *argv[]) {
	int retval = 0;
	int files = argc - 1;
	int current_file;

	if (files == 0) {
		return usage(argv[0]);
	}

	for (current_file = 1; current_file <= files; current_file++) {
		retval += find_binary(argv[current_file]) * 2;
	}

	return retval;
}

