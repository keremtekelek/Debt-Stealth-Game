#include "AI/AIController/AIC_Enemy.h"


#define DELAY(time, block) \
{ \
    FTimerHandle LocalTimerHandle; \
    GetWorld()->GetTimerManager().SetTimer(LocalTimerHandle, [this]() { block; }, time, false); \
}

AAIC_Enemy::AAIC_Enemy()
{

    static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/01_MyContent/AI/BT_EnemyAI_Base")); //Getting the BehaviourTree
    if (BTObject.Succeeded())
    {
        BT_EnemyAI_Base = BTObject.Object;   // If it is exixts, set it
    }


    AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));

    //Setting Up the Sight Sense

    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    
    SightConfig->SightRadius = 3000.0f;
    SightConfig->LoseSightRadius = 3200.f;
    SightConfig->PeripheralVisionAngleDegrees = 80.0f;
    SightConfig->SetMaxAge(15.f);
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;


    AIPerceptionComp->ConfigureSense(*SightConfig);



    //Setting Up the Hear Sense

    HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));

   
    HearingConfig->HearingRange = 3000.f;
    HearingConfig->SetMaxAge(10.f);
    HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
    HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;  //When this value changed the true, then AI's attacking each other
    HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

    AIPerceptionComp->ConfigureSense(*HearingConfig);

    //Setting Up the Prediction Sense

    PredictionConfig = CreateDefaultSubobject<UAISenseConfig_Prediction>(TEXT("PredictionConfig"));

    PredictionConfig->SetMaxAge(5.f);
   


    AIPerceptionComp->ConfigureSense(*PredictionConfig);


    //Setting the Default Dominant Sense and Stimulus
    AIPerceptionComp->SetDominantSense(*SightConfig->GetSenseImplementation());
    AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AAIC_Enemy::OnTargetPerceptionUpdated);



    //Getting Sense's ID's
    SenseSightID = SightConfig->GetSenseID();
    SenseHearID = HearingConfig->GetSenseID();
    SensePredictionID = PredictionConfig->GetSenseID();



    //Giving default value of the  Enums
    EenemySitutation = EEnemySitutation::None;
    Eenemy_SuspiciousReason = EEnemy_SuspiciousReason::None;
    Eenemy_AlarmLevel = EEnemy_AlarmLevel::None;
    Eenemy_HeardReason = EEnemy_HeardReason::None;

    TypeOfSuspicion = ESuspiciousMeterType::None;



    //Giving default value of the Variables
    
    
   
}

void AAIC_Enemy::BeginPlay()
{
    Super::BeginPlay();

    PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    BlackboardComp->SetValueAsObject(FName("PlayerCharacter"), PlayerCharacter);

    GetWorld()->GetTimerManager().SetTimer(GetEnemyAndWidgetTimerHandle,this,&AAIC_Enemy::GetEnemyAndWidget,2.f,false);

    GetWorldTimerManager().SetTimer(DelayHandler,this,&AAIC_Enemy::DelayHandlerFunction,2.5f,false);
}



// Basically its EventOnPossess
void AAIC_Enemy::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
  

    if (BT_EnemyAI_Base)
    {   

        // Blackboard setup
        UseBlackboard(BT_EnemyAI_Base->BlackboardAsset, BlackboardComp);

        // Run Behaviour Tree
        RunBehaviorTree(BT_EnemyAI_Base);


        AEnemyBase* EnemyBase = Cast<AEnemyBase>(InPawn);

        //If EnemyBase is exists, EnemyBase's EEnemySitutation ENUM is equalized to the "EenemySitutation" variable on this code.
        if (EnemyBase)
        {
            EenemySitutation = EnemyBase->DefaultEnemySitutation;
        }

        //Defining ENUMS Default Value for Blackboard
        BlackboardComp->SetValueAsObject(FName("SelfActor"), this->GetPawn()); //Temporary
        BlackboardComp->SetValueAsEnum(FName("EnemySitutation"), static_cast<uint8>(EenemySitutation));
        BlackboardComp->SetValueAsEnum(FName("Enemy_InvestigateSuspiciousReason"), static_cast<uint8>(Eenemy_SuspiciousReason));
        BlackboardComp->SetValueAsEnum(FName("EnemyAlarmLevel"), static_cast<uint8>(Eenemy_AlarmLevel));
        BlackboardComp->SetValueAsEnum(FName("Enemy_HeardReason"), static_cast<uint8>(Eenemy_HeardReason));
        BlackboardComp->SetValueAsEnum(FName("SuspiciousLevel"),0.f);
    }
}


