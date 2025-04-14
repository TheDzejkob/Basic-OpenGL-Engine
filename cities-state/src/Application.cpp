#include <glad/glad.h> // GLAD musí být zahrnut jako první
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void processInput(GLFWwindow* window);

// Function to load shader source from a file
std::string loadShaderSource(const char* filePath) {
    std::ifstream shaderFile(filePath);
    if (!shaderFile.is_open()) {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << shaderFile.rdbuf();
    return buffer.str();
}

int main() {
    // Inicializuje GLFW
    if (!glfwInit()) {
        std::cout << "Chyba: Nejde inicializovat GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Cities State", NULL, NULL);
    if (window == NULL) {
        std::cout << "Chyba: Nejde vytvoøit okno" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Check zda se loadnul GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD se dosral" << std::endl;
        return -1;
    }

    // Velikost okna
    glViewport(0, 0, 800, 600);

    // Load vertex shader source
    std::string vertexShaderSource = loadShaderSource("src/Vertex_shader.frag");
    const char* vertexShaderSourceCStr = vertexShaderSource.c_str();

    // Load fragment shader source
    std::string fragmentShaderSource = loadShaderSource("src/fragment_shader.frag");
    const char* fragmentShaderSourceCStr = fragmentShaderSource.c_str();

    // Create and compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourceCStr, NULL);
    glCompileShader(vertexShader);

    // Check for vertex shader compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Create and compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceCStr, NULL);
    glCompileShader(fragmentShader);

    // Check for fragment shader compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Link shaders into a program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Use the shader program
    glUseProgram(shaderProgram);

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 3 body ktere maji x,y,z souradnice
    float verticies[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO); // Vytvoreni bufferu

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bindne buffer jako array pro vertex data

    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW); // Naplní buffer Verticies Daty

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // Rendering
        glClearColor(39.0f / 255.0f, 157.0f / 255.0f, 245.0f / 255.0f, 0.8f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw your objects here

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Freene vsecky resources
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
