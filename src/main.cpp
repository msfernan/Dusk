#include "rtweekend.h"

#include "camera.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"


void check_version_cpp(){

    if(__cplusplus > 201703L) std::cout << "C++20\n";
    else if (__cplusplus == 201703L) std::cout << "C++17\n";
    else if (__cplusplus == 201402L) std::cout << "C++14\n";
    else if (__cplusplus == 201103L) std::cout << "C++11\n";
    else if (__cplusplus == 199711L) std::cout << "C++98\n";
    else std::cout << "pre-standard C++\n";

}

vec3 color_pixel(const ray& r){
    vec3 unit_direction = unit_vector(r.direction());
    float y_value = unit_direction.y(); //This value will affect the lerp between -1 and 1
    float scaled_y_value = (y_value + 1)/2; //Scale so value between 0 and 1
    vec3 white(1.0, 1.0, 1.0);
    vec3 blue(0.5, 0.7, 1.0);
    vec3 lerp_color = (1.0 - scaled_y_value) * white + (scaled_y_value) * blue;
    return lerp_color;
}



void write_test_ppm(){

    int nx = 200;
    int ny = 100;


    std::ofstream ofs;


    try {

        ofs.open("test.ppm", std::ios::binary);

        ofs << "P3 \n" << nx << " " << ny << "\n255\n";

        for(int j = ny - 1; j >= 0; j--) {
            for(int i = 0; i < nx; i++) {
                float r = float(i) / float(nx);
                float g = float(j) / float(ny);
                float b  = 0.2; 
                int ir = int(255.99 * r);
                int ig = int(255.99 * g);
                int ib = int(255.99 * b);

                ofs << ir << " " << ig << " " << ib << "\n";

            }

        }

        ofs.close(); 
    }

    catch (const char *err) { 
        fprintf(stderr, "%s\n", err); 
        ofs.close(); 
    } 

}

void write_test_ppm_vec3(){

    int nx = 200;
    int ny = 100;


    std::ofstream ofs;


    try {

        ofs.open("test_vec3.ppm", std::ios::binary);

        ofs << "P3 \n" << nx << " " << ny << "\n255\n";

        for(int j = ny - 1; j >= 0; j--) {
            for(int i = 0; i < nx; i++) {

                vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
                int ir = int(255.99 * col[0]);
                int ig = int(255.99 * col[1]);
                int ib = int(255.99 * col[2]);

                ofs << ir << " " << ig << " " << ib << "\n";

            }

        }

        ofs.close(); 
    }

    catch (const char *err) { 
        fprintf(stderr, "%s\n", err); 
        ofs.close(); 
    } 

}


void write_test_ppm_ray(){

    int nx = 200;
    int ny = 100;


    std::ofstream ofs;


    try {

        ofs.open("test_ray.ppm", std::ios::binary);

        ofs << "P3 \n" << nx << " " << ny << "\n255\n";

        vec3 lower_left_corner(-2.0, -1.0, -1.0);
        vec3 horizontal(4.0, 0.0, 0.0);
        vec3 vertical(0.0, 2.0, 0.0);
        vec3 origin(0.0, 0.0, 0.0);

        for(int j = ny - 1; j >= 0; j--) {
            for(int i = 0; i < nx; i++) {

                float u = float(i) / float(nx);
                float v = float(j) / float(ny);

                ray r(origin, lower_left_corner + (u * horizontal) + (v * vertical));

                vec3 col = color_pixel(r);
                int ir = int(255.99 * col[0]);
                int ig = int(255.99 * col[1]);
                int ib = int(255.99 * col[2]);

                ofs << ir << " " << ig << " " << ib << "\n";

            }

        }

        ofs.close(); 
    }

    catch (const char *err) { 
        fprintf(stderr, "%s\n", err); 
        ofs.close(); 
    } 

}




//In order to use do ./a.out > testimage.ppm.
//WARN: Command line cant print out anything else to std::cout 
void write_test_ppm_commandline() {

    int nx = 200;
    int ny = 100;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for(int j  = ny - 1; j >= 0; j--){

        for(int i = 0; i < nx; i++){
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.2;
            int ir = int(255.99 * r);
            int ig = int(255.99 * g);
            int ib = int(255.99 * b);
            std::cout << ir << " " << ig << " " << ib << "\n";

        }
    }
}


