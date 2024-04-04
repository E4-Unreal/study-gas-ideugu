// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGASPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "Attribute/ABGASCharacterAttributeSet.h"
#include "Player/ABGASPlayerState.h"
#include "Tag/ABGameplayTag.h"
#include "UI/ABGASWidgetComponent.h"

AABGASPlayerCharacter::AABGASPlayerCharacter()
{
    static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ArenaBattleGAS/Animation/AM_ComboAttack.AM_ComboAttack'"));
    if (ComboActionMontageRef.Object)
    {
    	ComboActionMontage = ComboActionMontageRef.Object;
    }

    HpBar = CreateDefaultSubobject<UABGASWidgetComponent>(TEXT("HpBar"));
    HpBar->SetupAttachment(GetMesh());
    HpBar->SetRelativeLocation(FVector(0.f, 0.f, 180.f));
    static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ArenaBattle/UI/WBP_HpBar.WBP_HpBar_C'"));
    if(HpBarWidgetRef.Class)
    {
        HpBar->SetWidgetClass(HpBarWidgetRef.Class);
        HpBar->SetWidgetSpace(EWidgetSpace::Screen);
        HpBar->SetDrawSize(FVector2D(200.f, 20.f));
        HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blunt/Blunt_Hellhammer/SK_Blunt_HellHammer.SK_Blunt_HellHammer'"));
    if(WeaponMeshRef.Object)
    {
        WeaponMesh = WeaponMeshRef.Object;
    }

    WeaponRange = 75.f;
    WeaponRate = 100.f;

    static ConstructorHelpers::FObjectFinder<UAnimMontage> SkillMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ArenaBattleGAS/Animation/AM_SkillAttack.AM_SkillAttack'"));
    if(SkillMontageRef.Object)
    {
        SkillMontage = SkillMontageRef.Object;
    }
}

void AABGASPlayerCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    if(AABGASPlayerState* PS = GetPlayerState<AABGASPlayerState>())
    {
        // ASC 레퍼런스 주입
        AbilitySystem = PS->GetAbilitySystemComponent();

        // ASC 초기화
        AbilitySystem->InitAbilityActorInfo(PS, this);
        const UABGASCharacterAttributeSet* CharacterAttributes = AbilitySystem->GetSet<UABGASCharacterAttributeSet>();
        CharacterAttributes->OnOutOfHealth.AddDynamic(this, &ThisClass::OnOutOfHealthCallBack);

        // 게임플레이 이벤트
        AbilitySystem->GenericGameplayEventCallbacks.FindOrAdd(ABGameplayTags::Event::Character::Weapon::Equip)
        .AddUObject(this, &ThisClass::EquipWeaponCallback);

        AbilitySystem->GenericGameplayEventCallbacks.FindOrAdd(ABGameplayTags::Event::Character::Weapon::Unequip)
        .AddUObject(this, &ThisClass::UnequipWeaponCallback);

        // 기본 GA 부여
        for(const auto& DefaultAbility : DefaultAbilities)
        {
            FGameplayAbilitySpec GameplayAbilitySpec = AbilitySystem->BuildAbilitySpecFromClass(DefaultAbility);
            AbilitySystem->GiveAbility(GameplayAbilitySpec);
        }

        // 기본 입력 GA 부여
        for (const auto& [DefaultInputID, DefaultAbility] : DefaultInputAbilities)
        {
            FGameplayAbilitySpec GameplayAbilitySpec = AbilitySystem->BuildAbilitySpecFromClass(DefaultAbility);
            GameplayAbilitySpec.InputID = DefaultInputID;
            AbilitySystem->GiveAbility(GameplayAbilitySpec);
        }
    }
}

void AABGASPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    SetupGasInputComponent();
}

void AABGASPlayerCharacter::SetupGasInputComponent()
{
    if(AbilitySystem.IsValid() && IsValid(InputComponent))
    {
        UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, AbilitySystem.Get(), &UAbilitySystemComponent::PressInputID, 0);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, AbilitySystem.Get(), &UAbilitySystemComponent::ReleaseInputID, 0);
        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, AbilitySystem.Get(), &UAbilitySystemComponent::PressInputID, 1);
        EnhancedInputComponent->BindAction(SkillAction, ETriggerEvent::Triggered, AbilitySystem.Get(), &UAbilitySystemComponent::PressInputID, 2);
    }
}

void AABGASPlayerCharacter::OnOutOfHealthCallBack()
{
    SetDead();
}

void AABGASPlayerCharacter::EquipWeaponCallback(const FGameplayEventData* EventData)
{
    if(Weapon)
    {
        Weapon->SetSkeletalMesh(WeaponMesh);

        FGameplayAbilitySpec NewSkillSpec(SkillAbilityClass);
        NewSkillSpec.InputID = 2;
        if(!AbilitySystem->FindAbilitySpecFromClass(SkillAbilityClass))
        {
            AbilitySystem->GiveAbility(NewSkillSpec);
        }

        const float CurrentAttackRange = AbilitySystem->GetNumericAttributeBase(UABGASCharacterAttributeSet::GetAttackRangeAttribute());
        const float CurrentAttackRate = AbilitySystem->GetNumericAttributeBase(UABGASCharacterAttributeSet::GetAttackRateAttribute());

        AbilitySystem->SetNumericAttributeBase(UABGASCharacterAttributeSet::GetAttackRangeAttribute(), CurrentAttackRange + WeaponRange);
        AbilitySystem->SetNumericAttributeBase(UABGASCharacterAttributeSet::GetAttackRateAttribute(), CurrentAttackRate + WeaponRate);
    }
}

void AABGASPlayerCharacter::UnequipWeaponCallback(const FGameplayEventData* EventData)
{
    if(Weapon)
    {
        Weapon->SetSkeletalMesh(nullptr);

        FGameplayAbilitySpec* SkillAbilitySpec = AbilitySystem->FindAbilitySpecFromClass(SkillAbilityClass);
        if(SkillAbilitySpec)
        {
            AbilitySystem->ClearAbility(SkillAbilitySpec->Handle);
        }

        const float CurrentAttackRange = AbilitySystem->GetNumericAttributeBase(UABGASCharacterAttributeSet::GetAttackRangeAttribute());
        const float CurrentAttackRate = AbilitySystem->GetNumericAttributeBase(UABGASCharacterAttributeSet::GetAttackRateAttribute());

        AbilitySystem->SetNumericAttributeBase(UABGASCharacterAttributeSet::GetAttackRangeAttribute(), CurrentAttackRange - WeaponRange);
        AbilitySystem->SetNumericAttributeBase(UABGASCharacterAttributeSet::GetAttackRateAttribute(), CurrentAttackRate - WeaponRate);
    }
}
