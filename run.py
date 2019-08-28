import subprocess
import sys

def main():
    subprocess.run((["./emulator.out", sys.argv[1]]))
    
if __name__ == "__main__":
    main()
