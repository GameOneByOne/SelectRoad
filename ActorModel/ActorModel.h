#pragma once

#include "ActorModel/Actor.h"

class ActorFactory {
public:
    static Actor Generate(const ActorName &name);

private:
    static Actor CreateActor(const ActorModel &model);
    static ActorModel GetActorModel(const ActorName &name);
};
