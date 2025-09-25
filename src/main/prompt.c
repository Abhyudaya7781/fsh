#include "../header/headers.h"
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define USERNAME_BUFFER_SIZE 64
#define SYSNAME_BUFFER_SIZE 64

char userName[USERNAME_BUFFER_SIZE];
char sysName[SYSNAME_BUFFER_SIZE];
char homeDirectory[DIRECTORY_BUFFER_SIZE];
char absolutePath[DIRECTORY_BUFFER_SIZE];
char currentDirectory[DIRECTORY_BUFFER_SIZE];
char previousDirectory[DIRECTORY_BUFFER_SIZE];

int initPrompt() {
    if (getcwd(homeDirectory, DIRECTORY_BUFFER_SIZE) == NULL) {
        // TODO Handle error
        return 1;
    }
    strcpy(previousDirectory, "");
    return 0;
}

void getUsername(char* buffer) {
    // First try getlogin_r
    if (getlogin_r(buffer, USERNAME_BUFFER_SIZE) == 0 && buffer[0] != '\0') {
        return;
    }

    // Try environment variables
    const char *env_user = getenv("USER");
    if (!env_user) env_user = getenv("LOGNAME");
    if (env_user && *env_user) {
        strncpy(buffer, env_user, USERNAME_BUFFER_SIZE - 1);
        buffer[USERNAME_BUFFER_SIZE - 1] = '\0';
        return;
    }

    // Try password database
    struct passwd *pw = getpwuid(getuid());
    if (pw) {
        strncpy(buffer, pw->pw_name, USERNAME_BUFFER_SIZE - 1);
        buffer[USERNAME_BUFFER_SIZE - 1] = '\0';
        return;
    }

    // Fallback
    strcpy(buffer, "username");
}

void getSysname(char* buffer) {
    if (gethostname(buffer, SYSNAME_BUFFER_SIZE) != 0) {
        printf("Error retrieving hostname\n");
        strcpy(buffer, "hostname");
    }
}

void setCurrentDirectory() {
    if (getcwd(absolutePath, DIRECTORY_BUFFER_SIZE) == NULL) {
        // TODO Handle error
        strcpy(absolutePath, "?");
    }
    strcpy(currentDirectory, absolutePath);
    replaceHomeDirPrefix(currentDirectory);
}

void prompt() {
    getUsername(userName);
    getSysname(sysName);
    setCurrentDirectory();

#ifdef DEBUG
    printf("[PROMPT_DEBUG] absolutePath: %s\n", absolutePath);
    printf("[PROMPT_DEBUG] currentDirectory: %s\n", currentDirectory);
    printf("[PROMPT_DEBUG] previousDirectory: %s\n", previousDirectory);
#endif

    colorPrintf(COLOR_GREEN, "<");
    colorPrintf(USERNAME_COLOR, "%s", userName);
    colorPrintf(COLOR_GREEN, "@");
    colorPrintf(SYSNAME_COLOR, "%s", sysName);
    colorPrintf(COLOR_GREEN, ":%s", currentDirectory);

    if (longestTime > 2) {
        printf(" %s : %ld", longestCommand, longestTime);
    }

    colorPrintf(COLOR_GREEN, ">");
}
