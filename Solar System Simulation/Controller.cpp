#include "Controller.h"
#include "InputHandler.h"
#include "Pawn.h"

Controller::Controller()
{
    InputComponent = std::shared_ptr<InputHandler>(new InputHandler());
    ControlledPawn = std::shared_ptr<Pawn>(new Pawn(glm::vec3(0.0f, 0.0f, -3.0f)));
    if (ControlledPawn && InputComponent)
    {
        ControlledPawn->SetupInput(InputComponent);
    }
}

void Controller::ProcessKeyboard(int Key, int Scancode, int Action, int Mods) 
{
    InputComponent->InputTriggered(static_cast<EKey>(Key), static_cast<ETriggerEvent>(Action));
}

void Controller::ProcessMouseMotion(double XPos, double YPos) 
{

}

glm::mat4 Controller::GetView() const
{
    return ControlledPawn->GetView();
}