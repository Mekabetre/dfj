#ifndef _EnemyLayer_H_
#define _EnemyLayer_H_
#include "cocos2d.h"
USING_NS_CC;

class EnemyLayer :public CCLayer
{
public:
	static CCScene * scene();
	CREATE_FUNC(EnemyLayer);
	bool init();
	void onExit();

	void removeEnemyCallback(CCNode *);
	void stopSchedule();

	void addEnemy(float);

	void letAllEnemiesBoom();

	CCArray * enemies;
};

#endif