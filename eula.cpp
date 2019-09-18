#include "eula.h"

#include <Wt/WPushButton.h>
#include <Wt/WMessageBox.h>
#include <Wt/WFlags.h>
#include <Wt/WLink.h>
#include <Wt/WBreak.h>

namespace example {

Eula::Eula()
{
    addNew<Wt::WText>(tr("str.eula"));
    addNew<Wt::WBreak>();

    auto acceptButton = addWidget(std::make_unique<Wt::WPushButton>(tr("btn.accept")));
    auto declineButton = addWidget(std::make_unique<Wt::WPushButton>(tr("btn.decline")));

    acceptButton->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/reg"));

    addWidget(Wt::cpp14::make_unique<Wt::WBreak>());

    declineButton->clicked().connect([=]() {
      Wt::WMessageBox::show("EULA", tr("str.eula_decline"), Wt::StandardButton::Ok);
    });

}

} // namespace example
