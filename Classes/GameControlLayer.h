#ifndef _GameControlLayer_H_
#define _GameControlLayer_H_
#include "cocos2d.h"
USING_NS_CC;

class GameControlLayer : public CCLayer
{
public:
	static CCScene * scene();
	CREATE_FUNC(GameControlLayer);
	bool init();

	void clickPauseMenuCallBack(CCObject * obj);
	void updateScore(int score);
private:
	CCMenuItemSprite * pauseMenuItem;
	CCLabelBMFont * scoreLabel;
};

#endif