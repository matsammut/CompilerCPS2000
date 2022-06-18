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

class BLOCK;

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

class INVALIDST : public Statement{
    public:
        virtual ~INVALIDST() = default;
        bool error;
};

class AS : public Statement{
    public:
        virtual ~AS() = default;
        IDENTIFIER* iden;
        bool equals;
        EXPR* express;
};

class PS : public Statement{
    public:
        virtual ~PS() = default;
        bool prinT;
        EXPR* express;
};

class IS : public Statement{
    public:
        virtual ~IS() = default;
        bool iF;
        bool lBrac;
        EXPR* express;
        bool rBrac;
        BLOCK* blk;
        bool elSe;
        BLOCK* blks; 
};

class BLOCK : public Statement{
    public:
        virtual ~BLOCK() = default;
        bool lBrac;
        vector<Statement*> stmts;
        bool rBrac;
};

class RS : public Statement{
    public:
        virtual ~RS() = default;
        bool rtrn;
        EXPR* express;
};

class FS : public Statement{
    public:
        virtual ~FS() = default;
        bool fOr;
        bool lBrac;
        bool hasVarDec;
        Statement* varDec;
        bool semiColA;
        EXPR* express;
        bool semiColB;
        bool hasAssignMNT;
        Statement* assignMNT;
        bool rBrac;
        Statement* blck;
};

class WS : public Statement{
    public:
        virtual ~WS() = default;
        bool whl;
        bool lBrac;
        EXPR* express;
        bool rBrac;
        Statement* blck;
};

//skip FACTOR go straight to options
class FACTOR {
    public:
        virtual ~FACTOR() = default;
};

class ACTUALPARAMS{
    public:
        virtual ~ACTUALPARAMS() = default;
        EXPR* express;
        bool hasMoreEXPR;
        vector<EXPR*> moreEXPR;
};

class FORMALPARAM{
    public:
        virtual ~FORMALPARAM() = default;
        IDENTIFIER* iden;
        bool colin;
        string typ;
};

class FORMALPARAMS{
    public:
        virtual ~FORMALPARAMS() = default;
        FORMALPARAM* fmlprms;
        bool hasMorePRMS;
        vector<FORMALPARAM*> morePRMS;
};

class FD : public Statement{
    public:
        virtual ~FD() = default; 
        bool fn;
        IDENTIFIER* iden;
        bool lBrac;
        bool hasFParams;
        FORMALPARAMS* FParams;
        bool rBrac;
        string arrow;
        string typ;
        Statement* blck;
};

