// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PinguCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
APinguCharacter::APinguCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Material = ConstructorHelpers::FObjectFinder<UMaterialInterface>(*MAT_PATH).Object;
	GetMesh()->SetSkeletalMesh(ConstructorHelpers::FObjectFinder<USkeletalMesh>(*MESH_PATH).Object);
	GetMesh()->SetMaterial(0, Material);

	if (!Cam) Cam = InitCamera();
	InitInputAction();
}

auto APinguCharacter::InitCamera() -> UCameraComponent*
{
	auto cam = CreateDefaultSubobject<UCameraComponent>(*CAMERA_NAME);
	cam->SetupAttachment(GetMesh());
	cam->SetRelativeLocation(FVector(-500.0f, 0.0f, 150.0f));
	return cam;
}

void APinguCharacter::InitInputAction()
{
	if (!InputCtx) InputCtx = ConstructorHelpers::FObjectFinder<UInputMappingContext>(*PLAYER_CTX_PATH).Object;
	if (!MoveActionRight) MoveActionRight = ConstructorHelpers::FObjectFinder<UInputAction>(*IA_MOVE_RIGHT_PATH).Object;
}



void APinguCharacter::HandleRightMovement(const FInputActionValue& Ctx)
{
	auto input = Ctx.Get<float>();
	if (input < 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Magenta, "Links");
		auto location = GetActorLocation();
		location += FVector(0.0f, input, 0.0f) * GetWorld()->TimeSeconds * Speed;
		SetActorLocation(location);
		//AddMovementInput(FVector(10000.0f, 0.0f, 0.0f), -10000, true);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Magenta, "Rechts");
		auto location = GetActorLocation();
		location += FVector(0.0f, input, 0.0f) * GetWorld()->TimeSeconds * Speed;
		SetActorLocation(location);
	}
}

void APinguCharacter::HandleStopMovement()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Magenta, "Stop");

	Dir.Y = 0.0f;
}

// Called when the game starts or when spawned
void APinguCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (auto* controller = CastChecked<APlayerController>(GetController()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller exist!"))
			if (auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(controller->GetLocalPlayer()))
			{
				subsystem->AddMappingContext(InputCtx, 0);
			}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller doesnt exist!"))
	}

}

// Called every frame
void APinguCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APinguCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* inputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		inputComponent->BindAction(MoveActionRight, ETriggerEvent::Triggered, this, &APinguCharacter::HandleRightMovement);
		inputComponent->BindAction(MoveActionRight, ETriggerEvent::Completed, this, &APinguCharacter::HandleStopMovement);
	}
}