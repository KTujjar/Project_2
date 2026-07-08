#include <iostream>

#include <common/particle.h>
#include <renderer/window.h>
#include <renderer/shader.h>
#include <renderer/camera.h>
#include <renderer/particle_renderer.h>

int main(){
    try {
        // Window first: everything below needs a live GL context.
        Window window(800, 600, "N-Body");

        Shader shader(SHADER_DIR "/particle.vert", SHADER_DIR "/particle.frag");
        ParticleRenderer renderer;
        Camera camera(window.aspect());

        std::vector<Particle> particles;
        initialize_particles(particles, 2000, 42);

        // gl_PointSize in the vertex shader only takes effect with this on.
        glEnable(GL_PROGRAM_POINT_SIZE);
        // Additive blending: overlapping particles brighten each other (glow).
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        // Mouse-drag state for the orbit camera.
        double last_x = 0.0, last_y = 0.0;
        bool dragging = false;

        while (!window.should_close()) {
            // --- input: drag rotates, scroll zooms ---
            double mx, my;
            glfwGetCursorPos(window.native(), &mx, &my);
            bool down = glfwGetMouseButton(window.native(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
            if (down && dragging)
                camera.rotate((float)(mx - last_x) * 0.005f,
                              (float)(my - last_y) * 0.005f);
            dragging = down;
            last_x = mx; last_y = my;

            camera.zoom(-window.take_scroll() * 0.2f);
            camera.set_aspect(window.aspect());

            // --- physics: fixed small dt for stability (see Stage 2 energy test) ---
            step(particles, 0.001f);
            renderer.upload(particles);

            // --- render ---
            glClearColor(0.02f, 0.02f, 0.05f, 1.0f);   // near-black space
            glClear(GL_COLOR_BUFFER_BIT);

            shader.use();
            shader.set_mat4("uMVP", camera.projection() * camera.view());
            shader.set_float("uPointSize", 8.0f);
            renderer.draw();

            window.swap_and_poll();
        }
    } catch (const std::exception& e) {
        // Constructor failures (bad shader path, GLSL typo...) land here with
        // the driver's log instead of a silent crash.
        std::cerr << "fatal: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
