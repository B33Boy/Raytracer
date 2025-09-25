#include "camera.hpp"
#include "raytracer.hpp"
#include "sphere.hpp"
#include "timer.hpp"

#include <iostream>

int main()
{
    scoped_timer timer;

    // ====== Camera ======
    constexpr cam_params params;
    constexpr camera cam(params);

    // ====== World ======
    hittable_list world;
    world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

    cam.render(world);
}
