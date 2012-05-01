#ifndef TAGS_H
#define TAGS_H

#include <string>
#include <vector>

class Tags {
public:
    Tags();
    ~Tags();

    int add(std::string tag);
    int remove(std::string tag);  
    int contains(std::string tag);  
    std::vector<std::string> asVector();
};

#endif
