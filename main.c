int syscall(int id, int a1, int a2, int a3) {
    int r = -1;
    asm (
        "syscall"
        : "=a"(r)
        : "r"(id), "D"(a1), "S"(a2), "d"(a3)
        : "rcx", "r11", "memory"
    );
    return r;
}

void write(int fd, const char* buf, int size) {
    syscall(1, fd, (int)buf, size);
}

int strlen(const char* str) {
    int i = 0;
    for(;;) {
        if (str[i] == 0)
            break;
        i++;
    }
    return i;
}

void print(const char* str) {    
    write(1, str, strlen(str));
}

void exit(int code) {
    syscall(60, code, 0, 0);
}

int alog(int a, int b) {
    int i = 0;
    while (a > 0) {
        a /= b;
        i++;
    }
    return i;
}

void print_number(const char* digits, int n) {
    if (n < 0) {
        print("-");
        n = -n;
    }
    int dc = alog(n, 10), S = 1;
    for (int i = 1; i < dc; i++) {
        S *= 10;
    }
    while (S > 0) {
        int d = (n / S) % 10;
        write(1, digits+d, 1);
        S /= 10;
    }
}

int main() {
    const char* wh = "simple demo\n";
    const char* digits = "01234567890";
    print(wh);
    int x = 1, y = 0, z;
    while (x < 3e8) {
        z = x + y;
        y = x;
        x = z;
        print_number(digits, x);
        print("\n");
    }
    return 0;
}

void _start() {
    int c = main();
    exit(c);
}