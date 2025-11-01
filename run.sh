[run]
# Example 1: Trying a command that normally needs root access
python simple_sudo.py "ls -l /root"

# Example 2: Trying a command that works for any user
python simple_sudo.py "whoami"

# Example 3: with auth
python sudo_with_auth.py "whoami"
