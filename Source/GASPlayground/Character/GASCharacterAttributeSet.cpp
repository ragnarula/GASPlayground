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
	UE_LOG(LogTemp, Warning, TEXT("PreGameplayEffectExecute -- CurrentHealth: %f"), Health.GetCurrentValue());
	return true;
}

void UGASCharacterAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{
	UE_LOG(LogTemp, Warning, TEXT("PostGameplayEffectExecute -- CurrentHealth: %f"), Health.GetCurrentValue());
}

void UGASCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	UE_LOG(LogTemp, Warning, TEXT("PreAttributeChange -- CurrentHealth: %f, NewHealth: %f"), Health.GetCurrentValue(), NewValue);
}

void UGASCharacterAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	UE_LOG(LogTemp, Warning, TEXT("PreAttributeBaseChange -- CurrentHealth: %f, NewValue: %f"), Health.GetCurrentValue(), NewValue);
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
	GetOwningAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(AttributeHealth()).AddUObject(this, &UGASCharacterAttributeSet::OnHealthChange);
}

void UGASCharacterAttributeSet::OnEffectAppliedToSelf(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handle)
{
	UE_LOG(LogTemp, Warning, TEXT("OnEffectAppliedToSelf -- CurrentHealth: %f"), Health.GetCurrentValue());
}

void UGASCharacterAttributeSet::OnEffectAppliedToTarget(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handle)
{
	UE_LOG(LogTemp, Warning, TEXT("OnEffectAppliedToTarget -- CurrentHealth: %f"), Health.GetCurrentValue());
}

void UGASCharacterAttributeSet::OnHealthChange(const FOnAttributeChangeData& ChanegData)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHealthChange -- CurrentHealth: %f, ModData: %s"), Health.GetCurrentValue(), ChanegData.GEModData ? TEXT("True") : TEXT("False"));
}

#pragma optimize("", on)
