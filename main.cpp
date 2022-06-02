#include <iostream>
#include <stack>
#include <string>
#include <fstream>
using namespace std;

int main(){
    cout << "Test123 FOR BASH";
    ofstream myfile;
    myfile.open ("example.txt");
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
    }


}


string NextWord(string line){
    int state = 0;
    string lexeme = "";
    stack<int> stack;
    stack.push(0);

    while (state != 69){
        lexeme.append(character);

    }
    if()
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