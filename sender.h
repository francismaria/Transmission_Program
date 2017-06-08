#ifndef _SENDER_H_
#define _SENDER_H_

#include "transmissionLibrary.h"

FIFO fifo_id;

char* FILE_NAME = "/tmp/sender_info.txt";

pthread_mutex_t mut;

void initCommunications();

void runRequests();

void closeCommunications();

#endif