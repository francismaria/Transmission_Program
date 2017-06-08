#ifndef _TRANSMISSIONLIBRARY_H_
#define _TRANSMISSIONLIBRARY_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FILE_PERMISSIONS 0660

typedef struct fifo_info{
	int fd;
	int file_fd;
} FIFO;

char* FIFO_NAME = "/tmp/transmission_fifo";

#endif