#version 330 core
out vec4 FragColor;
in vec3 localPos;

void main()
{
    float edgeThreshold = 0.02;

    float eX = step(0.5 - edgeThreshold, abs(localPos.x));
    float eY = step(0.5 - edgeThreshold, abs(localPos.y));
    float eZ = step(0.5 - edgeThreshold, abs(localPos.z));

    float edgeCount = eX + eY + eZ;
    float isEdge = step(2.0, edgeCount); // 1.0 if 2 or more axes near edge

    vec3 fill = vec3(1.0f, 0.5f, 0.2f);  // White
    vec3 color = mix(fill, vec3(0.0), isEdge);
    FragColor = vec4(color, 1.0);
}