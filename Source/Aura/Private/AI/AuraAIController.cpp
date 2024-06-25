// Fedahumada 


#include "AI/AuraAIController.h"

AAuraAIController::AAuraAIController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
	check(BlackboardComponent);
	BehaviorTreeComponent= CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
	check(BehaviorTreeComponent);
}
