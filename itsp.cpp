#include<iostream>
#include<vector>
using namespace std;

struct board
{
	piece a[8][8];
};

struct tree
{
	board node;
	vector<tree*> vec;
};


void insert(tree initial_tree,board b,vector<board> vec)
{
    if(initial_tree.node == b)
    {
    	for(int i=0;i<vec.size();i++)
    	{   tree t;
    		t.node = vec[i];
    		t.vec.push_back(NULL);
    		initial_tree.vec.push_back(t);
    	}
    }
	else if(initial_tree.vec[0]=NULL) {}
		else
	{
		for(int i=0;i<initial_tree.vec.size();i++)
		{
			insert(*(initial_tree.vec[i]),b,vec);
		}
	}
}

void generate_tree(tree t , board a , int level)
{ 
    if(level == 0){}
    	else
    	{
    		insert(t,a,possible_boards(a));
    		for(int i=0;i<t.vec.size();i++)
    		{
    			generate_tree(*(t.vec[i]),t.vec[i]->node,level-1);
    		}
    	}
}

int main()
{
    board initial_board;
    piece b[8][8];
    for(int i=2;i<6;i++)
    {
    	for(int j=0;j<8;j++)
    	{
             b[i][j].type=0;
    	}
    }
    for(int i=0;i<8;i++)
    {
    	b[1][i].type=1;
    	b[6][i].type=1;
    }
    for(int i=0,j=2;i<4;i++,j++)
    {
    	b[i][i].type=j;
    	b[7-i][i].type=j;
    	b[i][7-i].type=j;
    	b[7-i][7-i].type=j;
    }
    for(int i=0;i<8;i++)
    {
    	for(int j=0;j<8;j++)
    	{
    		initial_board.a[i][j]=b[i][j];
    	}
    }

    int state = -1,level=3;
    board current_board = initial_board;
    while(true)
    {
    	if(game_end(current_board))
    	{
    		break;
    	}
    	else if(state == -1)
    	{
    		current_board = generate_new(current-board,move);
    		state *= -1;
    	}
    	else if(state == 1)
    	{
            tree t;
    		t.node = current_board;
    		t.vec.push_back(NULL);
            generate_tree(t,current_board,level);
            evaluate(t);
    		state *= -1;
    	}
    }
}