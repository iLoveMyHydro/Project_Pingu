// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Character/BossEnemy.h"
#include "Enemy/Controller/BossAIController.h"
#include "FiniteStateMachine/Machines/NormalSimpleFSM.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "OilBarrel/OilBarrel.h"
#include "FiniteStateMachine/FSM/NormalFSM.h"
#include "Player/PinguCharacter.h"
#include "Player/InputController.h"

#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABossEnemy::ABossEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(175.0f, 175.0f);

	Material = ConstructorHelpers::FObjectFinder<UMaterial>(*MATERIAL_PATH).Object;
	GetMesh()->SetSkeletalMesh(ConstructorHelpers::FObjectFinder<USkeletalMesh>(*MESH_PATH).Object);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -180.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	GetMesh()->SetRelativeScale3D(FVector(.5f, 0.5f, 0.5f));
	GetMesh()->SetMaterial(0, Material);
	
	OilBarrelProjectile = ConstructorHelpers::FClassFinder<AOilBarrel>(*OIL_BARREL_PATH).Class;

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(*BOX_COLLISION_NAME);
	CollisionMesh->bDynamicObstacle = true;
	CollisionMesh->SetupAttachment(RootComponent);
	CollisionMesh->SetGenerateOverlapEvents(true);
	CollisionMesh->SetBoxExtent(FVector(100.0f, 150.0f, 150.0f));
	CollisionMesh->SetHiddenInGame(false);

	SphereColl = CreateDefaultSubobject<USphereComponent>(TEXT("Perception Trigger"));
	SphereColl->SetSphereRadius(4000);
	SphereColl->SetRelativeLocation(FVector(0, 0, 90));
	SphereColl->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SphereColl->SetHiddenInGame(true);
	SphereColl->OnComponentBeginOverlap.AddDynamic(this, &ABossEnemy::OnCollision);
	SphereColl->OnComponentEndOverlap.AddDynamic(this, &ABossEnemy::OnCollisionExit);
	SphereColl->SetupAttachment(GetMesh());

	SpawnLocationOilBarrel = CreateDefaultSubobject<USceneComponent>(*SPAWNLOCATION_OIL_BARREL_NAME);
	SpawnLocationOilBarrel->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	SpawnLocationOilBarrel->SetupAttachment(RootComponent);

	AIControllerClass = ConstructorHelpers::FClassFinder<ABossAIController>(*FSM_CONTROLLER_PATH).Class;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	IdleAnim = ConstructorHelpers::FObjectFinder<UAnimSequence>(*IDLE_ANIM_PATH).Object;
	ThrowAnim = ConstructorHelpers::FObjectFinder<UAnimSequence>(*THROW_ANIM_PATH).Object;

	//Audio Code
	BossDamageSFXComponent = CreateDefaultSubobject<UAudioComponent>(*BOSS_DAMAGE_SFX_COMPONENT_NAME);

	BossDamageSFXComponent->SetSound(ConstructorHelpers::FObjectFinder<USoundBase>(*BOSS_DAMAGE_SFX_PATH).Object);

	BossDamageSFXComponent->SetAutoActivate(bAutoActivate);

	BossDamageSFXComponent->SetupAttachment(RootComponent);
	//No more Audio Code
}

// Called when the game starts or when spawned
void ABossEnemy::BeginPlay()
{
	Super::BeginPlay();

	Controller = Cast<ABossAIController>(GetController());
	Controller->SetCharacter(this);

	PlayerController = Cast<AInputController>(GetWorld()->GetFirstPlayerController());

	if (Fsm == nullptr)
	{
		Fsm = static_cast<NormalSimpleFSM*>(new NormalSimpleFSM(Controller));
	}
	if (Fsm != nullptr)
	{
		Fsm->Initialize();
	}
	SetIdleAnimation();
}

// Called every frame
void ABossEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABossEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABossEnemy::ApplyDamage(int A_DamageAmount)
{
	Health -= A_DamageAmount;

	if (Health <= 0)
	{
		ABossEnemy::Destroy();

		UGameplayStatics::OpenLevel(GetWorld(), MAIN_MENU_LEVEL);
	}
}

void ABossEnemy::ThrowOilBarrel()
{
	Character = GetController()->GetPawn<ABossEnemy>();

	if (OilBarrelProjectile != nullptr)
	{
		//Aus FirstPlayer UE Demo
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			FRotator Rotator = GetActorRotation();

			World->SpawnActor<AOilBarrel>(OilBarrelProjectile, SpawnLocationOilBarrel->GetRelativeLocation() + GetActorLocation(), FRotator(0.0f, -90.0f, 0.0f), ActorSpawnParams);
		}
		SetThrowAnimation();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Projectile"));
	}
}

void ABossEnemy::ThrowThreeOilBarel()
{
	Character = GetController()->GetPawn<ABossEnemy>();

	if (OilBarrelProjectile != nullptr)
	{
		//Aus FirstPlayer UE Demo
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			FRotator Rotator = GetActorRotation();

			World->SpawnActor<AOilBarrel>(OilBarrelProjectile, SpawnLocationOilBarrel->GetRelativeLocation() + GetActorLocation(), FRotator(0.0f, -90.0f, 0.0f), ActorSpawnParams);

		}
		SetThrowAnimation();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Projectile"));
	}
}

void ABossEnemy::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APinguCharacter::StaticClass()) && !PlayerController->IsPaused())
	{
		if(Health > 3)
		{
			GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, [this]() {Fsm->Transition(static_cast<NormalSimpleFSM*>(Fsm)->GetBossThrowObjectState()); }, RespawnDelay, true);
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, TEXT("Enter"));
		}
		else if(Health <= 3)
		{
			GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandleThree, [this]() {Fsm->Transition(static_cast<NormalSimpleFSM*>(Fsm)->GetThrowThreeObjectsState()); }, RespawnDelayFast, true);
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, TEXT("Enter"));
		}
	}
}

void ABossEnemy::OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(APinguCharacter::StaticClass()) && !PlayerController->IsPaused())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, TEXT("Exit"));
		Fsm->Transition(static_cast<NormalSimpleFSM*>(Fsm)->GetSearchPlayerState());
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandleThree);
		SetIdleAnimation();
	}
}

void ABossEnemy::PlayBossDamageSFX()
{
	if (!BossDamageSFXComponent) return;
	if (!BossDamageSFXComponent->GetSound()) return;

	if (BossDamageSFXComponent->IsActive() == false) BossDamageSFXComponent->SetActive(true);
	if (BossDamageSFXComponent->IsPlaying() == false) BossDamageSFXComponent->Play();

	BossDamageSFXComponent->SetTriggerParameter(*BOSS_DAMAGE_SFX_TRIGGER_NAME);
}

ABossEnemy& ABossEnemy::SetIdleAnimation()
{
	GetMesh()->PlayAnimation(IdleAnim, true);
	return *this;
}

ABossEnemy& ABossEnemy::SetThrowAnimation()
{
	GetMesh()->PlayAnimation(ThrowAnim, false);
	return *this;
}