void test_vec3(){

    vec3 col(10.0, 10.0, 10.0);
    std::cout << "Testing " <<  col.r() << std::endl;

    std::cout << "Testing dot product " << dot(col, col) << std::endl;

    vec3 mul = col * col;
    vec3 add = col + col;
    vec3 sub = col - col;
    vec3 div = col / col;

    std::cout << "Testing multiplication " << mul.x() << std::endl;

    std::cout << "Testing addition " << add.x() << std::endl;

    std::cout << "Testing subtraction " << sub.x() << std::endl;

    std::cout << "Testing division " << div.x() << std::endl;

    vec3 v1(1.0, 2.0, 3.0);
    vec3 v2(10.0, 2.0, 4.0);

    vec3 vcross = cross(v1, v2);

    std::cout << "Testing cross product " <<  vcross.x() << " " << vcross.y() << " " << vcross.z() << " " << std::endl;

    v1 += v2;
    std::cout << "Testing += " <<  v1.x() << " " << v1.y() << " " << v1.z() << " " << std::endl;

    v1 -= v2;
    std::cout << "Testing -= " <<  v1.x() << " " << v1.y() << " " << v1.z() << " " << std::endl;


    v1 *= v2;
    std::cout << "Testing *= " <<  v1.x() << " " << v1.y() << " " << v1.z() << " " << std::endl;


    v1 /= v2;
    std::cout << "Testing /= " <<  v1.x() << " " << v1.y() << " " << v1.z() << " " << std::endl;

    v1 *= 10;
    std::cout << "Testing *= " <<  v1.x() << " " << v1.y() << " " << v1.z() << " " << std::endl;

    v1 /= 10;
    std::cout << "Testing *= " <<  v1.x() << " " << v1.y() << " " << v1.z() << " " << std::endl;


    float len = v1.length();
    std::cout << " Length " <<  len << std::endl;


    float sq_len = v1.length_squared();
    std::cout << "Squared length " <<  sq_len << std::endl;

    std::cout <<  "Testing vector output " << v1 << std::endl;

    std::cout <<  "v1[0] " << v1[0] << " v1[1] " << v1[1] << " v1[2] " << v1[2] << std::endl;

    v1[0] = 9.0;
    v1[1] = 8.0;
    v1[2] = 8.09;
    std::cout <<  "v1[0] " << v1[0] << " v1[1] " << v1[1] << " v1[2] " << v1[2] << std::endl;

    v1[0] = 2.0;
    v1[1] = 0.0;
    v1[2] = 1.0;

    std::cout << "v1 is " << v1 << std::endl;

    len = v1.length();
    std::cout << "The length is " << len << std::endl;

    vec3 unit_vec = unit_vector(v1);
    std::cout << "Unit vector " << unit_vec << std::endl;

    len = unit_vec.length();
    std::cout << "The unit length is " << len << std::endl;

}


void test_ray() {

    vec3 origin(1.0, 2.0, 3.0);
    vec3 direction(1.1, 2.1, 3.1);

    ray test_ray(origin, direction);
    //std::cout << "Testing ray origin ... "<< test_ray.o << std::endl;
    //std::cout << "Testing ray direction ... "<< test_ray.d << std::endl;

    vec3 point_test1;
    point_test1 = test_ray.point_at_parameter(1);
    std::cout << "point test " << point_test1 << std::endl;

    point_test1 = test_ray.point_at_parameter(10);
    std::cout << "point test " << point_test1 << std::endl;

}

double hit_sphere(const point3& center, double radius, const ray &r) {
    vec3 oc = (r.origin() - center);
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - (radius * radius);
    auto discriminant = (b * b) - (4 * a * c);
    
    if(discriminant < 0) {
        return -1.0;
    }
    else {
        return ((- b - sqrt(discriminant)) / (2.0 * a)); //Return for visualizing normal
    }
}


color ray_color(const ray &r) {

    auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
    if(t > 0.0) { 
        vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1)); //get unit vector at intersection point
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1); //Move vector to 0 -1 range
    }
    //if (hit_sphere(point3(0, 0, +1), 0.5, r))
        //return color(1, 0, 0);

    //DEFAULT color
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y() + 1.0); //Move vector 0 to 1 range
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); //Interpolate color
}


color ray_color(const ray &r, const hittable_list& world) {
    hit_record rec;
    if(world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


//Function to write to a ppm image
void write_test_ppm_ray_focal() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel  = 100;

    //World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Camera
    camera cam;

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
                 auto u  = double(i + random_double()) / (image_width  - 1);
                 auto v  = double(j + random_double()) / (image_height - 1);
                 ray r = cam.get_ray(u, v);
                 pixel_color += ray_color(r, world);
            }
           
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone. \n";
}



int main(){

    check_version_cpp();

    //write_test_ppm();

    //write_test_ppm_vec3();

    //write_test_ppm_ray();

    //test_vec3();


    //test_ray();

    //write_test_ppm_color();

    
    //write_test_ppm_ray_focal();



    return 0;
    

}