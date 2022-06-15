#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string.h>
using namespace std;

class tableLexerReturn {       // The class
  public:             // Access specifier
    int stackTop;        // Attribute (int variable)
    string lexemeFin;  // Attribute (string variable)
    int counter;
};


class Statement{
    public:

};


class VD : public Statement{
    public:
        bool let;
        // identifiers are strings
        string iden;
        bool colin;
        // types are 4 different strings
        string typ;
        bool equals;
        //EXPR express;
};

class EXPR{

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

enum classif{ ERROR = 0,EXCLEMATION = 1, SINGLEQUOTE = 2, LBRACKET = 3, RBRACKET =  4,MULTI = 5, PLUS = 6, MINUS = 7, STOP = 8, DIVISION = 9, DIGIT = 10, COLIN = 11, SEMICOLIN = 12, LTHAN = 13, EQUALS = 14, GTHAN = 15, CHAR = 16, BACKSLASH = 17, LCURLY = 18, RCURLY = 19, COMMA = 20,SPACE = 21, NEWLINE = 22 };
classif CharCat(char character){
    // -100 = other
    int asciiIndex = character;
    classif CAT[] = {ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,NEWLINE,ERROR,ERROR,NEWLINE,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,SPACE, EXCLEMATION, ERROR,ERROR, ERROR, ERROR, ERROR, SINGLEQUOTE, LBRACKET,RBRACKET,MULTI, PLUS,COMMA,MINUS, STOP, DIVISION,DIGIT,DIGIT,DIGIT,DIGIT,DIGIT,DIGIT,DIGIT,DIGIT,DIGIT,DIGIT, COLIN, SEMICOLIN, LTHAN,EQUALS,GTHAN, ERROR, ERROR, CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,ERROR,BACKSLASH,ERROR,ERROR,CHAR,ERROR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR,CHAR, LCURLY, ERROR, RCURLY, ERROR, ERROR};
    
    return CAT[asciiIndex];
}

tableLexerReturn NextWord(vector<char> input){
    // token type
    int Sa[] = {1,3,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,26,27,30,32,33};
    tableLexerReturn returnLexer;

    // state x character
    // transition table
    int TX[34][23] = {};
    for ( int i = 0; i < 34; i ++){
        for(int j = 0; j < 23; j++){
            TX[i][j] = -1;
        }
    }
    TX[0][10] = 1;
    TX[1][8] = 2;
    TX[1][10] = 1;
    TX[2][10] = 3;
    TX[3][10] = 3;
    TX[0][2] = 4;
    for(int j = 0; j < 23; j++){
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
    for(int j = 0; j < 23; j++){
            TX[27][j] = 27;
    }
    TX[27][22] = -1;
    TX[0][12] = 20;
    TX[0][11] = 21;
    TX[0][18] = 22;
    TX[0][19] = 23;
    TX[0][20] = 24;
    TX[0][1] = 25;
    TX[25][14] = 26;
    TX[19][5] = 28;
    for(int j = 0; j < 23; j++){
            TX[28][j] = 28;
    }
     for(int j = 0; j < 23; j++){
            TX[31][j] = 28;
    }
    TX[28][5] = 31;
    TX[31][9] = 32;
    TX[0][17] = 29;
    TX[29][17] = 30;
    TX[30][16] = 30;
    TX[0][21] = 33;
    TX[0][22] = 33;
    TX[27][22] = -1;
    TX[27][21] = 27;
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
    bool exists = (std::find(std::begin(Sa), std::end(Sa), state) != std::end(Sa));
    while ( exists == false && state != 100){
        // method to safely pop in c++
        stack.pop();
        lexeme.pop_back();
        state = stack.top();
        exists = (std::find(std::begin(Sa), std::end(Sa), state) != std::end(Sa));
    }

    
    // Report result
    if (std::find(std::begin(Sa), std::end(Sa), state) != std::end(Sa)){
        returnLexer.stackTop = stack.top();
        returnLexer.lexemeFin = lexeme;
        // cout << lexeme <<"\t"<<+ stack.top() << "\n";
        return returnLexer;
    }
    else{
        cout << "ERROR";
        exit(0);
    }
}

tableLexerReturn getNextToken(vector<char> fileVector, bool lookahead){
    static size_t notEOF = 0;
    tableLexerReturn ReturnHold;

    if (notEOF != fileVector.size()){
        if (lookahead){
            ReturnHold = NextWord(fileVector);
            for (int i = 0; i < ReturnHold.counter; i++){
                NextChar(fileVector, -1);
            }
            return ReturnHold;
        }
        else{
            ReturnHold = NextWord(fileVector);
            notEOF += ReturnHold.counter;
            notEOF -= 1;
            NextChar(fileVector, -1);
            return ReturnHold;
        }  
    }
    else{
        cout << "end";
        ReturnHold.stackTop = -100;
        return ReturnHold;
    }

}



int functionCall(vector<char> fileVector){
    vector<string> returnVec;
    tableLexerReturn nextToken;
    nextToken = getNextToken(fileVector, false);

    // left Bracket
    if (nextToken.stackTop == 7){

    }
    else{
        cout << "ERROR EXPECTED LEFT BRACKET FOR SUB EXPRESSION";
        exit(0);
    }

    // need method to have multiple params

    // right Bracket
    if (nextToken.stackTop == 12){

    }
    else{
        cout << "ERROR EXPECTED RIGHT BRACKET FOR SUB EXPRESSION";
        exit(0);
    }
    return 0;

    return 0;
}


int term(vector<char> fileVector){
    //make a vector to return the finished statement
    vector<string> returnVec;
    // factor(fileVector);
    return 0;
}

int simpleExpr(vector<char> fileVector){
    //make a vector to return the finished statement
    vector<string> returnVec;
    term(fileVector);
    return 0;
}


EXPR expression(vector<char> fileVector){
    //make a vector to return the finished statement
    EXPR returnEXPR;

    simpleExpr(fileVector);
    return returnEXPR;
}

int actualParams(vector<char> fileVector){
    expression(fileVector);
    return 0;
}

int subExpression(vector<char> fileVector){
    vector<string> returnVec;
    tableLexerReturn nextToken;
    nextToken = getNextToken(fileVector, false);

    // left Bracket
    if (nextToken.stackTop == 7){

    }
    else{
        cout << "ERROR EXPECTED LEFT BRACKET FOR SUB EXPRESSION";
        exit(0);
    }

    expression(fileVector);

    // right Bracket
    if (nextToken.stackTop == 12){

    }
    else{
        cout << "ERROR EXPECTED RIGHT BRACKET FOR SUB EXPRESSION";
        exit(0);
    }
    return 0;
}
string identifier(vector<char> fileVector){
    tableLexerReturn nextToken;
    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);
    
    if (nextToken.stackTop == 6){
        return nextToken.lexemeFin;
    }
    else{
        cout << "ERROR IDENTIFIER INVALID";
        exit(0);
    }
}

// int factor(vector<char> fileVector){
//     //make a vector to return the finished statement
//     vector<string> returnVec;
//     tableLexerReturn nextToken;
//     nextToken = getNextToken(fileVector, true);
    
//     if (nextToken.stackTop == 7){
//         subExpression(fileVector);
//     }
//     else if(nextToken.lexemeFin == "float" ||nextToken.lexemeFin == "int" ||nextToken.lexemeFin == "char" ||nextToken.lexemeFin == "bool" || nextToken.lexemeFin == "true" ||nextToken.lexemeFin == "false" || nextToken.stackTop == 1 || nextToken.stackTop == 3){
//         identifier(fileVector);
//     }
//     else if(nextToken.stackTop == 6){
//         identifier(fileVector);
//         tableLexerReturn nextTokenisFC;
//         nextTokenisFC = getNextToken(fileVector, true);
//         if (nextTokenisFC.stackTop == 7){
//             // function call
//             functionCall(fileVector);
//         }
//     }
//     else{
//         cout << "ERROR FACTOR EXPECTED";
//         exit(0);
//     }
//     return 0;
// }

string type(vector<char> fileVector){
    tableLexerReturn nextToken;
    nextToken = getNextToken(fileVector, false);
    if (nextToken.lexemeFin == "float"){
        return "float";
    }
    else if (nextToken.lexemeFin == "int"){
        return "int";
    }
    else if (nextToken.lexemeFin == "bool"){
        return "bool";
    }
    else if (nextToken.lexemeFin == "char"){
        return "char";
    }
    else{
        cout << "ERROR TYPE EXPECTED";
        exit(0);
    }
}

Statement* variableDecl(vector<char> fileVector){
    //make a vector to return the finished statement
    VD holdVD;
    VD* returnVD = &holdVD;
    tableLexerReturn nextToken;
    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);
    
