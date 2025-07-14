// Fill out your copyright notice in the Description page of Project Settings.


#include "TPV_Controller.h"
#include "Camera/CameraComponent.h"
#include "MGraf2/MyPlayer.h"
#include "MGraf2/Components/HealthComponent.h"
#include "MGraf2/Components/WeaponComponent.h"


// Sets default values
ATPV_Controller::ATPV_Controller()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	cameraComponent->SetupAttachment(RootComponent);
	cameraComponent->bUsePawnControlRotation = true;

	axeComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Axe Component"));

	swordComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Sword Component"));
	
	swordMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword Mesh"));
	
	axeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Axe Mesh"));

	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &ATPV_Controller::OnAttackEnded);
	}
}

// Called when the game starts or when spawned
void ATPV_Controller::BeginPlay()
{
	Super::BeginPlay();
	
	swordComponent->InitializeComponent(GetMesh(), swordMesh, swordMesh->GetSocketLocation(FName("Start")), swordMesh->GetSocketLocation(FName("End")), "SwordSocket", "ScabbardSocket");
	axeComponent->InitializeComponent(GetMesh(), axeMesh, axeMesh->GetSocketLocation(FName("Start")), axeMesh->GetSocketLocation(FName("End")), "SwordSocket", "ScabbardSocket");
	
	if (swordMesh && GetMesh())
	{
		swordComponent->UseWeapon();
	}
	
	if (axeMesh && GetMesh())
	{
		axeComponent->SheathWeapon();
	}
}

// Called every frame
void ATPV_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATPV_Controller::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATPV_Controller::Jump);
	PlayerInputComponent->BindAxis("Forward", this, &ATPV_Controller::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATPV_Controller::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ATPV_Controller::LookUp);
	PlayerInputComponent->BindAxis("TurnCamera", this, &ATPV_Controller::TurnCamera);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ATPV_Controller::StartAttack);
	PlayerInputComponent->BindAction("UseSword", IE_Pressed, this, &ATPV_Controller::UseSword);
	PlayerInputComponent->BindAction("UseAxe", IE_Pressed, this, &ATPV_Controller::UseAxe);
	PlayerInputComponent->BindAction("SwapWeapon", IE_Pressed, this, &ATPV_Controller::SwapWeapon);
}

void ATPV_Controller::SwapWeapon()
{
	if (swapWeaponMontage)
	{
		UAnimInstance* animInstance = GetMesh()->GetAnimInstance();

		if (animInstance)
		{
			if (swordComponent->bIsUsingWeapon == false)
			{
				animInstance->Montage_Play(swapWeaponMontage);
				float animDuration = swapWeaponMontage->GetPlayLength();
				GetWorldTimerManager().SetTimer(swapWeaponHandle, this, &ATPV_Controller::UseSword, animDuration, false);		
			}

			if (axeComponent->bIsUsingWeapon == false)
			{
				animInstance->Montage_Play(swapWeaponMontage);
				float animDuration = swapWeaponMontage->GetPlayLength();
				GetWorldTimerManager().SetTimer(swapWeaponHandle, this, &ATPV_Controller::UseAxe, animDuration, false);
			}
		}
	}
}


void ATPV_Controller::UseSword()
{
	swordComponent->UseWeapon();
	axeComponent->SheathWeapon();
}

void ATPV_Controller::UseAxe()
{
	axeComponent->UseWeapon();
	swordComponent->SheathWeapon();
}

void ATPV_Controller::StartAttack()
{
	// if (attackAnimation && !isAttacking)
	// {
	// 	if (swordComponent->bIsUsingWeapon)
	// 	{
	// 		GetMesh()->PlayAnimation(attackAnimation, false);			
	// 	}
	//
	// 	if (axeComponent->bIsUsingWeapon)
	// 	{
	// 		GetMesh()->PlayAnimation(axeAttackAnimation, false);
	// 	}
	// }

	if (attackMontage && !isAttacking && swordComponent->bIsUsingWeapon)
	{
		UAnimInstance* animInstance = GetMesh()->GetAnimInstance();

		if (animInstance)
		{
			animInstance->Montage_Play(attackMontage);
			isAttacking = true;
			float attackDuration = attackMontage->GetPlayLength();
			GetWorldTimerManager().SetTimer(attackResetHandle, this, &ATPV_Controller::ResetAttackState, attackDuration, false);
		}
	}

	if (attackMontage && !isAttacking && axeComponent->bIsUsingWeapon)
	{
		UAnimInstance* animInstance = GetMesh()->GetAnimInstance();

		if (animInstance)
		{
			animInstance->Montage_Play(axeAttackMontage);
			isAttacking = true;
			float attackDuration = axeAttackMontage->GetPlayLength();
			GetWorldTimerManager().SetTimer(attackResetHandle, this, &ATPV_Controller::ResetAttackState, attackDuration, false);
		}
	}
}

void ATPV_Controller::MoveForward(float inputVector)
{
	FVector forward = GetActorForwardVector();

	AddMovementInput(forward, inputVector);
}

void ATPV_Controller::MoveRight(float inputVector)
{
	FVector rightDirection = GetActorRightVector();

	AddMovementInput(rightDirection, inputVector);
}

void ATPV_Controller::TurnCamera(float inputVector)
{
	AddControllerYawInput(inputVector);
}

void ATPV_Controller::LookUp(float inputVector)
{
	AddControllerPitchInput(inputVector);
}

void ATPV_Controller::LineTrace()
{
	FHitResult hit;
	FCollisionQueryParams params;
	
	params.AddIgnoredActor(this);

	if (swordComponent->bIsUsingWeapon)
	{
		GetWorld()->LineTraceSingleByChannel(hit, swordComponent->startLocation, swordComponent->endLocation, ECC_Visibility, params);
		DrawDebugLine(GetWorld(), swordComponent->startLocation, swordComponent->endLocation, FColor::Red, false, 1, 0, 1);
	}

	if (axeComponent->bIsUsingWeapon)
	{
		GetWorld()->LineTraceSingleByChannel(hit, axeComponent->startLocation, axeComponent->endLocation, ECC_Visibility, params);
		DrawDebugLine(GetWorld(), axeComponent->startLocation, axeComponent->endLocation, FColor::Red, false, 1, 0, 1);
	}

	if (hit.bBlockingHit)
	{
		AActor* hitActor = hit.GetActor();
		UHealthComponent* enemyHit = hitActor->FindComponentByClass<UHealthComponent>();
	
		if (IsValid(enemyHit))
			enemyHit->TakeDamage(damage);
	}
}

void ATPV_Controller::OnAttackEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == attackMontage)
	{
		isAttacking = false;
	}
}

void ATPV_Controller::ResetAttackState()
{
	isAttacking = false;
}

