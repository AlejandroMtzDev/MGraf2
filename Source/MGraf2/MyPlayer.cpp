// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));

    CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionBox->SetCollisionObjectType(ECC_Pawn);
    CollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);
    CollisionBox->SetGenerateOverlapEvents(true);

    //CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMyPlayer::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void APlayerMovement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//    InputComponent->("VerticalAxis", this, &APlayerMovement::VerticalAxis);
//    InputComponent->("Fire", IE_Pressed, this, &APlayerMovement::FirePressed);
//}

// void AMyPlayer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
//     int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
//     if (OtherActor && OtherActor != this)
//     {
//         if (GEngine)
//         {
//             GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Choque contra algo");
//         }
//     }
//
//     AMyBullet* bullet = Cast<AMyBullet>(OtherActor);
//     health -= bullet->damage;
// }

