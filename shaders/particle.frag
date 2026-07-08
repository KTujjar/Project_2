#version 330 core

in float vSpeed;          // interpolated from the vertex shader

out vec4 FragColor;       // the pixel color we output

void main()
{
    // gl_PointCoord is this pixel's position within the point sprite,
    // (0,0) top-left to (1,1) bottom-right. Distance from center (0.5,0.5)
    // lets us shape the square point into a disc.
    vec2  fromCenter = gl_PointCoord - vec2(0.5);
    float dist = length(fromCenter);

    // Discard pixels outside the disc -> round particles instead of squares.
    if (dist > 0.5)
        discard;

    // Color by speed: slow = cold blue, fast = hot yellow-white.
    // mix() linearly blends the two colors; the clamp keeps t in [0,1].
    float t = clamp(vSpeed * 2.0, 0.0, 1.0);
    vec3 cold = vec3(0.2, 0.4, 1.0);
    vec3 hot  = vec3(1.0, 0.9, 0.5);
    vec3 color = mix(cold, hot, t);

    // Soft edge: alpha fades toward the rim of the disc, so points glow
    // instead of ending in a hard circle (pairs with additive blending).
    float alpha = smoothstep(0.5, 0.1, dist);

    FragColor = vec4(color, alpha);
}
