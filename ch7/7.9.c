#include <stdio.h>

// This macro version saves time, because there is no function call overhead. However,
// it does use up more space, as the macro is expanded everywhere in the source code
// where it is invoked.
#define isupper_time(c) ((c) >= 'A' && (c) <= 'Z') ? 1 : 0

// This function version is not as fast as the macro one, as it takes time to call the
// function at runtime everywhere it is invoked. But it doesn't incur the same space costs.
int isupper_space(char c) {
    return (c >= 'A' && c <= 'Z');
}