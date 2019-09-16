#ifndef EXAMPLES_EULA_H
#define EXAMPLES_EULA_H

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>

namespace example {

class Eula : public Wt::WContainerWidget
{
public:
    Eula();

private:
    Wt::WText* state_ = {};

};

} // namespace example

#endif // EXAMPLES_EULA_H
