import subprocess
import sys

T_RED = "\033[38;2;255;0;0m"
T_GREEN = "\033[38;2;0;255;0m"
T_BLUE = "\033[38;2;0;0;255m"
T_YELLOW = "\033[38;2;255;255;0m"
T_CYAN = "\033[38;2;0;255;255m"
T_RESET = "\033[0m"
T_MAGENTA = "\033[0;35m"


def add(flag, name):
    if flag == "-f":
        try:
            subprocess.run(["touch", name], check=True, capture_output=True, text=True)
            print(T_GREEN, f"файл: {name} успешно создан", T_RESET)
        except subprocess.CalledProcessError as e:
            print(T_RED, "ошибка создания файла", T_RESET)
            print(e.stderr)
            sys.exit(1)

    elif flag == "-d":
        try:
            subprocess.run(["mkdir", name], check=True, capture_output=True, text=True)
            print(T_GREEN, f"директория: {name} успешно создана", T_RESET)
        except subprocess.CalledProcessError as e:
            print(T_RED, "ошибка создания папки", T_RESET)
            print(e.stderr)
            sys.exit(1)
    else:
        print(T_YELLOW, "неизвестный флаг", T_RESET)
        print(T_YELLOW, "использование: add -f filename или add -d foldername", T_RESET)


def main():
    flag = None
    name = None
    try:
        add(flag, name)
    except subprocess.CalledProcessError:
        print(T_RED, "ошибка создания папки или файла", T_RESET)
        sys.exit(1)


if __name__ == "__main__":
    main()
