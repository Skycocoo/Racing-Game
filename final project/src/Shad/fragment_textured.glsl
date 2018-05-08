uniform sampler2D diffuse;
varying vec2 texCoordVar;

void main() {
    vec4 textureColor = texture2D(diffuse, texCoordVar);
    gl_FragColor = textureColor;
}