// Event Tick
void AAIC_Enemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CanTick)
    {
        HandleSuspiciousMeter(DeltaTime);
    }
}

// Event OnTargetPerceptionUpdated
void AAIC_Enemy::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    
    //Sight Sense
    if (Stimulus.Type == SenseSightID)
    {
        if (Stimulus.WasSuccessfullySensed())
        {

                // If what is seen is MainCharacter
                if (Actor == PlayerCharacter)
                {
                    // Suspicion Type
                    TypeOfSuspicion = ESuspiciousMeterType::Suspicion;

                    GetWorld()->GetTimerManager().ClearTimer(PlayerSawOrLostTimerHandle);

                    BlackboardComp->SetValueAsBool(FName("IsPlayerVisible"), true);
                    BlackboardComp->SetValueAsBool(FName("PlayerLostConfirmed"), false);
                    BlackboardComp->SetValueAsVector(FName("PlayerLastKnownLocation"), Stimulus.StimulusLocation);
                }

                // If what is seen is Rock
                if (Actor->ActorHasTag("ThrowableRock"))
                {   
                    // Suspicion Type
                    TypeOfSuspicion = ESuspiciousMeterType::Investigation;

                    SetEnemySitutationAs(EEnemySitutation::Investigate);
                    SetEnemyAlarmLevelAs(EEnemy_AlarmLevel::None);
                    SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason::Saw);


                    BlackboardComp->SetValueAsBool(FName("SawRock"), true);


                     // If Rock seen in the Air, PlayerCharacter location will be copmrimised!

                    FVector RockLocation = Actor->GetActorLocation();
                    FVector A(0.f, 0.f, -4.f);
                    FVector B(0.f, 0.f, -15.f);
                    FHitResult HitResult;

                    DrawDebugLine(GetWorld(), RockLocation + A, RockLocation + B, FColor::Cyan, false, 5.f, 0.f, 2.f);
                    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, RockLocation + A, RockLocation + B, ECC_Visibility);

                    // If enemy saw the rock on the Air Condition
                    if (!bHit)
                    {
                       DrawDebugSphere(GetWorld(), PlayerCharacter->GetActorLocation(), 15.f, 15, FColor::Blue, false, 5.f, 0, 2.f);
                       
                       BlackboardComp->SetValueAsBool(FName("IsRockSeenInTheAir"), true);
                       BlackboardComp->SetValueAsVector(FName("Investigation_Location"), PlayerCharacter->GetActorLocation());
                    }

                    // If enemy saw the rock not on the Air Condition
                     if (bHit)
                     {
                       BlackboardComp->SetValueAsBool(FName("IsRockSeenInTheAir"), false);
                       BlackboardComp->SetValueAsVector(FName("Investigation_Location"), RockLocation);
                     }
                }
        }

        else
        {
            //If enemy lost the PlayerCharacter, Predict the Player Location
            if (Actor == PlayerCharacter)
            {
                BlackboardComp->SetValueAsBool(FName("IsPlayerVisible"), false);

                //Prediction 
                UAISense_Prediction::RequestControllerPredictionEvent(this, Actor, 1.f);
                
            }

            if (Actor->ActorHasTag("ThrowableRock"))
            { 
                
            }
        }
    }

    //Hear Sense
    if (Stimulus.Type == SenseHearID)
    {
        
        if (Stimulus.WasSuccessfullySensed())
        {
            if (Stimulus.Tag == "FootStepSound.Walk" || Stimulus.Tag == "FootStepSound.Sprint")
            {
                TypeOfSuspicion = ESuspiciousMeterType::Investigation;

                SetEnemySitutationAs(EEnemySitutation::Investigate);
                SetEnemyAlarmLevelAs(EEnemy_AlarmLevel::None);
                SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason::Heard);
                SetEnemyHeardReasonAs(EEnemy_HeardReason::FootStep);

                BlackboardComp->SetValueAsVector(FName("Investigation_Location"), Stimulus.StimulusLocation);
                
                if (Stimulus.Tag == "FootStepSound.Walk")
                {
                    BlackboardComp->SetValueAsEnum(FName("HeardFootStepMovementType"), static_cast<uint8>(EHeardFootStepMovementType::Walk));
                    
                }

                if(Stimulus.Tag == "FootStepSound.Sprint")
                {
                    BlackboardComp->SetValueAsEnum(FName("HeardFootStepMovementType"), static_cast<uint8>(EHeardFootStepMovementType::Sprint));
                   
                }

                
            }

            else if (Stimulus.Tag == "RockSound")
            {
                TypeOfSuspicion = ESuspiciousMeterType::Investigation;

                SetEnemySitutationAs(EEnemySitutation::Investigate);
                SetEnemyAlarmLevelAs(EEnemy_AlarmLevel::None);
                SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason::Heard);
                SetEnemyHeardReasonAs(EEnemy_HeardReason::RockSound);

                BlackboardComp->SetValueAsVector(FName("Investigation_Location"), Stimulus.StimulusLocation);
            }
            
        }

        else
        {
            if (Stimulus.Tag == "FootStepSound.Walk" || Stimulus.Tag == "FootStepSound.Sprint")
            {
                
                SetEnemyHeardReasonAs(EEnemy_HeardReason::None);
                BlackboardComp->SetValueAsEnum(FName("HeardFootStepMovementType"), static_cast<uint8>(EHeardFootStepMovementType::None));
                
                
            }

            if (Stimulus.Tag == "RockSound")
            {
                SetEnemyHeardReasonAs(EEnemy_HeardReason::None);
            }
            
        }
    }

    //Prediction Sense
   
    if (Stimulus.Type == SensePredictionID)
    {
        if (Stimulus.WasSuccessfullySensed())
        {
            FVector PredictedLocation = Stimulus.StimulusLocation;
            FVector PlayerCharacterLoc;

            if (IsValid(PlayerCharacter))
            {
                PlayerCharacterLoc = PlayerCharacter->GetActorLocation();

                PredictedLocation.Z = PlayerCharacterLoc.Z;

                DrawDebugSphere(GetWorld(), PredictedLocation, 30.f, 18.f, FColor::Red, false, 7.f, 0.f, 0.3f);
                BlackboardComp->SetValueAsVector(FName("PredictedLocation"), PredictedLocation);
            }
        }
        else
        {
            
        }
    }
}



