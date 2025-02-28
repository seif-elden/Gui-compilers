//
// Created by Mohamd Tobgi on 28/02/2025.
//
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_set>
#include <unordered_map>

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
    // Possible info you might track:
    // - type (int, float, string, etc.)
    // - scope (global, local)
    // - usage counts
    // For simplicity, we'll store just the symbol name and a string "info"
    std::unordered_map<std::string, std::string> table;

    void addSymbol(const std::string& name, const std::string& info) {
        // If symbol doesn't exist, add it; else update or ignore
        if (table.find(name) == table.end()) {
            table[name] = info;
            std::cout << "Added symbol: " << name << " => " << info << "\n";
        }
    }

    bool hasSymbol(const std::string& name) {
        return (table.find(name) != table.end());
    }

    void printSymbols() {
        std::cout << "Symbol Table:\n";
        for (auto &entry : table) {
            std::cout << "  " << entry.first << " => " << entry.second << "\n";
        }
    }
};

// ----------------------------------------------
// 4. Lexer
// ----------------------------------------------
class Lexer {
public:
    // A set of Python keywords to illustrate
    // (not exhaustive of all Python keywords)
    std::unordered_set<std::string> pythonKeywords = {
        "False", "None", "True", "and", "as", "assert", "async", "await",
        "break", "class", "continue", "def", "del", "elif", "else",
        "except", "finally", "for", "from", "global", "if", "import",
        "in", "is", "lambda", "nonlocal", "not", "or", "pass", "raise",
        "return", "try", "while", "with", "yield"
    };

    // Some common single-character or multi-character operators
    // (not exhaustive)
    std::unordered_set<std::string> operators = {
        "+", "-", "*", "/", "%", "//", "**", "=", "==", "!=", "<", "<=", ">", ">="
    };

    // Delimiters (parentheses, commas, colons, etc.)
    // (again, not exhaustive for Python)
    std::unordered_set<char> delimiters = {
        '(', ')', ':', ',', '.', '[', ']', '{', '}', ';'
    };

    // Symbol table reference
    SymbolTable &symbolTable;

    Lexer(SymbolTable &symTable) : symbolTable(symTable) {}

    std::vector<Token> tokenize(const std::string& source) {
        std::vector<Token> tokens;
        int lineNumber = 1;
        size_t i = 0;

        while (i < source.size()) {
            char c = source[i];

            // Handle whitespace and newlines
            if (c == ' ' || c == '\t' || c == '\r') {
                i++;
                continue;
            }
            if (c == '\n') {
                lineNumber++;
                i++;
                continue;
            }

            // Handle comments (assuming # for inline comment)
            if (c == '#') {
                // Skip the rest of the line
                while (i < source.size() && source[i] != '\n') {
                    i++;
                }
                continue;
            }

            // Handle string literals (just double-quote in this example)
            if (c == '\"') {
                size_t start = i++;
                while (i < source.size() && source[i] != '\"') {
                    // Allow for escaped quotes (\")
                    if (source[i] == '\\' && i+1 < source.size() && source[i+1] == '\"') {
                        i += 2;
                    } else {
                        i++;
                    }
                }
                // Include the closing quote if present
                if (i < source.size() && source[i] == '\"') {
                    i++;
                }
                std::string strLiteral = source.substr(start, i - start);
                tokens.push_back(Token(TokenType::STRING_LITERAL, strLiteral, lineNumber));
                continue;
            }

            // Handle operators (could be 1 or 2 chars, e.g. ==, !=, >=, etc.)
            // We'll do a basic check for single-char and next check for two-char
            if (isOperatorStart(c)) {
                // Try two-character operator
                if (i + 1 < source.size()) {
                    std::string twoCharOp;
                    twoCharOp.push_back(c);
                    twoCharOp.push_back(source[i+1]);
                    if (operators.find(twoCharOp) != operators.end()) {
                        tokens.push_back(Token(TokenType::OPERATOR, twoCharOp, lineNumber));
                        i += 2;
                        continue;
                    }
                }
                // Otherwise it's a single-character operator
                std::string op(1, c);
                if (operators.find(op) != operators.end()) {
                    tokens.push_back(Token(TokenType::OPERATOR, op, lineNumber));
                    i++;
                    continue;
                }
            }

            // Handle delimiters
            if (delimiters.find(c) != delimiters.end()) {
                tokens.push_back(Token(TokenType::DELIMITER, std::string(1, c), lineNumber));
                i++;
                continue;
            }

            // Handle numeric literals
            if (std::isdigit(c)) {
                size_t start = i;
                while (i < source.size() && (std::isdigit(source[i]) || source[i] == '.')) {
                    i++;
                }
                std::string num = source.substr(start, i - start);
                tokens.push_back(Token(TokenType::NUMBER, num, lineNumber));
                continue;
            }

            // Handle identifiers/keywords (start with letter or underscore)
            if (std::isalpha(c) || c == '_') {
                size_t start = i;
                while (i < source.size() && (std::isalnum(source[i]) || source[i] == '_')) {
                    i++;
                }
                std::string word = source.substr(start, i - start);

                // Check if it's a keyword
                if (pythonKeywords.find(word) != pythonKeywords.end()) {
                    tokens.push_back(Token(TokenType::KEYWORD, word, lineNumber));
                } else {
                    // Otherwise treat it as an identifier
                    tokens.push_back(Token(TokenType::IDENTIFIER, word, lineNumber));

                    // Insert into symbol table if not present
                    if (!symbolTable.hasSymbol(word)) {
                        symbolTable.addSymbol(word, "identifier");
                    }
                }
                continue;
            }

            // If none of the above matched, mark as UNKNOWN
            tokens.push_back(Token(TokenType::UNKNOWN, std::string(1, c), lineNumber));
            i++;
        }

        return tokens;
    }

private:
    bool isOperatorStart(char c) {
        // A helper to quickly check if c could be an operator
        // We'll just check if it's in the set for single-char operators
        // or if it matches typical operator characters.
        return (operators.find(std::string(1, c)) != operators.end() ||
                c == '!' || c == '=' || c == '<' || c == '>');
    }
};

// ----------------------------------------------
// 5. Demonstration
// ----------------------------------------------
int main() {
    SymbolTable symTable;
    Lexer lexer(symTable);

    // Example Python-like source code
    std::string sourceCode = R"(
# This is a comment
def myFunction(x):
    if x > 10:
        return True
    else:
        return False

y = 5
while y < 10:
    y = y + 1
)";

    // Tokenize the code
    std::vector<Token> tokens = lexer.tokenize(sourceCode);

    // Print out tokens
    std::cout << "Tokens:\n";
    for (auto &tk : tokens) {
        std::cout << "  Line " << tk.lineNumber << " | "
                  << "Type: ";
        switch (tk.type) {
            case TokenType::KEYWORD:       std::cout << "KEYWORD";       break;
            case TokenType::IDENTIFIER:    std::cout << "IDENTIFIER";    break;
            case TokenType::NUMBER:        std::cout << "NUMBER";        break;
            case TokenType::OPERATOR:      std::cout << "OPERATOR";      break;
            case TokenType::DELIMITER:     std::cout << "DELIMITER";     break;
            case TokenType::STRING_LITERAL:std::cout << "STRING_LITERAL";break;
            case TokenType::COMMENT:       std::cout << "COMMENT";       break;
            case TokenType::UNKNOWN:       std::cout << "UNKNOWN";       break;
        }
        std::cout << " | Lexeme: " << tk.lexeme << "\n";
    }

    // Print out the symbol table
    std::cout << "\n";
    symTable.printSymbols();

    return 0;
}
