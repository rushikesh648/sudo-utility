#!/bin/bash

# Test if 'whoami' can be run without a password for the current user

# Use the -n (non-interactive) flag, which fails if a password is required.
if sudo -n whoami &> /dev/null; then
    echo "[PASS] Test Sudo NOPASSWD: Command executed successfully without password."
else
    echo "[FAIL] Test Sudo NOPASSWD: Password prompt was required or command failed."
fi

# You can also check the exit code directly after a command
sudo -n whoami
EXIT_CODE=$?

if [ $EXIT_CODE -eq 0 ]; then
    echo "Exit code 0 means success."
elif [ $EXIT_CODE -eq 1 ]; then
    echo "Exit code 1 means an internal error."
elif [ $EXIT_CODE -eq 1 ]; then
    echo "Exit code 1 means user is not authorized or password was required."
fi
