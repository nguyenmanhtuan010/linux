/*Experiment with the program in Listing 24-5 (fork_whos_on_first.c) on other UNIX
implementations to determine how these implementations schedule the parent
and child processes after a fork().*/
Listing 24-5: Parent and child race to write a message after fork()
–––––––––––––––––––––––––––––––––––––––––––––– procexec/fork_whos_on_first.c
#include <sys/wait.h>
#include "tlpi_hdr.h"
int
main(int argc, char *argv[])
{
	int numChildren, j;
	pid_t childPid;
	if (argc > 1 && strcmp(argv[1], "--help") == 0)
		usageErr("%s [num-children]\n", argv[0]);
		numChildren = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-children") : 1;
		setbuf(stdout, NULL); /* Make stdout unbuffered */
		for (j = 0; j < numChildren; j++) {
			switch (childPid = fork()) {
				case -1:
					errExit("fork");
				case 0:
					printf("%d child\n", j);
					_exit(EXIT_SUCCESS);
				default:
					printf("%d parent\n", j);
					wait(NULL); /* Wait for child to terminate */
					break;
		}
	}
	exit(EXIT_SUCCESS);
}
––Listing 24-5: Parent and child race to write a message after fork()
–––––––––––––––––––––––––––––––––––––––––––––– procexec/fork_whos_on_first.c
#include <sys/wait.h>
#include "tlpi_hdr.h"
int main(int argc, char *argv[])
{
	int numChildren, j;
	pid_t childPid;
	if (argc > 1 && strcmp(argv[1], "--help") == 0)
		usageErr("%s [num-children]\n", argv[0]);
		numChildren = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-children") : 1;
		setbuf(stdout, NULL); /* Make stdout unbuffered */
		for (j = 0; j < numChildren; j++) {
			switch (childPid = fork()) {
				case -1:
				errExit("fork");
				case 0:
				printf("%d child\n", j);
				_exit(EXIT_SUCCESS);
				default:
				printf("%d parent\n", j);
				wait(NULL); /* Wait for child to terminate */
			break;
		}
	}
	exit(EXIT_SUCCESS);
}
/*
	Chương trình trong Listing 24-5 tạo ra một số lượng tiến trình con được chỉ định 
bởi tham số dòng lệnh (hoặc mặc định là 1 nếu không có tham số). Mỗi tiến trình con 
sẽ in ra một thông báo, cho biết nó là tiến trình con thứ mấy, sau đó kết thúc. Tiến 
trình cha cũng sẽ in ra thông báo của mình, sau đó chờ cho đến khi tiến trình con kết 
thúc trước khi tiếp tục.
	Khi chạy chương trình trên các hệ điều hành UNIX khác nhau, cách mà các tiến trình 
cha và con được lập lịch sau khi gọi fork() có thể khác nhau. Một số hệ điều hành có thể 
lập lịch các tiến trình con trước, trong khi một số khác có thể lập lịch tiến trình cha 
trước. Kết quả chính xác sẽ phụ thuộc vào cách thức lập lịch của hệ điều hành cụ thể và 
yếu tố ngẫu nhiên trong hệ thống.*/