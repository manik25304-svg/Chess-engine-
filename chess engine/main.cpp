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
using namespace std;

typedef struct board{
    vector<vector<int> > a;\
    board() : a(8, vector<int>(8)) {}
}board;

typedef struct piece{
    int ws,wr,wh,wb,wk,wq,bs,br,bh,bb,bq,bk;
    
    //w starting pieces are white b starting pieces are black
}pieces;
void piece_initialize(pieces& p){
    p.ws=1;
    p.wr=2;
    p.wh=3;
    p.wb=4;
    p.wq=5;
    p.wk=6;                    // initialized each piece for a specific number if number is -ve the pieece is black                                 otherwise in case of positive number the piece is white
    p.bs=-1;
    p.br=-2;
    p.bh=-3;
    p.bb=-4;
    p.bq=-5;
    p.bk=-6;
}

void board_initialize(board& b){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){                    //here 0 mean board square is empty
            b.a[i][j]=0;
        }
    }
    
}
int main(){
    board b1;
    board_initialize(b1);
}
