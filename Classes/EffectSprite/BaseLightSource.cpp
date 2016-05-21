/**
 * Autogenerated by ObjCToCppTranslator on 24/03/2016
 * @author Deep Shah
 * (c) 2015 Makkajai
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */

//
// Created by batman on 21/06/15.
//

#include "BaseLightSource.h"
#include "LightSourceDetail.h"


USING_NS_CC;


bool BaseLightSource::initWithLightSourceDetail(LightSourceDetail * detail) {
    this->setGroups(detail->getGroups());
    return true;
}


void BaseLightSource::onExit() {
    CC_SAFE_RELEASE_NULL(groups);
    BaseLight::onExit();
}


BaseLightSource::~BaseLightSource() {
    CC_SAFE_RELEASE_NULL(groups);
}

