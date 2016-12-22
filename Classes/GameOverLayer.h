#ifndef _GameOverLayer_H_
#define _GameOverLayer_H_
#include "cocos2d.h"
USING_NS_CC;

class GameOverLayer :public CCLayer
{
public:
	static CCScene * scene(int score);
	static GameOverLayer* create(int score);
	bool init(int score);
	void backToGameCallBack(CCObject *);

	void addBackground(int score);


	void keyBackClicked();
	void removeNoticeSchedule(float dt);
};

#endif