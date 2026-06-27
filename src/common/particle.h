/*
At minimum each particle needs:
- position (3D)
- velocity (3D)
- mass (scalar)
*/
#include <glm/glm.hpp>

struct Particle {
    glm::vec3 position;
    glm::vec3 velocity;
    float mass;
};
