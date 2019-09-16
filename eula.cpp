#include "eula.h"

#include <Wt/WPushButton.h>
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
    state_ = addWidget(Wt::cpp14::make_unique<Wt::WText>());

    declineButton->clicked().connect([=]() {
      state_->setText(tr("str.eula_decline"));
    });

}

} // namespace example
