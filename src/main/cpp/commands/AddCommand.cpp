#include <stdio.h>
#include <string>
#include <iostream>
#include <iterator>
#include <vector>
#include "AddCommand.h"
#include "../util/Tags.h"

typedef struct context {
    std::string* text;
    Tags* tags;
} Context;

typedef struct tag {
    std::string* tag;
    std::string* value;
} Tag;

Context context;

AddCommand::AddCommand() {
}

AddCommand::~AddCommand() {
    //printf("deleting context.text\n");
    //delete context.text;
    //printf("deleting context.tags\n");
    //delete context.tags;
}

Tag* parseTag(std::string text) {
    std::string key;
    std::string value;
    int i;
    switch (text.at(0)) {
    case '-':
    case '+':
    case '#':
        i = 1;
        break;
    default:
        i = 0;
        break;
    }
    Tag* tag = new Tag();
    int separator = text.find_first_of(":");
    if (separator == std::string::npos) {
        // key is from beginning to the end if no separator
        key = text.substr(i, text.length() - i);
    } else {
        // key is from beginning to the separator
        key = text.substr(i, separator);
        // value is from separator to the end
        value = text.substr(separator, text.length() - i - key.length());
        tag->value = &value;
    }
    tag->tag = &key;
    return tag;
}

/**
 * Parses the command line to add a life tracker entry.
 * <p>
 * The command line syntax is as follows:
 *
 * <pre>
 * [tags...] <entry text>
 * </pre>
 *
 * Tag syntax is <code>[(+|-|#)[a-zA-Z-_]]</code>.
 */
int AddCommand::parseCommandLine(int argc, char** argv) {
     // require at least 2 arguments
     if (argc < 2) {
         return 0;
     }
     std::string text;
     Tags* tags = new Tags();
     context.text = &text;
     context.tags = tags;
     int i = 1;
     std::string arg = argv[1];
     if (!arg.compare("add")) {
         // skip the command name
         i = 2;
     }
     int treat_remaining_as_text = 0;
     for (i; i < argc; i++) {
        arg = argv[i];
        if (!arg.compare("--")) {
            treat_remaining_as_text++;
            continue; // we don't care about the --
        }
        if (treat_remaining_as_text) {
            context.text->append(argv[i]);
            // append a space only if not last arg
            if (i != (argc - 1)) {
                context.text->append(" ");
            }
        } else {
            if (argv[i][0] == '-' ||
                argv[i][0] == '+' ||
                argv[i][0] == '#') {
                Tag* tag = parseTag(argv[i]);
                switch (argv[i][0]) {
                case '-':
                    context.tags->remove(argv[i]);
                    break;
                case '+':
                    context.tags->add(argv[i]);
                    break;
                case '#': // fall through
                default:
                    if (context.tags->contains(argv[i])) {
                        context.tags->remove(argv[i]);
                    } else {
                        context.tags->add(argv[i]);
                    }
                    break;
                }
                delete tag;
            } else {
                context.text->append(argv[i]);
                // append a space only if not last arg
                if (i != (argc - 1)) {
                    context.text->append(" ");
                }
            }
        }
    }

    return 0;
}

int AddCommand::execute() {
    printf("TEXT: %s\n", (*context.text).c_str());
    std::vector<std::string> tags = context.tags->asVector();
    std::vector<std::string>::iterator iter = tags.begin();
    while (iter != tags.end()) {
        printf("TAGS: %s\n", (*iter).c_str());
        iter++;
    }
    return 0;
}
