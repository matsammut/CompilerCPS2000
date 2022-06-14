#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

int main(){
    cout << "Test123 FOR BASH";
    ifstream myfile("example.txt");
    string line;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
        cout << line << '\n';
        }
        cin >> line;
        for (int i; i < line.length(); i++){

        }
        myfile.close();
    }


}

enum classif{ ERROR = 0,EXCLEMATION = 1, SINGLEQUOTE = 2, LBRACKET = 3, RBRACKET =  4,MULTI = 5, PLUS = 6, MINUS = 7, STOP = 8, DIVISION = 9, DIGIT = 10, COLIN = 11, SEMICOLIN = 12, LTHAN = 13, EQUALS = 14, GTHAN = 15, CHAR = 16, BACKSLASH = 17, LCURLY = 18, RCURLY = 19 };
string CharCat(char character){
    // -100 = other
    string CAT[] = {"ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR", "EXCLEMATION", "ERROR","ERROR", "ERROR", "ERROR", "ERROR", "SINGLEQUOTE", "LBRACKET","RBRACKET","MULTI", "PLUS","ERROR","MINUS", "STOP", "DIVISION","DIGIT","DIGIT","DIGIT","DIGIT","DIGIT","DIGIT","DIGIT","DIGIT","DIGIT","DIGIT", "COLIN", "SEMICOLIN", "LTHAN","EQUALS","GTHAN", "ERROR", "ERROR", "CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","BACKSLASH","ERROR","ERROR","CHAR","ERROR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR","CHAR", "LCURLY", "ERROR", "RCURLY", "ERROR", "ERROR"};
    
    return CAT[character];
}

string NextWord(string line){
    int Sa[] = {1,3,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,26,28,30,35};
    
    int n = sizeof(Sa) / sizeof(*Sa);
    // state x character
    int TX[36][20] = {};
    for ( int i = 0; i < 36; i ++){
        for(int j = 0; j < 20; j++){
            TX[i][j] = 0;
        }
    }
    TX[0][10] = 1;
    TX[1][8] = 2;
    TX[1][10] = 1;
    TX[2][10] = 3;
    TX[3][10] = 3;
    TX[0][2] = 4;
    TX[4][] = 4;
    TX[4][2] = 5;
    TX[0][16] = 6;
    TX[6][16] = 6;
    TX[0][3] = 7;
    TX[0][4] = 12;
    TX[0][13] = 8;
    TX[8][14] = 9;
    TX[0][15] = 10;
    TX[10][14] = 11;
    TX[12]
    // Initialisation
    int state = 0;
    string lexeme = "";
    stack<int> stack;
    stack.push(100);
    // 100 is bad

    char character = '\0';
    int pointer = 0;
    // Scanning Loop
    // 69 is Se (error state)
    while (state != 69){
        // Next Char
        character = line[pointer];
        lexeme.append(&character);
        bool exists = std::find(Sa, Sa + n, character) != Sa + n;
            if (exists) {
                //clear stack
                while (stack.top() != 0){
                    stack.pop();
                }
            }
        stack.push(state);
        // return the class of the character
        string cat = CharCat(character);
        // update state
        state = TX[state][cat];
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