#ifndef _Enemy_H_
#define _Enemy_H_
#include "cocos2d.h"
USING_NS_CC;

enum DEGREE{
	LOW = 1,
	MIDDLE = 2,
	HIGH = 3
};

class Enemy : public CCSprite
{
public:
	static Enemy * create(DEGREE degree);
	bool init(DEGREE degree);
	void setHit();
	void boom();
	void removeFromParentAndCleanCallback(CCNode * node );

	CCRect getBoundingBox();
	
	CC_SYNTHESIZE(int, _life, Life);
	CC_SYNTHESIZE(DEGREE, _degree, Degree);
};

#endif