#include <stdlib.h>

class N {
public:
    N(int i);
    void setAnnotation(char* text);
};

int main(int argc, char **argv) {
    if (argc <= 1) {
        _exit(1);
    }

    N* obj1 = new N(5);
    N* obj2 = new N(6);

    obj1->setAnnotation(argv[1]);
    

    return 0;
}