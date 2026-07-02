#include <iostream>
#include <common/particle.h>
#include <renderer/window.h>

void particleTest(){
    std::cout << "hello";
    std::vector<Particle> particles;
    initialize_particles(particles, 100, 42);
    std::cout << "start energy: " << total_energy(particles) << "\n";
    for (int i = 0; i < 1000; ++i) step(particles, 0.0001f);
    std::cout << "end energy:   " << total_energy(particles) << "\n";
}


int main(){
    particleTest();

    Window newWindow(800,600,"N-Body");
    
    while(!newWindow.should_close()){
        glClearColor(0.1f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        newWindow.swap_and_poll();
    }
}