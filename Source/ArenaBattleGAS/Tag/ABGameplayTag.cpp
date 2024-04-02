
#include "ABGameplayTag.h"

namespace ABGameplayTags
{
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
        }
    }
}
