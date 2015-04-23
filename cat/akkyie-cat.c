//
//  main.c
//  cat
//
//  Created by Akio Yasui on 4/17/15.
//  Copyright (c) 2015 Akio Yasui. All rights reserved.
//

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define ERROR(x) print(x, strlen(x), 2)

#define BUFFER_SIZE 1024

void print(const char* str, size_t length, int fd) {
	write(fd, str, length);
}

int main(int argc, const char* argv[]) {

	if (argc < 1) {
		ERROR("Invalid invocation\n");
		return -1;
	}

	bool stdi = argc == 1;
	for (int i = 1; stdi || i < argc; i++) {
		const char* path = argv[i];
		int fd = stdi ? 0 : open(path, O_RDONLY);

		if (fd == -1) {
			ERROR("File read error\n");
			return -1;
		}

		char buffer[BUFFER_SIZE + 1];
		ssize_t rc = read(fd, buffer, BUFFER_SIZE);

		if (rc == -1) {
			ERROR("File read error\n");
			return -1;
		}

		buffer[rc] = '\0';
		print(buffer, rc, 1);
	}

	return 0;
}
