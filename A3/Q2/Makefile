output:
	gcc -pthread Q2_P1_fifo.c -o P1_fifo.o
	gcc -pthread Q2_P2_fifo.c -o P2_fifo.o
	gcc -pthread Q2_P1_socket.c -o P1_socket.o
	gcc -pthread Q2_P2_socket.c -o P2_socket.o
	gcc -pthread Q2_P1_shmem.c -o P1_shmem.o -lrt
	gcc -pthread Q2_P2_shmem.c -o P2_shmem.o -lrt

clean:
	rm *.o
	rm -f Q2_FIFO1 Q2_FIFO2 Q2_SOCKET
