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

void printtokens(auto tokens, auto symbols)
{
    cout << "\n\nTokens:\n";
    for (auto &tk : tokens)
    {
        cout << "< ";
        switch (tk.type)
        {
        case TokenType::FalseKeyword:
            cout << "FalseKeyword";
            break;
        case TokenType::NoneKeyword:
            cout << "NoneKeyword";
            break;
        case TokenType::TrueKeyword:
            cout << "TrueKeyword";
            break;
        case TokenType::AndKeyword:
            cout << "AndKeyword";
            break;
        case TokenType::AsKeyword:
            cout << "AsKeyword";
            break;
        case TokenType::AssertKeyword:
            cout << "AssertKeyword";
            break;
        case TokenType::AsyncKeyword:
            cout << "AsyncKeyword";
            break;
        case TokenType::AwaitKeyword:
            cout << "AwaitKeyword";
            break;
        case TokenType::BreakKeyword:
            cout << "BreakKeyword";
            break;
        case TokenType::ClassKeyword:
            cout << "ClassKeyword";
            break;
        case TokenType::ContinueKeyword:
            cout << "ContinueKeyword";
            break;
        case TokenType::DefKeyword:
            cout << "DefKeyword";
            break;
        case TokenType::DelKeyword:
            cout << "DelKeyword";
            break;
        case TokenType::ElifKeyword:
            cout << "ElifKeyword";
            break;
        case TokenType::ElseKeyword:
            cout << "ElseKeyword";
            break;
        case TokenType::ExceptKeyword:
            cout << "ExceptKeyword";
            break;
        case TokenType::FinallyKeyword:
            cout << "FinallyKeyword";
            break;
        case TokenType::ForKeyword:
            cout << "ForKeyword";
            break;
        case TokenType::FromKeyword:
            cout << "FromKeyword";
            break;
        case TokenType::GlobalKeyword:
            cout << "GlobalKeyword";
            break;
        case TokenType::IfKeyword:
            cout << "IfKeyword";
            break;
        case TokenType::ImportKeyword:
            cout << "ImportKeyword";
            break;
        case TokenType::InKeyword:
            cout << "InKeyword";
            break;
        case TokenType::IsKeyword:
            cout << "IsKeyword";
            break;
        case TokenType::LambdaKeyword:
            cout << "LambdaKeyword";
            break;
        case TokenType::NonlocalKeyword:
            cout << "NonlocalKeyword";
            break;
        case TokenType::NotKeyword:
            cout << "NotKeyword";
            break;
        case TokenType::OrKeyword:
            cout << "OrKeyword";
            break;
        case TokenType::PassKeyword:
            cout << "PassKeyword";
            break;
        case TokenType::RaiseKeyword:
            cout << "RaiseKeyword";
            break;
        case TokenType::ReturnKeyword:
            cout << "ReturnKeyword";
            break;
        case TokenType::TryKeyword:
            cout << "TryKeyword";
            break;
        case TokenType::WhileKeyword:
            cout << "WhileKeyword";
            break;
        case TokenType::WithKeyword:
            cout << "WithKeyword";
            break;
        case TokenType::YieldKeyword:
            cout << "YieldKeyword";
            break;
        case TokenType::IDENTIFIER:
            cout << "IDENTIFIER";
            break;
        case TokenType::NUMBER:
            cout << "NUMBER";
            break;
        case TokenType::OPERATOR:
            cout << "OPERATOR";
            break;
        case TokenType::LeftParenthesis:
            cout << "LeftParenthesis";
            break;
        case TokenType::RightParenthesis:
            cout << "RightParenthesis";
            break;
        case TokenType::LeftBracket:
            cout << "LeftBracket";
            break;
        case TokenType::RightBracket:
            cout << "RightBracket";
            break;
        case TokenType::LeftBrace:
            cout << "LeftBrace";
            break;
        case TokenType::RightBrace:
            cout << "RightBrace";
            break;
        case TokenType::Colon:
            cout << "Colon";
            break;
        case TokenType::Comma:
            cout << "Comma";
            break;
        case TokenType::Dot:
            cout << "Dot";
            break;
        case TokenType::Semicolon:
            cout << "Semicolon";
            break;
        case TokenType::STRING_LITERAL:
            cout << "STRING_LITERAL";
            break;
        case TokenType::INDENT:
            cout << "INDENT";
            break;
        case TokenType::DEDENT:
            cout << "DEDENT";
            break;
        case TokenType::UNKNOWN:
            cout << "UNKNOWN";
            break;
        }
        cout << ", ";
        if (tk.type == TokenType::IDENTIFIER)
        {
            string key = tk.lexeme + "@" + tk.scope;
            if (symbols.table.find(key) != symbols.table.end())
            {
                cout << "symbol table entry : " << symbols.table[key].entry;
            }
            else
            {
                cout << "symbol table entry: not found";
            }
        }
        else
        {
            cout << tk.lexeme;
        }
        cout << " > ";
        cout << " | LINE NUMBER: " << tk.lineNumber << endl;
    }
    cout << endl;
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
        printtokens(tokens, symbols);
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