// Suspicioun Meter Functions

void AAIC_Enemy::HandleSuspiciousMeter(float DeltaTime)
{
    bool IsPlayerVisible = BlackboardComp->GetValueAsBool(FName("IsPlayerVisible"));
    float CurrentSuspiciousLevel = BlackboardComp->GetValueAsFloat(FName("SuspiciousLevel"));
    FVector MainCharacterLocation = PlayerCharacter->GetActorLocation();
    FVector EnemyLocation = Enemy->GetActorLocation();
    
    if (GetEnemySitutation() == EEnemySitutation::Investigate)
    {
        OpenOrCloseWidget("question", "open");
        SuspiciousMeter_Widget->SetColorAndOpacity(FLinearColor::Yellow);
        SuspiciousMeter_Widget->Question_Mark->SetPercent(1.f);

        if (IsPlayerVisible)
        {
            SetEnemySitutationAs(EEnemySitutation::Alarm);
            SetEnemyAlarmLevelAs(EEnemy_AlarmLevel::HugeAlarm);
            SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason::None);
            WarnOtherAIs(EEnemySitutation::Alarm, EEnemy_AlarmLevel::HugeAlarm, PlayerCharacter->GetActorLocation(), EEnemy_SuspiciousReason::None);
            PlayerSawOrLostConfirmed("saw", true);
        }
    }
    else if (GetEnemySitutation() == EEnemySitutation::Alarm)
    {
        OpenOrCloseWidget("exclamation", "open");

        if (IsPlayerVisible == false)
        {
            if (!GetWorld()->GetTimerManager().IsTimerActive(PlayerSawOrLostTimerHandle))
            {
                PlayerSawOrLostTimerDelegate.BindUObject(this, &AAIC_Enemy::PlayerSawOrLostConfirmed, FString("lost"), true);
                GetWorld()->GetTimerManager().SetTimer(PlayerSawOrLostTimerHandle, PlayerSawOrLostTimerDelegate, 4.3f, false);
            }

        }
    }
    
    else
    {
        if (IsPlayerVisible == true)
        {
            float SawPlayerCoefficient = 0.5f;
            CurrentSuspiciousLevel += DeltaTime * SawPlayerCoefficient;

            if (CurrentSuspiciousLevel >= 1.0f)
            {
                SetEnemySitutationAs(EEnemySitutation::Alarm);
                SetEnemyAlarmLevelAs(EEnemy_AlarmLevel::HugeAlarm);
                SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason::None);
                WarnOtherAIs(EEnemySitutation::Alarm, EEnemy_AlarmLevel::HugeAlarm, PlayerCharacter->GetActorLocation(), EEnemy_SuspiciousReason::None);
                PlayerSawOrLostConfirmed("saw", true);
            }
        }

        else if (IsPlayerVisible == false)
        {
            CurrentSuspiciousLevel = FMath::Max(0.0f, CurrentSuspiciousLevel - DeltaTime * 0.2f);
        }

        if (CurrentSuspiciousLevel > 0.0f)
        {
            OpenOrCloseWidget("question", "open");
            SuspiciousMeter_Widget->SetColorAndOpacity(FLinearColor::White);
            SuspiciousMeter_Widget->Question_Mark->SetPercent(CurrentSuspiciousLevel);
        }

        else
        {
            OpenOrCloseWidget("question", "close");
            SuspiciousMeter_Widget->Question_Mark->SetPercent(0.0f);
        }
    }
    
    /*
    //DEBUG PURPOSES
    FString DebugMessage = FString::Printf(TEXT("Current: %.5f"), CurrentSuspiciousLevel);
    UKismetSystemLibrary::PrintString(this, DebugMessage, true, true, FLinearColor::Red, 0.1f);
    */
     
    CurrentSuspiciousLevel = FMath::Clamp(CurrentSuspiciousLevel, 0.0f, 1.0f);
    BlackboardComp->SetValueAsFloat(FName("SuspiciousLevel"), CurrentSuspiciousLevel);
    
}


