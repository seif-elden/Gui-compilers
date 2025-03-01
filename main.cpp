#include <iostream>
#include <fstream>
#include <sstream>
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
    struct SymbolInfo {
        std::string type = "unknown";  // Placeholder type
        std::string scope = "unknown"; // Placeholder scope
        int firstAppearance = -1;      // Line of first appearance
        int usageCount = 0;            // How many times it is referenced
    };

    std::unordered_map<std::string, SymbolInfo> table;

    void addSymbol(const std::string& name, const std::string& type, int lineNumber, const std::string& scope = "unknown") {
        if (table.find(name) == table.end()) {
            table[name] = SymbolInfo{ type, scope, lineNumber, 1 };
        } else {
            table[name].usageCount++;
        }
    }

    void printSymbols() {
        std::cout << "Symbol Table:\n";
        for (auto &entry : table) {
            std::cout << "  " << entry.first << " => "
                      << "Type: " << entry.second.type << ", "
                      << "Scope: " << entry.second.scope << ", "
                      << "First Appearance: Line " << entry.second.firstAppearance << ", "
                      << "Usage Count: " << entry.second.usageCount << "\n";
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
        // Keywords
        "False", "None", "True", "and", "as", "assert", "async", "await",
        "break", "class", "continue", "def", "del", "elif", "else",
        "except", "finally", "for", "from", "global", "if", "import",
        "in", "is", "lambda", "nonlocal", "not", "or", "pass", "raise",
        "return", "try", "while", "with", "yield",

        // Built-in functions
        "abs", "all", "any", "ascii", "bin", "bool", "breakpoint", "bytearray",
        "bytes", "callable", "chr", "classmethod", "compile", "complex", "delattr",
        "dict", "dir", "divmod", "enumerate", "eval", "exec", "filter", "float",
        "format", "frozenset", "getattr", "globals", "hasattr", "hash", "help",
        "hex", "id", "input", "int", "isinstance", "issubclass", "iter", "len",
        "list", "locals", "map", "max", "memoryview", "min", "next", "object",
        "oct", "open", "ord", "pow", "print", "property", "range", "repr",
        "reversed", "round", "set", "setattr", "slice", "sorted", "staticmethod",
        "str", "sum", "super", "tuple", "type", "vars", "zip", "__import__",
        "exit", "quit"
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

// Helper function to skip spaces, tabs, and carriage returns (but not newlines).
void skipWhitespace(const std::string& source, size_t& idx) {
    while (idx < source.size() &&
           (source[idx] == ' ' || source[idx] == '\t' || source[idx] == '\r')) {
        idx++;
    }
}

// Handle a single-line comment of the form: # ...
// Returns true if it handled a comment (and advanced the index), false otherwise.
bool handleSingleLineComment(const std::string& source, size_t& idx) {
    if (source[idx] == '#') {
        // Skip until the end of line
        while (idx < source.size() && source[idx] != '\n') {
            idx++;
        }
        return true;
    }
    return false;
}

// Handle triple-quoted strings (either """...""" or '''...'''), which we treat
// as multi-line comments/docstrings. Returns true if a triple-quoted string
// was found and handled, false otherwise. Updates lineNumber as needed.
bool handleTripleQuotedString(const std::string& source, size_t& idx, int& lineNumber) {
    if (idx + 2 < source.size()) {
        char c = source[idx];
        // Check for """ or ''' pattern
        if ((c == '"' || c == '\'') &&
            source[idx + 1] == c &&
            source[idx + 2] == c) {
            // Found triple quotes
            char quoteChar = c;
            idx += 3; // skip the opening triple quotes
            // Keep going until we find the matching triple quotes
            while (idx + 2 < source.size()) {
                if (source[idx] == '\n') {
                    lineNumber++;
                }
                if (source[idx] == quoteChar &&
                    source[idx + 1] == quoteChar &&
                    source[idx + 2] == quoteChar) {
                    idx += 3; // skip the closing triple quotes
                    break;
                }
                idx++;
            }
            return true;
        }
    }
    return false;
}

// After we've recognized an "import" keyword, parse one or more libraries.
// (Handles lines like: "import sys, os")
void parseImportLibraries(const std::string& source,
                          size_t& idx,
                          int lineNumber,
                          std::string& lastKeyword,
                          std::unordered_set<std::string>& importedLibraries)
{
    // We'll consider the identifier right after 'import' already consumed by the caller,
    // so we parse any subsequent libraries separated by commas.
    // e.g. "import sys, os"
    while (true) {
        skipWhitespace(source, idx);
        if (idx >= source.size() || source[idx] == '\n') {
            // End of line or file
            break;
        }
        if (source[idx] == ',') {
            idx++; // skip comma
            skipWhitespace(source, idx);

            // parse next library name
            size_t startLib = idx;
            while (idx < source.size() && (std::isalnum(source[idx]) || source[idx] == '_')) {
                idx++;
            }
            std::string libName = source.substr(startLib, idx - startLib);
            if (!libName.empty()) {
                importedLibraries.insert(libName);
                std::cout << "Imported library: " << libName << "\n";
            }
            continue;
        }
        // No comma => we must have reached something that's not part of the import line
        break;
    }
    lastKeyword.clear();
}

// After we've recognized "from <library>", parse "import <symbol(s)>"
// e.g. "from math import sqrt, cos"
void parseFromImport(const std::string& source,
                     size_t& idx,
                     int lineNumber,
                     std::string currentLibrary,
                     std::string& lastKeyword,
                     std::unordered_set<std::string>& importedSymbols,
                     std::unordered_set<std::string>& importedLibraries,
                     std::vector<Token>& tokens)
{
    skipWhitespace(source, idx);

    // Check if the next word is "import"
    size_t importStart = idx;
    while (idx < source.size() && std::isalpha(static_cast<unsigned char>(source[idx]))) {
        idx++;
    }
    std::string maybeImport = source.substr(importStart, idx - importStart);

    if (maybeImport == "import") {
        // We found "import" - add a keyword token if you like
        tokens.push_back(Token(TokenType::KEYWORD, "import", lineNumber));
        skipWhitespace(source, idx);

        // read symbols until EOL or comma
        bool done = false;
        while (!done && idx < source.size()) {
            // read a single symbol
            size_t startSym = idx;
            while (idx < source.size() &&
                   (std::isalnum(static_cast<unsigned char>(source[idx])) || source[idx] == '_')) {
                idx++;
            }
            std::string sym = source.substr(startSym, idx - startSym);

            if (!sym.empty()) {
                // e.g. "from math import sqrt"
                importedSymbols.insert(sym);
            }
            skipWhitespace(source, idx);

            if (idx >= source.size() || source[idx] == '\n') {
                done = true;
            }
            else if (source[idx] == ',') {
                idx++; // skip comma
                skipWhitespace(source, idx);
            }
            else {
                // Something else => done
                done = true;
            }
        }

        // Also track the library itself
        importedLibraries.insert(currentLibrary);
    }
    else {
        // If it's not "import", we do nothing special.
        // Optionally, you can backtrack idx = importStart if needed.
        idx = importStart; // restoring if you want to re-parse later
    }

    lastKeyword.clear();
}

// Handle an identifier or keyword. If it's an actual Python keyword (in pythonKeywords),
// we push a KEYWORD token. Otherwise, we decide if it's something to skip (self, imported lib, etc.)
// or to treat as an identifier (variable, function, class).
//
// Also deals with the logic after we see "import" or "from".
bool handleIdentifierOrKeyword(const std::string& source,
                               size_t& idx,
                               int& lineNumber,
                               std::string& lastKeyword,
                               std::vector<Token>& tokens,
                               std::unordered_set<std::string>& importedLibraries,
                               std::unordered_set<std::string>& importedSymbols)
{
    char c = source[idx];
    if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
        // Consume the entire identifier
        size_t start = idx;
        while (idx < source.size() &&
               (std::isalnum(static_cast<unsigned char>(source[idx])) || source[idx] == '_'))
        {
            idx++;
        }
        std::string word = source.substr(start, idx - start);

        // Check if it's a Python keyword
        if (pythonKeywords.find(word) != pythonKeywords.end()) {
            tokens.push_back(Token(TokenType::KEYWORD, word, lineNumber));
            lastKeyword = word;
        }
        else {
            // e.g. skip "self"
            if (word == "self") {
                return true; // We skip adding it to tokens
            }
            // If it's an imported library name or symbol, skip
            if (importedLibraries.count(word) > 0) {
                return true;
            }
            if (importedSymbols.count(word) > 0) {
                return true;
            }

            // Otherwise, treat it as an identifier (unless preceded by 'import' / 'from')
            if (!(lastKeyword == "import") && !(lastKeyword == "from")) {
                tokens.push_back(Token(TokenType::IDENTIFIER, word, lineNumber));

                // If we just had "def" or "class", register as function/class
                if (lastKeyword == "def") {
                    symbolTable.addSymbol(word, "function", lineNumber, "global");
                    lastKeyword.clear();
                }
                else if (lastKeyword == "class") {
                    symbolTable.addSymbol(word, "class", lineNumber, "global");
                    lastKeyword.clear();
                }
                else {
                    // Otherwise, treat as variable
                    symbolTable.addSymbol(word, "variable", lineNumber);
                }
            }
            else {
                // If the last keyword was 'import', we treat 'word' as a library name
                if (lastKeyword == "import") {
                    importedLibraries.insert(word);
                    std::cout << "Imported library: " << word << "\n";
                    parseImportLibraries(source, idx, lineNumber, lastKeyword, importedLibraries);
                }
                // If the last keyword was 'from', this is the library name
                else if (lastKeyword == "from") {
                    std::string currentLibrary = word;
                    parseFromImport(source, idx, lineNumber, currentLibrary,
                                    lastKeyword, importedSymbols, importedLibraries, tokens);
                }
            }
        }
        return true;
    }
    return false;
}

// Handle an assignment operator '='
bool handleAssignmentOperator(const std::string& source,
                              size_t& idx,
                              int lineNumber,
                              std::vector<Token>& tokens)
{
    if (source[idx] == '=') {
        tokens.push_back(Token(TokenType::OPERATOR, "=", lineNumber));
        idx++;
        return true;
    }
    return false;
}

// Handle a reference that starts with '.' (e.g., .upper(), .append()).
// We'll skip them entirely. Returns true if a '.' was found and consumed, false otherwise.
bool handleDotReference(const std::string& source, size_t& idx) {
    if (source[idx] == '.') {
        idx++; // skip the dot
        // Move forward past the method/attribute name
        while (idx < source.size() &&
               (std::isalnum(static_cast<unsigned char>(source[idx])) || source[idx] == '_'))
        {
            idx++;
        }
        return true;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////
//
// Now the refactored tokenize() function that uses the helper functions.
//
//////////////////////////////////////////////////////////////////////////

std::vector<Token> tokenize(const std::string& source)
{
    std::vector<Token> tokens;
    int lineNumber = 1;
    size_t i = 0;

    // Track the last keyword we saw
    std::string lastKeyword;

    // Keep track of imported libraries and symbols
    std::unordered_set<std::string> importedLibraries;
    std::unordered_set<std::string> importedSymbols;

    while (i < source.size()) {
        // 1. Skip basic whitespace (not newlines)
        skipWhitespace(source, i);
        if (i >= source.size()) {
            break;
        }

        char c = source[i];

        // 2. Handle newlines
        if (c == '\n') {
            lineNumber++;
            lastKeyword.clear();
            i++;
            continue;
        }

        // 3. Handle single-line comment (# ...)
        if (handleSingleLineComment(source, i)) {
            continue;
        }

        // 4. Handle triple-quoted strings (multiline comments/docstrings)
        if (handleTripleQuotedString(source, i, lineNumber)) {
            continue;
        }

        // 5. Handle identifiers / keywords
        if (handleIdentifierOrKeyword(source, i, lineNumber, lastKeyword,
                                      tokens, importedLibraries, importedSymbols)) {
            continue;
        }

        // 6. Handle assignment operator
        if (handleAssignmentOperator(source, i, lineNumber, tokens)) {
            continue;
        }

        // 7. Handle references starting with '.'
        if (handleDotReference(source, i)) {
            continue;
        }

        // 8. If we reach here, we have some character we don't explicitly handle
        //    Just move past it
        i++;
    }

    // Return the collected tokens
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
std::string readFile(const std::string& filename) {
    std::ifstream fileStream(filename);
    if (!fileStream.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::stringstream buffer;
    buffer << fileStream.rdbuf();  // Read the entire file into a stringstream
    return buffer.str();
}

int main() {
    try {
        SymbolTable symTable;
        Lexer lexer(symTable);

        // Read Python-like source code from an external file, e.g. script.py
        std::string sourceCode = readFile("/Users/mohamdtobgi/CLionProjects/compilers/script.py");

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

    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
