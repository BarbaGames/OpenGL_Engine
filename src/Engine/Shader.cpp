#include "Shader.h"
#include <fstream>
#include <sstream>
namespace MyEngine
{
    unsigned int Shader::shapeShaderProgram = 0;
    unsigned int Shader::textureShaderProgram = 0;
  
    unsigned int Shader::compileShader(unsigned int type, string& source) {
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

    int Shader::createShader(string& vertexShader, string& fragmentShader) {
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
    void Shader::loadBasicShaders() { // This is a test function that creates a simple hardcoded shader program and applies it

        ShaderProgramSource sourceShape = parseShader("res/Shaders/Basic.shader");
        ShaderProgramSource sourceTexture = parseShader("res/Shaders/Texture.shader");
        
        shapeShaderProgram = createShader(sourceShape.VertexSource, sourceShape.FragmentSource);
        textureShaderProgram = createShader(sourceTexture.VertexSource, sourceTexture.FragmentSource);

        Renderer::setShaderProgram(shapeShaderProgram);
    }

    void Shader::unloadShaders() {
        glDeleteProgram(shapeShaderProgram);
        glDeleteProgram(textureShaderProgram);
    }

    Shader::ShaderProgramSource Shader::parseShader(const string& filepath)
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
}
