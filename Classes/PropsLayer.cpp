#include "PropsLayer.h"
#include "SimpleAudioEngine.h"


bool PropsLayer::init(){
	CCLayer::init();
	props = CCArray::create();
	props->retain();

	startAddProps();

	return true;
}

void  PropsLayer::startAddProps(){
	schedule(schedule_selector(PropsLayer::scheduleAddProps), 5);
}

void PropsLayer::scheduleAddProps(float dt){
	Prop * propSprite;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int nextProp = rand() % 9 + 1;
	if (nextProp <= 3)
		propSprite = Prop::create(BULLET);
	else
		propSprite = Prop::create(BOOM);

	propSprite->setPosition(ccp(CCRANDOM_0_1()*winSize.width, winSize.height + propSprite->boundingBox().size.height / 2));
	if (propSprite->boundingBox().size.width / 2 > propSprite->getPositionX())
		propSprite->setPositionX(propSprite->getPositionX() + propSprite->boundingBox().size.width / 2);
	if (propSprite->boundingBox().size.width / 2 + propSprite->getPositionX() > winSize.height)
		propSprite->setPositionX(propSprite->getPositionX() - propSprite->boundingBox().size.width / 2);

	CCMoveBy * by1 = CCMoveBy::create(0.5f, ccp(0, -150));
	CCMoveBy * by2 = CCMoveBy::create(0.3f, ccp(0, 100));
	CCMoveBy * by3 = CCMoveBy::create(1.0f, ccp(0, 0 - winSize.height - propSprite->boundingBox().size.height / 2 - 10));
	CCCallFuncN * removeCallFunc = CCCallFuncN::create(this, callfuncN_selector(PropsLayer::removePropCallBack));
	CCSequence * sequence = CCSequence::create(by1, by2, by3, removeCallFunc, NULL);
	propSprite->runAction(sequence);

	props->addObject(propSprite);
	addChild(propSprite);
}


void PropsLayer::removePropCallBack(CCNode * node){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/out_porp.wav");
	props->removeObject(node);
	node->removeFromParentAndCleanup(true);
}