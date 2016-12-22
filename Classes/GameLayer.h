#ifndef _GameLayer_H_
#define _GameLayer_H_

#include "cocos2d.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"
#include "Enemy.h"
#include "GameControlLayer.h"
#include "PropsLayer.h"
USING_NS_CC;

const int PROPTAG = 999;
const int PROPCOUNTTAGE = 9999;

class GameLayer : public CCLayer
{
public:
	static CCScene * scene();
	CREATE_FUNC(GameLayer);
	bool init();
	void addBackground();
	void updateBackground();
	void checkEnemyKnocking();
	void checkPropsKnocking();
	void updatePropDisplay();

	void boomClickedCallBack(CCObject *obj);


	void update(float);
	void keyBackClicked();
	void removeNoticeSchedule(float dt);

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	enum BACKGROUND{
		BACK1,
		BACK2
	};
private:
	int score;
	int propCount;

	void addPlane();
	void addBullet();
	void addEnemy();
	void addControlLayer();
	void addPropsLayer();
private:
	BulletLayer * bulletLayer;
	EnemyLayer * enemyLayer;
	GameControlLayer * gameControlLayer;
	PropsLayer * propsLayer;
};

#endif