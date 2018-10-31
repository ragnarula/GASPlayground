#pragma once
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GASCharacterAttributeSet.generated.h"

UCLASS()
class UGASCharacterAttributeSet
	: public UAttributeSet
{
	GENERATED_BODY()

public:

	UGASCharacterAttributeSet();

	UPROPERTY(Category = "Attribute | Health", EditAnywhere, ReplicatedUsing = OnRep_Health, BlueprintReadWrite) FGameplayAttributeData Health;
	UFUNCTION() void OnRep_Health() { GAMEPLAYATTRIBUTE_REPNOTIFY(UGASCharacterAttributeSet, Health); }
	static FGameplayAttribute AttributeHealth();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;


	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData &Data) override;


	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;


	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;


	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;


	virtual void PostInitProperties() override;

	void OnEffectAppliedToSelf(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handle);

	void OnEffectAppliedToTarget(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handle);

	void OnHealthChange(const FOnAttributeChangeData& ChanegData);

};