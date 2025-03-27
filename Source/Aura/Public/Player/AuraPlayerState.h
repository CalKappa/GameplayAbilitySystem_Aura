// Copyright CalKappa

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"


// Forward Declarations
class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AAuraPlayerState();
	

	// Ability System Interface Function override
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// Custom AttributeSet Getter
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	// Ability System pointers
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;


private:


};
