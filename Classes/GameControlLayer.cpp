#include "GameControlLayer.h"
#include "Plane.h"
#include "SimpleAudioEngine.h"


CCScene * GameControlLayer::scene(){
	CCScene* scene = CCScene::create();
	scene->addChild(create());
	return scene;
}

bool GameControlLayer::init(){
	CCLayer::init();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	scoreLabel = CCLabelBMFont::create("0", "font/font.fnt");
	scoreLabel->setColor(ccc3(143, 146, 147));
	scoreLabel->setPosition(ccp(winSize.width / 2, winSize.height - scoreLabel->boundingBox().size.height / 2 - 10));

	pauseMenuItem = CCMenuItemSprite::create(
		CCSprite::createWithSpriteFrameName("game_pause_nor.png"),
		CCSprite::createWithSpriteFrameName("game_pause_pressed.png"),
		this,
		menu_selector(GameControlLayer::clickPauseMenuCallBack)
		);
	CCMenu * menu = CCMenu::create(pauseMenuItem, NULL);
	menu->setPosition(ccp(pauseMenuItem->boundingBox().size.width / 2 + 10,
		CCDirector::sharedDirector()->getWinSize().height - pauseMenuItem->boundingBox().size.height / 2 - 10));
	addChild(menu);

	addChild(scoreLabel);

	return true;
}


void GameControlLayer::clickPauseMenuCallBack(CCObject * obj){
	if (!CCDirector::sharedDirector()->isPaused())
	{
		pauseMenuItem->setNormalImage(CCSprite::createWithSpriteFrameName("game_resume_nor.png"));
		pauseMenuItem->setSelectedImage(CCSprite::createWithSpriteFrameName("game_resume_pressed.png"));


		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		CCDirector::sharedDirector()->pause();
		((CCLayer*)(Plane::getPlane()->getParent()))->setTouchEnabled(false);
	}
	else
	{
		pauseMenuItem->setNormalImage(CCSprite::createWithSpriteFrameName("game_pause_nor.png"));
		pauseMenuItem->setSelectedImage(CCSprite::createWithSpriteFrameName("game_pause_pressed.png"));

		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		CCDirector::sharedDirector()->resume();
		((CCLayer*)(Plane::getPlane()->getParent()))->setTouchEnabled(true);
	}
}


void GameControlLayer::updateScore(int score){
	CCString * strScore = CCString::createWithFormat("%d", score);
	scoreLabel->setCString(strScore->getCString());
}