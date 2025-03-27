// Copyright CalKappa


#include "Player/AuraPlayerState.h"
#include <AbilitySystem/AuraAbilitySystemComponent.h>
#include <AbilitySystem/AuraAttributeSet.h>

AAuraPlayerState::AAuraPlayerState()
{

	// Ability System Component Construction
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	// Attribute Set Component Construction
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");


	// Set the network update frequency
	NetUpdateFrequency = 100.f;

	
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
