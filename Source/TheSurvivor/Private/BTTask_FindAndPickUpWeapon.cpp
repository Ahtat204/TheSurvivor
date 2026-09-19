#include "BTTask_FindAndPickUpWeapon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Npc.h"
#include "NavigationSystem.h"
#include "NpcAIController.h"
#include "Weapon.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FindAndPickUpWeapon::UBTTask_FindAndPickUpWeapon(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "FindWeapon";
    
	// Crucial: Tell the node to filter for Vectors in the behavior tree details panel
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindAndPickUpWeapon, BlackboardKey));
}

EBTNodeResult::Type UBTTask_FindAndPickUpWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = Cast<ANpcAIController>(OwnerComp.GetOwner());
	if (!Controller) return EBTNodeResult::Failed;

	const auto Pawn = Cast<ANpc>(Controller->GetPawn());
	if (!Pawn) return EBTNodeResult::Failed;

	const auto Weapon = UGameplayStatics::GetActorOfClass(GetWorld(), AWeapon::StaticClass());
	if (!Weapon) return EBTNodeResult::Failed;

	// Set the location on the blackboard
	FVector TargetLocation = Weapon->GetActorLocation();
	FNavLocation NavLocation;

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (NavSys && NavSys->ProjectPointToNavigation(TargetLocation, NavLocation, FVector(1000.f, 1000.f, 100.f)))
	{
		TargetLocation = NavLocation.Location; // This ensures the vector sits perfectly on the NavMesh
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TargetLocation);

	// Clean exit: No FinishLatentTask needed for instant success
	return EBTNodeResult::Succeeded;
}