// can prob remove
class IDENTIFIER : public FACTOR{
    public:
        virtual ~IDENTIFIER() = default;
        string iden;
};

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
        bool hasAct;
        ACTUALPARAMS* act;
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
BLOCK* block(vector<char> fileVector);
ACTUALPARAMS* actualParams(vector<char> fileVector);

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
    TX[15][15] = 16;
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

    do{
        nextToken = getNextToken(fileVector, true);
        if (nextToken.stackTop == 33){
            nextToken = getNextToken(fileVector, false);
        }
    }while(nextToken.stackTop == 33);


    // right Bracket
    if (nextToken.stackTop == 12){
        returnFC->rBrac = true;
        returnFC->hasAct = false;
    }
    else{
        returnFC->hasAct = true;
        returnFC->act = actualParams(fileVector);
        do{
        nextToken = getNextToken(fileVector, false);
        }while(nextToken.stackTop == 33);
        if (nextToken.stackTop == 12){
            returnFC->rBrac = true;
        }
        else{
            returnFC->rBrac = false;
            cout << "ERROR EXPECTED RIGHT BRACKET FOR FUNCTIONCALL";
            exit(0);
        }
        
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
        if (nextToken.stackTop == 33){
            nextToken = getNextToken(fileVector, false);
        }
    }while(nextToken.stackTop == 33);

    returnTRM->mulOP = {};
    if (nextToken.lexemeFin == "*" || nextToken.lexemeFin == "/" || nextToken.lexemeFin == "and" ){
        returnTRM->mulOP.push_back(multiplicaticveOp(fileVector));
        returnTRM->rFac.push_back(factor(fileVector));
        do{
            nextToken = getNextToken(fileVector, true);
            if (nextToken.stackTop == 33){
                nextToken = getNextToken(fileVector, false);
            }
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
        if (nextToken.stackTop == 33){
            nextToken = getNextToken(fileVector, false);
        }
    }while(nextToken.stackTop == 33);

    while (nextToken.lexemeFin == "+" || nextToken.lexemeFin == "-" || nextToken.lexemeFin == "or" ){
        returnSIEXPR->addOP.push_back(additiveOp(fileVector));
        returnSIEXPR->rTrm.push_back(term(fileVector));
        do{
            nextToken = getNextToken(fileVector, true);
            if (nextToken.stackTop == 33){
                nextToken = getNextToken(fileVector, false);
            }
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
        if (nextToken.stackTop == 33){
            nextToken = getNextToken(fileVector, false);
        }
    }while(nextToken.stackTop == 33);

    while (nextToken.lexemeFin == ">" || nextToken.lexemeFin == "<" || nextToken.lexemeFin == "==" || nextToken.lexemeFin == "<=" || nextToken.lexemeFin == ">=" || nextToken.lexemeFin == "!=" ){

        returnEXPR->relOP.push_back(relationalOp(fileVector));
        returnEXPR->rExpres.push_back(simpleExpr(fileVector));
        do{
            nextToken = getNextToken(fileVector, true);
            if (nextToken.stackTop == 33){
                nextToken = getNextToken(fileVector, false);
            }
        }while(nextToken.stackTop == 33);
    }

    return returnEXPR;
}

// TODO
// update functioncall when done
ACTUALPARAMS* actualParams(vector<char> fileVector){
    ACTUALPARAMS* returnAP = new ACTUALPARAMS();


    returnAP->express = expression(fileVector);
    tableLexerReturn nextToken;

    do{
        nextToken = getNextToken(fileVector, true);
        if (nextToken.stackTop == 33){
            nextToken = getNextToken(fileVector, false);
        }
    }while(nextToken.stackTop == 33);

    while (nextToken.stackTop == 24){
        nextToken = getNextToken(fileVector, false);
        returnAP->hasMoreEXPR = true;
        returnAP->moreEXPR.push_back(expression(fileVector));
        do{
        nextToken = getNextToken(fileVector, true);
        if (nextToken.stackTop == 33){
            nextToken = getNextToken(fileVector, false);
        }
    }while(nextToken.stackTop == 33);
    }
    
    return returnAP;
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

    if(nextToken.stackTop == 5){
        returnLit->literalType = "CHAR";
        do{
            nextToken = getNextToken(fileVector, false);
        }while(nextToken.stackTop == 33);
        returnLit->contentsType = nextToken.lexemeFin;
        do{
            nextToken = getNextToken(fileVector, false);
        }while(nextToken.stackTop == 33);
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

        // tableLexerReturn nextToken;
        do{
            nextToken = getNextToken(fileVector, true);
            if (nextToken.stackTop == 33){
                nextToken = getNextToken(fileVector, false);
            }
        }while(nextToken.stackTop == 33);
        // if the next is 7 then it is a function call
        if (nextToken.stackTop == 7){
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

FORMALPARAM* formalparam(vector<char> fileVector){
    FORMALPARAM* returnFP = new FORMALPARAM();
    tableLexerReturn nextToken;

    do{
        nextToken = getNextToken(fileVector, true);
        if (nextToken.stackTop == 33){
            nextToken = getNextToken(fileVector, false);
        }
    }while(nextToken.stackTop == 33);

    returnFP->iden = identifier(fileVector);

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    if (nextToken.stackTop == 21){
        returnFP->colin = true;
    }
    else{
        returnFP->colin = false;
        cout << "ERROR EXPECTED COLIN FOR FORMAL PARAMETERS";
        exit(0);
    }

    returnFP->typ = type(fileVector);

    return returnFP;
}

FORMALPARAMS* formalparams(vector<char> fileVector){
    FORMALPARAMS* returnFPS = new FORMALPARAMS();
    tableLexerReturn nextToken;

    returnFPS->fmlprms = formalparam(fileVector);

    do{
        nextToken = getNextToken(fileVector, true);
        if (nextToken.stackTop == 33){
            nextToken = getNextToken(fileVector, false);
        }
    }while(nextToken.stackTop == 33);

    while (nextToken.stackTop == 24){
        do{
            nextToken = getNextToken(fileVector, false);
        }while(nextToken.stackTop == 33);
        returnFPS->hasMorePRMS = true;
        returnFPS->morePRMS.push_back(formalparam(fileVector));
        do{
            nextToken = getNextToken(fileVector, true);
            if (nextToken.stackTop == 33){
                nextToken = getNextToken(fileVector, false);
            }
        }while(nextToken.stackTop == 33);
    }

    return returnFPS;
}

Statement* functionDecl(vector<char> fileVector){
    FD* returnFD = new FD();
    tableLexerReturn nextToken;

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);
    
    if (nextToken.lexemeFin == "fn"){
        returnFD->fn = true;
    }
    else{
        returnFD->fn = false;
        cout << "ERROR EXPECTED FN FOR FUNCTION DECLERATION";
        exit(0);
    }

    returnFD->iden = identifier(fileVector);

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    // left Bracket
    if (nextToken.stackTop == 7){
        returnFD->lBrac = true;
    }
    else{
        returnFD->lBrac = false;
        cout << "ERROR EXPECTED LEFT BRACKET FOR FUNCTIONCALL";
        exit(0);
    }

    do{
        nextToken = getNextToken(fileVector, true);
        if (nextToken.stackTop == 33){
            nextToken = getNextToken(fileVector, false);
        }
    }while(nextToken.stackTop == 33);


    // right Bracket
    if (nextToken.stackTop == 12){
        returnFD->rBrac = true;
        returnFD->hasFParams = false;
    }
    else{
        returnFD->hasFParams = true;
        returnFD->FParams = formalparams(fileVector);
        do{
        nextToken = getNextToken(fileVector, false);
        }while(nextToken.stackTop == 33);
        if (nextToken.stackTop == 12){
            returnFD->rBrac = true;
        }
        else{
            returnFD->rBrac = false;
            cout << "ERROR EXPECTED RIGHT BRACKET FOR FUNCTIONCALL";
            exit(0);
        }
        
    }

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    if (nextToken.stackTop == 16){
        returnFD->arrow = true;
    }
    else{
        cout << "ERROR EXPECTED -> FOR FUNCTION DECLERATION";
        exit(0);
    }

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    if (nextToken.lexemeFin == "float" || nextToken.lexemeFin == "int" || nextToken.lexemeFin == "bool" || nextToken.lexemeFin == "char"){
        returnFD->typ = nextToken.lexemeFin;
    }
    else{
        cout << "ERROR EXPECTED TYPE";
        exit(0);
    }

    returnFD->blck = block(fileVector);

    return returnFD;

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
        cout << "ERROR EQUALS EXPECTED FOR VARIABLE DECLERATION";
        exit(0);
    }

    
    returnVD->express = expression(fileVector);
    return returnVD;
}

Statement* assignment(vector<char> fileVector){
    AS* returnAS = new AS();
    tableLexerReturn nextToken;
    
    do{
        nextToken = getNextToken(fileVector, true);
        if (nextToken.stackTop == 33){
            nextToken = getNextToken(fileVector, false);
        }
    }while(nextToken.stackTop == 33);

    if (nextToken.stackTop == 6){
        returnAS->iden = identifier(fileVector);
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

Statement* ifStatement(vector<char> fileVector){
    IS* returnIs = new IS();
    tableLexerReturn nextToken;
    
    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);
    
    if (nextToken.lexemeFin == "if"){
        returnIs->iF = true;
    }
    else{
        returnIs->iF = false;
        cout << "ERROR EXPECTED IF FOR IF STATEMENT";
        exit(0);
    }

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    if (nextToken.stackTop == 7){
        returnIs->lBrac = true;
    }
    else{
        returnIs->lBrac = false;
        cout << "ERROR EXPECTED LEFT BRACKET FOR IF STATEMENT";
        exit(0);
    }

    returnIs->express = expression(fileVector);

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    if (nextToken.stackTop == 12){
        returnIs->rBrac = true;
    }
    else{
        returnIs->rBrac = false;
        cout << "ERROR EXPECTED RIGHT BRACKET FOR IF STATEMENT";
        exit(0);
    }

    returnIs->blk = block(fileVector);

    do{
        nextToken = getNextToken(fileVector, true);
        if (nextToken.stackTop == 33){
            nextToken = getNextToken(fileVector, false);
        }
    }while(nextToken.stackTop == 33);

    if (nextToken.lexemeFin == "else"){
        nextToken = getNextToken(fileVector, false);
        returnIs->elSe = true;
        returnIs->blks = block(fileVector);
    }
    else{
        returnIs->elSe = false;
    }
    return returnIs;
}

Statement* rtrnStatement(vector<char> fileVector){
    RS* returnRS = new RS();
    tableLexerReturn nextToken;

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);
    
    if (nextToken.lexemeFin == "return"){
        returnRS->rtrn = true;
    }
    else{
        returnRS->rtrn = false;
        cout << "ERROR EXPECTED RETURN FOR RETURN STATEMENT";
        exit(0);
    }

    returnRS->express = expression(fileVector);
    return returnRS;
}

Statement* forStatement(vector<char> fileVector){
    FS* returnFS = new FS();
    tableLexerReturn nextToken;

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);
    
    if (nextToken.lexemeFin == "for"){
        returnFS->fOr = true;
    }
    else{
        returnFS->fOr = false;
        cout << "ERROR EXPECTED FOR FOR FOR STATEMENT";
        exit(0);
    }

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    // left Bracket
    if (nextToken.stackTop == 7){
        returnFS->lBrac = true;
    }
    else{
        returnFS->lBrac = false;
        cout << "ERROR EXPECTED LEFT BRACKET FOR FOR STATEMENT";
        exit(0);
    }

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    if(nextToken.stackTop != 20){
        returnFS->hasVarDec = true;
        returnFS->varDec = variableDecl(fileVector);

        do{
        nextToken = getNextToken(fileVector, false);
        }while(nextToken.stackTop == 33);
        if(nextToken.stackTop == 20){
            returnFS->semiColA = true;
        }
        else{
            cout << "ERROR EXPECTED SEMICOLIN FOR FOR STATEMENT";
            exit(0);
        }
    }
    else{
        returnFS->hasVarDec = false;
        returnFS->semiColA = true;
    }

    returnFS->express = expression(fileVector);

    if(nextToken.stackTop == 20){
        returnFS->semiColB = true;
    }
    else{
        returnFS->semiColB = false;
        cout << "ERROR EXPECTED SEMICOLIN FOR FOR STATEMENT";
        exit(0);
    }

    // check if closing bracket or assignment

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    if(nextToken.stackTop != 12){
        returnFS->hasAssignMNT = true;
        returnFS->assignMNT = assignment(fileVector);

        do{
        nextToken = getNextToken(fileVector, false);
        }while(nextToken.stackTop == 33);
        if(nextToken.stackTop == 12){
            returnFS->rBrac = true;
        }
        else{
            cout << "ERROR EXPECTED RIGHT BRACKET FOR FOR STATEMENT";
            exit(0);
        }
    }
    else{
        returnFS->hasAssignMNT = false;
        returnFS->rBrac = true;
    }

    returnFS->blck = block(fileVector);
    return returnFS;
}

Statement* whileStatement(vector<char> fileVector){
    WS* returnWS = new WS();
    tableLexerReturn nextToken;

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);
    
    if (nextToken.lexemeFin == "while"){
        returnWS->whl = true;
    }
    else{
        returnWS->whl = false;
        cout << "ERROR EXPECTED WHILE FOR WHILE STATEMENT";
        exit(0);
    }

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    // left Bracket
    if (nextToken.stackTop == 7){
        returnWS->lBrac = true;
    }
    else{
        returnWS->lBrac = false;
        cout << "ERROR EXPECTED LEFT BRACKET FOR WHILE STATEMENT";
        exit(0);
    }

    returnWS->express = expression(fileVector);

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    // left Bracket
    if (nextToken.stackTop == 12){
        returnWS->rBrac = true;
    }
    else{
        returnWS->rBrac = false;
        cout << "ERROR EXPECTED LEFT BRACKET FOR WHILE STATEMENT";
        exit(0);
    }

    returnWS->blck = block(fileVector);
    return returnWS;
}

