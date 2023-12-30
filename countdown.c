#include <ncurses.h>
#include <unistd.h>

// gcc -o countdown countdown.c -lncurses
int main() {
    initscr(); // Khởi tạo môi trường ncurses
    curs_set(0); // Ẩn con trỏ nhấp nháy

    int seconds = 200;
    int minutes, seconds_remain;

    while (seconds >= 0) {
        minutes = seconds / 60;
        seconds_remain = seconds % 60;

        mvprintw(0, 0, "Countdown Timer: %02d:%02d", minutes, seconds_remain);
        refresh(); // Cập nhật màn hình

        sleep(1); // Đợi 1 giây
        seconds--;

        clear(); // Xóa màn hình để cập nhật đồng hồ
    }

    mvprintw(0, 0, "Countdown Timer: 00:00");
    refresh(); // Cập nhật màn hình
    sleep(2); // Dừng 2 giây trước khi kết thúc chương trình

    endwin(); // Kết thúc môi trường ncurses
    return 0;
}
