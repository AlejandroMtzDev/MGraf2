// Fill out your copyright notice in the Description page of Project Settings.


#include "FPV_Controller.h"
#include "Camera/CameraComponent.h"
#include "MGraf2/MyPlayer.h"


// Sets default values
AFPV_Controller::AFPV_Controller()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	cameraComponent->SetupAttachment(RootComponent);
	cameraComponent->bUsePawnControlRotation = true;

	swordMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword Mesh"));
}

// Called when the game starts or when spawned
void AFPV_Controller::BeginPlay()
{
	Super::BeginPlay();

	if (swordMesh && GetMesh())
	{
		swordMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("SwordSocket"));
	}
}

// Called every frame
void AFPV_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFPV_Controller::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPV_Controller::Jump);
	PlayerInputComponent->BindAxis("Forward", this, &AFPV_Controller::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPV_Controller::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPV_Controller::LookUp);
	PlayerInputComponent->BindAxis("TurnCamera", this, &AFPV_Controller::TurnCamera);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AFPV_Controller::StartAttack);
}

void AFPV_Controller::MoveForward(float inputVector)
{
	FVector forward = GetActorForwardVector();

	AddMovementInput(forward, inputVector);
}

void AFPV_Controller::MoveRight(float inputVector)
{
	FVector rightDirection = GetActorRightVector();

	AddMovementInput(rightDirection, inputVector);
}

void AFPV_Controller::TurnCamera(float inputVector)
{
	AddControllerYawInput(inputVector);
}

void AFPV_Controller::LookUp(float inputVector)
{
	AddControllerPitchInput(inputVector);
}

void AFPV_Controller::StartAttack()
{
	if (attackAnimation && !isAttacking)
	{
		GetMesh()->PlayAnimation(attackAnimation, false);
	}
}

void AFPV_Controller::LineTrace()
{
	FVector startLocation = swordMesh->GetSocketLocation(FName("Start"));
	FVector endLocation = swordMesh->GetSocketLocation(FName("End"));
	FHitResult hit;
	FCollisionQueryParams params;
	
	params.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(hit, startLocation, endLocation, ECC_Visibility, params);
	DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Red, false, 1, 0, 1);

	// if (hit.bBlockingHit)
	// {
	// 	AActor* hitActor = hit.GetActor();
	// 	UHealthComponent* enemyHit = hitActor->FindComponentByClass<UHealthComponent>();
	//
	// 	if (IsValid(enemyHit))
	// 		enemyHit->TakeDamage(damage);
	// }
}

