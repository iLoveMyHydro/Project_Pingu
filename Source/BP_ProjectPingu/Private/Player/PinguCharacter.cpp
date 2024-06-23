// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PinguCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


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
	if (!MoveAction) MoveAction = ConstructorHelpers::FObjectFinder<UInputAction>(*IA_MOVE_PATH).Object;
}

void APinguCharacter::MovePlayer()
{
	auto loca = GetActorLocation() + (Speed * Dir * GetWorld()->GetDeltaSeconds());
	SetActorLocation(loca);
}

void APinguCharacter::HandleRightMovement(const FInputActionValue& ctx)
{
	//auto input = ctx.Get<float>;
	//if (input < 0.0f) UE_LOG(LogTemp, Warning, TEXT("Left"));
	//Dir.Y = input;
}

void APinguCharacter::HandleLeftMovement(const FInputActionValue& ctx)
{
	//auto input = ctx.Get<float>;
	//if (input > 0.0f) UE_LOG(LogTemp, Warning, TEXT("Right"));
	//Dir.Y = input;
}

// Called when the game starts or when spawned
void APinguCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (Speed == 0) Speed = 50.0f;
	if (Dir == FVector::Zero()) Dir = FVector::ForwardVector;

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
	MovePlayer();
}

// Called to bind functionality to input
void APinguCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* inputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			inputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &APinguCharacter::HandleLeftMovement);
			inputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &APinguCharacter::HandleRightMovement);
		}
	}
}

