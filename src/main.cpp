#include "main.h"
#include "gui.h"

using namespace std;

// ----------------------------------------------
// Token Implementation
// ----------------------------------------------
Token::Token(TokenType t, const string &l, int line, const string &s)
    : type(t), lexeme(l), lineNumber(line), scope(s) {}

// ----------------------------------------------
// SymbolTable Implementation
// ----------------------------------------------
void SymbolTable::addSymbol(const string &name, const string &type,
                            int lineNumber, const string &scope,
                            const string &val)
{
    string uniqueKey = name + "@" + scope;
    auto it = table.find(uniqueKey);
    if (it == table.end())
    {
        SymbolInfo info;
        info.type = type;
        info.scope = scope;
        info.firstAppearance = lineNumber;
        info.usageCount = 1;
        info.value = val;
        table[uniqueKey] = info;
    }
    else
    {
        it->second.usageCount++;
        if (it->second.type == "unknown" && type != "unknown")
        {
            it->second.type = type;
        }
        if (!val.empty())
        {
            it->second.value = val;
        }
    }
}

// ... (Other SymbolTable methods from your code)
void SymbolTable::updateType(const string &name, const string &scope, const string &newType)
{
    string key = name + "@" + scope;
    if (table.find(key) != table.end())
    {
        table[key].type = newType;
    }
}
void SymbolTable::updateValue(const string &name, const string &scope, const string &newValue)
{
    string key = name + "@" + scope;
    if (table.find(key) != table.end())
    {
        table[key].value = newValue;
    }
}
bool SymbolTable::exist(const string &name, const string &scope)
{
    return table.find(name + "@" + scope) != table.end();
}
string SymbolTable::getType(const string &name, const string &scope)
{
    auto it = table.find(name + "@" + scope);
    return it != table.end() ? it->second.type : "unknown";
}
string SymbolTable::getValue(const string &name, const string &scope)
{
    auto it = table.find(name + "@" + scope);
    return it != table.end() ? it->second.value : "";
}

void SymbolTable::printSymbols(std::ostream &out)
{
    out << "Symbol Table:\n";
    for (auto &[key, info] : table)
    {
        auto at = key.find('@');
        string name = key.substr(0, at);
        string scope = key.substr(at + 1);
        out << "Name: " << name
            << ", Scope: " << scope
            << ", Type: " << info.type
            << ", First Appearance: Line " << info.firstAppearance
            << ", Usage Count: " << info.usageCount;
        if (!info.value.empty())
            out << ", Value: " << info.value;
        out << "\n";
    }
}

