#include<iostream>
#include<vector>
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

class Piece{
public:
	bool mult_by_constant;
	bool can_travel_opposite;
	vector<Coordinate> step_size;
	Coordinate posn;
	Piece(){
		posn.x=0;
		posn.y=0;
	}
	Piece(int xi, int yi){
		posn.x=xi;
		posn.y=yi;
	}
};

class Pawn : public Piece{
public:
	Pawn(){
		mult_by_constant=false;
		can_travel_opposite=false;
		Coordinate c(0,1);
		step_size.push_back(c);
	}
};

class Rook : public Piece{
public:
	Rook(){
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

bool inside_board(Coordinate c){
	int cx=c.x;
	int cy=c.y;
	return (((cx>=1)&&(cx<=8))&&((cy>=1)&&(cy<=8)));
}

vector<Coordinate> possibleMoves(Piece p){
	vector<Coordinate> res;
	int px=p.posn.x;
	int py=p.posn.y;
	if (p.can_travel_opposite){
		if (p.mult_by_constant){
			int lim=max(max(px-1,8-px),max(py-1,8-py));
			for(int j=0; j<lim; j++){
				for(int i=0; i<p.step_size.size(); i++){
					Coordinate c;
					c.x=px+j*p.step_size[i].x;
					c.y=py+j*p.step_size[i].y;
					if (inside_board(c)) res.push_back(c);
					c.x=px-j*p.step_size[i].x;
					c.y=py-j*p.step_size[i].y;
					if (inside_board(c)) res.push_back(c);
				}
			}
		}
		else {
			for(int i=0; i<p.step_size.size(); i++){
				Coordinate c;
				c.x=px+p.step_size[i].x;
				c.y=py+p.step_size[i].y;
				if (inside_board(c)) res.push_back(c);
				c.x=px-p.step_size[i].x;
				c.y=py-p.step_size[i].y;
				if (inside_board(c)) res.push_back(c);
			}
		}
	}
	else {
		if (p.mult_by_constant){
			int lim=max(max(px-1,8-px),max(py-1,8-py));
			for(int j=0; j<lim; j++){
				for(int i=0; i<p.step_size.size(); i++){
					Coordinate c;
					c.x=px+j*p.step_size[i].x;
					c.y=py+j*p.step_size[i].y;
					if (inside_board(c)) res.push_back(c);
				}
			}
		}
		else {
			for(int i=0; i<p.step_size.size(); i++){
				Coordinate c;
				c.x=px+p.step_size[i].x;
				c.y=py+p.step_size[i].y;
				if (inside_board(c)) res.push_back(c);
			}
		}
	}
	return res;
}

int main(){
	Piece a(1,1);
	Rook r;
	a=r;
	vector<Coordinate> res=possibleMoves(a);
	for(int i=0; i<res.size(); i++){
		cout<<res[i].x<<" , "<<res[i].y<<"\n";
	}
}
