
#include "ABGameplayTag.h"

namespace ABGameplayTags
{
    namespace Data
    {
        UE_DEFINE_GAMEPLAY_TAG(Damage, "Data.Damage")
    }

    namespace Actor
    {
        namespace Action
        {
            UE_DEFINE_GAMEPLAY_TAG(Rotate, "Actor.Action.Rotate")
        }

        namespace State
        {
            UE_DEFINE_GAMEPLAY_TAG(Rotating, "Actor.State.Rotating")
        }
    }

    namespace Character
    {
        namespace Action
        {
            UE_DEFINE_GAMEPLAY_TAG(AttackHitCheck, "Character.Action.AttackHitCheck")
        }

        namespace State
        {
            UE_DEFINE_GAMEPLAY_TAG(Jumping, "Character.State.Jumping")
            UE_DEFINE_GAMEPLAY_TAG(Attacking, "Character.State.Attacking")
            UE_DEFINE_GAMEPLAY_TAG(Dead, "Character.State.Dead")
            UE_DEFINE_GAMEPLAY_TAG(Invincible, "Character.State.Invincible")
        }
    }

    namespace GameplayCue
    {
        namespace Character
        {
            UE_DEFINE_GAMEPLAY_TAG(AttackHit, "GameplayCue.Character.AttackHit")
        }

        namespace Chest
        {
            UE_DEFINE_GAMEPLAY_TAG(Open, "GameplayCue.Chest.Open")
        }
    }
}
