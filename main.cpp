#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// ----------------------------------------------
// 1. Token Types
// ----------------------------------------------
enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    DELIMITER,
    STRING_LITERAL,
    COMMENT,
    UNKNOWN
};

// ----------------------------------------------
// 2. Token Structure
// ----------------------------------------------
struct Token {
    TokenType type;
    std::string lexeme;
    int lineNumber;

    Token(TokenType t, const std::string& l, int line)
        : type(t), lexeme(l), lineNumber(line) {}
};

// ----------------------------------------------
// 3. Symbol Table
// ----------------------------------------------
class SymbolTable {
public:
    struct SymbolInfo {
        std::string type = "unknown";  // e.g., "function", "class", "int", etc.
        std::string scope = "unknown"; // e.g., "global" or "local"
        int firstAppearance = -1;      // line of first appearance
        int usageCount = 0;            // how many times it is referenced

        // A new field to store a literal value if we know it (optional).
        // For example, if x = 42, then `value = "42"`. If x = y, no literal is stored.
        std::string value;
    };

    std::unordered_map<std::string, SymbolInfo> table;

    void addSymbol(const std::string& name, const std::string& type,
                   int lineNumber, const std::string& scope = "global",
                   const std::string& val = "")
    {
        auto it = table.find(name);
        if (it == table.end()) {
            // If this symbol hasn't appeared before, create an entry
            SymbolInfo info;
            info.type = type;
            info.scope = scope;
            info.firstAppearance = lineNumber;
            info.usageCount = 1;
            info.value = val;
            table[name] = info;
        } else {
            // If it already exists, increment usage and possibly update the type/value
            it->second.usageCount++;
            // If the type was unknown before, or if we want to override it, do so:
            if (it->second.type == "unknown" && type != "unknown") {
                it->second.type = type;
            }
            // Update the value if we explicitly have a new one
            if (!val.empty()) {
                it->second.value = val;
            }
        }
    }

    // Allows updating a symbol's type after creation.
    void updateType(const std::string& name, const std::string& newType) {
        auto it = table.find(name);
        if (it != table.end()) {
            it->second.type = newType;
        }
    }

    // Allows updating a symbol's literal value after creation.
    void updateValue(const std::string& name, const std::string& newValue) {
        auto it = table.find(name);
        if (it != table.end()) {
            it->second.value = newValue;
        }
    }

    bool exist(const std::string& name) {
        return (table.find(name) != table.end());
    }

    // Retrieve the type of a symbol if it exists
    std::string getType(const std::string& name) {
        auto it = table.find(name);
        if (it != table.end()) {
            return it->second.type;
        }
        return "unknown";
    }

    // Retrieve the literal value (if any)
    std::string getValue(const std::string& name) {
        auto it = table.find(name);
        if (it != table.end()) {
            return it->second.value;
        }
        return "";
    }

    void printSymbols() {
        std::cout << "Symbol Table:\n";
        for (auto &entry : table) {
            std::cout << "  " << entry.first << " => "
                      << "Type: " << entry.second.type << ", "
                      << "Scope: " << entry.second.scope << ", "
                      << "First Appearance: Line " << entry.second.firstAppearance << ", "
                      << "Usage Count: " << entry.second.usageCount
                      << "\n";
            if (!entry.second.value.empty()) {
                std::cout << ", Value: " << entry.second.value;
            }
            std::cout << "\n";
        }
    }
};

// ----------------------------------------------
// 4. Lexer (purely lexical analysis)
// ----------------------------------------------
class Lexer {
public:
    // A set of Python-like keywords (not exhaustive)
    std::unordered_set<std::string> pythonKeywords = {
        "False", "None", "True", "and", "as", "assert", "async", "await",
        "break", "class", "continue", "def", "del", "elif", "else",
        "except", "finally", "for", "from", "global", "if", "import",
        "in", "is", "lambda", "nonlocal", "not", "or", "pass", "raise",
        "return", "try", "while", "with", "yield"
    };

