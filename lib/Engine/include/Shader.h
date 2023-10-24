#pragma once
#include "Engine.h"
#include <iostream>

using namespace std;

namespace MyEngine {

    class Shader {
    private:
        
        static unsigned int compileShader(unsigned int type, string& source);
        static int createShader(string& vertexShader, string& fragmentShader);

    public:
        struct ShaderProgramSource
        {
            string VertexSource;
            string FragmentSource;
        };
        static unsigned int shapeShaderProgram;
        static unsigned int textureShaderProgram;

        static ShaderProgramSource parseShader(const string& filepath); 
        static void loadBasicShaders();
        static void unloadBasicShaders();

        static void setShaderProgram(unsigned int shaderProgram);
    };
}
