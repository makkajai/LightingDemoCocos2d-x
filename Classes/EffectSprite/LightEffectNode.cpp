
/*
 * based on cocos2d-x-3.6/tests/cpp-tests/Classes/ShaderTest/ShaderTest2.cpp
 * based on CodeAndWeb https://www.codeandweb.com/spriteilluminator
 * extended by Kotaiba Jabkji
 */
#include "LightEffectNode.h"
#include "EffectSprite.h"
#include "BaseLightSource.h"
#include "LightEffect.h"
#include "StringFormat.h"

USING_NS_CC;

namespace effect {

    effect::LightEffectNode *effect::LightEffectNode::createWithGroupsSpecularColorShininess(__String *normalFileName,
            __Array *groups, Color4F specularColor, float shininess, bool isLightsEnabled) {
        effect::LightEffectNode *node = effect::LightEffectNode::create();
        node->setNormalFileName(normalFileName);
        node->setGroups(groups);
        node->setSpecularColor(specularColor);
        node->setShininess(shininess);
        node->setLightEffects(__Array::create());
        node->setIsLightsEnabled(isLightsEnabled);
        return node;
    }


    void LightEffectNode::onEnter() {
        Node::onEnter();
        this->scheduleUpdate();
    }


    void LightEffectNode::update(float delta) {
        Node::update(delta);
        if(!this->getIsLightsEnabled())
            return;

        if(!this->getIsLightEffectAlreadyApplied()) {
            EffectSprite *parentSprite = dynamic_cast<effect::EffectSprite *>(this->getParent());
            if(!parentSprite) return;

            std::vector<BaseLight *> lights = Director::getInstance()->getRunningScene()->getLights();
            if(lights.size() == 0) return ;

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

                                if(source->getAmbientIntensity() > 0.0f) {
                                    const Color3B &aColor = source->getAmbientColor();
                                    float aIntensity = source->getAmbientIntensity();
                                    ambientLight = Color3B(aColor.r * aIntensity, aColor.g * aIntensity, aColor.b * aIntensity);
                                }

                                if(!this->getNormalFileName()) {
                                    parentSprite->setColor(ambientLight);
                                    break;
                                }
                                LightEffect *lightEffect = LightEffect::create();
                                Vec2 position = source->getPosition();
                                float cutoffRadius = source->getCutoffRadius();
                                float halfRadius = source->getHalfRadius();
                                float brightness = source->getIntensity() > 0? source->getBrightness() : source->getAmbientBrightness();
                                Color3B lightColor = source->getIntensity() > 0? source->getColor() : source->getAmbientColor();

                                lightEffect->setLightPos(Vec3(position.x, position.y, source->getLocalZOrder()));
                                lightEffect->setLightCutoffRadius(cutoffRadius);
                                lightEffect->setLightHalfRadius(halfRadius);
                                lightEffect->setBrightness(brightness);
                                lightEffect->setLightColor(lightColor);

                                parentSprite->addEffect(lightEffect);
                                this->getLightEffects()->addObject(lightEffect);
                                break;

                        }
                }
            }
            if(this->getNormalFileName()) {
                if(!contains(this->getNormalFileName()->getCString(), "/"))
                    parentSprite->initLampWithSpriteFrameName(this->getNormalFileName()->getCString(), ambientLight);
                else
                    parentSprite->initLamp(this->getNormalFileName()->getCString(), ambientLight);
            }
            this->setIsLightEffectAlreadyApplied(true);
            this->unscheduleUpdate();
        }
    }

    void LightEffectNode::onExit() {
        CC_SAFE_RELEASE_NULL(lightEffects);
        Node::onExit();
    }


    LightEffectNode::~LightEffectNode() {
        CC_SAFE_RELEASE_NULL(lightEffects);
        CC_SAFE_RELEASE_NULL(normalFileName);
        CC_SAFE_RELEASE_NULL(groups);
    }
}

