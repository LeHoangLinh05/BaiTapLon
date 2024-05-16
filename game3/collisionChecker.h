#ifndef COLLISIONCHECKER_H_INCLUDED
#define COLLISIONCHECKER_H_INCLUDED
bool checkCollision(int foodx, int foody, int playerx, int playery) {

	if (playerx == foodx && playery == foody){
		return true;
	}

	return false;
}


#endif // COLLISIONCHECKER_H_INCLUDED
