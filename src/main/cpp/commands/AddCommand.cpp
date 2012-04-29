#include <stdio.h>
#include <string.h>
#include <iostream>
#include <iterator>
#include <vector>
#include "AddCommand.h"
#include "../util/Tags.h"

typedef struct context {
    char* text;
    Tags tags;
} Context;

Context context;

AddCommand::AddCommand() {
}

AddCommand::~AddCommand() {
    delete context.text;
}

int AddCommand::parseCommandLine(int argc, char** argv) {
     char* text = new char[140]; // arbitrary length but we use SMS length
     Tags tags;
     context.text = text;
     context.tags = tags;
     int i = 1;
     if (!strcmp(argv[1], "add")) {
         // skip the command name
         i = 2;
     }
     printf("HERE\n");
     int treat_remaining_as_text = 0;
     for (i; i < argc; i++) {
        if (!strcmp(argv[i], "--")) {
            treat_remaining_as_text++;
            continue; // we don't care about the --
        }
        if (treat_remaining_as_text) {
            strcat(context.text, argv[i]);
            // append a space only if not last arg
            if (i != (argc - 1)) {
                strcat(context.text, " ");
            }
        } else {
            if (argv[i][0] == '+' ||
                argv[i][0] == '-' ||
                argv[i][0] == '#') {
                //printf("TAG: %s\n", argv[i]);
                context.tags.add(argv[i]);
            } else {
                strcat(context.text, argv[i]);
                // append a space only if not last arg
                if (i != (argc - 1)) {
                    strcat(context.text, " ");
                }
            }
        }
    }
    return 0;
}

int AddCommand::execute() {
    printf("TEXT: %s\n", context.text);
    return 0;
}
