#include "Enemy.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"



Enemy * Enemy::create(DEGREE degree){
	Enemy * enemy = new Enemy;
	if (enemy&&enemy->init(degree)){
		enemy->autorelease();
	}
	else{
		delete enemy;
		enemy = NULL;
	}
	return enemy;
}

bool Enemy::init(DEGREE degree){
	setDegree(degree);
	switch (degree)
	{
	case LOW:
		setLife(1);
		CCSprite::initWithSpriteFrameName("enemy1.png");
		break;
	case MIDDLE:
		CCSprite::initWithSpriteFrameName("enemy2.png");
		setLife(3);
		break;
	case HIGH:
		CCSprite::initWithSpriteFrameName("enemy3_n1.png");
		CCAnimation * animation = CCAnimation::create();
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n1.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n2.png"));
		animation->setDelayPerUnit(0.2f);
		animation->setLoops(-1);
		CCAnimate * animate = CCAnimate::create(animation);
		animate->setTag(999);
		this->runAction(animate);
		setLife(7);
		break;
	}
	return true;
}

CCRect Enemy::getBoundingBox(){
	CCRect boundingBox = this->boundingBox();
	boundingBox.origin = convertToWorldSpace(boundingBox.origin);
	return boundingBox;
}

void Enemy::setHit(){
	switch (_degree)
	{
	case MIDDLE:
		setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_hit.png"));
		break;
	case HIGH:
		stopActionByTag(999);
		setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_hit.png"));
		break;
	}
}
void Enemy::boom(){
	CCAnimation * animation = animation = CCAnimation::create();
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	switch (_degree)
	{
	case LOW:
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down1.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down2.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down3.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down4.png"));
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy1_down.wav");
		break;
	case MIDDLE:
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down1.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down2.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down3.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down4.png"));
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy2_down.wav");
		break;
	case HIGH:
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down1.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down2.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down3.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down4.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down5.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down6.png"));
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy3_down.wav");
		break;
	}
	stopAllActions();
	CCCallFuncN * callback = CCCallFuncN::create(this, callfuncN_selector(Enemy::removeFromParentAndCleanCallback));

	runAction(CCSequence::create(CCAnimate::create(animation), callback, NULL));
}

void Enemy::removeFromParentAndCleanCallback(CCNode * node){
	node->removeFromParentAndCleanup(true);
}