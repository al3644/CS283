1. Your shell forks multiple child processes when executing piped commands. How does your implementation ensure that all child processes complete before the shell continues accepting user input? What would happen if you forgot to call waitpid() on all child processes?

My implementation utilizes Waitpid() to ensure that the child processes are completed. If it was forgotten and not used, the child processes would remain on the process table and take up resources in the system, even if it has finished running.

2. The dup2() function is used to redirect input and output file descriptors. Explain why it is necessary to close unused pipe ends after calling dup2(). What could go wrong if you leave pipes open?

dup2() duplicates a file descriptor, used for piping purposes. If the unused pipe is still open, it would confuse the process reading the pipe, causing delays or waiting for data that will not arrive. Additionally, it would take up resources in the system like from waitpid().

3. Your shell recognizes built-in commands (cd, exit, dragon). Unlike external commands, built-in commands do not require execvp(). Why is cd implemented as a built-in rather than an external command? What challenges would arise if cd were implemented as an external process?

The cd command is built-in because it needs to manipulate and work with the shell's current working directory. If it was an external command, it wouldn't actually change the current shell directory, which is unhelpful.

4. Currently, your shell supports a fixed number of piped commands (CMD_MAX). How would you modify your implementation to allow an arbitrary number of piped commands while still handling memory allocation efficiently? What trade-offs would you need to consider?

For an arbitrary number of piped commands with memory allocation, I would need to dynamically allocate memory for each pipe and its command buffer, maybe storing it in the cmd_buff_t structure. However, this can cause increased complexity within the code, and an increase of system resources needed for this undertaking.
