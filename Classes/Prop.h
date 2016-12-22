#ifndef _Prop_H_
#define _Prop_H_
#include "cocos2d.h"
USING_NS_CC;

enum PROPTYPE{
	BOOM,
	BULLET
};

class Prop : public CCSprite
{
public:
	static Prop * create(PROPTYPE type);
	bool init(PROPTYPE type);
	CC_SYNTHESIZE(PROPTYPE, _propType, PropType);
};


#endif
