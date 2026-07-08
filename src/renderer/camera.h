#pragma once

#include <glm/glm.hpp>

// Orbit camera: circles the origin at `radius`, described by two angles
// (spherical coordinates). Pure math — no OpenGL, no resources — so unlike
// Window/Shader/ParticleRenderer it needs no destructor: it's just state
// plus two functions that produce matrices.
class Camera {
public:
    // Start at a sensible default orbit (e.g. radius 3, slight downward tilt).
    // `aspect` is width/height of the window, needed by the projection.
    Camera(float aspect);

    // The "where am I standing / where am I looking" matrix.
    // Convert yaw/pitch/radius to an eye position with sin/cos, then
    // glm::lookAt(eye, origin, up). Up is +Y: glm::vec3(0, 1, 0).
    glm::mat4 view() const;

    // The "lens" matrix: glm::perspective(fov, aspect, near, far).
    // 45 degrees fov (glm::radians!), near 0.1, far 100 are good defaults.
    glm::mat4 projection() const;

    // Mouse-drag rotates the orbit: adjust yaw/pitch by the given deltas.
    // Clamp pitch short of +/-90 degrees or the camera flips at the poles.
    void rotate(float yaw_delta, float pitch_delta);

    // Scroll zooms: change radius, clamped to some [min, max] so you can't
    // zoom through the origin or into the far plane.
    void zoom(float radius_delta);

    // Keep the projection matched to the window when it's resized.
    void set_aspect(float aspect);

private:
    float yaw;      // horizontal angle around the origin (radians)
    float pitch;    // vertical angle above/below the equator (radians)
    float radius;   // distance from the origin
    float aspect;   // window width / height
};
