#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

#include <deque>

using namespace std;

class Image
{
public:
    deque <deque <char>> Board;

    Image(const int&, const int&, const char&, const char&, const char&, const char&, const char&,  const char&);
    ~Image();

    class Main_frame
    {
        int x, y, width, height;

    public:
        Main_frame(const int&, const int&, const int&, const int&, const char&, const char&, const char&, const char&, const char&, const char&);
        ~Main_frame();

        void make_frame();
    };

};






#endif // MAIN_FRAME_H
