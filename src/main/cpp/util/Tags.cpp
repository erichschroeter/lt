#include<stdio.h>
#include <set>
#include <string>
#include "Tags.h"

std::set<std::string>* tags;

Tags::Tags() {
    tags = new std::set<std::string>();
}

Tags::~Tags() {
    delete tags;
}

int Tags::add(std::string tag) {
    tags->insert(tag);
    return 0;
}

int Tags::remove(std::string tag) {
    std::set<std::string>::iterator tag_iter = tags->find(tag);
    if (tag_iter == tags->end()) {
        return 0;
    }
    printf("HERE\n");
    tags->erase(tag_iter);
    return 1;
}

int Tags::contains(std::string tag) {
    return 0;
}

std::vector<std::string> Tags::asVector() {
    std::vector<std::string>* v = new std::vector<std::string>();
    std::set<std::string>::iterator it = tags->begin();
    while (it != tags->end()) {
        v->push_back(*it);
        it++;
    }
    return *v;
}
