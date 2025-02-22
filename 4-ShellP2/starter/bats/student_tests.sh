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

@test "Handling empty quotes" {
    run "./dsh" <<EOF
echo ""
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="dsh2>dsh2>cmdloopreturned0"

    echo "Output: $output"

    [ "$stripped_output" = "$expected_output" ]
    [ "$status" -eq 0 ]
}

@test "Change directory - invalid directory" {
    run "./dsh" <<EOF
cd none
EOF

    expected_error="cd:Nosuchfileordirectorydsh2>dsh2>cmdloopreturned0"
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    [ "$stripped_output" == "$expected_error" ]
}

@test "Change directory - too many arguments" {
    run "./dsh" <<EOF
cd arg1 arg2
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="cd:toomanyargumentsdsh2>dsh2>cmdloopreturned0"

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
    expected_output="/usr/bin/lsdsh2>dsh2>cmdloopreturned0"

    echo "Output: $output"

    [ "$stripped_output" = "$expected_output" ]
}
