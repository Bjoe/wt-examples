#include "registration.h"

#include <memory>

namespace example {

Registration::Registration()
{
    userFormView_ = addWidget(std::make_unique<UserFormView>());
}

} // namespace example
