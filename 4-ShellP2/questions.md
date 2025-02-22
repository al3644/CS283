1. Can you think of why we use `fork/execvp` instead of just calling `execvp` directly? What value do you think the `fork` provides?

    > **Answer**: Fork would create a new child process to be replaced, rather than replacing the entire parent process.

2. What happens if the fork() system call fails? How does your implementation handle this scenario?

    > **Answer**: In my implementation, it would print out an error message in relation to the fork process and continue to run.

3. How does execvp() find the command to execute? What system environment variable plays a role in this process?

    > **Answer**: Execvp() would search through the listed directories in PATH in order to find the command.

4. What is the purpose of calling wait() in the parent process after forking? What would happen if we didn’t call it?

    > **Answer**: It waits for the child process to finish. If waitpid was not called, the child process would still remain, which can cause errors and take up memory resources.

5. In the referenced demo code we used WEXITSTATUS(). What information does this provide, and why is it important?

    > **Answer**: The status code can be evaluated to show that the process was successfully or encountered an error.

6. Describe how your implementation of build_cmd_buff() handles quoted arguments. Why is this necessary?

    > **Answer**: The process checks to see if quotes are detected, and works it as a boolean. It continues until the end quote, closing and terminating the string. This allows multi-strings to be counted as one argument.

7. What changes did you make to your parsing logic compared to the previous assignment? Were there any unexpected challenges in refactoring your old code?

    > **Answer**: Due to the removal of the piping logic and clist, there were challenges involved. Instead of storing multiple commands, single commands were done by tokenizing, costing some time.

8. For this quesiton, you need to do some research on Linux signals. You can use [this google search](https://www.google.com/search?q=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&oq=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&gs_lcrp=EgZjaHJvbWUyBggAEEUYOdIBBzc2MGowajeoAgCwAgA&sourceid=chrome&ie=UTF-8) to get started.

- What is the purpose of signals in a Linux system, and how do they differ from other forms of interprocess communication (IPC)?

    > **Answer**: Signals are notifications to show an event occurred, whether it is a termination or interruption. IPC are direct data transfer while signals are not.

- Find and describe three commonly used signals (e.g., SIGKILL, SIGTERM, SIGINT). What are their typical use cases?

    > **Answer**: SIGKILL: Forces a process to terminate immediately. This cannot be ignored. 
		  SIGTERM: Requests a process to be terminated, which can be ignored. 
		  SIGINT: Terminates a process by "Crtl-C"

- What happens when a process receives SIGSTOP? Can it be caught or ignored like SIGINT? Why or why not?

    > **Answer**: SIGSTOP will pause (not terminate) a process. Both of these can be ignored through a process, but is considered to be bad practice.
