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
	auto TargetLocation = Weapon->GetActorLocation();

	if (auto NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()) /*&& NavSys->ProjectPointToNavigation(TargetLocation, NavLocation, FVector(1000.f, 1000.f, 100.f))*/)
	{
		FNavLocation NavLocation;
		TargetLocation = NavLocation.Location; // This ensures the vector sits perfectly on the NavMesh
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TargetLocation);

	// Clean exit: No FinishLatentTask needed for instant success
	return EBTNodeResult::Succeeded;
}
