#include <common/particle.h>

void initialize_particles(std::vector<Particle>& particles, int count, unsigned int seed){
    //resizes particle vector to match count
    particles.resize(count);
    
    //creates a random uniform distribution.
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    
    //sets position velocity and mass
    for (Particle& p : particles) {
        p.position = glm::vec3(dist(rng), dist(rng), dist(rng));
        p.velocity = glm::vec3(0.0f);
        p.mass = 1.0f; 
    }

}

void compute_accelerations(const std::vector<Particle>& particles,
std::vector<glm::vec3>& accelerations){
    accelerations.assign(particles.size(), glm::vec3(0.0f));
    for(size_t i = 0; i < particles.size(); ++i){
        for(size_t j = 0; j < particles.size(); ++j){
            if(i == j) continue;
            glm::vec3 direction = particles[j].position - particles[i].position;
            float distance = glm::length(direction);
            float magnitude = G * particles[j].mass / (glm::dot(distance,distance) + (SOFTENING * SOFTENING));
            accelerations[i] += magnitude * glm::normalize(direction);
        }
    }
}
                           

void step(std::vector<Particle>& particles, float dt){
    std::vector<glm::vec3> accelerations;
    compute_accelerations(particles, accelerations);
    for(size_t i = 0; i < particles.size(); ++i){
        particles[i].velocity += accelerations[i] * dt;
        particles[i].position += particles[i].velocity * dt;
    }

}

float total_energy(const std::vector<Particle>& particles){
    float kinetic = 0.0f;
    float potential = 0.0f;
    for(size_t i = 0; i < particles.size(); i++){
        kinetic += 0.5f * particles[i].mass * glm::dot(particles[i].velocity, particles[i].velocity);
        for(size_t j = i + 1; j < particles.size(); j++){
            glm::vec3 direction = particles[j].position - particles[i].position;
            float distance = std::sqrt(glm::dot(direction, direction) + SOFTENING * SOFTENING);
            potential += -G * particles[i].mass * particles[j].mass / distance;
        }
    } 
    return kinetic + potential;
}
