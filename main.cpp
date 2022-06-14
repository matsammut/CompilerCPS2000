#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

class tableLexerReturn {       // The class
  public:             // Access specifier
    int stackTop;        // Attribute (int variable)
    string lexemeFin;  // Attribute (string variable)
    int counter;
};

char NextChar(vector<char> input,int decrement){
    static int nextcharpointer = -1;
    if (decrement == -1){
        nextcharpointer -= 1;
        return 'F';
    }
    else if(decrement == 0){
        nextcharpointer = -1;
        return 'F';
    }
    else{
        nextcharpointer += 1;
        return input[nextcharpointer];
    }
}

enum classif{ ERROR = 0,EXCLEMATION = 1, SINGLEQUOTE = 2, LBRACKET = 3, RBRACKET =  4,MULTI = 5, PLUS = 6, MINUS = 7, STOP = 8, DIVISION = 9, DIGIT = 10, COLIN = 11, SEMICOLIN = 12, LTHAN = 13, EQUALS = 14, GTHAN = 15, CHAR = 16, BACKSLASH = 17, LCURLY = 18, RCURLY = 19, COMMA = 20,SPACE = 21 };
classif CharCat(char character){
    // -100 = other
    int asciiIndex = character;
    classif CAT[] = {ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,SPACE, EXCLEMATION, ERROR,ERROR, ERROR, ERROR, ERROR, SINGLEQUOTE, LBRACKET,RBRACKET,MULTI, PLUS,COMMA,MINUS, STOP, DIVISION,DIGIT,DIGIT,DIGIT,DIGIT,DIGIT,DIGIT,DIGIT,DIGIT,DIGIT,DIGIT, COLIN, SEMICOLIN, LTHAN,EQUALS,GTHAN, ERROR, ERROR, CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,ERROR,BACKSLASH,ERROR,ERROR,CHAR,ERROR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR, LCURLY, ERROR, RCURLY, ERROR, ERROR};
    
    return CAT[asciiIndex];
}

tableLexerReturn NextWord(vector<char> input){
    // token type
    int Sa[] = {1,3,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,26,27,30,33,34};
    tableLexerReturn returnLexer;

    // state x character
    // transition table
    int TX[36][20] = {};
    for ( int i = 0; i < 35; i ++){
        for(int j = 0; j < 22; j++){
            TX[i][j] = -1;
        }
    }
    TX[0][10] = 1;
    TX[1][8] = 2;
    TX[1][10] = 1;
    TX[2][10] = 3;
    TX[3][10] = 3;
    TX[0][2] = 4;
    for(int j = 0; j < 22; j++){
            TX[4][j] = 4;
    }
    TX[4][2] = 5;
    TX[0][16] = 6;
    TX[6][16] = 6;
    TX[6][10] = 6;
    TX[0][3] = 7;
    TX[0][4] = 12;
    TX[0][13] = 8;
    TX[8][14] = 9;
    TX[0][15] = 10;
    TX[10][14] = 11;
    TX[0][14] = 13;
    TX[13][14] = 14;
    TX[0][7] = 15;
    TX[15][13] = 16;
    TX[0][5] = 17;
    TX[0][6] = 18;
    TX[0][9] = 19;
    TX[19][9] = 27;
    for(int j = 0; j < 22; j++){
            TX[27][j] = 27;
    }
    TX[0][12] = 20;
    TX[0][11] = 21;
    TX[0][18] = 22;
    TX[0][19] = 23;
    TX[0][20] = 24;
    TX[0][1] = 25;
    TX[25][14] = 26;
    TX[19][5] = 28;
    TX[28][16] = 31;
    TX[31][16] = 31;
    TX[31][5] = 32;
    TX[32][16] = 31;
    TX[32][9] = 33;
    TX[0][17] = 29;
    TX[29][17] = 30;
    TX[30][16] = 30;
    TX[0][21] = 34;
    // Initialisation
    int state = 0;
    string lexeme = "";
    stack<int> stack;
    stack.push(100);
    // 100 is bad

    char character = '\0';
    returnLexer.counter = 0;
    // Scanning Loop
    // 69 is Se (error state)
    while (state != -1){
        returnLexer.counter += 1;
        // Next Char
        character = NextChar(input,4);
        lexeme.push_back(character);
        // bool exists = std::find(Sa, Sa + n, character) != Sa + n;
        bool exists = (std::find(std::begin(Sa), std::end(Sa), state) != std::end(Sa));
            if (exists) {
                //clear stack
                while (!stack.empty()){
                    stack.pop();
                }
            }
        stack.push(state);
        // return the class of the character
        classif cat = CharCat(character);
        // update state
        state = TX[state][cat];
    }
    stack.push(state);
    // Rollback Loop
    while (!(std::find(std::begin(Sa), std::end(Sa), state) != std::end(Sa)) || state == 100){
        // method to safely pop in c++
        stack.pop();
        lexeme.pop_back();
        state = stack.top();
    }

    
    // Report result
    if (std::find(std::begin(Sa), std::end(Sa), state) != std::end(Sa)){
        returnLexer.stackTop = stack.top();
        returnLexer.lexemeFin = lexeme;
        cout << lexeme <<"\t"<<+ stack.top() << "\n";
        return returnLexer;
    }
    else{
        cout << "ERROR";
        exit(0);
    }
}

int main(){
    ifstream myfile("example.txt");
    string line;
    tableLexerReturn ReturnHold;
    vector<string> tokens; 
    vector<int> stateType;
    
    
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {                          
            vector<char> fileVector; 
            size_t notEOF = 0;
            for (size_t i = 0; i < line.length(); i++){
                fileVector.push_back(line[i]);
            }

            //print vector as string
            std::string s(fileVector.begin(), fileVector.end());
            std::cout << s <<"\n";
            while (notEOF != fileVector.size()){
                
                ReturnHold = NextWord(fileVector);
                tokens.push_back(ReturnHold.lexemeFin);
                stateType.push_back(ReturnHold.stackTop);
                notEOF += ReturnHold.counter;
                notEOF -= 1;
                NextChar(fileVector, -1);
            }
            NextChar(fileVector, 0);
        }
        myfile.close();
    }
}

// NextWord() {
//  state = SO; 
// lexeme = "";
//  stack.clear0;
//  stack.push(bad);
//  } 

// Scanning Loop 
// while(state!=Se) NextChar(&char);
//  lexeme += char; 
// if (state in Sa) stack.clear();
//  stack.push(state);
//  cat = CharCat(char);
//  state = TX[state,cat]; 
// } 

// Rollback Loop 
// while( state!=Sa && state!=bad) { 
// state = stack.popl);
//  truncate lexeme; 
// }


// Report result 
// if(state in Sa) {
//  return Type[state]; 
// else return invalid; 
// }