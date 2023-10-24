#pragma once
#include "Engine.h"
#include <iostream>

using namespace std;

namespace MyEngine {

    class Shader {
    private:
        
        
        static unsigned int compileShader(unsigned int type, string& source);
        static int createShader(string& vertexShader, string& fragmentShader);
        // Reads a file containing shaders and returns them
        

    public:
        struct ShaderProgramSource
        {
            string VertexSource;
            string FragmentSource;
        };
        static ShaderProgramSource parseShader(const string& filepath); 
        static unsigned int shapeShaderProgram;
        static unsigned int textureShaderProgram;
        static void loadBasicShaders();
        static void unloadShaders();
    };
}
