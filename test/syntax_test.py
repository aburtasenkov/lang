import subprocess
import os

def status_code(status):
    return "Good" if not status else "Bad"

# Execute the Bash script
try:
    output = subprocess.run(["bash", "compile.bash"], check=True)
    print("Compiling status code -", status_code(output.returncode))
except subprocess.CalledProcessError as e:
    print(f"Error executing script: {e}")


