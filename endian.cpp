
#include <iostream>
using namespace std;

// Test if your machine is big endian or little endian
int main()
{
    unsigned int i = 1;
    char *c = (char *)&i;
    if (*c)
        cout << "Little endian";
    else
        cout << "Big endian";
    return 0;
}
