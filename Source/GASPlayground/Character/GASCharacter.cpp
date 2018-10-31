#include "GASCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbility.h"
#include "GASCharacterAttributeSet.h"

AGASCharacter::AGASCharacter(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
{
	GASComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("GASComponent"));
	AttributeSet = CreateDefaultSubobject<UGASCharacterAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* AGASCharacter::GetAbilitySystemComponent() const
{
	return GASComponent;
}

void AGASCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (!PlayerInputComponent)
	{
		return;
	}

	GASComponent->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbilityInputBinds(TEXT("ConfirmAbility"), TEXT("CancelAbility"), TEXT("EAbilityInput")));
}

void AGASCharacter::BeginPlay()
{
	GASComponent->InitAbilityActorInfo(this, this);
	
	if (HasAuthority())
	{
		for (const FAbilityBinding& Binding : BoundAbilities)
		{
			GASComponent->GiveAbility(FGameplayAbilitySpec(Binding.Ability, 1, static_cast<int32>(Binding.Input)));
		}
	}
}
