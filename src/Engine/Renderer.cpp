#include "Renderer.h"

#include <fstream>
#include <sstream>
#include <string>
#include <glm/gtc/type_ptr.hpp>

namespace MyEngine
{
// -- Private --
    unsigned int Renderer::shaderProgram = 0;
    glm::mat4 Renderer::projMatrix = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    glm::mat4 Renderer::viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 Renderer::modelMatrix = glm::mat4(1.0f);
    
    unsigned int Renderer::compileShader(unsigned int type, string& source) {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        // -- Error handling --
        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = static_cast<char*>(_malloca(length * sizeof(char))); // malloca allocates memory in the stack, this way we can create a stack array wihout defining a constant length
            glGetShaderInfoLog(id, length, &length, message);
            cout << "(Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " Shader) " << message << "\n";
            glDeleteShader(id);
            return 0;
        }

        return id;
    }
    
    int Renderer::createShader(string& vertexShader, string& fragmentShader) {
        unsigned int program = glCreateProgram(); // We create a shader program (this is a collection of compiled and linked shaders that run on our gpu)
        unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader); // We compile our vertex shader
        unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader); // We compile our fragment shader

        glAttachShader(program, vs); // We attach our shaders to our program
        glAttachShader(program, fs);
        glLinkProgram(program); // We link the shaders
        glValidateProgram(program);

        glDeleteShader(vs); // We delete the shaders (They're now linked to our program so we no longer need these shader objects)
        glDeleteShader(fs);

        // Set the MVP matrix uniform
        glUseProgram(program);
        
        return program;
    }

    void Renderer::setUpVertexAttributes() {
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // uv attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        // mvp
        glm::mat4 mvp = projMatrix * viewMatrix * modelMatrix;
        int mvpLocation = glGetUniformLocation(shaderProgram, "u_MVP");
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));
    }

    unsigned int Renderer::createVertexArrayObject() {
        unsigned int VAO; // Vertex Array Object
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        return VAO;
    }

    template <typename T, size_t N>
    unsigned int Renderer::createVertexBufferObject(const T(&vertexData)[N]) {
        unsigned int VBO; // Vertex Buffer Object
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW); // We assign the vertex data to this buffer
        return VBO;
    }

    template <typename T, size_t N>
    unsigned int Renderer::createElementBufferObject(const T(&indices)[N]) {
        unsigned int EBO; // Element Buffer Object
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Note that it's specified the fact that it's an element array
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // We assign the indices to this buffer
        return EBO;
    }

