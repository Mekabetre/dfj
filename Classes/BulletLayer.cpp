#include "BulletLayer.h"
#include "Plane.h"

#include "AppMacros.h"

CCScene * BulletLayer::scene(){
	CCScene * scene = CCScene::create();
	scene->addChild(create());
	return scene;
}
bool BulletLayer::init(){
	CCLayer::init();

	isBigBullet = false;
	oneBulletLoseLife = 1;

	_bullets = CCArray::create();
	_bullets->retain();

	_bulletBatchNode = CCSpriteBatchNode::create("ui/shoot.png");
	addChild(_bulletBatchNode);

	startShoot();
	return true;
}


void BulletLayer::startShoot(){
	schedule(schedule_selector(BulletLayer::scheduleCallBack), 0.15f);
}

void BulletLayer::stopShoot(){
	unschedule(schedule_selector(BulletLayer::scheduleCallBack));
}

void BulletLayer::scheduleCallBack(float dt){
	CCSprite * bulletSprite;
	if (!isBigBullet)
		bulletSprite = CCSprite::createWithSpriteFrameName("bullet1.png");
	else
		bulletSprite = CCSprite::createWithSpriteFrameName("bullet2.png");

	CCPoint startPosition = Plane::getPlane()->getPosition();
	startPosition.y = startPosition.y + Plane::getPlane()->boundingBox().size.height / 2 + 5;
	bulletSprite->setPosition(startPosition);
	_bulletBatchNode->addChild(bulletSprite);
	_bullets->addObject(bulletSprite);

	float time = (winSize.height - bulletSprite->boundingBox().origin.y) / winSize.height * 2;
	CCMoveBy * toDispear = CCMoveBy::create(time, ccp(0, winSize.height + bulletSprite->boundingBox().size.height / 2));

	CCCallFuncN* removebulletCallFunc = CCCallFuncN::create(this, callfuncN_selector(BulletLayer::removeBulletCallBack));

	CCSequence * sequence = CCSequence::create(toDispear, removebulletCallFunc, NULL);
	bulletSprite->runAction(sequence);
}

void BulletLayer::removeBulletCallBack(CCNode * node){
	_bulletBatchNode->removeChild(node, true);
	_bullets->removeObject(node);
}

void BulletLayer::removeBullet(CCSprite * sprite){
	_bulletBatchNode->removeChild(sprite, true);
	_bullets->removeObject(sprite);
}