#include "gui.h"
#include <fstream>
#include <cstring>
#include <sstream>

// ImGui and GLFW includes
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

// Your compiler components
#include "utils.h"
#include "main.h"
#include "ImGuiFileDialog.h"

CompilerGUI::CompilerGUI() : window(nullptr)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // Create window
    window = glfwCreateWindow(1280, 720, "Python Compiler", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

CompilerGUI::~CompilerGUI()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}

void CompilerGUI::loadFile()
{
    // Open file dialog with proper configuration
    IGFD::FileDialogConfig config;
    config.path = "."; // Default path
    config.countSelectionMax = 1;
    config.flags = ImGuiFileDialogFlags_Modal;

    ImGuiFileDialog::Instance()->OpenDialog(
        "ChooseFileDlg",
        "Choose File",
        ".py",
        config);
}

void CompilerGUI::compile()
{
    try
    {
        // Use your existing compiler logic
        SymbolTable symbols;
        auto tokens = Lexer().tokenize(codeBuffer);
        Parser(tokens, symbols).parse();

        // Format symbol table output
        std::stringstream ss;
        symbols.printSymbols(ss);
        symbolTableOutput = ss.str();
        errorOutput.clear();
    }
    catch (const std::exception &e)
    {
        errorOutput = "Compilation Error: " + std::string(e.what());
    }
}

void CompilerGUI::render()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Handle file dialog
        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlg"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
                try
                {
                    std::ifstream file(filePath);
                    if (file)
                    {
                        codeBuffer.assign(
                            (std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
                    }
                    else
                    {
                        errorOutput = "Failed to open file: " + filePath;
                    }
                }
                catch (const std::exception &e)
                {
                    errorOutput = "File Error: " + std::string(e.what());
                }
            }
            ImGuiFileDialog::Instance()->Close();
        }

        // Main window
        ImGui::SetNextWindowSize(ImVec2(1280, 720), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("Python Compiler", nullptr, ImGuiWindowFlags_MenuBar))
        {
            // Menu bar
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Open"))
                        loadFile();
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }

            // Code editor
            static char buffer[4096] = {0};
            strncpy(buffer, codeBuffer.c_str(), sizeof(buffer));
            if (ImGui::InputTextMultiline("##Code", buffer, sizeof(buffer),
                                          ImVec2(-1, ImGui::GetContentRegionAvail().y * 0.4)))
            {
                codeBuffer = buffer;
            }

            // Compile button
            if (ImGui::Button("Compile", ImVec2(120, 30)))
            {
                compile();
            }

            // Symbol table display
            ImGui::Separator();
            ImGui::Text("Symbol Table:");
            if (ImGui::BeginChild("Symbols", ImVec2(0, 200), true))
            {
                ImGui::TextUnformatted(symbolTableOutput.c_str());
                ImGui::EndChild();
            }

            // Error display
            if (!errorOutput.empty())
            {
                ImGui::Separator();
                ImGui::TextColored(ImVec4(1, 0, 0, 1), "Errors:");
                ImGui::TextWrapped("%s", errorOutput.c_str());
            }

            ImGui::End(); // Single End() for main window
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
}