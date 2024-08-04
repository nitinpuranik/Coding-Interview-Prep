Example input:
a,b,c
9,foo,27

Example output:
a|b  |c
9|foo|27

#define INDENT 10

void Format(std::string& input, std::string& output) {
    // Breaking input into single lines.
    for (std::string& line: input.split("\n")) {
        
        std::string newword;
        for(std::string& word: line.split(",")) {
            if (word.length() < INDENT) {
                word.append(INDENT - word.length());
                newword.concat(word, "|");
            }
        }
        newword.pop(); "a|b  |c"
        
        output.appendWithNewLine(newword);
    }
}


int main() {
    std::string input {"/*Unformatted input*/"};
    
    std::string output;
    
    Format(input, output);
    
    std::cout << output;
    
    return 0;
}