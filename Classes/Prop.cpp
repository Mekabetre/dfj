#include "Prop.h"

Prop * Prop::create(PROPTYPE type){
	Prop * prop = new Prop;
	if (prop&&prop->init(type)){
		prop->autorelease();
	}
	else{
		delete prop;
		prop = NULL;
	}
	return prop;
}

bool Prop::init(PROPTYPE type){
	CCSprite::init();
	if (type == BULLET)
		CCSprite::initWithSpriteFrameName("ufo1.png");
	else
		CCSprite::initWithSpriteFrameName("ufo2.png");
	this->_propType = type;

	return true;
}