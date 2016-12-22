#include "GameStartLayer.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"




CCScene * GameStartLayer::scene(){
	CCScene* scene = CCScene::create();
	scene->addChild(create());
	return scene;
}
bool GameStartLayer::init(){
	CCLayer::init();
	loadSpriteCacheAndMusic();
	addAnimation();
	return true;
}

void GameStartLayer::addAnimation(){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.wav");
	//开始这个场景的背景
	CCSprite * spriteBackground = CCSprite::createWithSpriteFrameName("background.png");
	spriteBackground->ignoreAnchorPointForPosition(true);
	spriteBackground->setPosition(ccp(0, 0));
	addChild(spriteBackground);
	//添加灰机大战的logo
	CCSprite * spriteCopyright = CCSprite::createWithSpriteFrameName("shoot_copyright.png");
	spriteCopyright->setAnchorPoint(ccp(0.5, 0));
	spriteCopyright->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	addChild(spriteCopyright);
	//添加动画
	CCSprite * spriteLoading = CCSprite::createWithSpriteFrameName("game_loading1.png");
	spriteLoading->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 50));
	addChild(spriteLoading);
	CCAnimation * animationLoading = CCAnimation::create();
	animationLoading->setDelayPerUnit(0.2f);
	animationLoading->setLoops(3);
	animationLoading->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
	animationLoading->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading2.png"));
	animationLoading->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading3.png"));
	CCAnimate * animateLoading = CCAnimate::create(animationLoading);

	CCCallFunc * startGame = CCCallFunc::create(this, callfunc_selector(GameStartLayer::startGame));

	CCSequence * sequence = CCSequence::create(animateLoading, startGame, NULL);

	spriteLoading->runAction(sequence);
}

void GameStartLayer::loadSpriteCacheAndMusic(){
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot_background.plist");

	CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->sharedEngine()->preloadBackgroundMusic("sound/game_music.wav");
	
	
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/achievement.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/big_spaceship_flying.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/bullet.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/button.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/enemy1_down.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/enemy2_down.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/enemy3_down.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/game_over.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/get_bomb.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/get_double_laser.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/out_porp.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/use_bomb.wav");
}

void GameStartLayer::startGame(){
	CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
}