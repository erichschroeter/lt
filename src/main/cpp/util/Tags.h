#ifndef TAGS_H
#define TAGS_H

class Tags {
public:
    Tags();
    ~Tags();

    int add(char* tag);
    int remove(char* tag);  
    int contains(char* tag);  
};

#endif
