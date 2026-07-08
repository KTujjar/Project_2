#pragma once

#include <glad/gl.h>
#include <vector>
#include "common/particle.h"

// Owns the GPU-side buffer (VBO) holding the particle array and the vertex
// attribute description (VAO) that tells OpenGL how to read Particle structs
// out of it. Third RAII class: create buffers in the constructor, delete in
// the destructor.
class ParticleRenderer {
public:
    // Create the VAO + VBO and describe the two vertex attributes so they
    // match the vertex shader's layout locations:
    //   location 0 -> Particle::position (3 floats, offset 0)
    //   location 1 -> Particle::velocity (3 floats, offsetof(Particle, velocity))
    // Stride for both is sizeof(Particle). Use glVertexAttribPointer +
    // glEnableVertexAttribArray with the VAO and VBO bound.
    ParticleRenderer();

    // Free the GPU buffers (glDeleteBuffers + glDeleteVertexArrays).
    ~ParticleRenderer();

    // Copy the CPU-side particle array into the VBO (glBufferData with
    // GL_DYNAMIC_DRAW — the data changes every frame). Call after each
    // physics step, before draw().
    void upload(const std::vector<Particle>& particles);

    // Bind the VAO and draw one point per particle
    // (glDrawArrays(GL_POINTS, 0, count)). Remembers the count from the
    // last upload().
    void draw() const;

private:
    GLuint vao = 0;       // attribute description (how to read the buffer)
    GLuint vbo = 0;       // the GPU memory holding the Particle array
    GLsizei count = 0;    // number of particles in the buffer (set by upload)
};
