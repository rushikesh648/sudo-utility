import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class SudoCommandExecutor {

    public static void main(String[] args) {
        // Command that requires elevated privileges (Linux example)
        String command = "sudo apt update";
        
        System.out.println("Executing command: " + command);

        try {
            // 1. Execute the external command using Runtime
            // This relies on the native 'sudo' program being present in the system's PATH.
            Process process = Runtime.getRuntime().exec(command);

            // 2. Read the command's output (stdout)
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println("OUTPUT: " + line);
            }

            // 3. Read the command's error stream (stderr)
            BufferedReader errorReader = new BufferedReader(new InputStreamReader(process.getErrorStream()));
            while ((line = errorReader.readLine()) != null) {
                System.err.println("ERROR: " + line);
            }

            // 4. Wait for the process to finish and get the exit code
            int exitCode = process.waitFor();
            System.out.println("\nCommand finished with exit code: " + exitCode);

        } catch (IOException e) {
            System.err.println("Error executing command. Check if 'sudo' and 'apt' exist: " + e.getMessage());
        } catch (InterruptedException e) {
            System.err.println("Process interrupted: " + e.getMessage());
        }
    }
              }
