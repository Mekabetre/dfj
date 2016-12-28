#include "EnemyLayer.h"
#include "Enemy.h"

#include "AppMacros.h"

CCScene * EnemyLayer::scene(){
	CCScene * scene = CCScene::create();
	scene->addChild(create());
	return scene;
}

bool EnemyLayer::init(){
	CCLayer::init();
	enemies = CCArray::create();
	enemies->retain();


	schedule(schedule_selector(EnemyLayer::addEnemy), 0.5f);
	return true;
}
void EnemyLayer::onExit(){
	CCLayer::onExit();
	enemies->release();
}

void EnemyLayer::addEnemy(float dt){
	Enemy * enemy;

	int nextEnemy = rand() % 9 + 1;
	if (nextEnemy == 1)
		enemy = Enemy::create(HIGH);
	else if (nextEnemy >= 2 && nextEnemy <= 4)
		enemy = Enemy::create(MIDDLE);
	else
		enemy = Enemy::create(LOW);

	enemies->addObject(enemy);
	addChild(enemy);

	float x = CCRANDOM_0_1() *  winSize.width;
	if (x - enemy->boundingBox().size.width / 2 < 0)
		x += enemy->boundingBox().size.width / 2;
	if (x + enemy->boundingBox().size.width / 2 > winSize.width)
		x -= enemy->boundingBox().size.width / 2;
	enemy->setPositionX(x);
	enemy->setPositionY(winSize.height + enemy->boundingBox().size.height / 2);

	CCMoveBy * by = CCMoveBy::create(rand() % 4 + 2, ccp(0, 0 - winSize.height - enemy->boundingBox().size.height));
	CCCallFuncN * removeCallFunN = CCCallFuncN::create(this, callfuncN_selector(EnemyLayer::removeEnemyCallback));

	CCSequence *sequence = CCSequence::create(by, removeCallFunN, NULL);

	enemy->runAction(sequence);
}

void EnemyLayer::removeEnemyCallback(CCNode * node){
	node->removeFromParentAndCleanup(true);
	enemies->removeObject(node);
}
void EnemyLayer::stopSchedule(){
	unscheduleAllSelectors();
}

void EnemyLayer::letAllEnemiesBoom(){
	
}
