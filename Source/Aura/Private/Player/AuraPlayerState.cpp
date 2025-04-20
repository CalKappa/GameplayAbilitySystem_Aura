// Copyright CalKappa


#include "Player/AuraPlayerState.h"

#include <AbilitySystem/AuraAbilitySystemComponent.h>
#include "Net/UnrealNetwork.h"
#include <AbilitySystem/AuraAttributeSet.h>

AAuraPlayerState::AAuraPlayerState()
{

	// Ability System Component Construction
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// Attribute Set Component Construction
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");


	// Set the network update frequency
	SetNetUpdateFrequency(100.f);

	
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAuraPlayerState, Level);

}


UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{

}
