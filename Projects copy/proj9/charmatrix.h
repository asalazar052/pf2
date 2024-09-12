#ifndef charmatrix_h
#define charmatrix_h
#include <vector>
#include <string>
#include "instancecounter.h"

using std::vector;
using std::string;

class CharMatrix : public InstanceCounter{

    protected:
        vector<string> chars;

    public:
        CharMatrix();
        CharMatrix(const CharMatrix& other);
        virtual ~CharMatrix();
        void resize(int width, int height);
        int width();
        int height();
        char get(int x, int y);
        void put(int x, int y, char c);

};

#endif