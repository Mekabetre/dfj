#ifndef _PropsLayer_H_
#define _PropsLayer_H_

#include "cocos2d.h"
#include "Prop.h"
USING_NS_CC;

class PropsLayer :public CCLayer
{
public:
	CREATE_FUNC(PropsLayer);
	bool init();

	void startAddProps();
	void scheduleAddProps(float dt);

	void removePropCallBack(CCNode * node);

	CCArray * props;
};

#endif