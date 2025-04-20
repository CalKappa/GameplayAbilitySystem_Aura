// Copyright CalKappa

#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"


UMMC_MaxHealth::UMMC_MaxHealth()
{
	// Link the "Def" Local attribute to the AttributeSet Attribute
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// Add the tags to the Evaluation Parameters
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Create local variable for an attribute we want to use in the calculation
	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluationParameters, Vigor);

	// Clamp Variables so they dont go below 0
	Vigor = FMath::Max<float>(Vigor, 0);

	// Cast to ICombatInterface so that we can obtain player level to include in calculation
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	// Call the GetPlayerLevel() function from the CombatInterface
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	// Create Variable for the various multipliers we want to use in the final calculation
	float MaxHealthBaseVal = 80.f;
	float VigorMultiplier = 2.5f;
	float PlayerLevelMultiplier = 10.f;

	// Create a variable to hold the result of the final calculation and make it equal your calculation
	float MaxHealthCalculation = MaxHealthBaseVal + VigorMultiplier * Vigor + PlayerLevelMultiplier * PlayerLevel;

	// Return the Calculation Result Variable
	return MaxHealthCalculation;
}
