# CS604P Assignment 1 - Two-Way IPC Using Pipes

Operating System Practical (CS604P) Assignment # 01, Fall 2026
Name: Sana Khalid
Student ID: BC240420011

## Task
Two-way Inter-Process Communication (IPC) between a parent process and a child process using two unnamed pipes in C.

- Parent sends "How are you? What's your VUID?" to the child through the first pipe.
- Child reads and displays the message.
- Child sends "I am fine. My VUID is BC240420011" to the parent through the second pipe.
- Parent reads and displays the reply.

## Compile and run
```
gcc two_way_ipc_BC240420011.c -o two_way_ipc
./two_way_ipc
```

## Output
```
Child received: How are you? What's your VUID?
Parent received: I am fine. My VUID is BC240420011
```

## Files
- two_way_ipc_BC240420011.c - C program
- README.md - this file
