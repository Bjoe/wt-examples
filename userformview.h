#ifndef EXAMPLE_USERFORMVIEW_H
#define EXAMPLE_USERFORMVIEW_H

#include <Wt/WTemplateFormView.h>
#include <memory>
#include "userformmodel.h"

namespace example {

class UserFormView : public Wt::WTemplateFormView
{
public:
    UserFormView();

private:
    std::shared_ptr<UserFormModel> model;

    void process();
};

} // namespace example

#endif // EXAMPLE_USERFORMVIEW_H
