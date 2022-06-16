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

class FACTOR;

class IDENTIFIER;

class TERM{
    public:
        virtual ~TERM() = default;
        FACTOR* lFac;
        vector<string> mulOP;
        vector<FACTOR*> rFac;
};

class SIEXPR{
    public:
        virtual ~SIEXPR() = default;
        TERM* trm;
        vector<string> addOP;
        vector<TERM*> rTrm;
};

class Statement{
    public:
        virtual ~Statement() = default;
};

class EXPR{
    public:
        virtual ~EXPR() = default;
        SIEXPR* lExpres;
        vector<string> relOP;
        vector<SIEXPR*> rExpres;
};

class VD : public Statement{
    public:
        virtual ~VD() = default;
        bool let;
        // identifiers are strings
        IDENTIFIER* iden;
        bool colin;
        // types are 4 different strings
        string typ;
        bool equals;
        EXPR* express;
};

class AS : public Statement{
    public:
        virtual ~AS() = default;
        string iden;
        bool equals;
        EXPR* express;
};

class PS : public Statement{
    public:
        virtual ~PS() = default;
        bool prinT;
        EXPR* express;
};

//skip FACTOR go straight to options
class FACTOR {
    public:
        virtual ~FACTOR() = default;
};

// can prob remove
class IDENTIFIER : public FACTOR{
    public:
        virtual ~IDENTIFIER() = default;
        string iden;
};

//
class LITERAL : public FACTOR{
    public:
        virtual ~LITERAL() = default;
        // string will hold BOOL or INT or FLOAT or CHAR to show which literal it is
        string literalType;
        string contentsType;
};

class FUNCTIONCALL : public FACTOR{
    public:
        virtual ~FUNCTIONCALL() = default;
        IDENTIFIER* iden;
        bool lBrac;
        // add one or more acutal params
        bool rBrac;
};

class SUBEXPRESSION : public FACTOR{
    public:
        virtual ~SUBEXPRESSION() = default;
        bool lBrac;
        EXPR* expression;
        bool rBrac;
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

FACTOR* factor(vector<char> fileVector);

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

// Done just test
// implementation should mirror Multiplicitive
string additiveOp(vector<char> fileVector){
    tableLexerReturn nextToken;
    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    if (nextToken.lexemeFin == "+" || nextToken.lexemeFin == "-" || nextToken.lexemeFin == "or" ){
        return nextToken.lexemeFin;
    }
    else{
        cout << "ERROR EXPECTED ADDITIVE OPERATOR";
        exit(0);
    }
}

// Done just test
// implementation should mirror Additive
string multiplicaticveOp(vector<char> fileVector){
    tableLexerReturn nextToken;
    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    if (nextToken.lexemeFin == "*" || nextToken.lexemeFin == "/" || nextToken.lexemeFin == "and" ){
        return nextToken.lexemeFin;
    }
    else{
        cout << "ERROR EXPECTED MULTIPLICATION OPERATOR";
        exit(0);
    }
}

// Done just test
// implementation should mirror Additive
string relationalOp(vector<char> fileVector){
    tableLexerReturn nextToken;
    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    if (nextToken.lexemeFin == ">" || nextToken.lexemeFin == "<" || nextToken.lexemeFin == "==" || nextToken.lexemeFin == "<=" || nextToken.lexemeFin == ">=" || nextToken.lexemeFin == "!=" ){
        return nextToken.lexemeFin;
    }
    else{
        cout << "ERROR EXPECTED RELATIONAL OPERATOR";
        exit(0);
    }
}

// Done just add Actual Params and test
FUNCTIONCALL* functionCall(vector<char> fileVector){
    tableLexerReturn nextToken;
    FUNCTIONCALL* returnFC = new FUNCTIONCALL();
    
    // do{
    //     nextToken = getNextToken(fileVector, false);
    // }while(nextToken.stackTop == 33);

    // if (nextToken.stackTop == 6){
    //     // identifier
    //     returnFC->iden = nextToken.lexemeFin;
    // }
    // else{
    //     cout << "ERROR EXPECTED IDENTIFIER FOR FUNCTIONCALL";
    //     exit(0);
    // } 

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    // left Bracket
    if (nextToken.stackTop == 7){
        returnFC->lBrac = true;
    }
    else{
        returnFC->lBrac = false;
        cout << "ERROR EXPECTED LEFT BRACKET FOR FUNCTIONCALL";
        exit(0);
    }

    // TODO
    // need method to have multiple params

    // right Bracket
    if (nextToken.stackTop == 12){
        returnFC->rBrac = true;
    }
    else{
        returnFC->rBrac = false;
        cout << "ERROR EXPECTED RIGHT BRACKET FOR FUNCTIONCALL";
        exit(0);
    }

    return returnFC;
}

// Done just test
// implementation should mirror Simple Example and Expression
TERM* term(vector<char> fileVector){
    tableLexerReturn nextToken;
    TERM* returnTRM = new TERM();


    returnTRM->lFac = factor(fileVector);

    do{
        nextToken = getNextToken(fileVector, true);
    }while(nextToken.stackTop == 33);

    while (nextToken.lexemeFin == "+" || nextToken.lexemeFin == "-" || nextToken.lexemeFin == "or" ){
        returnTRM->mulOP.push_back(multiplicaticveOp(fileVector));
        returnTRM->rFac.push_back(factor(fileVector));
        do{
            nextToken = getNextToken(fileVector, false);
        }while(nextToken.stackTop == 33);
    }

    return returnTRM;
}

// Done just test
// implementation should mirror Term and Expression
SIEXPR* simpleExpr(vector<char> fileVector){
    //make a vector to return the finished statement
    SIEXPR* returnSIEXPR = new SIEXPR();
    returnSIEXPR->trm = term(fileVector);

    tableLexerReturn nextToken;

    do{
        nextToken = getNextToken(fileVector, true);
    }while(nextToken.stackTop == 33);

    while (nextToken.lexemeFin == "+" || nextToken.lexemeFin == "-" || nextToken.lexemeFin == "or" ){
        returnSIEXPR->addOP.push_back(additiveOp(fileVector));
        returnSIEXPR->rTrm.push_back(term(fileVector));
        do{
        nextToken = getNextToken(fileVector, false);
        }while(nextToken.stackTop == 33);
    }

    return returnSIEXPR;
}

// Done just test
// implementation should mirror Term and Simple Expression
EXPR* expression(vector<char> fileVector){
    //make a vector to return the finished statement
    EXPR* returnEXPR = new EXPR();

    returnEXPR->lExpres = simpleExpr(fileVector);
    
    tableLexerReturn nextToken;


    do{
        nextToken = getNextToken(fileVector, true);
    }while(nextToken.stackTop == 33);

    while (nextToken.lexemeFin == ">" || nextToken.lexemeFin == "<" || nextToken.lexemeFin == "==" || nextToken.lexemeFin == "<=" || nextToken.lexemeFin == ">=" || nextToken.lexemeFin == "!=" ){
        returnEXPR->relOP.push_back(relationalOp(fileVector));
        returnEXPR->rExpres.push_back(simpleExpr(fileVector));
        do{
            nextToken = getNextToken(fileVector, false);
        }while(nextToken.stackTop == 33);
    }

    return returnEXPR;
}

// TODO
// update functioncall when done
int actualParams(vector<char> fileVector){
    expression(fileVector);
    return 0;
}

// Done just Test
SUBEXPRESSION* subExpression(vector<char> fileVector){
    tableLexerReturn nextToken;
    SUBEXPRESSION* returnSubExp = new SUBEXPRESSION();

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    // left Bracket
    if (nextToken.stackTop == 7){
        returnSubExp->lBrac = true;
    }
    else{
        returnSubExp->lBrac = false;
        cout << "ERROR EXPECTED LEFT BRACKET FOR SUB EXPRESSION";
        exit(0);
    }

    returnSubExp->expression = expression(fileVector);

    // need method to have multiple params

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);


