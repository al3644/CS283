1. In this assignment I suggested you use `fgets()` to get user input in the main while loop. Why is `fgets()` a good choice for this application?

    > **Answer**:  It stops reading after an EOF or a new line, a line by line capability that is needed.

2. You needed to use `malloc()` to allocte memory for `cmd_buff` in `dsh_cli.c`. Can you explain why you needed to do that, instead of allocating a fixed-size array?

    > **Answer**:  Malloc would be better in terms of allocating due to its ability to handle changing memory. This would be useful due to the amount of the user's line commands.


3. In `dshlib.c`, the function `build_cmd_list(`)` must trim leading and trailing spaces from each command before storing it. Why is this necessary? If we didn't trim spaces, what kind of issues might arise when executing commands in our shell?

    > **Answer**:  It's necessary in order to parse commands correctly from the input. Otherwise, white space would cause problems, as well as incorrect amount of commands being recognized from input.

4. For this question you need to do some research on STDIN, STDOUT, and STDERR in Linux. We've learned this week that shells are "robust brokers of input and output". Google _"linux shell stdin stdout stderr explained"_ to get started.

- One topic you should have found information on is "redirection". Please provide at least 3 redirection examples that we should implement in our custom shell, and explain what challenges we might have implementing them.

    > **Answer**:  3 examples of redirection would be overwriting, appending, and merging. We can implement these with their respective operators. A challenge could be the error handling as we need to update dshlib.h and ensure it is all correct.

- You should have also learned about "pipes". Redirection and piping both involve controlling input and output in the shell, but they serve different purposes. Explain the key differences between redirection and piping.

    > **Answer**:  Redirection would be related to files in regards to input/output. Piping would be related to multiple commands/programs in regards to input/output.

- STDERR is often used for error messages, while STDOUT is for regular output. Why is it important to keep these separate in a shell?

    > **Answer**:  An error as an output can cause problems as it can be interpreted as a command by the shell, or be piped into another program.

- How should our custom shell handle errors from commands that fail? Consider cases where a command outputs both STDOUT and STDERR. Should we provide a way to merge them, and if so, how?

    > **Answer**:  The shell currently checks errors by returning the correct codes from dshlib.h. As stated from the last question, it should not be merged.
