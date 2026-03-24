# просто перепись tty.sh на питон

import subprocess
import sys

def main():
    tty_path = "/dev/tty1"
    baudrate = 9600
    if tty_path != "/dev/tty1":
        print(f"[err]: [device {tty_path} is undefind!]\n")
        sys.exit(1)
    else:
        try:
            subprocess.run(f"agetty -L {tty_path} {baudrate}", check=True, capture_output=True, text=True)
        except subprocess.CalledProcessError as e:
            print("[err]: [failed to init tty process]\n")
            print(e.stderr)
            sys.exit(1)

if __name__ == "__main__":
    main()
