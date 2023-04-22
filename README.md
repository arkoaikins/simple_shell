# 0x16. C - Simple Shell
We wrote a simple Unix command interpreter (Created our own shell)
## Resources for this project
https://intranet.alxswe.com/concepts/64
https://intranet.alxswe.com/concepts/350
https://intranet.alxswe.com/rltoken/f0YU9TAhniMXWlSXtb64Yw
https://intranet.alxswe.com/rltoken/7LJOp2qP7qHUcsOK2-F3qA
https://intranet.alxswe.com/rltoken/wTSu31ZP1f7fFTJFgRQC7w

## What we learnt in this project
In this project we learnt about
- How does a shell work
- pid and a ppid
- How to manipulate the environment of the current process
- The difference between a function and a system call
- How to create processes
- the three prototypes of main
- How the shell use the PATH to find the programs
- How to execute another program with the execve system call
- How to suspend the execution of a process until one of its children terminates
- What EOF / “end-of-file” is and what it does

## Project tasks

### 0. Betty would be proud
Write a beautiful code that passes the Betty checks
filename:

### 1. Simple shell 0.1
Write a UNIX command line interpreter.

- Usage: simple_shell
Your Shell should:

- Display a prompt and wait for the user to type a command. A command line always ends with a new line.
- The prompt is displayed again each time a command has been executed.
- The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
- The command lines are made only of one word. No arguments will be passed to programs.
- If an executable cannot be found, print an error message and display the prompt again.
- Handle errors.
- You have to handle the “end of file” condition (Ctrl+D)

You don’t have to:

- use the PATH
- implement built-ins
- handle special characters : ", ', `, \, *, &, #
- be able to move the cursor
- handle commands with arguments
execve will be the core part of your Shell, don’t forget to pass the environ to it…

filname:

### 2. Simple shell 0.2
Simple shell 0.1 +

Handle command lines with arguments
filename: 

### 3. Simple shell 0.3
Simple shell 0.2 +

Handle the PATH
fork must not be called if the command doesn’t exist
filename:

### 4. Simple shell 0.4
Simple shell 0.3 +

Implement the exit built-in, that exits the shell
Usage: exit
You don’t have to handle any argument to the built-in exit
filename:

### 5. Simple shell 1.0
Simple shell 0.4 +

Implement the env built-in, that prints the current environment
file name

## Authors:
### Edwin Aikins: [@arkoaikins](https://github.com/arkoaikins)
### Gideon Selorm Attakpah: [@iamgideonchrist](https://github.com/iamgideonchrist)
