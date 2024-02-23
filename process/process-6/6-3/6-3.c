/*Implement setenv() and unsetenv() using getenv(), putenv(), and, where necessary,
code that directly modifies environ. Your version of unsetenv() should check to see
whether there are multiple definitions of an environment variable, and remove
them all (which is what the glibc version of unsetenv() does).*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int setenv(const char *name, const char *value, int overwrite) {
    char *env_entry;
    size_t size = strlen(name) + strlen(value) + 2; // name=value\0

    env_entry = malloc(size);
    if (env_entry == NULL) {
        return -1;
    }

    snprintf(env_entry, size, "%s=%s", name, value);

    if (overwrite || getenv(name) == NULL) {
        return putenv(env_entry);
    }

    free(env_entry);
    return 0;
}

int unsetenv(const char *name) {
    char **ep = environ;
    int found = 0;

    while (*ep) {
        if (strncmp(*ep, name, strlen(name)) == 0 && (*ep)[strlen(name)] == '=') {
            char **next = ep + 1;
            found = 1;
            while (*next) {
                *ep++ = *next++;
            }
            *ep = NULL;
        } else {
            ep++;
        }
    }

    return found ? 0 : -1;
}

int main() {
    setenv("TEST_VAR", "test_value", 1);
    printf("TEST_VAR=%s\n", getenv("TEST_VAR"));

    unsetenv("TEST_VAR");
    printf("TEST_VAR=%s\n", getenv("TEST_VAR"));

    return 0;
}

