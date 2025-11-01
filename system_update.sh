#!/bin/bash

# A simple script to update and upgrade the system packages.

echo "Starting system maintenance script..."
echo "This script requires superuser privileges and will prompt you for your password."

# 1. Update the local package list
echo "--- Running: sudo apt update ---"
# 'sudo' prompts for the user's password and runs 'apt update' as root.
sudo apt update

# Check the exit status of the previous command
if [ $? -eq 0 ]; then
    echo "Package lists updated successfully."
else
    echo "[ERROR] Failed to update package lists. Exiting."
    exit 1
fi

# 2. Upgrade all installed packages
echo "--- Running: sudo apt upgrade -y ---"
# '-y' flag assumes 'yes' to all prompts, allowing unattended execution.
sudo apt upgrade -y

# Check the exit status of the previous command
if [ $? -eq 0 ]; then
    echo "System upgrade complete."
else
    echo "[WARNING] System upgrade may have encountered errors."
fi

# 3. Clean up unneeded packages
echo "--- Running: sudo apt autoremove -y ---"
sudo apt autoremove -y

echo "System maintenance finished!"
