#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Coordinate{
public:
	int x;
	int y;
	Coordinate(){
		x=0;
		y=0;
	}
	Coordinate(int a, int b){
		x=a;
		y=b;
	}
};

class board;

class Piece{
public:
	string type;
	int colour;    //1 for white, -1 for black.
	bool mult_by_constant;
	bool can_travel_opposite;
	vector<Coordinate> step_size;
	Coordinate posn;
	Piece(){
		posn.x=1;
		posn.y=1;
	}
	Piece(int xi, int yi){
		posn.x=xi;
		posn.y=yi;
	}
	void set_posn(int xi, int yi){
		posn.x=xi;
		posn.y=yi;
	}
	void operator=(const Piece& p){
		type=p.type;
		colour=p.colour;
		mult_by_constant=p.mult_by_constant;
		can_travel_opposite=p.can_travel_opposite;
		step_size=p.step_size;
	}
	vector<Coordinate> possibleMoves();
	bool is_empty(){
		return type=="Empty";
	}

	vector<Coordinate> validMoves(board b);
};


class Pawn : public Piece{
public:
	Pawn(){
		type="Pawn";
		mult_by_constant=false;
		can_travel_opposite=false;
		Coordinate c(0,colour); //white is below, black is above.
		step_size.push_back(c);
	}
};

class Rook : public Piece{
public:
	Rook(){
		type="Rook";
		mult_by_constant=true;
		can_travel_opposite=true;
		Coordinate c1(0,1);
		step_size.push_back(c1);
		Coordinate c2(1,0);
		step_size.push_back(c2);
	}
};

class Knight : public Piece{
public:
	Knight(){
		type="Knight";
		mult_by_constant=false;
		can_travel_opposite=true;
		Coordinate c1(2,1);
		step_size.push_back(c1);
		Coordinate c2(1,2);
		step_size.push_back(c2);
		Coordinate c3(2,-1);
		step_size.push_back(c3);
		Coordinate c4(1,-2);
		step_size.push_back(c4);
	}
};

class Bishop : public Piece{
public:
	Bishop(){
		type="Bishop";
		mult_by_constant=true;
		can_travel_opposite=true;
		Coordinate c1(1,1);
		step_size.push_back(c1);
		Coordinate c2(1,-1);
		step_size.push_back(c2);
	}
};

class Queen : public Piece{
public:
	Queen(){
		type="Queen";
		mult_by_constant=true;
		can_travel_opposite=true;
		Coordinate c1(0,1);
		step_size.push_back(c1);
		Coordinate c2(1,0);
		step_size.push_back(c2);
		Coordinate c3(1,1);
		step_size.push_back(c3);
		Coordinate c4(1,-1);
		step_size.push_back(c4);
	}
};

class King : public Piece{
public:
	King(){
		type="King";
		mult_by_constant=false;
		can_travel_opposite=true;
		Coordinate c1(0,1);
		step_size.push_back(c1);
		Coordinate c2(1,0);
		step_size.push_back(c2);
		Coordinate c3(1,1);
		step_size.push_back(c3);
		Coordinate c4(1,-1);
		step_size.push_back(c4);
	}
};

class Empty : public Piece{
public:
	Empty(){
		type="Empty";
		mult_by_constant=false;
		can_travel_opposite=false;
	}
};

class board{
public:
	Piece a[8][8];
	board(){
		for(int i=0; i<8; i++){
			for(int j=0; j<8; j++){
				Coordinate c;
				c.x=i+1;
				c.y=j+1;
				a[i][j].posn=c;
				a[i][j].type="Empty";
			}
		}
	}
};




bool inside_board(Coordinate c){
	int cx=c.x;
	int cy=c.y;
	return (((cx>=1)&&(cx<=8))&&((cy>=1)&&(cy<=8)));
}

