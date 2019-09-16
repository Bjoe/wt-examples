#ifndef EXAMPLE_REGISTARTION_H
#define EXAMPLE_REGISTARTION_H

#include <Wt/WContainerWidget.h>

#include "userformview.h"

namespace example {

class Registration : public Wt::WContainerWidget
{
public:
    Registration();

private:
    UserFormView* userFormView_ = {};
};

} // namespace example

#endif // EXAMPLE_REGISTARTION_H
