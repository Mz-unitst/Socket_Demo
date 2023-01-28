#include <stdio.h>
#include <winsock2.h>
int main() {
//    printf("Hello, World!\n");
#ifdef WIN32
// TODO: WINDOWS平台的特定代码
    printf("Hello, Win!\n");
#else
    // TODO: LINUX平台的特定代码
    printf("Hello, Linux!\n");
#endif
    return 0;
}
