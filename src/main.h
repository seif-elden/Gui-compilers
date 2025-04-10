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
    Semicolon
};

// ----------------------------------------------
// 2. Token Structure
// ----------------------------------------------
struct Token
{
    TokenType type;
    std::string lexeme;
    int lineNumber;
    std::string scope;

    Token(TokenType t, const std::string &l, int line, const std::string &s = "");
};

// ----------------------------------------------
// 3. SymbolTable
// ----------------------------------------------
class SymbolTable
{
public:
    struct SymbolInfo
    {
        std::string type = "unknown";
        std::string scope = "unknown";
        int firstAppearance = -1;
        int usageCount = 0;
        std::string value;
    };

    std::unordered_map<std::string, SymbolInfo> table;

    void addSymbol(const std::string &name, const std::string &type,
                   int lineNumber, const std::string &scope,
                   const std::string &val = "");
    void updateType(const std::string &name, const std::string &scope, const std::string &newType);
    void updateValue(const std::string &name, const std::string &scope, const std::string &newValue);
    bool exist(const std::string &name, const std::string &scope);
    std::string getType(const std::string &name, const std::string &scope);
    std::string getValue(const std::string &name, const std::string &scope);
    void printSymbols(std::ostream &out);
};

// ----------------------------------------------
// 4. Lexer
// ----------------------------------------------
class Lexer
{
public:
    std::unordered_map<std::string, TokenType> pythonKeywords = {
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

    std::unordered_set<std::string> operators = {
        "+", "-", "*", "/", "%", "//", "**", "=", "==", "!=", "<", "<=", ">",
        ">=", "+=", "-=", "*=", "/=", "%=", "//=", "**=", "|", "&", "^", "~", "<<", ">>"};

    std::unordered_map<char, TokenType> punctuationSymbols = {
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
    std::string currentScope = "global";

    std::vector<Token> tokenize(const std::string &source);

private:
    void skipWhitespace(const std::string &source, size_t &idx);
    std::string handleTripleQuotedString(const std::string &source, size_t &idx, int &lineNumber);
    bool isOperatorStart(char c);
    std::string readStringLiteral(const std::string &source, size_t &idx, int lineNumber);
};

// ----------------------------------------------
// 5. Parser
// ----------------------------------------------
class Parser
{
public:
    Parser(const std::vector<Token> &tokens, SymbolTable &symTable);
    void parse();

private:
    const std::vector<Token> &tokens;
    SymbolTable &symbolTable;
    std::string lastKeyword;

    std::pair<std::string, std::string> parseExpression(size_t &i);
    std::pair<std::string, std::string> parseOperand(size_t &i);
    std::string unifyTypes(const std::string &t1, const std::string &t2);
};