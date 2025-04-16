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
    errors.clear(); // Clear previous errors
    try
    {
        // Use your existing compiler logic with error collection
        SymbolTable symbols;
        std::vector<Error> tokenErrors;
        auto tokens = Lexer().tokenize(codeBuffer, tokenErrors);

        // Add tokenization errors to main error list
        errors.insert(errors.end(), tokenErrors.begin(), tokenErrors.end());

        // Only proceed if no tokenization errors
        if (errors.empty())
        {
            Parser(tokens, symbols).parse();

            // Format symbol table output
            std::stringstream ss;
            symbols.printSymbols(ss);
            symbolTableOutput = ss.str();
        }
    }
    catch (const UnterminatedStringError &e)
    {
        errors.push_back({"Unterminated string literal", e.line_number, e.index});
    }
    catch (const std::exception &e)
    {
        errors.push_back({e.what(), -1, 0}); // Generic error
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
                        errors.clear(); // Clear errors when loading new file
                    }
                    else
                    {
                        errors.push_back({"Failed to open file: " + filePath, -1, 0});
                    }
                }
                catch (const std::exception &e)
                {
                    errors.push_back({"File Error: " + std::string(e.what()), -1, 0});
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

            // Error display section
            ImGui::Separator();
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Errors:");
            if (ImGui::BeginChild("Errors", ImVec2(0, 150), true))
            {
                for (const auto &error : errors)
                {
                    ImGui::TextWrapped("Line %d, Pos %zu: %s",
                                       error.line,
                                       error.position,
                                       error.message.c_str());
                }
                ImGui::EndChild();
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