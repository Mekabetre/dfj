#include "Plane.h"
#include "GameOverLayer.h"
#include "SimpleAudioEngine.h"

Plane * Plane::_plane = NULL;

Plane *  Plane::getPlane(){
	if (_plane)
		return _plane;
	_plane = new Plane();
	if (_plane && _plane->init()){

	}
	else{
		delete _plane;
		_plane = NULL;
	}
	return _plane;
}
bool Plane::init(){
	CCSprite::init();
	initWithSpriteFrameName("hero1.png");
	//布林布林闪三次
	CCBlink * blink = CCBlink::create(1, 3);

	//动画
	CCAnimation * planeAnimation = CCAnimation::create();
	planeAnimation->setDelayPerUnit(0.2f);
	planeAnimation->setLoops(-1);
	planeAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
	planeAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero2.png"));
	CCAnimate * planeAnimate = CCAnimate::create(planeAnimation);

	CCSpawn * spawn = CCSpawn::create(blink, planeAnimate, NULL);
	this->runAction(spawn);

	CCAnimation * boomAnimation = CCAnimation::create();
	boomAnimation->setDelayPerUnit(0.15f);
	boomAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n1.png"));
	boomAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n2.png"));
	boomAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n3.png"));
	boomAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n4.png"));
	CCAnimationCache::sharedAnimationCache()->addAnimation(boomAnimation, "PlaneBlowUp");

	return true;
}

void Plane::boom(int score){
	stopAllActions();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/game_over.wav");
	CCAnimate * animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("PlaneBlowUp"));
	CCDelayTime * delayTime = CCDelayTime::create(0.8);
	CCCallFuncND * removePlane = CCCallFuncND::create(this, callfuncND_selector(Plane::removePlaneCallback), (void *)score);
	CCSequence *sequence = CCSequence::create(animate, delayTime, removePlane, NULL);


	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	runAction(sequence);
}

void Plane::removePlaneCallback(CCNode* node, void *data){
	removeFromParentAndCleanup(true);
	CCDirector::sharedDirector()->replaceScene(GameOverLayer::scene((int)data));

	_plane = NULL;
}