    // Some common single/multi-character operators
    std::unordered_set<std::string> operators = {
        "+", "-", "*", "/", "%", "//", "**", "=", "==", "!=", "<", "<=", ">", ">="
    };

    // Common delimiters
    std::unordered_set<char> delimiters = {
        '(', ')', ':', ',', '.', '[', ']', '{', '}', ';'
    };

    // The tokenize() function produces tokens without modifying the symbol table.
    std::vector<Token> tokenize(const std::string& source)
    {
        std::vector<Token> tokens;
        int lineNumber = 1;
        size_t i = 0;

        while (i < source.size()) {
            skipWhitespace(source, i);
            if (i >= source.size()) break;

            char c = source[i];

            // Handle newlines
            if (c == '\n') {
                lineNumber++;
                i++;
                continue;
            }

            // Handle single-line comments (# ...)
            if (c == '#') {
                while (i < source.size() && source[i] != '\n') {
                    i++;
                }
                continue;
            }

            // Handle triple-quoted strings
            if (handleTripleQuotedString(source, i, lineNumber)) {
                continue;
            }

            // Identify keywords or identifiers
            if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
                size_t start = i;
                while (i < source.size() &&
                       (std::isalnum(static_cast<unsigned char>(source[i])) || source[i] == '_')) {
                    i++;
                }
                std::string word = source.substr(start, i - start);
                if (pythonKeywords.find(word) != pythonKeywords.end()) {
                    tokens.push_back(Token(TokenType::KEYWORD, word, lineNumber));
                } else {
                    tokens.push_back(Token(TokenType::IDENTIFIER, word, lineNumber));
                }
                continue;
            }

            // Handle operators (simple version)
            if (isOperatorStart(c)) {
                // Check 2-char operators first
                if ((i + 1) < source.size()) {
                    std::string twoChars = source.substr(i, 2);
                    if (operators.find(twoChars) != operators.end()) {
                        tokens.push_back(Token(TokenType::OPERATOR, twoChars, lineNumber));
                        i += 2;
                        continue;
                    }
                }
                // Otherwise single-char operator
                std::string oneChar(1, c);
                if (operators.find(oneChar) != operators.end()) {
                    tokens.push_back(Token(TokenType::OPERATOR, oneChar, lineNumber));
                    i++;
                    continue;
                }
            }

            // Handle string literals (single/double quotes)
            if (c == '"' || c == '\'') {
                tokens.push_back(Token(
                    TokenType::STRING_LITERAL,
                    readStringLiteral(source, i, lineNumber),
                    lineNumber
                ));
                continue;
            }

            // Handle numeric literals
            if (std::isdigit(static_cast<unsigned char>(c))) {
                size_t start = i;
                bool hasDot = false;
                while (i < source.size() && (std::isdigit(source[i]) || source[i] == '.')) {
                    if (source[i] == '.' && hasDot) break;
                    else if (source[i] == '.') hasDot = true;
                    i++;
                }
                std::string num = source.substr(start, i - start);
                tokens.push_back(Token(TokenType::NUMBER, num, lineNumber));
                continue;
            }

            // Handle delimiters
            if (delimiters.find(c) != delimiters.end()) {
                tokens.push_back(Token(TokenType::DELIMITER, std::string(1, c), lineNumber));
                i++;
                continue;
            }

            // Otherwise treat as UNKNOWN
            tokens.push_back(Token(TokenType::UNKNOWN, std::string(1, c), lineNumber));
            i++;
        }

        return tokens;
    }

