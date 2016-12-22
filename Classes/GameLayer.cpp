#include "GameLayer.h"
#include "Plane.h"
#include "GameControlLayer.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"

CCScene * GameLayer::scene(){
	CCScene * scene = CCScene::create();
	scene->addChild(create());
	return scene;
}

bool GameLayer::init(){
	score = 0;
	propCount = 0;

	CCLayer::init();
	addBackground();
	addPlane();
	addBullet();
	addEnemy();
	addControlLayer();
	addPropsLayer();

	scheduleUpdate();

	setKeypadEnabled(true);
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
	return true;
}

void GameLayer::keyBackClicked(){
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

void GameLayer::removeNoticeSchedule(float dt){
	if (getChildByTag(1111)){
		removeChildByTag(1111, true);
	}
}

void GameLayer::addPlane(){
	CCSprite * plane = Plane::getPlane();
	plane->setPosition(ccp(200, 200));
	addChild(plane);
}

void GameLayer::addBackground(){
	CCSprite * backSprite1 = CCSprite::createWithSpriteFrameName("background.png");
	CCSprite * backSprite2 = CCSprite::createWithSpriteFrameName("background.png");

	backSprite1->setTag(BACK1);
	backSprite2->setTag(BACK2);

	backSprite1->ignoreAnchorPointForPosition(true);
	backSprite2->ignoreAnchorPointForPosition(true);

	backSprite1->setPosition(ccp(0, 0));
	backSprite2->setPosition(ccp(0, 0));
	backSprite2->setPositionY(backSprite1->getPositionY() + backSprite1->boundingBox().size.height - 2);

	addChild(backSprite1);
	addChild(backSprite2);
}

void GameLayer::update(float dt){
	updateBackground();
	checkEnemyKnocking();
	checkPropsKnocking();
}

void GameLayer::updateBackground(){
	CCSprite * backSprite1 = (CCSprite *)getChildByTag(BACK1);
	CCSprite * backSprite2 = (CCSprite *)getChildByTag(BACK2);

	backSprite1->setPositionY(backSprite1->getPositionY() - 2);
	backSprite2->setPositionY(backSprite1->getPositionY() + backSprite1->boundingBox().size.height - 2);
	if (backSprite2->getPositionY() <= 0)
		backSprite1->setPositionY(0);
}

bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	CCRect planeRect = Plane::getPlane()->boundingBox();
	planeRect.setRect(planeRect.origin.x - 10, planeRect.origin.y - 10, planeRect.size.width + 20, planeRect.size.height + 20);
	if (planeRect.containsPoint(pTouch->getLocation()))
		return true;
	return false;
}

void GameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
	CCRect allowRect = this->boundingBox();
	Plane * plan = Plane::getPlane();
	allowRect.origin.x = allowRect.origin.x + plan->boundingBox().size.width / 2;
	allowRect.origin.y = allowRect.origin.y + plan->boundingBox().size.height / 2;
	allowRect.size.width = allowRect.size.width - 2 * plan->boundingBox().size.width / 2;
	allowRect.size.height = allowRect.size.height - 2 * plan->boundingBox().size.height / 2;

	if (allowRect.containsPoint(plan->getPosition() + pTouch->getDelta()))
		plan->setPosition(plan->getPosition() + pTouch->getDelta());
}

void GameLayer::addBullet(){
	bulletLayer = BulletLayer::create();
	addChild(bulletLayer);
}

void GameLayer::addEnemy(){
	enemyLayer = EnemyLayer::create();
	addChild(enemyLayer);
}

void GameLayer::addControlLayer(){
	gameControlLayer = GameControlLayer::create();
	addChild(gameControlLayer);
}

void  GameLayer::addPropsLayer(){
	propsLayer = PropsLayer::create();
	addChild(propsLayer);
}



