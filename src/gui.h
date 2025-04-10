#pragma once
#include <string>
#include <GLFW/glfw3.h> // Add GLFW header

class CompilerGUI
{
public:
    CompilerGUI();  // Constructor declaration
    ~CompilerGUI(); // Destructor declaration

    void render();

private:
    void loadFile();
    void compile();

    GLFWwindow *window;
    std::string codeBuffer;
    std::string symbolTableOutput;
    std::string errorOutput;
};