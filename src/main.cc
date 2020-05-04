#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

Color ray_color(const Ray& r) {
  Vec3 unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main() {
  const int image_width = 256;
  const int image_height = 256;

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  Point3 origin(0.0, 0.0, 0.0);
  Vec3 horizontal(4.0, 0.0, 0.0);
  Vec3 vertical(0.0, 2.25, 0.0);
  Point3 lower_left_corner =
      origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, 1);
  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      auto u = double(i) / (image_width - 1);
      auto v = double(j) / (image_height - 1);
      Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
      Color pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }
  std::cerr << "\nDone.\n";

  return 0;
}
