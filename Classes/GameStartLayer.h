#ifndef _GameStartLayer_H_
#define _GameStartLayer_H_
#include "cocos2d.h"
USING_NS_CC;


class GameStartLayer :public CCLayer
{
public:
	static CCScene * scene();
	virtual bool init();
	CREATE_FUNC(GameStartLayer);
private:
	void loadSpriteCacheAndMusic();
	void addAnimation();
	void startGame();
};

#endif