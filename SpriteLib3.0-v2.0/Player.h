#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "BackEnd.h"

enum AnimEnums
{
	IDLELEFT,
	IDLERIGHT,
	
	//Only in Top down
#ifdef TOPDOWN
	IDLEUP,
	IDLEDOWN,
#endif

	WALKLEFT,
	WALKRIGHT,

	//Only in Top down
#ifdef TOPDOWN
	WALKUP,
	WALKDOWN,
#endif

	RUNLEFT,
	RUNRIGHT,

	//Only in Top down
#ifdef TOPDOWN
	RUNKUP,
	RUNDOWN,
#endif
	
	JUMPLEFT,
	JUMPRIGHT,

	//Only in Top down
#ifdef TOPDOWN
	ATTACKUP,
	ATTACKDOWN
#endif
};

enum AnimTypes
{
#ifdef TOPDOWN
	IDLE = 0,
	WALK = 4,
	RUN = 8,
	JUMP = 12
#endif
#ifndef TOPDOWN
	IDLE = 0,
	WALK = 2,
	RUN = 4,
	JUMP = 6
#endif
};

enum AnimDir
{
	LEFT,
	RIGHT,
	//Only in Top Down
#ifdef TOPDOWN
	UP,
	DOWN
#endif
};

class Player
{
public:
	Player();
	Player(std::string& fileName, std::string& animationJSON, int width, int height, 
		Sprite* sprite, AnimationController* controller, Transform* transform, bool hasPhys = false, PhysicsBody* body = nullptr);

	void InitPlayer(std::string& fileName, std::string& animationJSON, int width, int height, 
		Sprite* sprite, AnimationController* controller, Transform* transform, bool hasPhys = false, PhysicsBody* body = nullptr);

	void Update();
	void MovementUpdate();
	void AnimationUpdate();

private:
	void SetActiveAnimation(int anim);

	//Basically, any animation OTHER than moving will not have a cancel, and we'll be checking whether or not that animation is done
	bool m_walking = false;
	//Is the player running?
	bool m_running = false;
	//Is the player currently attacking?
	bool m_attacking = false;
	//Is the player currently jumping?
	bool m_jumping = false;
	//Is the player currently crouched?
	bool m_crouched = false;
	//Have we locked the player from moving during this animation?
	bool m_locked = false;
	//Have we locked the player from jumping during this animation?
	bool m_jumplocked = false;

	//A reference to our sprite
	Sprite* m_sprite = nullptr;
	//A reference to our animation controller
	AnimationController* m_animController = nullptr;
	//A reference to our player transform
	Transform* m_transform = nullptr;

	//Physics importance
	//A reference to our physics body
	PhysicsBody* m_physBody = nullptr;
	//Does this player have physics?
	bool m_hasPhysics = false;

	//Default animation direction (feel free to change this to suit your game. If you're making a side-scroller, left or right would be better
	AnimDir m_facing = LEFT;
};

#endif // !__PLAYER_H__