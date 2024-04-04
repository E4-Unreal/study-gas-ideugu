
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
            UE_DEFINE_GAMEPLAY_TAG(Damage, "GameplayCue.Character.Damage")
        }

        namespace Chest
        {
            UE_DEFINE_GAMEPLAY_TAG(Open, "GameplayCue.Chest.Open")
        }
    }

    namespace Event
    {
        namespace Character
        {
            namespace Weapon
            {
                UE_DEFINE_GAMEPLAY_TAG(Equip, "Event.Character.Weapon.Equip")
                UE_DEFINE_GAMEPLAY_TAG(Unequip, "Event.Character.Weapon.Unequip")
            }

            namespace HitCheck
            {
                UE_DEFINE_GAMEPLAY_TAG(Attack, "Event.Character.HitCheck.Attack")
                UE_DEFINE_GAMEPLAY_TAG(Skill, "Event.Character.HitCheck.Skill")
            }
        }
    }

    namespace Cooldown
    {
        namespace Character
        {
            UE_DEFINE_GAMEPLAY_TAG(Skill, "Cooldown.Character.Skill")
        }
    }
}
