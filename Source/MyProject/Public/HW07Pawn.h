#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "HW07Pawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshConponent;
class USpringArmComponent;
class UCameraComponent;

struct FInputActionValue;



UCLASS()
class MYPROJECT_API AHW07Pawn : public APawn
{
	GENERATED_BODY()

public:
	AHW07Pawn();
	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	USkeletalMeshComponent* SkeletalMeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	UCameraComponent* CameraComp;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float MoveSpeed = 600.0f;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
};

