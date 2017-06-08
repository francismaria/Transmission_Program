#ifndef _RECEIVER_H_
#define _RECEIVER_H_

#include "transmissionLibrary.h"

FIFO fifo_id_receiver;

char* FILE_NAME = "receiver_info.txt";

int sum = 0;

pthread_mutex_t mut;

void initCommunications();

void runRequests();

void closeCommunications();

#endif