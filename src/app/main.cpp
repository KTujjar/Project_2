#include <iostream>
#include <common/particle.h>

int main(){
    std::cout << "hello";
    std::vector<Particle> particles;
    initialize_particles(particles, 100, 42);
    std::cout << "start energy: " << total_energy(particles) << "\n";
    for (int i = 0; i < 1000; ++i) step(particles, 0.0001f);
    std::cout << "end energy:   " << total_energy(particles) << "\n";
}