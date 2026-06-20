//
//  main.cpp
//  chess engine
//
//  Created by Manik Goel on 16/06/26.
//

#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
using namespace std;

typedef struct board{
    vector<vector<int> > a;
    board() : a(8, vector<int>(8)) {}
}board;

typedef struct piece{
    int wp,wr,wh,wb,wk,wq,bp,br,bh,bb,bq,bk;
    
    //w starting pieces are white b starting pieces are black
}pieces;
void piece_initialize(pieces& p){
    p.wp=1;
    p.wr=2;
    p.wh=3;
    p.wb=4;
    p.wq=5;
    p.wk=6;                    // initialized each piece for a specific number if number is -ve the pieece is black                                 otherwise in case of positive number the piece is white
    p.bp=-1;
    p.br=-2;
    p.bh=-3;
    p.bb=-4;
    p.bq=-5;
    p.bk=-6;
}

void initialize_game(board& b1,pieces& p){
    b1.a[1][0]=p.wp;
    b1.a[1][1]=p.wp;
    b1.a[1][2]=p.wp;
    b1.a[1][3]=p.wp;
    b1.a[1][4]=p.wp;
    b1.a[1][5]=p.wp;
    b1.a[1][6]=p.wp;
    b1.a[1][7]=p.wp;
    b1.a[0][0]=p.wr;
    b1.a[0][7]=p.wr;
    b1.a[0][1]=p.wh;
    b1.a[0][6]=p.wh;
    b1.a[0][5]=p.wb;
    b1.a[0][2]=p.wb;
    b1.a[0][3]=p.wq;
    b1.a[0][4]=p.wk;
    b1.a[6][0]=p.bp;
    b1.a[6][1]=p.bp;
    b1.a[6][2]=p.bp;
    b1.a[6][3]=p.bp;
    b1.a[6][4]=p.bp;
    b1.a[6][5]=p.bp;
    b1.a[6][6]=p.bp;
    b1.a[6][7]=p.bp;
    b1.a[7][0]=p.br;
    b1.a[7][7]=p.br;
    b1.a[7][1]=p.bh;
    b1.a[7][6]=p.bh;
    b1.a[7][5]=p.bb;
    b1.a[7][2]=p.bb;
    b1.a[7][3]=p.bq;
    b1.a[7][4]=p.bk;
}
void board_initialize(board& b){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){                    //here 0 mean board square is empty
            b.a[i][j]=0;
        }
    }
    
}

int piece_position(string s){
    int x_index=0,yindex=0;
    if(s[0]=='a') x_index=0;
    if(s[0]=='b') x_index=1;
    if(s[0]=='c') x_index=2;
    if(s[0]=='d') x_index=3;
    if(s[0]=='e') x_index=4;
    if(s[0]=='f') x_index=5;
    if(s[0]=='g') x_index=6;
    if(s[0]=='h') x_index=7;
    yindex=s[1]-49;
    return 10*x_index+yindex;
}
void display_board(board& b){
    for(int i=7;i>=0;i--){          // print black side at top
        for(int j=0;j<8;j++)
            cout << b.a[i][j] << "\t";
        cout << "\n";
    }
}

bool move_possible(board& b1,pieces& p1,int x1,int y1,int x2,int y2){
    if(valid(b1,x1,y1,x2,y2)){
        b1.a[x2][y2]=b1.a[x1][y1];
        b1.a[x1][y1]=0;
        return true;
    }
    else{
        cout << "invaild move" << endl;
        return false;
    }
}

void startgame(board& b1,pieces& p1){
    string i,e;
    bool wt=true;
    while(true){
        display_board(b1);
        cout << (wt ? "white turn" : "black turn") << endl;
        cout << "p1 to p2" << endl;          // here peoplr enter initial position and final position they want
        cin >> i >> e;
        int initial=piece_position(i);
        int finale=piece_position(e);
        int x1=initial/10,x2=finale/10,y1=initial%10,y2=finale%10;
        int p=b1.a[x1][y1];
        if(p==0) cout << "empty box no element exist" << endl;
        else if((p>0 && !wt) || (p<0 && wt)) cout << "choosen opponent piece so we can not move" << endl;
        if(move_possible(b1,p1,x1,y1,x2,y2)) wt=!wt;
    }
}

int main(){
    board b1;
    board_initialize(b1);
    pieces p;
    piece_initialize(p);
    initialize_game(b1,p);
    startgame(b1,p);
    
    
}