// ----------------------------------------------
// Lexer Implementation
// ----------------------------------------------
vector<Token> Lexer::tokenize(const string &source)
{
    vector<Token> tokens;
    int lineNumber = 1;
    size_t i = 0;

    while (i < source.size())
    {
        skipWhitespace(source, i);
        if (i >= source.size())
            break;

        char c = source[i];

        // Handle newlines
        if (c == '\n')
        {
            lineNumber++;
            i++;
            continue;
        }

        // Handle single-line comments (# ...)
        if (c == '#')
        {
            while (i < source.size() && source[i] != '\n')
            {
                i++;
            }
            continue;
        }

        int startlineNumber = lineNumber;
        string triplestring = handleTripleQuotedString(source, i, lineNumber);
        // Handle triple-quoted strings
        if (triplestring.length())
        {
            tokens.push_back(Token(
                TokenType::STRING_LITERAL,
                triplestring,
                startlineNumber));
            continue;
        }

        // Identify keywords and identifiers
        if (isalpha(static_cast<unsigned char>(c)) || c == '_')
        {
            size_t start = i;
            while (i < source.size() &&
                   (isalnum(static_cast<unsigned char>(source[i])) || source[i] == '_'))
            {
                i++;
            }
            string word = source.substr(start, i - start);
            if (pythonKeywords.find(word) != pythonKeywords.end())
            {
                // change the scope if it is a function or class
                if (word == "def" || word == "class")
                {
                    tokens.push_back(Token(pythonKeywords[word], word, lineNumber));
                    skipWhitespace(source, i);
                    size_t identifierStart = i;
                    while (i < source.size() && (isalnum(static_cast<unsigned char>(source[i])) || source[i] == '_'))
                    {
                        i++;
                    }
                    if (identifierStart < i)
                    {
                        string identifier = source.substr(identifierStart, i - identifierStart);
                        currentScope = identifier;
                        // cout<<"Current scope: " << currentScope << endl;
                        tokens.push_back(Token(TokenType::IDENTIFIER, identifier, lineNumber, currentScope));
                    }
                }
                else
                {
                    tokens.push_back(Token(pythonKeywords[word], word, lineNumber));
                }
            }
            else
            {
                tokens.push_back(Token(TokenType::IDENTIFIER, word, lineNumber, currentScope));
                // cout<< "scope of " << word << " is " << currentScope << endl;
            }
            continue;
        }

        // Handle operators (simple version)
        if (isOperatorStart(c))
        {
            // Check 2-char operators first
            if ((i + 1) < source.size())
            {
                string twoChars = source.substr(i, 2);
                if (operators.find(twoChars) != operators.end())
                {
                    tokens.push_back(Token(TokenType::OPERATOR, twoChars, lineNumber));
                    i += 2;
                    continue;
                }
            }
            // Otherwise single-char operator
            string oneChar(1, c);
            if (operators.find(oneChar) != operators.end())
            {
                tokens.push_back(Token(TokenType::OPERATOR, oneChar, lineNumber));
                i++;
                continue;
            }
        }

        // Handle string literals (single/double quotes)
        if (c == '"' || c == '\'')
        {
            tokens.push_back(Token(
                TokenType::STRING_LITERAL,
                readStringLiteral(source, i, lineNumber),
                lineNumber));
            continue;
        }

        // Handle numeric literals
        if (isdigit(static_cast<unsigned char>(c)))
        {
            size_t start = i;
            bool hasDot = false;
            while (i < source.size() && (isdigit(source[i]) || source[i] == '.'))
            {
                if (source[i] == '.' && hasDot)
                    break;
                else if (source[i] == '.')
                    hasDot = true;
                i++;
            }
            string num = source.substr(start, i - start);
            tokens.push_back(Token(TokenType::NUMBER, num, lineNumber));
            continue;
        }

        // Handle punctuation symbols
        if (punctuationSymbols.find(c) != punctuationSymbols.end())
        {
            tokens.push_back(Token(punctuationSymbols[c], string(1, c), lineNumber));
            i++;
            continue;
        }

        // Otherwise treat as UNKNOWN
        tokens.push_back(Token(TokenType::UNKNOWN, string(1, c), lineNumber));
        i++;
    }

    return tokens;
}

void Lexer::skipWhitespace(const string &source, size_t &idx)
{
    static const regex ws_regex(R"(^[ \t\r]+)");
    smatch match;

    if (idx >= source.size())
        return;

    string remaining = source.substr(idx);
    if (regex_search(remaining, match, ws_regex))
    {
        idx += match.length();
    }
}

string Lexer::handleTripleQuotedString(const string &source, size_t &idx, int &lineNumber)
{
    string mystring = "\"\"\" ";
    if (idx + 2 < source.size())
    {
        char c = source[idx];
        if ((c == '"' || c == '\'') &&
            source[idx + 1] == c &&
            source[idx + 2] == c)
        {
            char quoteChar = c;
            idx += 3; // skip opening triple quotes
            while (idx + 2 < source.size())
            {
                mystring += source[idx];
                if (source[idx] == '\n')
                {
                    lineNumber++;
                }
                if (source[idx] == quoteChar &&
                    source[idx + 1] == quoteChar &&
                    source[idx + 2] == quoteChar)
                {
                    idx += 3; // skip closing triple quotes
                    mystring += "\"\"";
                    break;
                }
                idx++;
            }
            return mystring;
        }
    }
    return "";
}

bool Lexer::isOperatorStart(char c)
{
    regex operatorRegex("[+\\-*/%=!<>]");
    return regex_match(string(1, c), operatorRegex);
}
string Lexer::readStringLiteral(const string &source, size_t &idx, int /*lineNumber*/)
{
    if (idx >= source.size())
        return "";

    char quote = source[idx];
    size_t start = idx;

    // Construct regex pattern without raw string issues
    string pattern;
    pattern += quote;         // Opening quote
    pattern += "(?:\\\\.|[^"; // Escaped sequences or non-special chars
    pattern += quote;         // Add quote to excluded chars
    pattern += "\\\\])*+";    // Close group and add quantifier
    pattern += quote;         // Closing quote

    regex re(pattern);
    smatch match;
    string remaining = source.substr(start);

    if (regex_search(remaining, match, re) && match.position() == 0)
    {
        idx = start + match.length();
        return match.str();
    }
    else
    {
        // Handle unterminated string
        idx = source.size();
        return source.substr(start);
    }
}

