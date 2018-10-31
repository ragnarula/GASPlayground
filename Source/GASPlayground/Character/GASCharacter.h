#pragma once
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GASCharacter.generated.h"

UENUM()
enum class EAbilityInput : uint8
{
	Ability0,
	Ability1,
	Ability2,
	Ability3
};

USTRUCT()
struct FAbilityBinding
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UGameplayAbility> Ability;

	UPROPERTY(EditDefaultsOnly)
	EAbilityInput Input = static_cast<EAbilityInput>(0);
};

UCLASS(Blueprintable)
class AGASCharacter
	: public ACharacter
	, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGASCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
	UAbilitySystemComponent* GASComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TArray<FAbilityBinding> BoundAbilities;

	UPROPERTY()
	class UGASCharacterAttributeSet* AttributeSet = nullptr;
};
