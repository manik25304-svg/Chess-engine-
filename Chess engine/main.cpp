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
bool is_path_clear(board& b,int x1,int y1,int x2,int y2) {
    int dx=(x2>x1)?1:((x2<x1)?-1:0);
    int dy=(y2>y1)?1:((y2<y1)?-1:0);
    
    int x=x1+dx;
    int y=y1+dy;
    while (x != x2 || y != y2) {
        if (b.a[x][y]!=0) return false;
        x+=dx;
        y+=dy;
    }
    return true;
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
bool valid_pawn(board& b1,int x1,int y1,int x2,int y2,int p){
    int dis=(p>0)? 1: -1;
    int s=(p>0)? 1 : 6;
    if(y1==y2 && x2==x1+dis && b1.a[x2][y2]==0) return true; // here x axis reffer to vertical line like lines from king to king at start of game move 1 step in forward direction
    if(y1==y2 && x1==s && x2==x1+2*dis && b1.a[x1+1*dis][y1]==0 && b1.a[x1+2*dis][y1]==0 ) return true;
    if (abs(y2-y1)==1 && x2==x1+dis){
            if((b1.a[x1][y1]>0 && b1.a[x2][y2]<0)||(b1.a[x1][y1]<0 && b1.a[x2][y2]>0)) {
                return true;
            }
        }
    return false;
}
bool valid_rook(board& b1,int x1,int y1,int x2,int y2,int p){
    if(x1!=x2 && y1!=y2) return false;
    if (!is_path_clear(b1,x1,y1,x2,y2)) return false;
    if((b1.a[x1][y1]>0 && b1.a[x2][y2]>0)||(b1.a[x1][y1]<0 && b1.a[x2][y2]<0)) return false;
    return true;
}
bool valid_horse(board& b1,int x1,int y1,int x2,int y2,int p){
    int dx=abs(x2-x1);
    int dy=abs(y2-y1);
    if(!((dx==2 && dy==1)||(dx==1 && dy==2))) return false;
    if((b1.a[x1][y1]>0 && b1.a[x2][y2]>0)||(b1.a[x1][y1]<0 && b1.a[x2][y2]<0)) return false;
    return true;
}

bool valid_bishop(board& b1,int x1,int y1,int x2,int y2,int p){
    int dx=abs(x2-x1);
    int dy=abs(y2-y1);
    if(dx!=dy) return false;
    if(dx==0|| dy==0) return false;
    if (!is_path_clear(b1,x1,y1,x2,y2)) return false;
    if((b1.a[x1][y1]>0 && b1.a[x2][y2]>0)||(b1.a[x1][y1]<0 && b1.a[x2][y2]<0)) return false;
    return true;
}
bool valid_queen(board& b1,int x1,int y1,int x2,int y2,int p){
    return valid_rook(b1,x1,y1,x2,y2,p)||valid_bishop(b1,x1,y1,x2,y2,p);
}
bool valid_king(board& b1,int x1,int y1,int x2,int y2,int p){
    int dx=abs(x2-x1);
    int dy=abs(y2-y1);
    if(dx>1|| dy>1) return false;
    if(dx==0 && dy==0) return false;
    if((b1.a[x1][y1]>0 && b1.a[x2][y2]>0)||(b1.a[x1][y1]<0 && b1.a[x2][y2]<0)) return false;
    return true;
}


bool valid(board& b1,int x1,int y1,int x2,int y2){
    int p=b1.a[x1][y1];
    if(p==0) return false;
    int pi=abs(p);
    bool b=false;
    switch(pi){
        case 1:{ b=valid_pawn(b1,x1,y1,x2,y2,p);
            break;
        }
        case 2:{ b=valid_rook(b1,x1,y1,x2,y2,p); break;}
        case 3: {b=valid_horse(b1,x1,y1,x2,y2,p);break;}
        case 4: {
            b=valid_bishop(b1,x1,y1,x2,y2,p);break;
        }
        case 5: {
            b=valid_queen(b1,x1,y1,x2,y2,p);break;
        }
        case 6:{
            b=valid_king(b1,x1,y1,x2,y2,p);break;
        }
        default: b=false;
    }
    if(b){
        b1.a[x2][y2]=b1.a[x1][y1];
        b1.a[x1][y1]=0;
        if(pi==1){
            bool evolve=false;
            if(p>0 && x2==7) evolve=true;
            if(p<0 && x2==0) evolve=true;
            if(evolve){
                string s;
                cout << "evolve to queen(q),rook(r),bishop(b),horse(h): " << endl;
                cin >> s;
                int col=(p>0) ? 1:-1;
                switch(s[0]){
                    case 'q': b1.a[x2][y2] =5*col; break;
                    case 'r': b1.a[x2][y2] =2*col; break;
                    case 'b': b1.a[x2][y2] =4*col; break;
                    case 'h': b1.a[x2][y2] =3*col; break;
                    default:  b1.a[x2][y2] =5*col; break;
                }
            }
        }
    }
    return b;
}

bool move(board& b1,int x1,int y1,int x2,int y2){
    if(valid(b1,x1,y1,x2,y2)){
        return true;
    }
    else{
        cout << "invaild move" << endl;
        return false;
    }
}

void startgame(board& b1){
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
        if(p==0) {cout << "empty box no element exist" << endl;
            continue;
        }
        else if((p>0 && !wt) || (p<0 && wt)) {
            cout << "choosen opponent piece so we can not move" << endl;
            continue;}
        if(move(b1,x1,y1,x2,y2)) wt=!wt;
    }
}

int main(){
    board b1;
    board_initialize(b1);
    pieces p;
    piece_initialize(p);
    initialize_game(b1,p);
    startgame(b1);
    
    
}
