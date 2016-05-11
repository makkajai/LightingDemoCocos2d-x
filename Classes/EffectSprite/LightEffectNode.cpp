
/*
 * based on cocos2d-x-3.6/tests/cpp-tests/Classes/ShaderTest/ShaderTest2.cpp
 * based on CodeAndWeb https://www.codeandweb.com/spriteilluminator
 * extended by Kotaiba Jabkji
 */
#include "LightEffectNode.h"
#include "EffectSprite.h"
#include "BaseLightSource.h"
#include "LightEffect.h"

USING_NS_CC;

namespace effect {

    effect::LightEffectNode *effect::LightEffectNode::createWithGroupsSpecularColorShininess(__String *normalFileName,
            __Array *groups, Color4F specularColor, float shininess) {
        effect::LightEffectNode *node = effect::LightEffectNode::create();
        node->setNormalFileName(normalFileName);
        node->setGroups(groups);
        node->setSpecularColor(specularColor);
        node->setShininess(shininess);
        return node;
    }


    void LightEffectNode::onEnter() {
        Node::onEnter();
        this->scheduleUpdate();
    }


    void LightEffectNode::update(float delta) {
        Node::update(delta);

        if(!this->getIsLightEffectAlreadyApplied()) {
            EffectSprite *parentSprite = dynamic_cast<effect::EffectSprite *>(this->getParent());
            if(!parentSprite) return;

            std::vector<BaseLight *> lights = Director::getInstance()->getRunningScene()->getLights();
            if(lights.size() == 0) return ;

            CCLOGWARN("#########Got the on NEter: %d", lights.size());
            Color3B ambientLight = Color3B::WHITE;
            for(BaseLight *light : lights) {
                BaseLightSource *source = dynamic_cast<BaseLightSource *>(light);
                if(!source) continue;

                Ref *lightgroup_ref = nullptr;
                Ref *group_ref = nullptr;
                __Array *lightGroups = source->getGroups();
                CCARRAY_FOREACH(lightGroups, lightgroup_ref) {
                        __String *lightgroup = dynamic_cast<__String *>(lightgroup_ref);
                        CCARRAY_FOREACH(groups, group_ref) {
                                __String *group = dynamic_cast<__String *>(group_ref);
                                if(!lightgroup->isEqual(group))
                                    continue;

                                if(!this->getNormalFileName()) {
                                    parentSprite->setColor(source->getAmbientColor());
                                    break;
                                }
                                LightEffect *lightEffect = LightEffect::create();
                                lightEffect->setLightPos(Vec3(source->getPosition().x,
                                        source->getPosition().y, source->getLocalZOrder()));
                                lightEffect->setLightCutoffRadius(source->getCutoffRadius());
                                lightEffect->setLightHalfRadius(source->getHalfRadius());
                                lightEffect->setBrightness(source->getIntensity() > 0? source->getIntensity() : source->getAmbientIntensity());
                                lightEffect->setLightColor(source->getIntensity() > 0? source->getColor() : source->getAmbientColor());

                                parentSprite->addEffect(lightEffect);
                                break;

                        }
                }
                if(source->getAmbientIntensity() > 0.0f) {
                    ambientLight = source->getAmbientColor();
                }
            }
            if(this->getNormalFileName())
                parentSprite->initLampWithSpriteFrameName(this->getNormalFileName()->getCString(), ambientLight);
            this->setIsLightEffectAlreadyApplied(true);
        }
    }


}

