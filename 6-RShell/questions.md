1. How does the remote client determine when a command's output is fully received from the server, and what techniques can be used to handle partial reads or ensure complete message transmission?

The remote client determines when a command's output is fully received from the server when it receives the EOF marker. RDSH_EOF_CHAR would be sent. Looping and reading over the input would be a technique used to handle partial reads or to ensure complete message transmission.

2. This week's lecture on TCP explains that it is a reliable stream protocol rather than a message-oriented one. Since TCP does not preserve message boundaries, how should a networked shell protocol define and detect the beginning and end of a command sent over a TCP connection? What challenges arise if this is not handled correctly?

A networked shell could define and detect the beginning and end of a command sent over a TCP connection by using different techniques, such as delimiters or fixed length headers. If this is not handled correctly, it could cause infinite looping on servers, or deadlocks.

3. Describe the general differences between stateful and stateless protocols.

Stateful protocols "retains" context and interactions done by the user. The client would thus rely on the server in order to keep track of things. Stateless protocols would be the opposite, where it treats each request as something independent. As a result, the client would not rely on the server as much.

4. Our lecture this week stated that UDP is "unreliable". If that is the case, why would we ever use it?

UDP is "unreliable" in the sense that it does not offer guarantees. However, it more often then not gets the job done. It is also lightweight and more "simple" protocol.

5. What interface/abstraction is provided by the operating system to enable applications to use network communications?

The socket interface would be the interface/abstraction that is provided by the operating system to enable applications to use network communications. It allows applications to send and receive data over the network, while closing down connections.