// convert memory address stored in AST back to variableDEC to check if output is printable
vector<Statement*>* parser(vector<char> fileVector){
    // a program is a Vector of Statements
    vector<Statement*> *AST = new vector<Statement*>();
    // vector<Statement*> AST = {};
    tableLexerReturn nextToken;

    for(;;){
        do{
            nextToken = getNextToken(fileVector, true);
            if (nextToken.stackTop == 33 || nextToken.stackTop == 30 || nextToken.stackTop == 27 || nextToken.stackTop == 32){
                nextToken = getNextToken(fileVector, false);
            }
        }while(nextToken.stackTop == 33 || nextToken.stackTop == 30 || nextToken.stackTop == 27 || nextToken.stackTop == 32);
        // Statement returnStatement;
        if (nextToken.stackTop == -100){
            cout <<  "\nParsing completed";
            break;
        }
        if (nextToken.lexemeFin == "let"){

            AST->push_back(variableDecl(fileVector));
            do{
                nextToken = getNextToken(fileVector, false);
            }while(nextToken.stackTop == 33);

            // vector<Statement*>::iterator iter;
            // for (iter = AST->begin(); iter != AST->end(); ++iter){
            //     // prints out memory location
            //     // cout << *iter;
            //     VD* printVD = dynamic_cast<VD*>(*iter);
            //     cout << printVD->typ << "\n";

            //     IDENTIFIER* printIden = printVD->iden;
            //     cout << printIden->iden <<"\n";
            // }

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
            AST->push_back(rtrnStatement(fileVector));

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
        else if (nextToken.lexemeFin == "if"){
            AST->push_back(ifStatement(fileVector));
        }
        else if (nextToken.lexemeFin == "for"){
            AST->push_back(forStatement(fileVector));
        }
        else if (nextToken.lexemeFin == "while"){
            AST->push_back(whileStatement(fileVector));
        }
        else if (nextToken.lexemeFin == "fn"){
            AST->push_back(functionDecl(fileVector));
        }
        // block
        else if (nextToken.stackTop == 22){
            AST->push_back(block(fileVector));
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
    
    return AST;
}

// should be a copy of parser
Statement* statement(vector<char> fileVector){
    Statement* returnStatement = new Statement();
    tableLexerReturn nextToken;
    
    do{
        nextToken = getNextToken(fileVector, true);
        if (nextToken.stackTop == 33 || nextToken.stackTop == 30 || nextToken.stackTop == 27 || nextToken.stackTop == 32){
            nextToken = getNextToken(fileVector, false);
        }

    }while(nextToken.stackTop == 33 || nextToken.stackTop == 30 || nextToken.stackTop == 27 || nextToken.stackTop == 32);
    // Statement returnStatement;
    if (nextToken.stackTop == 23){
        INVALIDST* invalidR = new INVALIDST();
        invalidR->error = true;
        returnStatement = invalidR;
        return returnStatement;
    }
    if (nextToken.lexemeFin == "let"){

        returnStatement = variableDecl(fileVector);
        do{
            nextToken = getNextToken(fileVector, false);
        }while(nextToken.stackTop == 33);

        if (nextToken.stackTop == 20){
            
        }
        else{
            cout << "ERROR EXPECTED SEMICOLIN EXPECTED";
            exit(0);
        }

        return returnStatement;
    }
    else if (nextToken.lexemeFin == "print"){
        returnStatement = printStatement(fileVector);
        do{
            nextToken = getNextToken(fileVector, false);
        }while(nextToken.stackTop == 33);

        if (nextToken.stackTop == 20){
            
        }
        else{
            cout << "ERROR EXPECTED SEMICOLIN EXPECTED";
            exit(0);
        }

        return returnStatement;
    }
    else if (nextToken.lexemeFin == "return"){
        returnStatement = rtrnStatement(fileVector);

        do{
                nextToken = getNextToken(fileVector, false);
            }while(nextToken.stackTop == 33);

            if (nextToken.stackTop == 20){
                
            }
            else{
                cout << "ERROR EXPECTED SEMICOLIN EXPECTED";
                exit(0);
        }

        return returnStatement;
    }
    else if (nextToken.lexemeFin == "if"){
        returnStatement = ifStatement(fileVector);
        return returnStatement;
    }
    else if (nextToken.lexemeFin == "for"){
        returnStatement = forStatement(fileVector);
        return returnStatement;
    }
    else if (nextToken.lexemeFin == "while"){
        returnStatement = whileStatement(fileVector);
        return returnStatement;
    }
    else if (nextToken.lexemeFin == "fn"){
        returnStatement = functionDecl(fileVector);
        return returnStatement;
    }
    // block
    else if (nextToken.stackTop == 22){
        returnStatement = block(fileVector);
        return returnStatement;
    }
    else if (nextToken.stackTop == 6){

        returnStatement = assignment(fileVector);
        do{
            nextToken = getNextToken(fileVector, false);
        }while(nextToken.stackTop == 33);

        if (nextToken.stackTop == 20){
            
        }
        else{
            cout << "ERROR EXPECTED SEMICOLIN EXPECTED";
            exit(0);
        }

        return returnStatement;
    }
    else{
        cout << "ERROR EXPECTED STATEMENT";
        exit(0);
    }

}

BLOCK* block(vector<char> fileVector){
    BLOCK* returnBlock = new BLOCK();
    tableLexerReturn nextToken;

    do{
        nextToken = getNextToken(fileVector, false);
    }while(nextToken.stackTop == 33);

    if (nextToken.stackTop == 22){
        returnBlock->lBrac = true;
    }
    else{
        returnBlock->lBrac = false;
        cout << "ERROR EXPECTED LEFT BRACKET FOR BLOCK";
        exit(0);
    }

    Statement* holdSTMT = new Statement();
    
    // closing bracket
    if (nextToken.stackTop != 23){
        for(;;){
            holdSTMT = statement(fileVector);
            //check if statement was invalid if so than a closing bracket was found
            if  (dynamic_cast<INVALIDST*>(holdSTMT) == NULL){
                returnBlock->stmts.push_back(holdSTMT);
            }
            // if a closing bracket is found we stop looping
            else{
                do{
                nextToken = getNextToken(fileVector, false);
                }while(nextToken.stackTop == 33);
                returnBlock->rBrac = true;
                break;
            }
        }
    }

    returnBlock->rBrac = true;
  

    return returnBlock;
}

void printTabs(int indent){
    for (int i = 0; i < indent; i++){
        cout << "\t";
    }
}

void printEXPR(EXPR* express, int indentAmnt);

int XML(vector<Statement*> *AST, int indentAmnt);

void printIden(IDENTIFIER* ident, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<Identifier>\n";
    printTabs(indentAmnt+1);
    cout << ident->iden <<"\n";
    printTabs(indentAmnt);
    cout << "<\\Identifier>\n";
}

void printLit(LITERAL* lit, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<Literal>\n";
    if (lit->literalType == "CHAR"){
        printTabs(indentAmnt+1);
        cout << "<CharLiteral>\n";
        printTabs(indentAmnt+2);
        cout << lit->contentsType<<"\n";
        printTabs(indentAmnt+1);
        cout << "<//CharLiteral>\n";
    }
    else if (lit->literalType == "BOOL"){
        printTabs(indentAmnt+1);
        cout << "<BoolLiteral>\n";
        printTabs(indentAmnt+2);
        cout << lit->contentsType<<"\n";
        printTabs(indentAmnt+1);
        cout << "<//BoolLiteral>\n";
    }
    else if (lit->literalType == "FLOAT"){
        printTabs(indentAmnt+1);
        cout << "<FloatLiteral>\n";
        printTabs(indentAmnt+2);
        cout << lit->contentsType<<"\n";
        printTabs(indentAmnt+1);
        cout << "<//FloatLiteral>\n";
    }
    else if (lit->literalType == "INT"){
        printTabs(indentAmnt+1);
        cout << "<IntLiteral>\n";
        printTabs(indentAmnt+2);
        cout << lit->contentsType<<"\n";
        printTabs(indentAmnt+1);
        cout << "<//IntLiteral>\n";
    }
    printTabs(indentAmnt);
    cout << "<\\Literal>\n";
}

void printSubEXPR(SUBEXPRESSION* subEXPR, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<SubExpression>\n";
    printEXPR(subEXPR->expression, indentAmnt);
    printTabs(indentAmnt);
    cout << "<\\SubExpression>\n";
}

void printAct(ACTUALPARAMS* act, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<ActualParams>\n";
    printEXPR(act->express, indentAmnt);
    

    if(act->hasMoreEXPR == true){
        vector<EXPR*>::iterator iterAct;
        for (iterAct = (act->moreEXPR).begin(); iterAct != (act->moreEXPR).end(); ++iterAct){
            printEXPR(*iterAct, indentAmnt);
        }
    }
    printTabs(indentAmnt);
    cout << "<\\ActualParams>\n";
}

void printFunCall(FUNCTIONCALL* func, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<FunctionCall>\n";
    printIden(func->iden, indentAmnt);
    if (func->hasAct == true){
        printAct(func->act, indentAmnt);
    }
    printTabs(indentAmnt);
    cout << "<\\FunctionCall>\n";
}

// NEED TO ADD FUNCTIONCALL
void printFactor(FACTOR* fac, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<Factor>\n";
    if (dynamic_cast<IDENTIFIER*>(fac) != NULL){
        IDENTIFIER* printFac = dynamic_cast<IDENTIFIER*>(fac);
        printIden(printFac, indentAmnt);
    }
    else if (dynamic_cast<LITERAL*>(fac) != NULL){
        LITERAL* printFac = dynamic_cast<LITERAL*>(fac);
        printLit(printFac, indentAmnt);
    }
    else if (dynamic_cast<SUBEXPRESSION*>(fac) != NULL){
        SUBEXPRESSION* printFac = dynamic_cast<SUBEXPRESSION*>(fac);
        printSubEXPR(printFac, indentAmnt);
    }
    else if (dynamic_cast<FUNCTIONCALL*>(fac) != NULL){
        FUNCTIONCALL* printFac = dynamic_cast<FUNCTIONCALL*>(fac);
        printFunCall(printFac, indentAmnt);
    }
    printTabs(indentAmnt);
    cout << "<\\Factor>\n";
}

void printTerm(TERM* terms, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<Term>\n";
    printFactor(terms->lFac, indentAmnt);
    vector<FACTOR*> ::iterator iterTrm;
    int counter = 0;
    for (iterTrm = (terms->rFac).begin(); iterTrm != (terms->rFac).end(); ++iterTrm){
        printTabs(indentAmnt+1);
        cout << "<Multiplicitive Op>\n";
        printTabs(indentAmnt+2);
        cout << terms->mulOP[counter] << "\n";
        printTabs(indentAmnt+1);
        cout << "<\\Multiplicitive Op>\n";
        printFactor(*iterTrm, indentAmnt);
        counter += 1;
    }
    printTabs(indentAmnt);
    cout << "<\\Term>\n";
}

void printSiEXPR(SIEXPR* simpExp, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<SimpleExpr>\n";
    printTerm(simpExp->trm,indentAmnt);
    
    vector<TERM*> ::iterator iterSimp;
    int counter = 0;
    for (iterSimp = (simpExp->rTrm).begin(); iterSimp != (simpExp->rTrm).end(); ++iterSimp){
        printTabs(indentAmnt+1);
        cout << "<Additive Op>\n";
        printTabs(indentAmnt+2);
        cout << simpExp->addOP[counter] << "\n";
        printTabs(indentAmnt+1);
        cout << "<\\Additive Op>\n";
        printTerm(*iterSimp,indentAmnt);
        counter += 1;
    }
    printTabs(indentAmnt);
    cout << "<\\SimpleExpr>\n";
}

void printEXPR(EXPR* express, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<Expression>\n";
    printSiEXPR(express->lExpres, indentAmnt);
    
    vector<SIEXPR*> ::iterator iterEXPR;
    int counter = 0;
    for (iterEXPR = (express->rExpres).begin(); iterEXPR != (express->rExpres).end(); ++iterEXPR){
        printTabs(indentAmnt + 1);
        cout << "<Relational Op>\n";
        printTabs(indentAmnt + 2);
        cout << express->relOP[counter] << "\n";
        printTabs(indentAmnt + 1);
        cout << "<\\Relational Op>\n";
        printSiEXPR(*iterEXPR, indentAmnt);
        counter += 1;
    }
    printTabs(indentAmnt);
    cout << "<\\Expression>\n";
}

void printBLK(BLOCK* blk, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<Block>\n";
    XML(&blk->stmts, indentAmnt);
    printTabs(indentAmnt);
    cout << "<\\Block>\n";
}

void printVarD(VD* printVD, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<VariableDecl>\n";       
    printIden(printVD->iden, indentAmnt);

    printTabs(indentAmnt);
    cout << "<Type>\n";
    printTabs(indentAmnt+1);
    cout <<printVD->typ<<"\n";
    printTabs(indentAmnt);
    cout << "<\\Type>\n";
    printTabs(indentAmnt);

    printEXPR(printVD->express, indentAmnt);
    printTabs(indentAmnt);
    cout << "<\\VariableDecl>\n";
}

void printAssing(AS* printAS, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<Assignment>\n";         
    printIden(printAS->iden, indentAmnt);
    printEXPR(printAS->express, indentAmnt);
    printTabs(indentAmnt);
    cout << "<\\Assignment>\n";
}

void printPState(PS* printPS, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<PrintStatement>\n";
    printEXPR(printPS->express, indentAmnt);
    printTabs(indentAmnt);
    cout << "<\\PrintStatement>\n";
}

void printIState(IS* printIS, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<IfStatement>\n";         
    printEXPR(printIS->express, indentAmnt);
    printBLK(printIS->blk, indentAmnt);
    if (printIS->elSe == true){
        cout << "<Else>\n";
        printBLK(printIS->blks, indentAmnt);
        cout << "<\\Else>\n";
    }
    printTabs(indentAmnt);
    cout << "<\\IfStatement>\n";
}

void printFState(FS* printFS, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<ForStatement>\n";  
    if ( printFS->hasVarDec == true){
        VD* printVD = dynamic_cast<VD*>(printFS->varDec);
        printVarD(printVD, indentAmnt);
    }

    printEXPR(printFS->express, indentAmnt);

    if ( printFS->hasAssignMNT == true){
        AS* printAS = dynamic_cast<AS*>(printFS->assignMNT);
        printAssing(printAS, indentAmnt);
    }

    BLOCK* printBLCK = dynamic_cast<BLOCK*>(printFS->blck);
    printBLK(printBLCK, indentAmnt);
    printTabs(indentAmnt);
    cout << "<\\ForStatement>\n";
}

void printWState(WS* printWS, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<WhileStatement>\n";
    printEXPR(printWS->express, indentAmnt);

    BLOCK* printBLCK = dynamic_cast<BLOCK*>(printWS->blck);
    printBLK(printBLCK,indentAmnt);
    printTabs(indentAmnt);
    cout << "<\\WhileStatement>\n";
}

void printRState(RS* printRS, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<ReturnStatement>\n";
    printEXPR(printRS->express, indentAmnt);
    printTabs(indentAmnt);
    cout << "<\\ReturnStatement>\n";
}

void printPRM(FORMALPARAM* param, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<FormalParam>\n";
    printIden(param->iden, indentAmnt);
    printTabs(indentAmnt);
    cout << "<Type>\n";
    printTabs(indentAmnt+1);
    cout <<param->typ<<"\n";
    printTabs(indentAmnt);
    cout << "<\\Type>\n";
    printTabs(indentAmnt);
    cout << "<\\FormalParam>\n";
}

void printFmlPRMS(FORMALPARAMS* params, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<FormalParams>\n";
    printPRM(params->fmlprms, indentAmnt);
    

    if(params->hasMorePRMS == true){
        vector<FORMALPARAM*>::iterator iterFPM;
        for (iterFPM = (params->morePRMS).begin(); iterFPM != (params->morePRMS).end(); ++iterFPM){
            printPRM(*iterFPM, indentAmnt);
        }
    }
    printTabs(indentAmnt);
    cout << "<\\FormalParams>\n";
}

void printFDec(FD* printFD, int indentAmnt){
    indentAmnt += 1;
    printTabs(indentAmnt);
    cout << "<FunctionDecleration>\n";
    printIden(printFD->iden, indentAmnt);

    if (printFD->hasFParams == true){
        printFmlPRMS(printFD->FParams, indentAmnt);
    }

    printTabs(indentAmnt);
    cout << "<Type>\n";
    printTabs(indentAmnt+1);
    cout <<printFD->typ <<"\n";
    printTabs(indentAmnt);
    cout << "<\\Type>\n";

    BLOCK* blockkk = dynamic_cast<BLOCK*>(printFD->blck);
    printBLK(blockkk, indentAmnt);
    printTabs(indentAmnt);
    cout << "<\\FunctionDecleration>\n";
}

int XML(vector<Statement*> *AST, int indentAmnt){
    vector<Statement*>::iterator iter;
    indentAmnt += 1;
    
    for (iter = AST->begin(); iter != AST->end(); ++iter){
        printTabs(indentAmnt);
        cout <<"<Statement>\n";
        // prints out memory location
        // cout << *iter;
        if (dynamic_cast<VD*>(*iter) != NULL){
            VD* printVD = dynamic_cast<VD*>(*iter);
            printVarD(printVD, indentAmnt);
        }
        else if (dynamic_cast<AS*>(*iter) != NULL){
            AS* printAS = dynamic_cast<AS*>(*iter);
            printAssing(printAS, indentAmnt);
        }
        else if (dynamic_cast<PS*>(*iter) != NULL){
            PS* printPS = dynamic_cast<PS*>(*iter);
            printPState(printPS, indentAmnt);
        }
        else if (dynamic_cast<IS*>(*iter) != NULL){
            IS* printIS = dynamic_cast<IS*>(*iter);
            printIState(printIS, indentAmnt);
        }   
        else if (dynamic_cast<FS*>(*iter) != NULL){
            FS* printFS = dynamic_cast<FS*>(*iter);
            printFState(printFS, indentAmnt);
        }
        else if (dynamic_cast<WS*>(*iter) != NULL){
            WS* printWS = dynamic_cast<WS*>(*iter);
            printWState(printWS, indentAmnt);
        }
        else if (dynamic_cast<RS*>(*iter) != NULL){
            RS* printRS = dynamic_cast<RS*>(*iter);
            printRState(printRS, indentAmnt);
        }
        else if (dynamic_cast<FD*>(*iter) != NULL){
            FD* printFD = dynamic_cast<FD*>(*iter);
            printFDec(printFD, indentAmnt);
        }
        else if (dynamic_cast<BLOCK*>(*iter) != NULL){
            BLOCK* printBLOCK = dynamic_cast<BLOCK*>(*iter);
            printBLK(printBLOCK, indentAmnt);
        }
        printTabs(indentAmnt);
        cout <<"<\\Statement>\n";
    }

    
    return 0;
}

int main(){
    ifstream myfile("example.txt");
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

        vector<Statement*> *returnAST = parser(fileVector);  
        cout << returnAST;
        int indentAmnt = 0;
        cout << "\n";
        cout << "<Program>\n";
        XML(returnAST, indentAmnt);
        cout << "<\\Program>\n";
    }
    
}
