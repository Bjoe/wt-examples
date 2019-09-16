#include "mainmenu.h"

#include <Wt/WApplication.h>
#include <Wt/WStackedWidget.h>

#include <memory>

namespace example {

MainMenu::MainMenu() : Wt::WContainerWidget()
{
    mainStack_ = new Wt::WStackedWidget();

    eula_ = mainStack_->addWidget(std::make_unique<Eula>());
    mainStack_->setCurrentWidget(eula_);

    addWidget(std::unique_ptr<Wt::WStackedWidget>(mainStack_));
}

void MainMenu::handlePathChange()
{
    Wt::WApplication* app = Wt::WApplication::instance();
    if(app->internalPath() == "/reg")
    {
        if(registration_ == nullptr)
        {
            registration_ = mainStack_->addWidget(std::make_unique<Registration>());
        }
        mainStack_->setCurrentWidget(registration_);
    }
    else if(app->internalPath() == "/eula")
    {
        mainStack_->setCurrentWidget(eula_);
    }
}

} // namespace example
