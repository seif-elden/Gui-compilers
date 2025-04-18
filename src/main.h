// compiler.h
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <fstream>
#include <cctype>
#include <regex>
using namespace std;

// ----------------------------------------------
// 0. Error Structure
// ----------------------------------------------
struct Error
{
    string message;
    int line;
    size_t position;
    void print() const
    {
        cerr << "Error at line " << line << ", position " << position
             << ": " << message << endl;
    }
};

// Exception for string handling
class UnterminatedStringError : public exception
{
public:
    int line_number;
    size_t index;
    // Constructor that takes line number and index
    UnterminatedStringError(int line, int idx)
        : line_number(line), index(idx) {}
};

// ----------------------------------------------
// 1. Token Types
// ----------------------------------------------
enum class TokenType
{
    FalseKeyword,
    NoneKeyword,
    TrueKeyword,
    AndKeyword,
    AsKeyword,
    AssertKeyword,
    AsyncKeyword,
    AwaitKeyword,
    BreakKeyword,
    ClassKeyword,
    ContinueKeyword,
    DefKeyword,
    DelKeyword,
    ElifKeyword,
    ElseKeyword,
    ExceptKeyword,
    FinallyKeyword,
    ForKeyword,
    FromKeyword,
    GlobalKeyword,
    IfKeyword,
    ImportKeyword,
    InKeyword,
    IsKeyword,
    LambdaKeyword,
    NonlocalKeyword,
    NotKeyword,
    OrKeyword,
    PassKeyword,
    RaiseKeyword,
    ReturnKeyword,
    TryKeyword,
    WhileKeyword,
    WithKeyword,
    YieldKeyword,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    STRING_LITERAL,
    COMMENT,
    UNKNOWN,
    LeftParenthesis,
    RightParenthesis,
    LeftBracket,
    RightBracket,
    LeftBrace,
    RightBrace,
    Colon,
    Comma,
    Dot,
    Semicolon,
    INDENT,
    DEDENT
};

// ----------------------------------------------
// 2. Token Structure
// ----------------------------------------------
struct Token
{
    TokenType type;
    string lexeme;
    int lineNumber;
    string scope;

    Token(TokenType t, const string &l, int line, const string &s = "");
};
// 3. Scope Info Structure
// ----------------------------------------------
struct ScopeInfo
{
    std::string name;
    int indentLevel; // Indentation level when the scope started
};

// ----------------------------------------------
// 4. SymbolTable
// ----------------------------------------------
class SymbolTable
{
public:
    struct SymbolInfo
    {
        int entry;                // unique entry number
        string type = "unknown";  // e.g., "function", "class", "int", etc.
        string scope = "unknown"; // e.g., "global" or function name
        int firstAppearance = -1; // line of first appearance
        int usageCount = 0;       // how many times it is referenced

        // A new field to store a literal value if we know it (optional).
        string value;
    };

    unordered_map<string, SymbolInfo> table;
    int nextEntry = 1;

    void addSymbol(const string &name, const string &type,
                   int lineNumber, const string &scope,
                   const string &val = "");
    void updateType(const string &name, const string &scope, const string &newType);
    void updateValue(const string &name, const string &scope, const string &newValue);
    bool exist(const string &name, const string &scope);
    string getType(const string &name, const string &scope);
    string getValue(const string &name, const string &scope);
    void printSymbols(ostream &out);
};

// ----------------------------------------------
// 5. Lexer
// ----------------------------------------------
class Lexer
{
public:
    unordered_map<string, TokenType> pythonKeywords = {
        {"False", TokenType::FalseKeyword},
        {"None", TokenType::NoneKeyword},
        {"True", TokenType::TrueKeyword},
        {"and", TokenType::AndKeyword},
        {"as", TokenType::AsKeyword},
        {"assert", TokenType::AssertKeyword},
        {"async", TokenType::AsyncKeyword},
        {"await", TokenType::AwaitKeyword},
        {"break", TokenType::BreakKeyword},
        {"class", TokenType::ClassKeyword},
        {"continue", TokenType::ContinueKeyword},
        {"def", TokenType::DefKeyword},
        {"del", TokenType::DelKeyword},
        {"elif", TokenType::ElifKeyword},
        {"else", TokenType::ElseKeyword},
        {"except", TokenType::ExceptKeyword},
        {"finally", TokenType::FinallyKeyword},
        {"for", TokenType::ForKeyword},
        {"from", TokenType::FromKeyword},
        {"global", TokenType::GlobalKeyword},
        {"if", TokenType::IfKeyword},
        {"import", TokenType::ImportKeyword},
        {"in", TokenType::InKeyword},
        {"is", TokenType::IsKeyword},
        {"lambda", TokenType::LambdaKeyword},
        {"nonlocal", TokenType::NonlocalKeyword},
        {"not", TokenType::NotKeyword},
        {"or", TokenType::OrKeyword},
        {"pass", TokenType::PassKeyword},
        {"raise", TokenType::RaiseKeyword},
        {"return", TokenType::ReturnKeyword},
        {"try", TokenType::TryKeyword},
        {"while", TokenType::WhileKeyword},
        {"with", TokenType::WithKeyword},
        {"yield", TokenType::YieldKeyword}};

    unordered_set<string> operators = {
        "+", "-", "*", "/", "%", "//", "**", "=", "==", "!=", "<", "<=", ">",
        ">=", "+=", "-=", "*=", "/=", "%=", "//=", "**=", "|", "&", "^", "~", "<<", ">>"};

    unordered_map<char, TokenType> punctuationSymbols = {
        {'(', TokenType::LeftParenthesis},
        {')', TokenType::RightParenthesis},
        {':', TokenType::Colon},
        {',', TokenType::Comma},
        {'.', TokenType::Dot},
        {'[', TokenType::LeftBracket},
        {']', TokenType::RightBracket},
        {'{', TokenType::LeftBrace},
        {'}', TokenType::RightBrace},
        {';', TokenType::Semicolon}};

    vector<ScopeInfo> scopeStack;

    vector<Token> tokenize(const string &source, vector<Error> &errors);

private:
    vector<int> indentStack = {0}; // Track indentation levels (e.g., [0, 4, 8])
    bool atLineStart = true;       // Flag for newline handling
    bool lineContinuation = false; // Track line continuation via '\'
    void skipNonLeadingWhitespace(const string &source, size_t &idx);
    string handleTripleQuotedString(const string &source, size_t &idx, int &lineNumber);
    bool isOperatorStart(char c);
    string handleDoubleQuotedString(const string &source, size_t &idx, int &lineNumber);
    void processIndentation(const string &source, size_t &i, int lineNumber,
                            vector<Token> &tokens, vector<Error> &errors);
    string getScope(const vector<ScopeInfo> &scopeStack);
};

// ----------------------------------------------
// 6. Parser
// ----------------------------------------------
class Parser
{
public:
    Parser(const vector<Token> &tokens, SymbolTable &symTable);
    void parse();

private:
    const vector<Token> &tokens;
    SymbolTable &symbolTable;
    string lastKeyword;

    pair<string, string> parseExpression(size_t &i);
    pair<string, string> parseOperand(size_t &i);
    string unifyTypes(const string &t1, const string &t2);
};
