#include "rtweekend.h"

#include "camera.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "moving_sphere.h"
#include "test_raytracer.h"
 
color ray_color(const ray &r, const hittable_list& world, int depth) {
    hit_record rec;

    //if we have exceeded the max depth we return
    if(depth <= 0) {
        return color(0, 0, 0);
    }

    double shadowAcneOffset = 0.001; //When a ray reflects off a surface, its origin is at t = 0. 
                                     //We want to ignore this as a hit and due to floating point offset should ignore from t = 0.001
                                     //or some offset or this ray will be considered as a shadow and we will have self shadow.
    if(world.hit(r, shadowAcneOffset, infinity, rec)) {
        //return 0.5 * (rec.normal + color(1, 1, 1));

        //Diffuse 1 : shoot a ray from the point of reflection plus the normal + some random vector in the unit sphere
        //point3 target = rec.p + rec.normal + random_in_unit_sphere();

        //Diffuse 2: shoot a ray from the point of reflection , uniform scatter pattern no dependence on normal
        //point3 target = rec.p + random_in_hemisphere(rec.normal);

        //Scatter
        ray scattered;
        color attenuation;
        if(rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return color(0, 0, 0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); //lerp between blue and white based on y direction normalized 0 - 1
}

hittable_list random_scene()
{
    /*hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(1.5);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0), -0.45, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

    return world;*/
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    auto center2 = center + vec3(0, random_double(0,.5), 0);
                    world.add(make_shared<moving_sphere>(
                        center, center2, 0.0, 1.0, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}


//Function to write to a ppm image
void render_scene() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 10;
    const int max_depth = 50;

    auto world = random_scene();

    // Camera
    //camera cam(point3(-2,2,1), point3(0,0,-1), vec3(0,1,0), 90, aspect_ratio);
    point3 lookfrom(13,2,3);
    point3 lookat(0,0,0);
    vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    /*auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);*/

    //Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for(int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << "\n";
        for(int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for(int s = 0; s < samples_per_pixel; ++s)
            {
                 auto u  = (i + random_double()) / (image_width  - 1);
                 auto v  = (j + random_double()) / (image_height - 1);
                 ray r = cam.get_ray(u, v);
                 pixel_color += ray_color(r, world, max_depth);
            }
           
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone. \n";
}



int main(){

    //check_version_cpp();
    //write_test_ppm();
    //write_test_ppm_vec3();
    //write_test_ppm_ray();
    //test_vec3();
    //test_ray();

    render_scene();

    return 0;
    

}