    // right Bracket
    if (nextToken.stackTop == 12){
        returnSubExp->rBrac = true;
    }
    else{
        returnSubExp->rBrac = false;
        cout << "ERROR EXPECTED RIGHT BRACKET FOR SUB EXPRESSION";
        exit(0);
    }

    return returnSubExp;

}

// may need two one for this and a pointer for FACTOR
// to upcast identifier to factor
IDENTIFIER* identifier(vector<char> fileVector){
    tableLexerReturn nextToken;
    IDENTIFIER* returnIDEN = new IDENTIFIER(); 

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);
    
    if (nextToken.stackTop == 6){
        returnIDEN->iden = nextToken.lexemeFin;
        return returnIDEN;
    }
    else{
        cout << "ERROR IDENTIFIER INVALID";
        exit(0);
    }
}

LITERAL* literal(vector<char> fileVector){
    LITERAL* returnLit = new LITERAL();

    tableLexerReturn nextToken;

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    if(nextToken.lexemeFin == "float" ||nextToken.lexemeFin == "int" ||nextToken.lexemeFin == "char" ||nextToken.lexemeFin == "bool"){
        returnLit->literalType = "TYPE";
        returnLit->contentsType = nextToken.lexemeFin;
    }
    else if(nextToken.lexemeFin == "true" ||nextToken.lexemeFin == "false"){
        returnLit->literalType = "BOOL";
        returnLit->contentsType = nextToken.lexemeFin;
    }
    else if(nextToken.stackTop == 1){
        returnLit->literalType = "INT";
        returnLit->contentsType = nextToken.lexemeFin;
    }
    else if(nextToken.stackTop == 3){
        returnLit->literalType = "FLOAT";
        returnLit->contentsType = nextToken.lexemeFin;
    }
    else{
        cout << "ERROR EXPECTED LITERAL";
        exit(0);
    }
    return returnLit;
}

