#include "GameOverLayer.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"

#include "AppMacros.h"

CCScene * GameOverLayer::scene(int score){
	CCScene * scene = CCScene::create();
	scene->addChild(create(score));
	return scene;
}

GameOverLayer * GameOverLayer::create(int score)
{
	GameOverLayer *pRet = new GameOverLayer();
	if (pRet && pRet->init(score))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool GameOverLayer::init(int score){
	CCLayer::init();

	addBackground(score);

	setKeypadEnabled(true);
	return true;
}

void GameOverLayer::addBackground(int score){
	CCSprite * back = CCSprite::createWithSpriteFrameName("gameover.png");
	back->ignoreAnchorPointForPosition(true);
	back->setPosition(ccp(0, -52));
	addChild(back);

	CCLabelBMFont * label = CCLabelBMFont::create(CCString::createWithFormat("%d", score)->getCString(), "font/font.fnt");
	label->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	label->setColor(ccc3(143, 146, 147));
	addChild(label);

	int maxScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("maxScore", 0);
	if (score > maxScore){
		CCUserDefault::sharedUserDefault()->setIntegerForKey("maxScore", score);
		maxScore = score;
	}

	CCLabelBMFont * maxScoreLabel = CCLabelBMFont::create(CCString::createWithFormat("%d", maxScore)->getCString(), "font/font.fnt");
	maxScoreLabel->setAnchorPoint(ccp(0, 0));
	maxScoreLabel->setPosition(ccp(150, winSize.height - 65));
	maxScoreLabel->setColor(ccc3(143, 146, 147));
	addChild(maxScoreLabel);

	CCMenuItem * menuBack = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("btn_finish.png"), CCSprite::createWithSpriteFrameName("btn_finish.png"), this, menu_selector(GameOverLayer::backToGameCallBack));
	CCMenu* pMenu = CCMenu::create(menuBack, NULL);
	pMenu->setPositionY(label->getPositionY() - label->boundingBox().size.height / 2 - menuBack->boundingBox().size.height - 20);
	addChild(pMenu);

}

void GameOverLayer::backToGameCallBack(CCObject *obj){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.wav");
	CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
}


void GameOverLayer::keyBackClicked(){
	if (!getChildByTag(1111)){
		CCLabelTTF * label = CCLabelTTF::create();
		label->setFontSize(30);
		label->setFontName("Courier New");
		label->setString("Touch again to exit");
		label->setFontFillColor(ccc3(143, 146, 147), true);
		label->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		label->_setZOrder(100);
		label->setTag(1111);
		addChild(label);

		scheduleOnce(schedule_selector(GameLayer::removeNoticeSchedule), 1);

		return;
	}
	else{
		exit(1);
	}
}

void GameOverLayer::removeNoticeSchedule(float dt){
	if (getChildByTag(1111)){
		removeChildByTag(1111, true);
	}
}