private:
    void skipWhitespace(const std::string& source, size_t& idx) {
        while (idx < source.size() &&
               (source[idx] == ' ' || source[idx] == '\t' || source[idx] == '\r')) {
            idx++;
        }
    }

    bool handleTripleQuotedString(const std::string& source, size_t &idx, int &lineNumber) {
        if (idx + 2 < source.size()) {
            char c = source[idx];
            if ((c == '"' || c == '\'') &&
                source[idx + 1] == c &&
                source[idx + 2] == c) {
                char quoteChar = c;
                idx += 3; // skip opening triple quotes
                while (idx + 2 < source.size()) {
                    if (source[idx] == '\n') {
                        lineNumber++;
                    }
                    if (source[idx] == quoteChar &&
                        source[idx + 1] == quoteChar &&
                        source[idx + 2] == quoteChar) {
                        idx += 3; // skip closing triple quotes
                        break;
                    }
                    idx++;
                }
                return true;
            }
        }
        return false;
    }

    bool isOperatorStart(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
                c == '=' || c == '!' || c == '<' || c == '>');
    }

    std::string readStringLiteral(const std::string& source, size_t &idx, int lineNumber) {
        char quote = source[idx];
        size_t start = idx;
        idx++; // skip the opening quote
        while (idx < source.size() && source[idx] != quote) {
            // handle escaped quotes or newlines if you want
            if (source[idx] == '\n') {
                // some languages error out, or allow triple-quoted multiline
            }
            idx++;
        }
        if (idx < source.size()) {
            idx++; // skip the closing quote
        }
        return source.substr(start, idx - start);
    }
};

// ----------------------------------------------
// 5. Parser for basic type inference
// ----------------------------------------------
class Parser {
public:
    Parser(const std::vector<Token>& tokens, SymbolTable& symTable)
        : tokens(tokens), symbolTable(symTable) {}

    void parse() {
        size_t i = 0;
        while (i < tokens.size()) {
            const Token& tk = tokens[i];

            if (tk.type == TokenType::KEYWORD) {
                // If we see 'def' or 'class', record that for the next identifier
                if (tk.lexeme == "def" || tk.lexeme == "class") {
                    lastKeyword = tk.lexeme;
                } else {
                    lastKeyword.clear();
                }
                i++;
            }
            else if (tk.type == TokenType::IDENTIFIER) {
                // If last keyword was 'def' or 'class', then this is a new function/class name
                if (lastKeyword == "def") {
                    symbolTable.addSymbol(tk.lexeme, "function", tk.lineNumber);
                    lastKeyword.clear();
                    i++;
                }
                else if (lastKeyword == "class") {
                    symbolTable.addSymbol(tk.lexeme, "class", tk.lineNumber);
                    lastKeyword.clear();
                    i++;
                }
                else {
                    // Check if next token is '=' (assignment)
                    if ((i + 1) < tokens.size() &&
                        tokens[i + 1].type == TokenType::OPERATOR &&
                        tokens[i + 1].lexeme == "=")
                    {
                        // We have "identifier = ..."
                        const std::string& lhsName = tk.lexeme;
                        int lineNumber = tk.lineNumber;
                        // Add symbol if not exist
                        if (!symbolTable.exist(lhsName)) {
                            symbolTable.addSymbol(lhsName, "unknown", lineNumber);
                        } else {
                            // If it exists, usage count will increment
                            symbolTable.table[lhsName].usageCount++;
                        }

                        // Now let's parse the assignment
                        i += 2; // skip past "identifier" and "="
                        auto [rhsType, rhsValue] = parseExpression(i);

                        // Update the LHS symbol with the inferred type/value
                        if (rhsType != "unknown") {
                            symbolTable.updateType(lhsName, rhsType);
                        }
                        if (!rhsValue.empty()) {
                            symbolTable.updateValue(lhsName, rhsValue);
                        }

                    }
                    else {

                        if (symbolTable.exist(tk.lexeme)) {
                            symbolTable.table[tk.lexeme].usageCount++;
                        }
                        i++;
                    }
                }
            }
            else {
                // We ignore other tokens (operators, delimiters, etc.) for now
                i++;
            }
        }
    }

private:
private:
    const std::vector<Token>& tokens;
    SymbolTable& symbolTable;
    std::string lastKeyword;

