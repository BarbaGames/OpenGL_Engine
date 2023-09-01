#include "Renderer.h"

#include <fstream>
#include <sstream>
#include <string>

namespace MyEngine
{

// -- Private --

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

        return program;
    }

    template <typename T, size_t N>
    unsigned int Renderer::createVertexBuffer(const T(&vertexData)[N]) {
        unsigned int buffer;
        glGenBuffers(1, &buffer); // We generate a buffer to store our vertex data in. 1 is the index
        glBindBuffer(GL_ARRAY_BUFFER, buffer); // We bind to that buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW); // We upload our array into our buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0); // We unbind from the buffer
        return buffer;
    }

    void Renderer::setUpVertexAttributes(unsigned int& buffer) {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        glEnableVertexAttribArray(0); // We enable vertex attributes
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); // We set up our attributes layout

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

// -- Public --

    void Renderer::tempSetUpRedShader() { // This is a test function that creates a simple hardcoded shader program and applies it

        ShaderProgramSource source = parseShader("res/Shaders/Basic.shader");
        
        unsigned int shader = createShader(source.VertexSource, source.FragmentSource);

        glUseProgram(shader);
        glDeleteProgram(shader);
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


    void Renderer::drawTriangle(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y) {
        float positions[6] = { // Setting up the vertices in an array (In this case it's only the positions)
            v1x, v1y,
            v2x, v2y,
            v3x, v3y
        };
        // Remember vertices can have additional information like "color" and "texture coordinates" that we need to specify later when setting up the attribute layout
        // Also remember that this doesn't necesarily need to be an array, it can also be a struct

        unsigned int buffer = createVertexBuffer(positions);
        setUpVertexAttributes(buffer);

        glDrawArrays(GL_TRIANGLES, 0, 3); // We draw!
        glDeleteBuffers(1, &buffer); // We're done, so we delete the buffer
    }

    void Renderer::drawTriangleLegacy(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y) {
        glBegin(GL_TRIANGLES);
            glVertex2f(v1x, v1y);
            glVertex2f(v2x, v2y);
            glVertex2f(v3x, v3y);
        glEnd();
    }

    void Renderer::drawTriangleLegacy(Window* window, int v1x, int v1y, int v2x, int v2y, int v3x, int v3y) {
        glBegin(GL_TRIANGLES);
            glVertex2f(window->getNormalizedX(v1x), window->getNormalizedX(v1y));
            glVertex2f(window->getNormalizedX(v2x), window->getNormalizedX(v2y));
            glVertex2f(window->getNormalizedX(v3x), window->getNormalizedX(v3y));
        glEnd();
    }
}
