#ifndef _Plane_H_
#define _Plane_H_
#include "cocos2d.h"
USING_NS_CC;

class Plane : public CCSprite
{
public:
	static Plane *  getPlane();
	bool init();
	void boom(int score);
	void removePlaneCallback(CCNode* node, void *data);
private:
	static Plane * _plane;
};
#endif