void AAIC_Enemy::ResetSuspiciousMeter()
{
    BlackboardComp->SetValueAsFloat(FName("SuspiciousLevel"), 0.0f);
}



void AAIC_Enemy::OpenOrCloseWidget(FString TypeQuestionOrExclamation, FString TypeOpenOrClose)
{
    FString OpenOrCloseWidget = TypeOpenOrClose.ToLower();
    FString WhichWidget = TypeQuestionOrExclamation.ToLower();
    
    
    if (WhichWidget == "question")
    {
        if (TypeOpenOrClose == "open")
        {
            if (SuspiciousMeter_WidgetComponent->IsVisible())
            {
                SuspiciousMeter_WidgetComponent->SetVisibility(false);
                SuspiciousMeter_WidgetComponent->SetHiddenInGame(true);

                if (SuspiciousMeter_Widget->GetVisibility() == ESlateVisibility::Visible)
                {
                    SuspiciousMeter_Widget->SetVisibility(ESlateVisibility::Hidden);
                    if (SuspiciousMeter_Widget->ExclamationMarkImage->GetVisibility() == ESlateVisibility::Visible)
                    {
                        SuspiciousMeter_Widget->ExclamationMarkImage->SetVisibility(ESlateVisibility::Hidden);
                    }
                }
            }
            
            SuspiciousMeter_WidgetComponent->SetVisibility(true);
            SuspiciousMeter_WidgetComponent->SetHiddenInGame(false);
            SuspiciousMeter_Widget->SetVisibility(ESlateVisibility::Visible);
            SuspiciousMeter_Widget->Question_Mark->SetVisibility(ESlateVisibility::Visible);
        }
        else if (TypeOpenOrClose == "close")
        {
            SuspiciousMeter_WidgetComponent->SetVisibility(false);
            SuspiciousMeter_WidgetComponent->SetHiddenInGame(true);
            SuspiciousMeter_Widget->SetVisibility(ESlateVisibility::Hidden);
            SuspiciousMeter_Widget->Question_Mark->SetVisibility(ESlateVisibility::Hidden);
        }
    }
    else if (WhichWidget == "exclamation")
    {
        if (TypeOpenOrClose == "open")
        {
            if (SuspiciousMeter_WidgetComponent->IsVisible())
            {
                SuspiciousMeter_WidgetComponent->SetVisibility(false);
                SuspiciousMeter_WidgetComponent->SetHiddenInGame(true);

                if (SuspiciousMeter_Widget->GetVisibility() == ESlateVisibility::Visible)
                {
                    SuspiciousMeter_Widget->SetVisibility(ESlateVisibility::Hidden);
                    if (SuspiciousMeter_Widget->Question_Mark->GetVisibility() == ESlateVisibility::Visible)
                    {
                        SuspiciousMeter_Widget->Question_Mark->SetVisibility(ESlateVisibility::Hidden);
                    }
                    

                    //else
                    //{
                    //    return;
                    //}
                }
                //else
                //{
                 //   return;
                //}
            }
            

            SuspiciousMeter_WidgetComponent->SetVisibility(true);
            SuspiciousMeter_WidgetComponent->SetHiddenInGame(false);
            SuspiciousMeter_Widget->SetVisibility(ESlateVisibility::Visible);
            SuspiciousMeter_Widget->ExclamationMarkImage->SetVisibility(ESlateVisibility::Visible);
        }
        else if (TypeOpenOrClose == "close")
        {
            SuspiciousMeter_WidgetComponent->SetVisibility(false);
            SuspiciousMeter_WidgetComponent->SetHiddenInGame(true);
            SuspiciousMeter_Widget->SetVisibility(ESlateVisibility::Hidden);
            SuspiciousMeter_Widget->ExclamationMarkImage->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}




// Timer Functions!!!

void AAIC_Enemy::GetEnemyAndWidget()
{
    GetWorld()->GetTimerManager().ClearTimer(GetEnemyAndWidgetTimerHandle);

    Enemy = Cast<AEnemyBase>(GetPawn());

    if (IsValid(Enemy))
    {
        SuspiciousMeter_WidgetComponent = Enemy->FindComponentByClass<UWidgetComponent>();
        if (SuspiciousMeter_WidgetComponent)
        {
            UUserWidget* Widget = SuspiciousMeter_WidgetComponent->GetWidget();

            if (Widget)
            {
                SuspiciousMeter_Widget = Cast<USuspiciousMeterCPP>(Widget);

            }
        }
    }
}



void AAIC_Enemy::PlayerSawOrLostConfirmed(FString TypeSawOrLost, bool ChangeItTrueOrFalse)
{
    UE_LOG(LogTemp, Warning, TEXT("PlayerSawOrLostConfirmed Function is working!"))

    FString SightType = TypeSawOrLost.ToLower();
    bool SightBool = ChangeItTrueOrFalse;
    bool BB_SawConfirmedValue = BlackboardComp->GetValueAsBool("PlayerSawConfirmed");
    bool BB_LostConfirmedValue = BlackboardComp->GetValueAsBool("PlayerLostConfirmed");


    if (SightType == "saw")
    {
        if (SightBool == true)
        {
            if (BB_LostConfirmedValue == true)
            {
                BlackboardComp->SetValueAsBool(FName("PlayerLostConfirmed"), false);
                BlackboardComp->SetValueAsBool(FName("PlayerSawConfirmed"), true);
            }
            else
            {
                BlackboardComp->SetValueAsBool(FName("PlayerSawConfirmed"), true);
            }
        }
        else
        {
            BlackboardComp->SetValueAsBool(FName("PlayerSawConfirmed"), false);
        }
    }
    else if (SightType == "lost")
    {
        if (SightBool == true)
        {
            if (BB_SawConfirmedValue == true)
            {
                BlackboardComp->SetValueAsBool(FName("PlayerSawConfirmed"), false);
                BlackboardComp->SetValueAsBool(FName("PlayerLostConfirmed"), true);
            }
            else
            {
                BlackboardComp->SetValueAsBool(FName("PlayerLostConfirmed"), true);
            }
             
        }
        else
        {
            BlackboardComp->SetValueAsBool(FName("PlayerLostConfirmed"), false);
        }
    }
}



void AAIC_Enemy::DelayHandlerFunction()
{
    CanTick = true;
}



// AI Communication Functions

void AAIC_Enemy::WarnOtherAIs(EEnemySitutation Situtation, EEnemy_AlarmLevel AlarmLevel, FVector AlarmLocation, EEnemy_SuspiciousReason Reason)
{
    float BroadcastRadius = 0.f;

    switch (AlarmLevel)
    {
    case EEnemy_AlarmLevel::HugeAlarm:
        BroadcastRadius = 9999999.f;        // Alert Everyone
        break;
    case EEnemy_AlarmLevel::BigAlarm:
        BroadcastRadius = 4500.f;           // Alert only nearby AI's.
        break;
    case EEnemy_AlarmLevel::MiddleAlarm:
        BroadcastRadius = 0.f;
        break;                             // Alert nobody. Just go by himself
    case EEnemy_AlarmLevel::SmallAlarm:
        BroadcastRadius = 0.f;            // Alert nobody and dont investigate anything
        break; 
    case EEnemy_AlarmLevel::None:
        BroadcastRadius = 0.f;            
        break;
       
    }

    for (TActorIterator<APawn> It(GetWorld()); It; ++It)
    {
        APawn* OtherPawn = *It;
        if (OtherPawn == GetPawn()) continue;

        AAIC_Enemy* OtherAI = Cast<AAIC_Enemy>(OtherPawn->GetController());
        if (OtherAI)
        {
            float Distance = FVector::Dist(OtherPawn->GetActorLocation(), GetPawn()->GetActorLocation());
            if (Distance <= BroadcastRadius)
            {

                OtherAI->ReceiveWarnFromOtherAI(Situtation, AlarmLevel, AlarmLocation, Reason);

            }
        }
    }
}

void AAIC_Enemy::ReceiveWarnFromOtherAI(EEnemySitutation Situtation, EEnemy_AlarmLevel AlarmLevel, FVector AlarmLocation, EEnemy_SuspiciousReason Reason)
{
    switch (Situtation)
    {

    case EEnemySitutation::Patrol:
        SetEnemySitutationAs(EEnemySitutation::Patrol);
        break;
    case EEnemySitutation::Investigate:
        SetEnemySitutationAs(EEnemySitutation::Investigate);
        break;
    case EEnemySitutation::Alarm:
        SetEnemySitutationAs(EEnemySitutation::Alarm);
        break;
    case EEnemySitutation::LifeCycle:
        SetEnemySitutationAs(EEnemySitutation::LifeCycle);
        break;
    case EEnemySitutation::None:
        SetEnemySitutationAs(EEnemySitutation::None);
        break;
    default:
        break;
    }


    switch (AlarmLevel)
    {

    case EEnemy_AlarmLevel::HugeAlarm:
        BlackboardComp->SetValueAsVector(FName("PlayerLastKnownLocation"), AlarmLocation);
        SetEnemyAlarmLevelAs(EEnemy_AlarmLevel::HugeAlarm);
        break;
    case EEnemy_AlarmLevel::BigAlarm:
        BlackboardComp->SetValueAsVector(FName("PlayerLastKnownLocation"), AlarmLocation);
        SetEnemyAlarmLevelAs(EEnemy_AlarmLevel::BigAlarm);
        break;
    case EEnemy_AlarmLevel::MiddleAlarm:
        BlackboardComp->SetValueAsVector(FName("PlayerLastKnownLocation"), AlarmLocation);
        SetEnemyAlarmLevelAs(EEnemy_AlarmLevel::MiddleAlarm);
        break;
    case EEnemy_AlarmLevel::SmallAlarm:
        BlackboardComp->SetValueAsVector(FName("PlayerLastKnownLocation"), AlarmLocation);
        SetEnemyAlarmLevelAs(EEnemy_AlarmLevel::SmallAlarm);
        break;
    case EEnemy_AlarmLevel::None:
        SetEnemyAlarmLevelAs(EEnemy_AlarmLevel::None);
        break;
    default:
        break;
    }


    switch (Reason)
    {

    case EEnemy_SuspiciousReason::Saw:
        SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason::Saw);
        break;
    case EEnemy_SuspiciousReason::Smell:
        SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason::Smell);
        break;
    case EEnemy_SuspiciousReason::Heard:
        SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason::Heard);
        break;
    case EEnemy_SuspiciousReason::Touch:
        SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason::Touch);
        break;
    case EEnemy_SuspiciousReason::Damage:
        SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason::Damage);
        break;
    case EEnemy_SuspiciousReason::None:
        SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason::None);
        break;

    default:
        break;
    }

}





