#include "renderer/particle_renderer.h"
#include <cstddef> 

ParticleRenderer::ParticleRenderer(){
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Particle), (void*)0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Particle),(void*)offsetof(Particle,velocity));
}

ParticleRenderer::~ParticleRenderer(){
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void ParticleRenderer::upload(const std::vector<Particle>& particles){
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(Particle), 
        particles.data(), GL_DYNAMIC_DRAW);
    count = (GLsizei)particles.size();

}

void ParticleRenderer::draw() const{
    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, count);
}
