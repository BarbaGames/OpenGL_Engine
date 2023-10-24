#include "Renderer.h"

#include <glm/gtc/type_ptr.hpp>

namespace MyEngine
{
// -- Private --
    
    glm::mat4 Renderer::projMatrix = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    glm::mat4 Renderer::viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 Renderer::modelMatrix = glm::mat4(1.0f);
    
    void Renderer::setUpVertexAttributesShape() {
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
        int mvpLocation = glGetUniformLocation(Shader::shapeShaderProgram, "u_MVP");
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));
    }

    void Renderer::setUpVertexAttributesTexture() {
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
        int mvpLocation = glGetUniformLocation(Shader::textureShaderProgram, "u_MVP");
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

    void Renderer::swapBuffers(GLFWwindow* window) {
        glfwSwapBuffers(window);
    }

    void Renderer::clear() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    template <size_t N, size_t N2>
    void Renderer::drawShape(float(&vertexData)[N], unsigned int(&indices)[N2]) {
        setShaderProgram(Shader::shapeShaderProgram);
        unsigned int VAO = createVertexArrayObject();
        unsigned int VBO = createVertexBufferObject(vertexData);
        unsigned int EBO = createElementBufferObject(indices);

        setUpVertexAttributesShape();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, N2, GL_UNSIGNED_INT, 0);
        glDeleteBuffers(1, &EBO);
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

    template <size_t N, size_t N2>
    void Renderer::drawTexture(float(&vertexData)[N], unsigned int(&indices)[N2], unsigned int textureID) {
        setShaderProgram(Shader::textureShaderProgram);
        unsigned int VAO = createVertexArrayObject();
        unsigned int VBO = createVertexBufferObject(vertexData);
        unsigned int EBO = createElementBufferObject(indices);

        setUpVertexAttributesTexture();
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

    void Renderer::setShaderProgram(unsigned int shaderProgram) {
        glUseProgram(shaderProgram);
    }

    double Renderer::getFrameTime() {
        return glfwGetTime();
    }
}