//Handling Enemy's Blackboard Value Fuctions

EEnemySitutation AAIC_Enemy::GetEnemySitutation() const
{
    uint8 CurrentEnemySitutation = BlackboardComp->GetValueAsEnum("EnemySitutation");
    return static_cast<EEnemySitutation>(CurrentEnemySitutation);
}

void AAIC_Enemy::SetEnemySitutationAs(EEnemySitutation NewSitutation)
{
    uint8 CurrentEnemySitutation = static_cast<uint8>(GetEnemySitutation());
    uint8 DesiredEnemySitutation = static_cast<uint8>(NewSitutation);

    if (!(NewSitutation == EEnemySitutation::None))
    {
        if (CurrentEnemySitutation > DesiredEnemySitutation)
        {
            return;
        }
        else
        {
            BlackboardComp->SetValueAsEnum(FName("EnemySitutation"), static_cast<uint8>(NewSitutation));
        }
    }
    else
    {
        BlackboardComp->SetValueAsEnum(FName("EnemySitutation"), static_cast<uint8>(NewSitutation));
    }
}






//Handling EnemyAlarmLevel Fuctions

EEnemy_AlarmLevel AAIC_Enemy::GetEnemyAlarmLevel() const
{
    uint8 CurrentEnemyAlarmLevel = BlackboardComp->GetValueAsEnum("EnemyAlarmLevel");
    return static_cast<EEnemy_AlarmLevel>(CurrentEnemyAlarmLevel);
}

