#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

#define CURSOR_START "\r"
#define CLEAR_LINE "\033[K" // ANSI escape code to clear from cursor to end of line

int main()
{
    int image_width = 256;
    int image_height = 256;

    std::cout << "P3\n"
              << image_width << ' ' << image_height
              << "\n255\n";

    for (int j = 0; j < image_height; j++)
    {
        std::clog << CURSOR_START << CLEAR_LINE << "Scanlines remaining: " << (image_height - j) << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            double r = static_cast<double>(i) / (image_width - 1);
            double g = static_cast<double>(j) / (image_height - 1);
            double b = 0.0;

            int ir = static_cast<int>(std::lround(r * 255));
            int ig = static_cast<int>(std::lround(g * 255));
            int ib = static_cast<int>(std::lround(b * 255));

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::clog << CURSOR_START << CLEAR_LINE << "Done.\n ";
}
