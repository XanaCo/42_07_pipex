
<div align=center>
<img src=https://github.com/Xanaco/42_00_Ressources/blob/main/pipexm.png alt=Xanaco's 42Project Badge/>
<h2>Final score</h2>
<img src=https://github.com/Xanaco/42_00_Ressources/blob/main/125Grade.png alt=Xanaco's 42Project Score/>
<h4>Completed + Bonus</h4>
</div>

## Overview

The `pipex` project at 42 School is a recreation of the Unix pipeline concept, mimicking the behavior of the shell command `cmd1 | cmd2`. This project introduces students to inter-process communication (IPC) and file manipulation, using pipes and redirections. In essence, the goal is to take two commands as input, run the first command on an input file, and then use its output as the input for the second command, eventually saving the output to another file.

Conceptually, the project can be seen as:
```
$> < infile cmd1 | cmd2 > outfile
```
It's an engaging way to understand how shell commands work beneath the surface, especially in the context of redirecting input and output between commands.

## Key Components

1. **Redirection**: The ability to use a file as the input or output for a command. This requires understanding and manipulating file descriptors.

2. **Pipes**: An essential part of inter-process communication, pipes allow the output of one process to be used as the input for another. In the context of `pipex`, this lets the output of `cmd1` be fed into `cmd2`.

3. **Execution of External Commands**: The project requires launching external commands from the program. This introduces students to system calls like `execve`.

4. **Error Handling**: Given that external commands can fail or files may not open correctly, robust error handling is essential to manage any unforeseen issues gracefully.

5. **Bonus Challenges**: For those looking to go the extra mile, the project offers bonus challenges like handling multiple pipes (more than two commands) or incorporating here-doc functionality.

## Key Skills Developed

1. **Understanding of IPC**: This project is an excellent introduction to Inter-Process Communication, a critical concept in operating systems and advanced programming.

2. **File Manipulation**: Through redirection, students get hands-on experience with file descriptor manipulation, an essential skill for system programming.

3. **Command Execution**: Learning how to launch and interact with external processes programmatically offers insights into how shells operate.

4. **Efficient Memory and Process Management**: Creating, managing, and closing multiple processes, as well as handling memory allocations for these tasks, emphasizes the importance of resource management.

5. **Deep Dive into Unix Concepts**: Students get a closer look at Unix mechanics, including processes, pipes, file descriptors, and the intricacies of command execution.

6. **Problem-solving and Debugging**: As with many programming projects, `pipex` demands critical thinking, problem-solving, and the ability to debug complex issues effectively.