void AAIC_Enemy::SetEnemyAlarmLevelAs(EEnemy_AlarmLevel NewAlarmLevel)
{
    
    uint8 CurrentEnemyAlarmLevel = static_cast<uint8>(GetEnemyAlarmLevel());
    uint8 DesiredNewAlarmLevel = static_cast<uint8>(NewAlarmLevel);
    
    
     if (GetEnemySitutation() == EEnemySitutation::Alarm)
    {
        if (CurrentEnemyAlarmLevel > DesiredNewAlarmLevel)
        {
            return;
        }
        else
        {
            BlackboardComp->SetValueAsEnum(FName("EnemyAlarmLevel"), static_cast<uint8>(NewAlarmLevel));
        }
        
    }
    else
    {
        BlackboardComp->SetValueAsEnum(FName("EnemyAlarmLevel"), static_cast<uint8>(EEnemy_AlarmLevel::None));
    }
    

    /*
    if (CurrentEnemyAlarmLevel > DesiredNewAlarmLevel)
    {
        return;
    }
    else
    {
        BlackboardComp->SetValueAsEnum(FName("EnemyAlarmLevel"), static_cast<uint8>(NewAlarmLevel));
    }
    */
    


}


//Handling Enemy_SuspiciousReason Fuctions

EEnemy_SuspiciousReason AAIC_Enemy::GetEnemySuspiciousReason() const
{
    uint8 CurrentEnemySuspiciousReason = BlackboardComp->GetValueAsEnum("Enemy_InvestigateSuspiciousReason");
    return static_cast<EEnemy_SuspiciousReason>(CurrentEnemySuspiciousReason);
}

