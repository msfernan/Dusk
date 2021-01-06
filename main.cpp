#include <iostream>
#include <fstream>

int main(){

    int nx = 200;
    int ny = 100;

    std::ofstream ofs;


    if (__cplusplus == 201703L) std::cout << "C++17\n";
    else if (__cplusplus == 201402L) std::cout << "C++14\n";
    else if (__cplusplus == 201103L) std::cout << "C++11\n";
    else if (__cplusplus == 199711L) std::cout << "C++98\n";
    else std::cout << "pre-standard C++\n";

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