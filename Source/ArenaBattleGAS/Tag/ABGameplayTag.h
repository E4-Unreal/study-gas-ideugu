#pragma once

#include "NativeGameplayTags.h"

namespace ABGameplayTags
{
    namespace Actor
    {
        namespace Action
        {
            UE_DECLARE_GAMEPLAY_TAG_EXTERN(Rotate)
        }

        namespace State
        {
            UE_DECLARE_GAMEPLAY_TAG_EXTERN(Rotating)
        }
    }

    namespace Character
    {
        namespace Action
        {
            UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttackHitCheck)
        }

        namespace State
        {
            UE_DECLARE_GAMEPLAY_TAG_EXTERN(Jumping)
            UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attacking)
        }
    }
}
