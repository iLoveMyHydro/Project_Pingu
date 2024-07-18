// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainMenuUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(PlayGameButton)
	{
		PlayGameButton->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnPlayGameButton);
	}
	if(OptionsButton)
	{
		OptionsButton->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnOptionsButtonClicked);
	}
	if(CreditsButton)
	{
		CreditsButton->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnCreditsButtonClicked);
	}
	if(QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnQuitButtonClicked);
	}
}

void UMainMenuUserWidget::OnPlayGameButton()
{
	UGameplayStatics::OpenLevel(this, TEXT("/Game/Maps/Project_Pingu"));
}

void UMainMenuUserWidget::OnOptionsButtonClicked()
{
}

void UMainMenuUserWidget::OnCreditsButtonClicked()
{
}

void UMainMenuUserWidget::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
