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

	pthread_mutex_init(&mut, NULL);

}

void* operateRequests(void* arg){
	
	int n = *(int*)arg;
	char* buf = malloc(sizeof(char)*13);

	pthread_mutex_lock(&mut);

		sprintf(buf, "Received: %d\n", n);

		if(write(fifo_id_receiver.file_fd, buf, strlen(buf)) < 0){
			perror("Error writing to 'receiver_info.txt'");
		}

		sum += n;

	pthread_mutex_unlock(&mut);

	return NULL;
}

void runRequests(){
	pthread_t tids[500];		//this should be given by the SENDER!!! - 500 is just a max value

	printf("I am going to start receiving requests.\n");

	int* n = malloc(sizeof(int));

	int k = 0, j;

	while(read(fifo_id_receiver.fd, n, sizeof(int))){

		pthread_create(&tids[k], NULL, operateRequests, (void*)n);

		k++;			//just to keep track of how much threads exist
	}

	for(j = 0; j < k; j++){
		pthread_join(tids[j], NULL);
	}

	printf("Total SUM: %d", sum);
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