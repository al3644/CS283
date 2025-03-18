#!/usr/bin/env bats

# File: student_tests.sh
# 
# Create your unit tests suit in this file

@test "Example: check ls runs without errors" {
    run ./dsh <<EOF                
ls
EOF

    # Assertions
    [ "$status" -eq 0 ]
}

# Helper function to start the server
start_server() {
    ./dsh -s -i 0.0.0.0 -p 1234 &
    SERVER_PID=$!
    sleep 1  # Give the server time to start
}

# Helper function to stop the server
stop_server() {
    if [ -n "$SERVER_PID" ]; then
        kill -TERM $SERVER_PID 2>/dev/null
        wait $SERVER_PID 2>/dev/null || true
    fi
}

setup() {
    start_server
}

teardown() {
    stop_server
}
# Helper function 
start_server() {
    ./dsh -s -i 0.0.0.0 -p 1234 &
    SERVER_PID=$!
    sleep 3  # Give the server time to start
}

# Helper function
stop_server() {
    if [ -n "$SERVER_PID" ]; then
        kill -TERM $SERVER_PID 2>/dev/null
        wait $SERVER_PID 2>/dev/null || true
    fi
}

setup() {
    start_server
}

teardown() {
    stop_server
}

@test "Server starts successfully" {
    run pgrep -f "./dsh -s"
    echo "Server PID: $SERVER_PID"
    echo "pgrep output: $output"
    echo "pgrep status: $status"
    [ "$status" -eq 0 ]
}

@test "Client connects to server" {
    run ./dsh -c -i 127.0.0.1 -p 1234 <<EOF
exit
EOF

    echo "Client connection output: $output"
    echo "Client connection status: $status"
    [ "$status" -eq 0 ]
}

@test "Server stops using 'stop-server' command" {
    run ./dsh -c -i 127.0.0.1 -p 1234 <<EOF
stop-server
EOF

    echo "Stop server command output: $output"
    echo "Stop server command status: $status"
    [ "$status" -eq 0 ]

    run pgrep -f "./dsh -s"
    echo "pgrep output after stop-server: $output"
    echo "pgrep status after stop-server: $status"
    [ "$status" -ne 0 ]
}

@test "Server stops using 'exit' command" {
    run ./dsh -c -i 127.0.0.1 -p 1234 <<EOF
exit
EOF

    echo "exit command output: $output"
    echo "exit command status: $status"
    [ "$status" -eq 0 ]

    run pgrep -f "./dsh -s"
    echo "pgrep output after exit: $output"
    echo "pgrep status after exit: $status"
    [ "$status" -ne 0 ]
}