// -- Public --

    void Renderer::loadBasicShader() { // This is a test function that creates a simple hardcoded shader program and applies it

        ShaderProgramSource source = parseShader("res/Shaders/Basic.shader");
        
        shaderProgram = createShader(source.VertexSource, source.FragmentSource);

        glUseProgram(shaderProgram);
    }

    void Renderer::unloadBasicShader() {
        glDeleteProgram(shaderProgram);
    }

    void Renderer::swapBuffers(GLFWwindow* window) {
        glfwSwapBuffers(window);
    }

    void Renderer::clear() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    Renderer::ShaderProgramSource Renderer::parseShader(const string& filepath)
    {
        ifstream file(filepath); // Opens a stream to the shader file

        enum class ShaderType
        {
            NONE = -1,
            VERTEX,
            FRAGMENT
        };
        
        stringstream ss[2];
        
        ShaderType type = ShaderType::NONE;
        
        try
        {
            if (file.is_open())
            {
                string line;
                
                while (getline(file, line)) // Traverses through the shader file
                {
                    if(line.find("#shader") != string::npos) // Looks for the line that defines the shader type
                    {
                        if(line.find("vertex") != string::npos) // Set mode to vertex
                            {
                            type = ShaderType::VERTEX;
                            }
                        else if (line.find("fragment") != string::npos) // Set mode to fragment
                            {
                            type = ShaderType::FRAGMENT;
                            
                            }
                    }
                    else
                    {
                        ss[static_cast<int>(type)] << line << '\n'; // Saves each shader in this array
                    }
                }
                file.close();
            }
            else
            {
                throw std::ofstream::failure("Error reading the file.");
            }
        }
        catch (const std::ifstream::failure& ifstreamFailure)
        {
            std::cout << "Error opening or reading file: " << ifstreamFailure.what() << std::endl;
        } catch (const std::exception& e)
        {
            std::cout << "Unknown error occurred: " << e.what() << std::endl;
        }
        
        return {ss[0].str(), ss[1].str()}; // Returns a ShaderProgramSource struct that contains the 2 shaders in its strings
    }

    template <size_t N, size_t N2>
    void Renderer::drawShape(float(&vertexData)[N], unsigned int(&indices)[N2]) {
        unsigned int VAO = createVertexArrayObject();
        unsigned int VBO = createVertexBufferObject(vertexData);
        unsigned int EBO = createElementBufferObject(indices);

        setUpVertexAttributes();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, N2, GL_UNSIGNED_INT, 0);
        glDeleteBuffers(1, &EBO);
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

    template <size_t N, size_t N2>
    void Renderer::drawTexture(float(&vertexData)[N], unsigned int(&indices)[N2], unsigned int textureID) {
        unsigned int VAO = createVertexArrayObject();
        unsigned int VBO = createVertexBufferObject(vertexData);
        unsigned int EBO = createElementBufferObject(indices);

        setUpVertexAttributes();
        glBindTexture(GL_TEXTURE_2D, textureID);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDeleteBuffers(1, &EBO);
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

    void drawTextureDefault() {
        float vertexData[] = {
            0.0f, 0.0f, 0.0f, /**/ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, /**/ 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, /**/ 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 0.0f, /**/ 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
        };
        unsigned int indices[] = {
            0, 1, 3,  // First Triangle
            1, 2, 3   // Second Triangle
        };

        Renderer::drawTexture(vertexData, indices, 0);
    }

    void Renderer::drawRect(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y, float v4x, float v4y, float r, float g, float b) {
        float vertexData[] = {
            v1x, v1y, 0.0f, /**/ r, g, b, 0.0f, 0.0f,
            v2x, v2y, 0.0f, /**/ r, g, b, 1.0f, 0.0f,
            v3x, v3y, 0.0f, /**/ r, g, b, 0.0f, 1.0f,
            v4x, v4y, 0.0f, /**/ r, g, b, 1.0f, 1.0f
        };
        unsigned int indices[] = {
            0, 1, 3,  // First Triangle
            1, 2, 3   // Second Triangle
        };
        
        drawShape(vertexData, indices);
    }

    void Renderer::drawTriangle(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y, float r, float g, float b) {
        float vertexData[] = {
            v1x, v1y, 0.0f, /**/ r, g, b, 0.0f, 0.0f,
            v2x, v2y, 0.0f, /**/ r, g, b, 0.0f, 0.0f,
            v3x, v3y, 0.0f, /**/ r, g, b, 0.0f, 0.0f
        };
        unsigned int indices[] = {
            0, 1, 2
        };
        
        drawShape(vertexData, indices);
    }

    void Renderer::drawTriangleLegacy(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y) {
        glBegin(GL_TRIANGLES);
            glVertex2f(v1x, v1y);
            glVertex2f(v2x, v2y);
            glVertex2f(v3x, v3y);
        glEnd();
    }

    void Renderer::bindTexture(unsigned int textureID) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    void Renderer::set2DProjectionMatrix(float width, float height) {
        projMatrix = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
    }

    void Renderer::setViewMatrix(float x, float y, float z) {
        viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
    }

    void Renderer::setViewMatrix(glm::mat4 newViewMatrix)
    {
        viewMatrix = newViewMatrix;
    }

    void Renderer::setModelMatrix(glm::mat4 newModelMatrix)
    {
        modelMatrix = newModelMatrix;
    }

    double Renderer::getFrameTime() {
        return glfwGetTime();
    }
}
