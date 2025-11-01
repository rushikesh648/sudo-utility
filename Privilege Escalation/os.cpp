#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For setuid, getuid, execvp
#include <sys/types.h> // For uid_t

// The user ID of the root user
#define ROOT_UID 0

// --- 1. Security Check Simulation ---
int check_sudoers_config(uid_t invoker_uid) {
    // In a real sudo, this function would:
    // 1. Prompt the user for a password (read from standard input).
    // 2. Validate the password against the system's authentication service.
    // 3. Parse /etc/sudoers to see if invoker_uid is authorized to run the command.
    
    // For this conceptual code, we'll just check if the UID is non-root (i.e., a normal user)
    if (invoker_uid != ROOT_UID) {
        printf("[DEBUG] User (UID %d) needs authorization. (Simulated PASS)\n", invoker_uid);
        return 1; // Simulated Success
    }
    printf("[DEBUG] User is already root (UID 0). Skipping authorization.\n");
    return 1;
}

// --- 2. Main Sudo Logic ---
int main(int argc, char *argv[]) {
    // We assume this program is compiled with the setuid bit set for root,
    // so it initially runs with an effective UID of 0 (root).
    
    // The actual user who executed this program (e.g., UID 1000)
    uid_t invoker_uid = getuid(); 

    // Command to execute (e.g., "reboot" if user typed: ./mysudo reboot)
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        return 1;
    }
    
    // --- Step A: Initial Privilege Drop (Secure Handling) ---
    // A real sudo immediately drops privileges to the invoker's user ID
    // while keeping root privileges available (using setresuid/seteuid) 
    // to prevent security issues while processing inputs.
    if (setuid(invoker_uid) != 0) {
        perror("ERROR: Could not drop privileges");
        return 1;
    }
    printf("[RUNTIME] Privileges temporarily dropped to invoker's UID (%d).\n", geteuid());

    // --- Step B: Authorization Check ---
    if (!check_sudoers_config(invoker_uid)) {
        fprintf(stderr, "[RUNTIME] Authorization failed. Command denied.\n");
        return 1;
    }

    // --- Step C: Privilege Re-escalation (The Core Sudo Action) ---
    printf("[RUNTIME] Authorization granted. Re-escalating privileges to root.\n");
    
    // The call to setuid(0) fails unless the program is running with an effective
    // UID of 0 or the proper capabilities. This is why the real sudo binary must 
    // be owned by root and have the SUID bit set.
    if (setuid(ROOT_UID) != 0) {
        perror("ERROR: Failed to elevate privileges to root (setuid(0))");
        return 1;
    }
    printf("[RUNTIME] Effective User ID is now root (UID %d).\n", geteuid());

    // --- Step D: Execute the Target Command ---
    // Use execvp to replace the current process with the desired command (e.g., 'reboot')
    printf("[RUNTIME] Executing command: %s...\n", argv[1]);
    
    // argv + 1 passes the command and its arguments (e.g., ["reboot", "now"])
    execvp(argv[1], &argv[1]);

    // If execvp succeeds, this code is never reached.
    // If it fails (e.g., command not found), it returns and we print an error.
    perror("ERROR: Command execution failed");
    return 1; 
}
