#include <stdio.h>
#include <stdarg.h>
#include <getopt.h>
#include "commands/AddCommand.h"

static int verbose_flag;

void printv(char* str, ...) {
    if (!verbose_flag) {
        return;
    }
    va_list args;
    va_start(args, str);
    vprintf(str, args);
    va_end(args);
}

int main(int argc, char** argv)
{
    static struct option long_options[] =
    {
        {"verbose", no_argument, &verbose_flag, 1},
        {"version", no_argument, NULL, 0}
    };

    int c = getopt_long(argc, argv, "vh", long_options, 0);

    switch(c)
    {
    case 'v':
        printf("1.0.0\n");
        break;
    case 'h':
        //print_help();
        break;
    default:
        break;
    }

    AddCommand cmd;
    printv("execute command: %s\n", "AddCommand");
    cmd.execute(argc, argv);

    return 0;
}
