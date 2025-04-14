#include "camera.h"
#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

double hit_sphere(const point3& center, double radius, const ray& r) {
  vec3 oc = r.origin() - center;
  auto a = r.direction().length_squared(); 
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius * radius;
  auto discriminant = half_b*half_b - a*c;

  if (discriminant < 0) {
    return -1.0;
  }
  else {
    return (-half_b - sqrt(discriminant)) / a;
  }
}

color ray_color(const ray& r, const hittable& world) {
  hit_record rec;

  if (world.hit(r, interval(0, infinity), rec)) {
    return 0.5 * (rec.normal + color(1,1,1));
  }

  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0-a)*color(1.0,1.0,1.0) + a*color(0.5,0.7,1.0);
}

int main() {


  // World
  hittable_list world;
  world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
  world.add(make_shared<sphere>(point3(0,-100.5,-1),100));

  // Camera
  camera cam;
  cam.aspect_ratio = 16.0/9.0;
  cam.image_width = 400;

  cam.render(world);

}