// ----------------------------------------------
// Parser Implementation
// ----------------------------------------------
Parser::Parser(const vector<Token> &tokens, SymbolTable &symTable)
    : tokens(tokens), symbolTable(symTable) {}

void Parser::parse()
{
    size_t i = 0;
    while (i < tokens.size())
    {
        const Token &tk = tokens[i];

        if (tk.type == TokenType::DefKeyword || tk.type == TokenType::ClassKeyword)
        {
            // If we see 'def' or 'class', record that for the next identifier
            if (tk.lexeme == "def" || tk.lexeme == "class")
            {
                lastKeyword = tk.lexeme;
            }
            else
            {
                lastKeyword.clear();
            }
            i++;
        }
        else if (tk.type == TokenType::IDENTIFIER)
        {
            // If last keyword was 'def' or 'class', then this is a new function/class name
            if (lastKeyword == "def")
            {
                symbolTable.addSymbol(tk.lexeme, "function", tk.lineNumber, tk.scope);
                lastKeyword.clear();
                i++;
            }
            else if (lastKeyword == "class")
            {
                symbolTable.addSymbol(tk.lexeme, "class", tk.lineNumber, tk.scope);
                lastKeyword.clear();
                i++;
            }
            else
            {
                // Check if next token is '=' (assignment)
                if ((i + 1) < tokens.size() &&
                    tokens[i + 1].type == TokenType::OPERATOR &&
                    tokens[i + 1].lexeme == "=")
                {
                    // We have "identifier = ..."
                    const string &lhsName = tk.lexeme;
                    int lineNumber = tk.lineNumber;
                    // Add symbol if not exist
                    string fullName = lhsName + "@" + tk.scope;
                    if (!symbolTable.exist(fullName, tk.scope))
                    {
                        symbolTable.addSymbol(lhsName, "unknown", lineNumber, tk.scope);
                    }
                    else
                    {
                        // If it exists, usage count will increment
                        symbolTable.table[lhsName + "@" + tk.scope].usageCount++;
                    }

                    // Now let's parse the assignment
                    i += 2; // skip past "identifier" and "="
                    auto [rhsType, rhsValue] = parseExpression(i);

                    // Update the LHS symbol with the inferred type/value
                    if (rhsType != "unknown")
                    {
                        symbolTable.updateType(lhsName, tk.scope, rhsType);
                    }
                    if (!rhsValue.empty())
                    {
                        symbolTable.updateValue(lhsName, tk.scope, rhsValue);
                    }
                }
                else
                {

                    if (symbolTable.exist(tk.lexeme, tk.scope))
                    {
                        symbolTable.table[tk.lexeme + "@" + tk.scope].usageCount++;
                    }
                    i++;
                }
            }
        }
        else
        {
            // We ignore other tokens (operators, delimiters, etc.) for now
            i++;
        }
    }
}

pair<string, string> Parser::parseExpression(size_t &i)
{
    // Parse the first operand
    auto [accumType, accumValue] = parseOperand(i);

    // If we have multiple operators, unify the type.
    while (i < tokens.size())
    {
        // Check if next token is +, -, *, /
        if (tokens[i].type == TokenType::OPERATOR)
        {
            string op = tokens[i].lexeme;
            if (op == "+" || op == "-" || op == "*" || op == "/")
            {
                // consume the operator
                i++;
                // parse next operand
                auto [nextType, nextValue] = parseOperand(i);
                // unify accumType with nextType
                accumType = unifyTypes(accumType, nextType);
                // If we do actual arithmetic, we'd combine accumValue & nextValue,
                // but for a multi-operand expression, let's just drop the literal:
                accumValue = "";
            }
            else
            {
                // not a recognized operator for expression => break
                break;
            }
        }
        else
        {
            // next token is not an operator => expression ended
            break;
        }
    }
    return {accumType, accumValue};
}

