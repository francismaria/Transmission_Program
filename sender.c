#include "sender.h"

/*TODO: runRquests().
	
	This program sends through threads random numbers to another process
	in which it has to do the sum of the sent numbers. This process also
	has to write the sent numbers to a file.
	
 */

int main(int argc, char* argv[]){

	initCommunications();

	runRequests();

	closeCommunications();

	return 0;
}

void initCommunications(){
	
	if(mkfifo(FIFO_NAME, 0660) < 0){
		perror("mkfifo() error ");
		exit(EXIT_FAILURE);
	}

	if((fifo_id.fd = open(FIFO_NAME, O_WRONLY)) < 0){
		perror("open() fifo error ");
		exit(EXIT_FAILURE);
	}

	if((fifo_id.file_fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_EXCL, FILE_PERMISSIONS)) < 0){
		perror("open() file error ");
		exit(EXIT_FAILURE);
	}

	pthread_mutex_init(&mut, NULL);
}

void* sendNumber(void* arg){

	int x = *(int*)arg;

	pthread_mutex_lock(&mut);

		if(write(fifo_id.fd, &x, sizeof(int)) < 0){
			perror("Error writing to FIFO.\n");
		}

		if(write(fifo_id.file_fd, &x, sizeof(int)) < 0){
			perror("Error writing to file.\n");
		}

	pthread_mutex_unlock(&mut);	

	return NULL;
}

void createThreads(int n){
	int i;
	pthread_t tids[n];


	for(i = 0; i < n; i++){
		int* arg = malloc(sizeof(int));

		*arg = i;

		pthread_create(&tids[i], NULL, sendNumber, (void*)arg);
	}

	for(i = 0; i < n; i++){
		pthread_join(tids[i], NULL);
	}
}

void runRequests(){
	int n;

	printf("How many numbers would you like to send?\n");
	scanf("%d",&n);

	createThreads(n);

	printf("Terminated program.\n");

}
void closeCommunications(){
	
	if(close(fifo_id.file_fd) < 0){
		perror("close() file error ");
		exit(EXIT_FAILURE);
	}

	if(close(fifo_id.fd) < 0){
		perror("close() fifo error ");
		exit(EXIT_FAILURE);
	}

	if(unlink(FIFO_NAME) < 0){
		perror("unlink() error ");
		exit(EXIT_FAILURE);
	}
}