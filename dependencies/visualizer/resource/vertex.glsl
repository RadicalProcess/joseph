attribute vec3 position;
uniform float zTransform;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * vec4(position.x, position.y, position.z + zTransform,  1.0);
}
