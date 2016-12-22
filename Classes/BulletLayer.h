#ifndef _BulletLayer_H_
#define _BulletLayer_H_
#include "cocos2d.h"
USING_NS_CC;

class BulletLayer :public CCLayer
{
public:
	static CCScene * scene();
	CREATE_FUNC(BulletLayer);
	bool init();

	void startShoot();
	void stopShoot();

	void scheduleCallBack(float dt);
	void removeBulletCallBack(CCNode * node);

	void removeBullet(CCSprite * sprite);
	CCArray * _bullets;
public:
	bool isBigBullet;
	int oneBulletLoseLife;

private:
	CCSpriteBatchNode * _bulletBatchNode;
};

#endif