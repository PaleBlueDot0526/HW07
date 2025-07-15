#include "HW07Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "HW07PlayerController.h"


AHW07Pawn::AHW07Pawn()
{
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComp;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComp->SetupAttachment(RootComponent);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	CapsuleComp->SetSimulatePhysics(false);
	SkeletalMeshComp->SetSimulatePhysics(false);

}


void AHW07Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AHW07PlayerController* PlayerController = Cast<AHW07PlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AHW07Pawn::Move
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AHW07Pawn::Look
				);
			}
		}
	}

}

void AHW07Pawn::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector MoveInput = value.Get<FVector>();

	if (!MoveInput.IsNearlyZero())
	{
		FVector CharactorMove = MoveInput * MoveSpeed * GetWorld()->GetDeltaSeconds();
	
		AddActorLocalOffset(CharactorMove, true);
	
	}
}

void AHW07Pawn::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();

	float MouseX = LookInput.X;
	float MouseY = LookInput.Y;

	FRotator CurrentRot = SpringArmComp->GetRelativeRotation();

	float NewPitch = CurrentRot.Pitch + (-MouseY);
	NewPitch = FMath::Clamp(NewPitch, -35.0f, 10.0f);

	AddActorLocalRotation(FRotator(0.0f, MouseX , 0.0f));
	SpringArmComp->SetRelativeRotation(FRotator(NewPitch , CurrentRot.Yaw, CurrentRot.Roll));
//	UE_LOG(LogTemp, Warning, TEXT("Mouse Y : %f"), NewPitch);
}