    // ------------------------------------------------------
    // parseExpression:
    // Parses a simple expression with multiple operands, e.g.
    //   y + 20 + z
    // We unify the types of each operand as we go.
    // We'll keep it very basic: no parentheses, no precedence.
    // We'll return the final type and a single literal value only
    // if the entire expression is a single literal. Otherwise, "".
    // ------------------------------------------------------
    std::pair<std::string, std::string> parseExpression(size_t &i) {
        // Parse the first operand
        auto [accumType, accumValue] = parseOperand(i);

        // If we have multiple operators, unify the type.
        while (i < tokens.size()) {
            // Check if next token is +, -, *, /
            if (tokens[i].type == TokenType::OPERATOR) {
                std::string op = tokens[i].lexeme;
                if (op == "+" || op == "-" || op == "*" || op == "/") {
                    // consume the operator
                    i++;
                    // parse next operand
                    auto [nextType, nextValue] = parseOperand(i);
                    // unify accumType with nextType
                    accumType = unifyTypes(accumType, nextType);
                    // If we do actual arithmetic, we'd combine accumValue & nextValue,
                    // but for a multi-operand expression, let's just drop the literal:
                    accumValue = "";
                } else {
                    // not a recognized operator for expression => break
                    break;
                }
            } else {
                // next token is not an operator => expression ended
                break;
            }
        }
        return {accumType, accumValue};
    }

    // ------------------------------------------------------
    // parseOperand:
    // Returns (type, literalValue) for a single operand,
    // advancing 'i' by one or more tokens.
    // This re-uses the same logic from a simplified version
    // of "inferTypeOfRHS" but for a single operand only.
    // ------------------------------------------------------
    std::pair<std::string, std::string> parseOperand(size_t &i) {
        if (i >= tokens.size()) {
            return {"unknown", ""};
        }

        const Token& tk = tokens[i];

        // If it's a numeric literal
        if (tk.type == TokenType::NUMBER) {
            // check if there's a '.' => float
            if (tk.lexeme.find('.') != std::string::npos) {
                i++;
                return {"float", tk.lexeme};
            } else {
                i++;
                return {"int", tk.lexeme};
            }
        }

        // If it's a string literal
        if (tk.type == TokenType::STRING_LITERAL) {
            i++;
            return {"string", tk.lexeme};
        }

        // If it's a keyword => might be True/False
        if (tk.type == TokenType::KEYWORD) {
            if (tk.lexeme == "True" || tk.lexeme == "False") {
                i++;
                return {"bool", tk.lexeme};
            }
            i++;
            return {"unknown", ""};
        }

        // If it's an identifier
        if (tk.type == TokenType::IDENTIFIER) {
            std::string name = tk.lexeme;
            std::string knownType = symbolTable.getType(name);
            std::string knownValue = symbolTable.getValue(name);
            if (!symbolTable.exist(name)) {
                symbolTable.addSymbol(name, "unknown", tk.lineNumber);
            } else {
                symbolTable.table[name].usageCount++;
            }
            i++;
            return { knownType, knownType == "unknown" ? "" : knownValue };
        }

        // if it's a tuple
        if(tk.lexeme == "("){
            string value = "(";
            i++;
            while ( i < tokens.size () && tokens[i].lexeme != ")"){
                //auto [type, value] = parseOperand(i); // if we want to know the type of the values stored too
                value = value + tokens[i].lexeme;
                i++;
            }
            if(i < tokens.size() && tokens[i].lexeme == ")"){
                i++;
            }
            value = value + ")";
            return {"tuple", value};
        }

        // if it's a list
        if(tk.lexeme == "["){
            string value = "[";
            i++;
            while ( i < tokens.size () && tokens[i].lexeme != "]"){
                value = value + tokens[i].lexeme;
                i++;
            }
            if(i < tokens.size() && tokens[i].lexeme == "]"){
                i++;
            }
            value = value + "]";
            return {"list", value};
        }

        // if it's a dictionary or set
        if(tk.lexeme == "{"){
            string value = "{";
            i++;
            bool isSet = true;
            while ( i < tokens.size () && tokens[i].lexeme != "}"){
                if(tokens[i].lexeme == ":"){
                    isSet = false;
                }
                value = value + tokens[i].lexeme;
                i++;
            }
            if(i < tokens.size() && tokens[i].lexeme == "}"){
                i++;
            }
            value = value + "}";
            return {isSet ? "set" : "dictionary", value};
        }

        // Otherwise unknown
        i++;
        return {"unknown", ""};
    }

