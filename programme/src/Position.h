#ifndef POSITION_H
#define POSITION_H
class Position {
    
    private :
    int x,y,z;
    
    public :
		Position();
		Position( int x, int y, int z);
		int getX();
		int getY();
		int getZ();
		void setPosition(int x, int y, int z);
		void setPosition(Position pos);

		Position operator + (const Position& pos1);

};

#endif