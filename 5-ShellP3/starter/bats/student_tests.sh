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

@test "Change directory" {
    current=$(pwd)

    cd /tmp
    mkdir -p dsh-test

    run "${current}/dsh" <<EOF
cd dsh-test
pwd
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="/tmp/dsh-testdsh3>dsh3>dsh3>cmdloopreturned0"

    # These echo commands will help with debugging and will only print
    #if the test fails
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    # Assertions
    [ "$status" -eq 0 ]
}

@test "Change directory - no args" {
    current=$(pwd)

    cd /tmp
    mkdir -p dsh-test

    run "${current}/dsh" <<EOF                
cd
pwd
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="/tmpdsh3>dsh3>dsh3>cmdloopreturned0"

    # These echo commands will help with debugging and will only print
    #if the test fails
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    # Assertions
    [ "$status" -eq 0 ]
}

@test "Which which ... which?" {
    run "./dsh" <<EOF
which which
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="/usr/bin/whichdsh3>dsh3>cmdloopreturned0"

    # These echo commands will help with debugging and will only print
    #if the test fails
    echo "Captured stdout:"
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]
}

@test "It handles quoted spaces" {
    run "./dsh" <<EOF
   echo " hello     world     "
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '\t\n\r\f\v')

    # Expected output with all whitespace removed for easier matching
    expected_output=" hello     world     dsh3> dsh3> cmd loop returned 0"

    # These echo commands will help with debugging and will only print
    #if the test fails
    echo "Captured stdout:"
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]
}

@test "Handling empty quotes" {
    run "./dsh" <<EOF
echo ""
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="dsh3>dsh3>cmdloopreturned0"

    echo "Output: $output"

    [ "$stripped_output" = "$expected_output" ]
    [ "$status" -eq 0 ]
}

@test "Change directory - invalid directory" {
    run "./dsh" <<EOF
cd none
EOF

    expected_error="cd:Nosuchfileordirectorydsh3>dsh3>cmdloopreturned0"
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    [ "$stripped_output" == "$expected_error" ]
}

@test "Change directory - too many arguments" {
    run "./dsh" <<EOF
cd arg1 arg2
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="cd:toomanyargumentsdsh3>dsh3>cmdloopreturned0"

    echo "Output: $output"

    [ "$stripped_output" = "$expected_output" ]
}

@test "ls command with arg" {
    run "./dsh" <<EOF
ls -l
EOF

    [ "$status" -eq 0 ]
}

@test "which command for ls" {
    run "./dsh" <<EOF
which ls
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="/usr/bin/lsdsh3>dsh3>cmdloopreturned0"

    echo "Output: $output"

    [ "$stripped_output" = "$expected_output" ]
}

@test "Exit command" {
    run "./dsh" <<EOF
exit
EOF
    [ "$status" -eq 0 ]
}


@test "normal echo" {
    run "./dsh" <<EOF
echo Hello, world!
EOF
    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="Hello,world!dsh3>dsh3>cmdloopreturned0"

    echo "Output: $output"

    [ "$stripped_output" = "$expected_output" ]
    [ "$status" -eq 0 ]
}

@test "Echo command - special characters" {
    run "./dsh" <<EOF
echo !@#
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="!@#dsh3>dsh3>cmdloopreturned0"

    echo "Output: $output"

    [ "$stripped_output" = "$expected_output" ]
    [ "$status" -eq 0 ]
}

@test "Pwd command" {
    current=$(pwd)

    run "./dsh" <<EOF
pwd
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')

    expected_output="${current}dsh3>dsh3>cmdloopreturned0"

    echo "Output: $output"

    [ "$stripped_output" = "$expected_output" ]
    [ "$status" -eq 0 ]
}

@test "Multiple pipes test" {
    run "./dsh" <<EOF
echo "hello" | tr '[:lower:]' '[:upper:]' | rev
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="OLLEHdsh3>dsh3>cmdloopreturned0"

    echo "Output: $output"

    [ "$stripped_output" = "$expected_output" ]
}