void AAIC_Enemy::SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason NewSuspiciousReason)
{
    uint8 CurrentSuspiciousReason = static_cast<uint8>(GetEnemySuspiciousReason());
    uint8 DesiredSuspiciousReason = static_cast<uint8>(NewSuspiciousReason);

    
    if (GetEnemySitutation() == EEnemySitutation::Investigate) 
    {
        if (CurrentSuspiciousReason > DesiredSuspiciousReason)
        {
            return;
        }
        else
        {
            BlackboardComp->SetValueAsEnum(FName("Enemy_InvestigateSuspiciousReason"), static_cast<uint8>(NewSuspiciousReason));
        }
    }
    else
    {
        BlackboardComp->SetValueAsEnum(FName("Enemy_InvestigateSuspiciousReason"), static_cast<uint8>(EEnemy_SuspiciousReason::None));
    }
}




EEnemy_HeardReason AAIC_Enemy::GetEnemyHeardReason() const
{
    uint8 CurrentEnemyHeardReason = BlackboardComp->GetValueAsEnum("Enemy_HeardReason");
    return static_cast<EEnemy_HeardReason>(CurrentEnemyHeardReason);
}

void AAIC_Enemy::SetEnemyHeardReasonAs(EEnemy_HeardReason NewHeardReason)
{
    uint8 CurrentHeardReason = static_cast<uint8>(GetEnemyHeardReason());
    uint8 DesiredHeardReason = static_cast<uint8>(NewHeardReason);

    BlackboardComp->SetValueAsEnum(FName("Enemy_HeardReason"), static_cast<uint8>(NewHeardReason));

    // Can be Change!
    if (GetEnemySuspiciousReason() == EEnemy_SuspiciousReason::Heard)
    {
        if (CurrentHeardReason > DesiredHeardReason)
        {
            return;
        }
        else
        {
            BlackboardComp->SetValueAsEnum(FName("Enemy_HeardReason"), static_cast<uint8>(NewHeardReason));
        }
    }
    else
    {
        BlackboardComp->SetValueAsEnum(FName("Enemy_HeardReason"), static_cast<uint8>(EEnemy_HeardReason::None));
    }
}



