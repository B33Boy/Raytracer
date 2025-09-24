#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <iostream>

#define CURSOR_START "\r"
#define CLEAR_LINE "\033[K" // ANSI escape code to clear from cursor to end of line

class scoped_timer
{
public:
    scoped_timer() : start_(std::chrono::high_resolution_clock::now())
    {
    }
    ~scoped_timer()
    {
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start_).count();
        std::clog << CURSOR_START << "\ntime elapsed: " << elapsed << "ms" << std::endl;
    }

private:
    std::chrono::high_resolution_clock::time_point start_;
};

#endif // TIMER_HPP
