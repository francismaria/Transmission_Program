#include "receiver.h"

int main(int argc, char* argv[]){

	initCommunications();

	runRequests();

	closeCommunications();

	return 0;
}

void initCommunications(){

	if((fifo_id_receiver.fd = open(FIFO_NAME, O_RDONLY)) < 0){
		perror("open() FIFO error ");
		exit(EXIT_FAILURE);
	}

	if((fifo_id_receiver.file_fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_EXCL, FILE_PERMISSIONS)) < 0){
		perror("open() file error ");
		exit(EXIT_FAILURE);
	}

}

void closeCommunications(){

	if(close(fifo_id_receiver.fd) < 0){
		perror("close() error ");
		exit(EXIT_FAILURE);
	}

	if(close(fifo_id_receiver.file_fd) < 0){
		perror("Error closing receiver's FIFO ");
		exit(EXIT_FAILURE);
	}
}