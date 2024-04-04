#pragma once

#include "NativeGameplayTags.h"

namespace ABGameplayTags
{
    namespace Data
    {
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage)
    }

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
            UE_DECLARE_GAMEPLAY_TAG_EXTERN(Dead)
            UE_DECLARE_GAMEPLAY_TAG_EXTERN(Invincible)
        }
    }

    namespace GameplayCue
    {
        namespace Character
        {
            UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttackHit)
            UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage)
        }

        namespace Chest
        {
            UE_DECLARE_GAMEPLAY_TAG_EXTERN(Open)
        }
    }

    namespace Event
    {
        namespace Character
        {
            namespace Weapon
            {
                UE_DECLARE_GAMEPLAY_TAG_EXTERN(Equip)
                UE_DECLARE_GAMEPLAY_TAG_EXTERN(Unequip)
            }
        }
    }
}