vector<Coordinate> Piece::possibleMoves(){
	vector<Coordinate> res;
	int px=posn.x;
	int py=posn.y;
	if (can_travel_opposite){
		if (mult_by_constant){
			int lim=max(max(px-1,8-px),max(py-1,8-py));
			for(int j=1; j<=lim; j++){
				for(int i=0; i<step_size.size(); i++){
					Coordinate c;
					c.x=px+j*step_size[i].x;
					c.y=py+j*step_size[i].y;
					if (inside_board(c)) res.push_back(c);
					c.x=px-j*step_size[i].x;
					c.y=py-j*step_size[i].y;
					if (inside_board(c)) res.push_back(c);
				}
			}
		}
		else {
			for(int i=0; i<step_size.size(); i++){
				Coordinate c;
				c.x=px+step_size[i].x;
				c.y=py+step_size[i].y;
				if (inside_board(c)) res.push_back(c);
				c.x=px-step_size[i].x;
				c.y=py-step_size[i].y;
				if (inside_board(c)) res.push_back(c);
			}
		}
	}
	else {
		if (mult_by_constant){
			int lim=max(max(px-1,8-px),max(py-1,8-py));
			for(int j=0; j<lim; j++){
				for(int i=0; i<step_size.size(); i++){
					Coordinate c;
					c.x=px+j*step_size[i].x;
					c.y=py+j*step_size[i].y;
					if (inside_board(c)) res.push_back(c);
				}
			}
		}
		else {
			for(int i=0; i<step_size.size(); i++){
				Coordinate c;
				c.x=px+step_size[i].x;
				c.y=py+step_size[i].y;
				if (inside_board(c)) res.push_back(c);
			}
		}
	}
	return res;
}

vector<Coordinate> Piece::validMoves(board b){
	vector<Coordinate> res;
	int px=posn.x;
	int py=posn.y;
	if (can_travel_opposite){
		if (mult_by_constant){
			int lim=max(max(px-1,8-px),max(py-1,8-py));
			for(int n=1; n>=-1; n-=2){
				for(int i=0; i<step_size.size(); i++){
					for(int j=1; j<=lim; j++){
						Coordinate c;
						c.x=px+n*j*step_size[i].x;
						c.y=py+n*j*step_size[i].y;
						if (inside_board(c)) {
							if (b.a[c.x-1][c.y-1].is_empty()){
								res.push_back(c);
							}
							else{
								Piece p=b.a[c.x-1][c.y-1];
								if (p.colour==colour) break;
								else{
									res.push_back(c);
									break;
								}
							}
						}
					}
				}
			}
		}
		else {
			for(int i=0; i<step_size.size(); i++){
				Coordinate c;
				c.x=px+step_size[i].x;
				c.y=py+step_size[i].y;
				if (inside_board(c)) {
					if (b.a[c.x-1][c.y-1].is_empty()){
						res.push_back(c);
					}
					else{
						Piece p=b.a[c.x-1][c.y-1];
						if (p.colour!=colour) res.push_back(c);
					}
				}
				
				
				c.x=px-step_size[i].x;
				c.y=py-step_size[i].y;
				if (inside_board(c)) {
					if (b.a[c.x-1][c.y-1].is_empty()){
						res.push_back(c);
					}
					else{
						Piece p=b.a[c.x-1][c.y-1];
						if (p.colour!=colour) res.push_back(c);
					}
				}
			}
		}
	}
	else {
		if (mult_by_constant){
			int lim=max(max(px-1,8-px),max(py-1,8-py));
			for(int j=1; j<=lim; j++){
				for(int i=0; i<step_size.size(); i++){
					Coordinate c;
					c.x=px+j*step_size[i].x;
					c.y=py+j*step_size[i].y;
					if (inside_board(c)) {
						if (b.a[c.x-1][c.y-1].is_empty()){
							res.push_back(c);
						}
						else{
							Piece p=b.a[c.x-1][c.y-1];
							if (p.colour==colour) break;
							else{
								res.push_back(c);
								break;
							}
						}
					}
				}
			}
		}
		else {
			for(int i=0; i<step_size.size(); i++){
				Coordinate c;
				c.x=px+step_size[i].x;
				c.y=py+step_size[i].y;
				if (inside_board(c)) {
					if (b.a[c.x-1][c.y-1].is_empty()){
						res.push_back(c);
					}
					else{
						Piece p=b.a[c.x-1][c.y-1];
						if (p.colour!=colour) res.push_back(c);
					}
				}
			}
		}
	}
	return res;
}

int main(){
	/*Piece a(3,2);
	Knight r;
	a=r;
	vector<Coordinate> res=a.possibleMoves();
	for(int i=0; i<res.size(); i++){
		cout<<res[i].x<<" , "<<res[i].y<<"\n";
	}
	*/
	board b_init;
	Rook r;
	Pawn p;
	p.colour=1;
	r.colour=1;
	b_init.a[3][2]=p;
	b_init.a[3][3]=r;
	vector<Coordinate> res=b_init.a[3][2].validMoves(b_init);
	for(int i=0; i<res.size(); i++){
		cout<<res[i].x<<" , "<<res[i].y<<"\n";
	}
}
