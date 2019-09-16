#ifndef EXAMPLE_MAINMENU_H
#define EXAMPLE_MAINMENU_H

#include <Wt/WContainerWidget.h>

#include "registration.h"
#include "eula.h"

namespace Wt {
    class WStackedWidget;
}

namespace example {

class MainMenu : public Wt::WContainerWidget
{
public:
    MainMenu();

    void handlePathChange();

private:
    Wt::WStackedWidget* mainStack_ = {};
    Registration* registration_ = {};
    Eula* eula_ = {};
};

} // namespace example

#endif // EXAMPLE_MAINMENU_H
