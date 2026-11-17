 #version 330 core\n
    layout(location = 0) in vec3 aPos;\n
    layout(location = 1) in vec3 aNormal;\n
    layout(location = 2) in vec2 aTexCoord;\n
    uniform mat4 model;\n
    uniform mat4 view;\n
    uniform mat4 projection;\n
    out vec3 FragPos;\n
    out vec3 Normal;\n
    out vec2 TexCoord;\n

    void main() {\n
        FragPos = vec3(model * vec4(aPos, 1.0));\n
        Normal = normalize(mat3(transpose(inverse(model))) * aNormal);\n
  	    TexCoord = aTexCoord;\n
        gl_Position = projection * view * vec4(FragPos, 1.0);\n
    }\n;
