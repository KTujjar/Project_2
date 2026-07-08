#version 330 core

// Per-vertex inputs, pulled from the VBO. The location numbers must match
// the glVertexAttribPointer setup in particle_renderer.cpp.
layout (location = 0) in vec3 aPos;   // particle position (world space)
layout (location = 1) in vec3 aVel;   // particle velocity (used for color)

// Uniforms: set once per frame from C++ (Shader::set_mat4 / set_float).
uniform mat4  uMVP;        // projection * view * model, built by the camera
uniform float uPointSize;  // base point size in pixels

// Passed on to the fragment shader (interpolated per pixel).
out float vSpeed;

void main()
{
    // Transform world-space position into clip space. The vec4's w=1.0 marks
    // this as a point (not a direction), so translation applies.
    gl_Position = uMVP * vec4(aPos, 1.0);

    // Perspective attenuation: gl_Position.w is the view-space depth, so
    // dividing makes far particles smaller, near ones bigger.
    gl_PointSize = uPointSize / gl_Position.w;

    vSpeed = length(aVel);
}