    if (nextToken.lexemeFin == "let"){
        returnVD->let = true;
    }
    else{
        returnVD->let = false;
        cout << "ERROR EXPECTED LET FOR VARIABLE DECLERATION";
        exit(0);
    }

    // holds identifier name as a string

    returnVD->iden = identifier(fileVector);
    
    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    // 21 being a colin
    if (nextToken.stackTop == 21){
        returnVD->colin = true;
    }
    else{
        cout << "ERROR COLIN EXPECTED FOR VARIABLE DECLERATION";
        exit(0);
    }

    returnVD->typ = type(fileVector);

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);
    // 13 being an equals
    if (nextToken.stackTop == 13){
       returnVD->equals = true;
    }
    else{
        cout << "ERROR COLIN EXPECTED FOR VARIABLE DECLERATION";
        exit(0);
    }

    return returnVD;
    // expression(fileVector);
}

int parser(vector<char> fileVector){
    // a program is a Vector of Statements
    vector<Statement*> *AST = new vector<Statement*>();
    // vector<Statement*> AST = {};
    tableLexerReturn nextToken;

    for(;;){
        nextToken = getNextToken(fileVector, true);
        // Statement returnStatement;
        if (nextToken.stackTop == -100){
            break;
        }
        if (nextToken.lexemeFin == "let"){

            AST->push_back(variableDecl(fileVector));
            do{
                nextToken = getNextToken(fileVector, false);
            }while(nextToken.stackTop == 33);

            Statement* printVD = &AST[0];
            // cout << AST[0]->iden <<"\n";
            if (nextToken.stackTop == 20){
                
            }
            else{
                cout << "ERROR EXPECTED SEMICOLIN EXPECTED";
                exit(0);
            }
        }
        else if (nextToken.lexemeFin == "print"){

        }
        else if (nextToken.lexemeFin == "return"){

        }
        else if (nextToken.lexemeFin == "if"){
            
        }
        else if (nextToken.lexemeFin == "for"){
            
        }
        else if (nextToken.lexemeFin == "while"){
            
        }
        else if (nextToken.lexemeFin == "fn"){
            
        }
        else if (nextToken.stackTop == 22){
            
        }
        // add assignment
               
        // AST->push_back(returnStatement);
    }
    
    return 0;
}

