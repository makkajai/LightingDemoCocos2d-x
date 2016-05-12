/*
 * based on cocos2d-x-3.6/tests/cpp-tests/Classes/ShaderTest/ShaderTest2.cpp
 * based on CodeAndWeb https://www.codeandweb.com/spriteilluminator
 * extended by Kotaiba Jabkji
 */

#ifndef _LIGHTEFFECTNODE_H_
#define _LIGHTEFFECTNODE_H_

#include "Effect.h"
#include "LightEffect.h"
USING_NS_CC;

namespace effect {

    class LightEffectNode : public cocos2d::Node {

    public:
        CC_SYNTHESIZE_RETAIN(__String *, normalFileName, NormalFileName)

        virtual void onExit() override;


        virtual void onEnter() override;


        virtual void update(float delta) override;


        CC_SYNTHESIZE_RETAIN(__Array *, groups, Groups);
        CC_SYNTHESIZE_RETAIN(__Array *, lightEffects, LightEffects);
        CC_SYNTHESIZE(Color4F, specularColor, SpecularColor);
        CC_SYNTHESIZE(float, shininess, Shininess);
        CC_SYNTHESIZE(bool, isLightEffectAlreadyApplied, IsLightEffectAlreadyApplied);

        static LightEffectNode *createWithGroupsSpecularColorShininess(__String *normalFileName, __Array *groups, Color4F specularColor, float shininess);

        CREATE_FUNC(LightEffectNode);
    };
}
#endif
