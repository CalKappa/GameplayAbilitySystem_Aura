// Copyright CalKappa


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	// Link the "Def" Local attribute to the AttributeSet Attribute
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// Add the tags to the Evaluation Parameters
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Create local variable(s) for an attribute we want to use in the calculation
	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParameters, Intelligence);

	// Clamp Variables so they dont go below 0
	Intelligence = FMath::Max<float>(Intelligence, 0);

	// Cast to ICombatInterface so that we can obtain player level to include in calculation
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	// Call the GetPlayerLevel() function from the CombatInterface
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	// Create Variable for the various multipliers we want to use in the final calculation
	float MaxManaBaseValue = 50.f;
	float IntelligenceMultiplier = 2.0f;
	float PlayerLevelMultiplier = 15.f;

	// Create a variable to hold the result of the final calculation and make it equal your calculation
	float MaxManaCalculation = MaxManaBaseValue + IntelligenceMultiplier * Intelligence + PlayerLevelMultiplier * PlayerLevel;

	// Return the Calculation Result Variable
	return MaxManaCalculation;
}
