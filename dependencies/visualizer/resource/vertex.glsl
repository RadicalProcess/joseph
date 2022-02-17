attribute vec3 position;
uniform float zTransform;
uniform mat4 projectionViewMatrix;

void main()
{
    gl_Position = projectionViewMatrix * vec4(position.x, position.y, position.z + zTransform,  1.0);
}