int main(){
    ifstream myfile("under.txt");
    string line;
    vector<string> tokens; 
    vector<int> stateType;
    vector<char> fileVector; 
    
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {                          
            
            for (size_t i = 0; i < line.length(); i++){
                fileVector.push_back(line[i]);
            }
            fileVector.push_back('\n');
        }
        myfile.close();

        //print vector as string
        // std::string s(fileVector.begin(), fileVector.end());
        // std::cout << s <<"\n";

        parser(fileVector);
        
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

// if (newState.stateNo == 1){
//             newState.name = "IntegerLiteral";
//             newState.value = nextToken.lexemeFin;
//             AST.push_back(newState);
//         }
//         else if (newState.stateNo == 3){
//             newState.name = "FloatLiteral";
//             AST.push_back(newState);
//         }
//         else if (newState.stateNo == 5){
//             newState.name = "CharLiteral";
//             AST.push_back(newState);
//         }
//         else if (newState.stateNo == 6){
//             newState.name = "Identifier";
//             AST.push_back(newState);
//         }
//         else if (newState.stateNo == 17 || newState.stateNo == 19){
//             newState.name = "MultiplicativeOp";
//             AST.push_back(newState);
//         }
//         else if (newState.stateNo == 18 || newState.stateNo == 15){
//             newState.name = "AdditiveOp";
//             AST.push_back(newState);
//         }
//         else if (newState.stateNo == 14 || newState.stateNo == 8|| newState.stateNo == 9 || newState.stateNo == 10|| newState.stateNo == 11|| newState.stateNo == 26){
//             newState.name = "RelationalOp";
//             AST.push_back(newState);
//         }