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

#define PRINT(x) print(x, strlen(x), 1)
#define ERROR(x) print(x, strlen(x), 2)

#define BUFFER_SIZE 1024

typedef char bool;
bool true = 1;
bool false = 0;

void print(const char* str, size_t length, int fd) {
	write(fd, str, length);
}

int main(int argc, const char* argv[]) {
	switch (argc) {
		case 0: {
			ERROR("Too few arguments\n");
			break;
		}
		default: {
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
				PRINT(buffer);
			}
			break;
		}
	}
	return 0;
}