pair<string, string> Parser::parseOperand(size_t &i)
{
    if (i >= tokens.size())
    {
        return {"unknown", ""};
    }

    const Token &tk = tokens[i];

    // If it's a numeric literal
    if (tk.type == TokenType::NUMBER)
    {
        // check if there's a '.' => float
        if (tk.lexeme.find('.') != string::npos)
        {
            i++;
            return {"float", tk.lexeme};
        }
        else
        {
            i++;
            return {"int", tk.lexeme};
        }
    }

    // If it's a string literal
    if (tk.type == TokenType::STRING_LITERAL)
    {
        i++;
        return {"string", tk.lexeme};
    }

    // If it's a keyword => might be True/False
    if (tk.type == TokenType::FalseKeyword || tk.type == TokenType::TrueKeyword)
    {
        if (tk.lexeme == "True" || tk.lexeme == "False")
        {
            i++;
            return {"bool", tk.lexeme};
        }
        i++;
        return {"unknown", ""};
    }

    // If it's an identifier
    if (tk.type == TokenType::IDENTIFIER)
    {
        string name = tk.lexeme;
        string knownType = symbolTable.getType(name, tk.scope);
        string knownValue = symbolTable.getValue(name, tk.scope);
        string fullName = name + "@" + tk.scope;
        if (!symbolTable.exist(fullName, tk.scope))
        {
            symbolTable.addSymbol(name, "unknown", tk.lineNumber, tk.scope);
        }
        else
        {
            symbolTable.table[name].usageCount++;
        }
        i++;
        return {knownType, knownType == "unknown" ? "" : knownValue};
    }

    // if it's a tuple
    if (tk.lexeme == "(")
    {
        string value = "(";
        i++;
        while (i < tokens.size() && tokens[i].lexeme != ")")
        {
            // auto [type, value] = parseOperand(i); // if we want to know the type of the values stored too
            value = value + tokens[i].lexeme;
            i++;
        }
        if (i < tokens.size() && tokens[i].lexeme == ")")
        {
            i++;
        }
        value = value + ")";
        return {"tuple", value};
    }

    // if it's a list
    if (tk.lexeme == "[")
    {
        string value = "[";
        i++;
        while (i < tokens.size() && tokens[i].lexeme != "]")
        {
            value = value + tokens[i].lexeme;
            i++;
        }
        if (i < tokens.size() && tokens[i].lexeme == "]")
        {
            i++;
        }
        value = value + "]";
        return {"list", value};
    }

    // if it's a dictionary or set
    if (tk.lexeme == "{")
    {
        string value = "{";
        i++;
        bool isSet = true;
        while (i < tokens.size() && tokens[i].lexeme != "}")
        {
            if (tokens[i].lexeme == ":")
            {
                isSet = false;
            }
            value = value + tokens[i].lexeme;
            i++;
        }
        if (i < tokens.size() && tokens[i].lexeme == "}")
        {
            i++;
        }
        value = value + "}";
        return {isSet ? "set" : "dictionary", value};
    }

    // Otherwise unknown
    i++;
    return {"unknown", ""};
}

string Parser::unifyTypes(const string &t1, const string &t2)
{
    if (t1 == "unknown" && t2 == "unknown")
        return "unknown";
    if (t1 == "unknown")
        return t2;
    if (t2 == "unknown")
        return t1;

    // If either is float => float
    if (t1 == "float" || t2 == "float")
    {
        // If one is string and other is float => unknown, or you can define a rule
        if (t1 == "string" || t2 == "string" ||
            t1 == "bool" || t2 == "bool")
        {
            return "unknown";
        }
        return "float";
    }

    // If both are int => int
    if (t1 == "int" && t2 == "int")
    {
        return "int";
    }

    // If both are bool => bool (some languages let you do bool+bool => int, but we'll keep it simple)
    if (t1 == "bool" && t2 == "bool")
    {
        return "bool";
    }

    // If either is string => let's say "unknown" for arithmetic
    if (t1 == "string" || t2 == "string")
    {
        return "unknown";
    }

    // If they're the same, return it
    if (t1 == t2)
    {
        return t1;
    }

    // Anything else => unknown
    return "unknown";
}

// ----------------------------------------------
// Main Function
// ----------------------------------------------
int main()
{
    CompilerGUI gui;
    gui.render();
    return 0;
}