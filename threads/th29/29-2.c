/*Aside from the absence of error checking and various variable and structure
declarations, what is the problem with the following program?*/


static void *threadFunc(void *arg)
{
	struct someStruct *pbuf = (struct someStruct *) arg;
	/* Do some work with structure pointed to by 'pbuf' */
}
int main(int argc, char *argv[])
{
	struct someStruct buf;
	pthread_create(&thr, NULL, threadFunc, (void *) &buf);
	pthread_exit(NULL);
}
/*
Trong chương trình trên, có một vấn đề nghiêm trọng là khi thread chạy hàm 
threadFunc, nó truy cập vào địa chỉ của biến buf trong hàm main. Tuy nhiên, 
sau khi hàm main kết thúc và gọi pthread_exit(NULL);, biến buf sẽ không còn 
tồn tại nữa và việc truy cập vào nó sẽ dẫn đến undefined behavior. Để sửa lỗi 
này, bạn cần đảm bảo rằng buf còn tồn tại khi thread sử dụng nó, ví dụ như sử 
dụng malloc để cấp phát bộ nhớ động cho buf.*/