// check problems with Identifier
// very rough implementation
// need to see if identifier function is necesary
FACTOR* factor(vector<char> fileVector){

    FACTOR* returnFac = new FACTOR();

    tableLexerReturn nextToken;
    do{
        nextToken = getNextToken(fileVector, true);
        if (nextToken.stackTop == 33){
            nextToken = getNextToken(fileVector, false);
        }
    }while(nextToken.stackTop == 33);
    
    if (nextToken.stackTop == 7){
        returnFac = subExpression(fileVector);
    }
    // literal
    else if(nextToken.lexemeFin == "float" ||nextToken.lexemeFin == "int" ||nextToken.lexemeFin == "char" ||nextToken.lexemeFin == "bool" || nextToken.lexemeFin == "true" ||nextToken.lexemeFin == "false" || nextToken.stackTop == 1 || nextToken.stackTop == 3){

        returnFac = literal(fileVector);

    }
    // identifier
    else if(nextToken.stackTop == 6){
        IDENTIFIER* returnIden = identifier(fileVector);

        do{
        nextToken = getNextToken(fileVector, false);
        }while(nextToken.stackTop == 33);


        tableLexerReturn nextTokenisFC;
        do{
            nextTokenisFC = getNextToken(fileVector, true);
        }while(nextToken.stackTop == 33);

        // if the next is 7 then it is a function call
        if (nextTokenisFC.stackTop == 7){
            // function call
            FUNCTIONCALL* returnFacCall = functionCall(fileVector);
            returnFacCall->iden = returnIden;
            returnFac = returnFacCall;
        }
        else{
            returnFac = returnIden;
        }
    }
    else{
        cout << "ERROR FACTOR EXPECTED";
        exit(0);
    }
    return returnFac;
}

// should be done
//function is basic enough
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


// tested w bf until expression everything until expression gets initilised correctly and memory address is returned
Statement* variableDecl(vector<char> fileVector){

    VD* returnVD = new VD();
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

    
    returnVD->express = expression(fileVector);
    return returnVD;
}

Statement* assignment(vector<char> fileVector){
    AS* returnAS = new AS();
    tableLexerReturn nextToken;
    
    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    if (nextToken.stackTop == 6){
        returnAS->iden = nextToken.lexemeFin;
    }
    else{
        cout << "ERROR IDENTIFIER EXPECTED";
        exit(0);
    }

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    if (nextToken.lexemeFin == "="){
        returnAS->equals = true;
    }
    else{
        cout<< "ERROR EXPECTED EQUALS FOR ASSIGNMENT";
        exit(0);
    }

    returnAS->express = expression(fileVector);
    return returnAS;

}

Statement* printStatement(vector<char> fileVector){
    PS* returnPS = new PS();
    tableLexerReturn nextToken;

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);
    
    if (nextToken.lexemeFin == "print"){
        returnPS->prinT = true;
    }
    else{
        returnPS->prinT = false;
        cout << "ERROR EXPECTED PRINT FOR PRINT STATEMENT";
        exit(0);
    }

    returnPS->express = expression(fileVector);
    return returnPS;
}

// convert memory address stored in AST back to variableDEC to check if output is printable
int parser(vector<char> fileVector){
    // a program is a Vector of Statements
    vector<Statement*> *AST = new vector<Statement*>();
    // vector<Statement*> AST = {};
    tableLexerReturn nextToken;

    for(;;){
        do{
        nextToken = getNextToken(fileVector, true);
        if (nextToken.stackTop == 33){
            nextToken = getNextToken(fileVector, false);
        }
    }while(nextToken.stackTop == 33);
        // Statement returnStatement;
        if (nextToken.stackTop == -100){
            break;
        }
        if (nextToken.lexemeFin == "let"){

            AST->push_back(variableDecl(fileVector));
            do{
                nextToken = getNextToken(fileVector, false);
            }while(nextToken.stackTop == 33);

            vector<Statement*>::iterator iter;
            for (iter = AST->begin(); iter != AST->end(); ++iter){
                // prints out memory location
                // cout << *iter;
                VD* printVD = dynamic_cast<VD*>(*iter);
                cout << printVD->typ << "\n";

                IDENTIFIER* printIden = printVD->iden;
                cout << printIden->iden <<"\n";
            }

            if (nextToken.stackTop == 20){
                
            }
            else{
                cout << "ERROR EXPECTED SEMICOLIN EXPECTED";
                exit(0);
            }
        }
        else if (nextToken.lexemeFin == "print"){
            AST->push_back(printStatement(fileVector));
            do{
                nextToken = getNextToken(fileVector, false);
            }while(nextToken.stackTop == 33);

            if (nextToken.stackTop == 20){
                
            }
            else{
                cout << "ERROR EXPECTED SEMICOLIN EXPECTED";
                exit(0);
            }
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
        // block
        else if (nextToken.stackTop == 22){
            
        }
        else if (nextToken.stackTop == 6){

            AST->push_back(assignment(fileVector));
            do{
                nextToken = getNextToken(fileVector, false);
            }while(nextToken.stackTop == 33);

            if (nextToken.stackTop == 20){
                
            }
            else{
                cout << "ERROR EXPECTED SEMICOLIN EXPECTED";
                exit(0);
            }
        }
        else{
            cout << "ERROR EXPECTED STATEMENT";
            exit(0);
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
