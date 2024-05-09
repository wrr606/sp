#include "net.h"
#include "vector.h"

Vector_t vector;

void* serv(void* idx){//thread 的 function
	int sockfd = vector.data[*(int*)idx].id;
	while(1){
		char buffer[SMAX];
        int bytes_read = read(sockfd, buffer, SMAX);
        if (bytes_read == 0) {
            close(sockfd);
            vector.data[*(int*)idx].id = -1;
            break;
        }
	}
}

net_t net;
void* loop(void* arg){
	while(1) { // 主迴圈：等待 client 連進來，然後啟動 serv 為其服務
		int connfd = net_accept(&net); // 等待連線進來
		assert(connfd >= 0);
		vector_push_back(&vector,connfd);
		int* idx_ptr = (int*)malloc(sizeof(int)); 
		*idx_ptr = vector.size - 1;
		pthread_create(&vector.data[vector.size-1].thread, NULL, serv, (void*)idx_ptr);
		//printf("ID:%d\n",vector.data[vector.size-1].id);
	}
}

void broadcast(char cmd[]){//廣播
	for(int i=0;i<vector.size;i++)
		if(vector.data[i].id != -1)
			write(vector.data[i].id, cmd, strlen(cmd));
}

int main(int argc, char *argv[]) {
	vector=vector_create();
	pthread_t main_loop;
	int port = (argc >= 2) ? atoi(argv[1]) : PORT;
	net_init(&net, TCP, SERVER, port, NULL);
	net_bind(&net);
	net_listen(&net);
	pthread_create(&main_loop, NULL, &loop, NULL);
	while(1){
		char cmd[SMAX],buffer[SMAX];
		printf("%s $ ", "localhost");           // 印出提示訊息
		fgets(cmd, SMAX, stdin);                // 等待使用者輸入命令！
		broadcast(cmd);
		if (strncmp(cmd, "exit", 4)==0) break; // 若是 exit 則離開！

		FILE* pipe=popen(cmd,"r");
		while (fgets(buffer, SMAX, pipe) != NULL) {
			fprintf(stdout, "%s", buffer); // 寫入標準輸出
			broadcast(buffer);
		}
		pclose(pipe);

		broadcast("\n"); // 至少要回應 1byte ，否則 client 會讀不到而導致當掉
	}
}