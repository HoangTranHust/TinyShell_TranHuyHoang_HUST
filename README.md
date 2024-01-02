# Project Tiny Shell - Trần Huy Hoàng 20210386 - HUST

## 1. Giới thiệu về TinyShell

Tiny Shell là một giao diện dòng lệnh (command-line interface) giúp người dùng tương tác với hệ điều hành Linux bằng cách nhập lệnh và nhận kết quả trả về.
TinyShel là một phiên bản đơn giản của Shell trong hệ điều hành Linux

## 2. Chức năng quản lý tiến trình
### 2.1. Thực hiện tiến trình ở chế độ foreground, background
+ Thực hiện tiến trình ở chế độ **foreground**, ta dùng câu lệnh:
``` 
[path] fg
```
Trong đó [path] là đường dẫn đến file thực thi của tiến trình cần chạy. Ví dụ: 
``` 
./Countdown fg
```
+ Thực hiện tiến trình ở chế độ **background**, ta dùng câu lệnh:
``` 
[path] bg
```
Trong đó [path] là đường dẫn đến file thực thi của tiến trình cần chạy. Ví dụ: 
``` 
./Countdown bg
``` 
### 2.2. Hiển thị danh sách các tiến trình
Để hiển thị danh sách các tiến trình, ta dùng câu lệnh: 
``` 
list
```
### 2.3. Kill một hoặc tất cả background process
+ Để kill một background process, ta dùng lệnh:
``` 
kill [id]
```
Trong đó [id] là ID của tiến trình cần kill. Ví dụ:
``` 
kill 2
```
+ Để kill tất cả background process, ta dùng lệnh:
``` 
killa
```
### 2.4. Stop và Resume một background process
+ Để stop một background process đang chạy, ta dùng lệnh:
``` 
stop [id]
```
Trong đó [id] là ID của tiến trình cần stop. Ví dụ:
``` 
stop 2
```
+ Để resume một background process đang dừng (stop), ta dùng lệnh:
``` 
resume [id]
```
Trong đó [id] là ID của tiến trình cần resume. Ví dụ:
``` 
resume 2
```
