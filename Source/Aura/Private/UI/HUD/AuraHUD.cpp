// Copyright CalKappa


#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/Widget/AuraUserWidget.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetcontrollerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();

		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{

	// Init Overlay needs to create two things, a widget and a widget controller, it then needs to tie those two together, using the below steps
		/*
			1) First we need to check that OverlayWidgetclass and OverlayWidgetControllerClass are not nullptr
			2) Next we need to create a local UserWidget class using the OverlayWidgetClass and cast it to a UAuraUserWidget so we can set the widget controller
			3) Now we can create the widget controller with the InitOverlay inputs of PlayerController, PlayerState, AbilitySystemComponent and AbilitySet
			4) Call GetOverlayWidgetController and create the OverlayWidgetController 
			5) Tie the OverlayWidget and the OverlayWidgetController together 
			6) Call BroadcastInitialValues() on the widget controller
			7) You can now add the Widget to the viewport
		*/
	
		
	// 1
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass uninitialized, please fill out BP_AuraHUD"));

	// 2
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	// 3
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	
	// 4
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	// 5
	OverlayWidget->SetWidgetController(WidgetController);
	
	//6
	WidgetController->BroadcastInitialValues();


	//7
	Widget->AddToViewport(); 
}