void GameLayer::checkEnemyKnocking(){
	CCArray * enemies = enemyLayer->enemies;
	CCArray * bullets = bulletLayer->_bullets;
	CCObject * en = NULL;
	CCObject * bu = NULL;
	CCARRAY_FOREACH_REVERSE(enemies, en){
		Enemy * enemy = (Enemy *)en;
		//敌人和子弹的碰撞
		CCARRAY_FOREACH_REVERSE(bullets, bu){
			CCSprite * bullet = (CCSprite *)bu;
			if (enemy->boundingBox().intersectsRect(bullet->boundingBox())){
				enemy->setLife(enemy->getLife() - bulletLayer->oneBulletLoseLife);
				if (enemy->getLife() <= 0){
					enemy->boom();
					enemies->removeObject(enemy);
					switch (enemy->getDegree())
					{
					case LOW:
						score += 1;
						break;
					case MIDDLE:
						score += 3;
						break;
					case HIGH:
						score += 7;
						break;
					}
					gameControlLayer->updateScore(score);
					break;
				}
				switch (enemy->getDegree())
				{
				case MIDDLE:
					enemy->setHit();
					break;
				case HIGH:
					if (enemy->getLife() <= 4)
						enemy->setHit();
					break;
				}
				bulletLayer->removeBullet(bullet);
			}
		}

		//敌人和灰机的碰撞
		CCRect planeBoundingBox = Plane::getPlane()->boundingBox();
		planeBoundingBox.size = planeBoundingBox.size - CCSize(40, 30);
		planeBoundingBox.origin = planeBoundingBox.origin + CCPoint(20, 15);
		if (planeBoundingBox.intersectsRect(enemy->boundingBox())){
			bulletLayer->stopShoot();
			enemyLayer->stopSchedule();
			unscheduleAllSelectors();
			Plane::getPlane()->boom(this->score);

			enemy->boom();
			enemies->removeObject(enemy);

			break;
		}
	}

}

void GameLayer::checkPropsKnocking(){
	CCArray * props = propsLayer->props;
	CCObject * obj;
	CCARRAY_FOREACH_REVERSE(props, obj){
		Prop * prop = (Prop *)obj;
		if (Plane::getPlane()->boundingBox().intersectsRect(prop->boundingBox())){
			if (prop->getPropType() == BULLET){
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/get_double_laser.wav");
				bulletLayer->isBigBullet = true;
				bulletLayer->oneBulletLoseLife = 2;
			}
			else{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/get_bomb.wav");
				propCount++;
				updatePropDisplay();
			}
			propsLayer->removePropCallBack(prop);
		}
	}
}

void GameLayer::updatePropDisplay(){
	if (propCount < 0)
		return;
	//没得炸弹就移除显示炸弹的东西
	if (propCount == 0){
		if (getChildByTag(PROPTAG))
			removeChildByTag(PROPTAG, true);
		if (getChildByTag(PROPCOUNTTAGE))
			removeChildByTag(PROPCOUNTTAGE, true);
		return;
	}
	//刚从0变为1
	if (propCount == 1){
		CCSprite * boomSprite1 = CCSprite::createWithSpriteFrameName("bomb.png");
		if (!getChildByTag(PROPTAG)){
			CCSprite * boomSprite2 = CCSprite::createWithSpriteFrameName("bomb.png");
			CCMenuItemSprite * boomMenuItem = CCMenuItemSprite::create(boomSprite1, boomSprite2, this, menu_selector(GameLayer::boomClickedCallBack));
			CCMenu * menu = CCMenu::create(boomMenuItem, NULL);
			menu->setTag(PROPTAG);
			menu->setPosition(ccp(boomMenuItem->boundingBox().size.width / 2, boomMenuItem->boundingBox().size.height / 2));
			addChild(menu);
		}
		if (!getChildByTag(PROPCOUNTTAGE)){
			CCLabelBMFont * propCountLabel = CCLabelBMFont::create(CCString::createWithFormat("%d", propCount)->getCString(), "font/font.fnt");
			propCountLabel->setTag(PROPCOUNTTAGE);
			propCountLabel->setAnchorPoint(ccp(0, 0.5));
			propCountLabel->setPosition(ccp(boomSprite1->getContentSize().width + 15, boomSprite1->getContentSize().height / 2));
			propCountLabel->setColor(ccc3(143, 146, 147));
			addChild(propCountLabel);
		}
		return;
	}

	if (propCount > 1)
		((CCLabelBMFont*)(getChildByTag(PROPCOUNTTAGE)))->setCString(CCString::createWithFormat("%d", propCount)->getCString());
}


void GameLayer::boomClickedCallBack(CCObject *obj){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/use_bomb.wav");
	propCount--;
	updatePropDisplay();

	CCArray * enemies = enemyLayer->enemies;
	CCObject * en;
	CCARRAY_FOREACH_REVERSE(enemies, en){
		Enemy * enemy = (Enemy *)en;
		enemy->boom();
		enemies->removeObject(enemy);
		switch (enemy->getDegree())
		{
		case LOW:
			score += 1;
			break;
		case MIDDLE:
			score += 3;
			break;
		case HIGH:
			score += 7;
			break;
		}
	}

	gameControlLayer->updateScore(score);
}