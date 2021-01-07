// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Shooter.h"


void AShooterAI::BeginPlay(){

    Super::BeginPlay();
    
    if(AIBehavior != nullptr){
        RunBehaviorTree(AIBehavior);

        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AShooterAI::Tick(float DeltaSeconds){

    Super::Tick(DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
    if(LineOfSightTo(PlayerPawn)){
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
    } else{
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    }
}

bool AShooterAI::IsDead() const{
    
    AShooter* ControlledCharacter = Cast<AShooter>(GetPawn());
    
    if(ControlledCharacter != nullptr){
        return ControlledCharacter->IsDead();
    }

    return true;
}