    // ------------------------------------------------------
    // unifyTypes:
    // A minimal "unify" function for numeric/string/bool/unknown.
    // - if either is "float", result => "float"
    // - if one is "int" and the other "int", => "int"
    // - if one is "unknown", => the other (or "unknown" if both unknown)
    // - if there's a conflict (e.g., "string" + "int"), => "unknown"
    // Expand this if you want to handle more complex rules
    // ------------------------------------------------------
    std::string unifyTypes(const std::string& t1, const std::string& t2) {
        if (t1 == "unknown" && t2 == "unknown")
            return "unknown";
        if (t1 == "unknown") return t2;
        if (t2 == "unknown") return t1;

        // If either is float => float
        if (t1 == "float" || t2 == "float") {
            // If one is string and other is float => unknown, or you can define a rule
            if (t1 == "string" || t2 == "string" ||
                t1 == "bool"   || t2 == "bool") {
                return "unknown";
            }
            return "float";
        }

        // If both are int => int
        if (t1 == "int" && t2 == "int") {
            return "int";
        }

        // If both are bool => bool (some languages let you do bool+bool => int, but we'll keep it simple)
        if (t1 == "bool" && t2 == "bool") {
            return "bool";
        }

        // If either is string => let's say "unknown" for arithmetic
        if (t1 == "string" || t2 == "string") {
            return "unknown";
        }

        // If they're the same, return it
        if (t1 == t2) {
            return t1;
        }

        // Anything else => unknown
        return "unknown";
    }
};

// ----------------------------------------------
// 6. Utility function to read the entire file
// ----------------------------------------------
std::string readFile(const std::string& filename) {
    std::ifstream fileStream(filename);
    if (!fileStream.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
}

// ----------------------------------------------
// 7. Main
// ----------------------------------------------
int main() {
    try {
        // 1. Read Python-like source code from an external file
        std::string sourceCode = readFile("script.py");

        // 2. Lexical analysis: produce tokens
        Lexer lexer;
        std::vector<Token> tokens = lexer.tokenize(sourceCode);

        // 3. Print out tokens (for demonstration)
        std::cout << "Tokens:\n";
        for (auto &tk : tokens) {
            std::cout << "  Line " << tk.lineNumber << " | ";
            switch (tk.type) {
                case TokenType::KEYWORD:        std::cout << "KEYWORD";        break;
                case TokenType::IDENTIFIER:     std::cout << "IDENTIFIER";     break;
                case TokenType::NUMBER:         std::cout << "NUMBER";         break;
                case TokenType::OPERATOR:       std::cout << "OPERATOR";       break;
                case TokenType::DELIMITER:      std::cout << "DELIMITER";      break;
                case TokenType::STRING_LITERAL: std::cout << "STRING_LITERAL"; break;
                case TokenType::COMMENT:        std::cout << "COMMENT";        break;
                case TokenType::UNKNOWN:        std::cout << "UNKNOWN";        break;
            }
            std::cout << " | Lexeme: " << tk.lexeme << "\n";
        }
        std::cout << std::endl;

        // 4. Parse/semantic pass: build the symbol table with type inference
        SymbolTable symTable;
        Parser parser(tokens, symTable);
        parser.parse();

        // 5. Print final symbol table
        symTable.printSymbols();
    }
    catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
