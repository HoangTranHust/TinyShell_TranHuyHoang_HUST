#include <stdio.h>
#include <stdlib.h>

int main() {
    // Thực hiện lệnh ls để liệt kê các tệp trong thư mục hiện tại
    int result = system("ls");

    // Kiểm tra kết quả của lệnh
    if (result == -1) {
        perror("Lỗi khi thực hiện lệnh");
        exit(EXIT_FAILURE);
    }
    return 0;
}

// /home/hoangtran/Documents/TinyShell