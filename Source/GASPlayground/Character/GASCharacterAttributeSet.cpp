#include "GASCharacterAttributeSet.h"
#include "UnrealNetwork.h"

#pragma optimize("", off)

UGASCharacterAttributeSet::UGASCharacterAttributeSet()
{
	Health = FGameplayAttributeData(100.f);
}

FGameplayAttribute UGASCharacterAttributeSet::AttributeHealth()
{
	static UProperty* Property = FindFieldChecked<UProperty>(UGASCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UGASCharacterAttributeSet, Health));
	return FGameplayAttribute(Property);
}

void UGASCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGASCharacterAttributeSet, Health, COND_None, REPNOTIFY_Always);
}

bool UGASCharacterAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData &Data)
{
	UE_LOG(LogTemp, Warning, TEXT("PreGameplayEffectExecute"));
	return true;
}

void UGASCharacterAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{
	UE_LOG(LogTemp, Warning, TEXT("PostGameplayEffectExecute"));
}

void UGASCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	UE_LOG(LogTemp, Warning, TEXT("PreAttributeChange"));
	NewValue = 0.f;
}

void UGASCharacterAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	UE_LOG(LogTemp, Warning, TEXT("PreAttributeBaseChange"));
}

void UGASCharacterAttributeSet::PostInitProperties()
{
	Super::PostInitProperties();

	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		return;
	}

	GetOwningAbilitySystemComponent()->OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UGASCharacterAttributeSet::OnEffectAppliedToSelf);
	GetOwningAbilitySystemComponent()->OnGameplayEffectAppliedDelegateToTarget.AddUObject(this, &UGASCharacterAttributeSet::OnEffectAppliedToTarget);
}


void UGASCharacterAttributeSet::OnEffectAppliedToSelf(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handle)
{
	const FActiveGameplayEffect* ActiveEffect1 = ASC->GetActiveGameplayEffect(Handle);
	const FActiveGameplayEffect* ActiveEffect2 = GetOwningAbilitySystemComponent()->GetActiveGameplayEffect(Handle);

	float HealthChange = ASC->GetGameplayEffectMagnitude(Handle, AttributeHealth());
	
	UE_LOG(LogTemp, Warning, TEXT("OnEffeftAppliedToSelf: HealthChange: %f"), HealthChange);
}

void UGASCharacterAttributeSet::OnEffectAppliedToTarget(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handle)
{
	UE_LOG(LogTemp, Warning, TEXT("OnEffectAppliedToTarget"));
}

#pragma optimize("", on)
