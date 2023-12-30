#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAXN 100

// Struct to store process information
typedef struct {
    pid_t pid;
    int id;
    char command[100];
} ProcessInfor;

ProcessInfor processes[MAXN]; // Array of processes
int countProcess = 1; 
int ctrlCPressed = 0;

int stoppedFlag = 0; // stoppedFlag = 0: Process has not stopped, toppedFlag = 1: Process has stopped
int getProcessStatus(pid_t pid) {
    int status;
    int result = waitpid(pid, &status, WNOHANG | WUNTRACED | WCONTINUED);

    if (result == 0) {
        if(stoppedFlag == 1){
            return 1; // Process has stopped
        }
        else return 0; // Process is running
    } else if (WIFSTOPPED(status)) {
        stoppedFlag = 1;
        return 1;// Process stopped
    } else if (WIFCONTINUED(status)) {
        stoppedFlag = 0; // Reset trạng thái nếu tiến trình được tiếp tục chạy
        return 0; // Tiến trình đã được tiếp tục chạy
    }
    else {
        return 2;
    }
}

// Add a process to processes[MAXN]
void addProcess(pid_t p, char * cmd) {
    ProcessInfor process;
    process.pid = p;
    countProcess++;
    process.id = countProcess;
    strcpy(process.command, cmd);
    processes[process.id] = process;
}

// Run process in background mode
void runInBackground(char *cmd) {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        if (execlp("xterm", "xterm", "-e", cmd, (char *)NULL) == -1) {
            perror("execlp failed");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        char cmdName[MAXN] = "";
        strcat(cmdName, cmd+2);
        strcat(cmdName, " bg");
        addProcess(child_pid, cmdName);
        printf("Process is running in the background.\n");
    }
}

// Run process in foreground mode
void runInForeground(char *cmd) {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        if (execlp("xterm", "xterm", "-e", cmd, (char *)NULL) == -1) {
            perror("execlp failed");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        char cmdName[MAXN] = "";
        strcat(cmdName, cmd+2);
        strcat(cmdName, " fg");
        addProcess(child_pid, cmdName);
        printf("Process is running in the foreground.\n");
        waitpid(child_pid, NULL, 0); // Parent waits for the child to finish
    }
}

// Run child process in foreground mode or background mode
void runChildProcess(char *cmd, char * mode){
    // Check if cmd is a excutable file
    if (access(cmd, X_OK) == -1) {
        printf("Error: %s is not a valid executable.\n", cmd+2);
        return;
    }
    else{
        if (strcmp(mode, "bg") == 0) {
            runInBackground(cmd);
        } else if (strcmp(mode, "fg") == 0) {
            runInForeground(cmd);
        } else {
            printf("Invalid mode. Use 'bg' or 'fg'.\n");
        }
    }
}

// List processes
char stringStatus[3][MAXN] = {"running", "stopped", "end"}; // Status of processes
void listProcess() {
    printf("==================================================\n");
    printf("ID          COMMAND                 STATUS\n");
    printf("--------------------------------------------------\n");
    printf("1           TinyShell               running\n");
    for (int i = 2; i <= countProcess; i++) {
        printf("%-12d%-24s%-s\n", processes[i].id, processes[i].command, stringStatus[getProcessStatus(processes[i].pid)]);
    }
    printf("==================================================\n");
}

// Kill process
void killProcess(int id) {
    if (id < 1 || id > countProcess) {
        printf("Invalid process ID.\n");
        return;
    }

    pid_t pidToKill = processes[id].pid;

    // Send signal SIGTERM to kill process
    if ((kill(pidToKill, SIGTERM) == 0)) {
        printf("Process with ID %d has been terminated.\n", id);
    } else {
        perror("Error killing process");
    }
}

// Stop process
void stopProcess(int id) {
    if (id < 1 || id > countProcess) {
        printf("Invalid process ID.\n");
        return;
    }

    pid_t pidToStop = processes[id].pid;

    // Send signal SIGSTOP to stop process
    if ((kill(pidToStop, SIGSTOP) == 0) && (kill(pidToStop+1, SIGSTOP) == 0)) {
        printf("Process with ID %d has been stopped.\n", id);
    } else {
        perror("Error stopping process");
    }
}

// Resume stopped process
void resumeProcess(int id) {
    if (id < 1 || id > countProcess) {
        printf("Invalid process ID.\n");
        return;
    }

    pid_t pidToResume = processes[id].pid;

    // Send signal SIGCONT to resume process
    if ((kill(pidToResume, SIGCONT) == 0) && (kill(pidToResume+1, SIGCONT) == 0)) {
        printf("Process with ID %d has been resumed.\n", id);
    } else {
        perror("Error resuming process");
    }
}

void sigintHandler(int signum) {
    if (signum == SIGINT) {
        printf("\nCtrl+C pressed. Foreground process has terminated\n");
    }
}

void handleCtrl_C(){
    // Đăng ký hàm xử lý tín hiệu cho SIGINT
    struct sigaction sa;
    sa.sa_handler = sigintHandler;
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
}

