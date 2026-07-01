/*
At minimum each particle needs:
- position (3D)
- velocity (3D)
- mass (scalar)
*/
#include <glm/glm.hpp>
#include <vector>
#include <random>

struct Particle {
    glm::vec3 position;
    glm::vec3 velocity;
    float mass;
};

constexpr float G = 1.0;
constexpr float SOFTENING = 0.01f;

// Fill `particles` with `count` bodies in the simulation's starting state
// (e.g. random positions inside a sphere, small or zero initial velocities).
// Take an explicit `seed` so runs are reproducible and can match the Octave
// reference's initial conditions exactly.
void initialize_particles(std::vector<Particle>& particles, int count, unsigned int seed);

// Compute the net gravitational acceleration on each particle from every other
// particle — the O(n^2) pairwise core. Writes one acceleration per particle
// into `accelerations` (same order/size as `particles`). Use Newton's law of
// gravity with a softening term so the force doesn't blow up when two bodies
// get very close (the 1/r^2 singularity).
void compute_accelerations(const std::vector<Particle>& particles,
                           std::vector<glm::vec3>& accelerations);

// Advance the whole system by one timestep `dt` using semi-implicit (symplectic)
// Euler: first update each velocity from its acceleration, then update each
// position from the new velocity. Mutates `particles` in place. This is the
// function the renderer calls once per frame.
void step(std::vector<Particle>& particles, float dt);

// Sum the system's total energy (kinetic + gravitational potential). It should
// stay roughly constant over time — useful as a correctness/stability check and
// for cross-verifying the C++ core against the Octave reference.
float total_energy(const std::vector<Particle>& particles);
