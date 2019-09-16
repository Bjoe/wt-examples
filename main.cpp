#include <Wt/WApplication.h>
#include <Wt/WServer.h>
#include <Wt/WWidget.h>
#include <Wt/WBootstrapTheme.h>

#include <memory>

#include "mainmenu.h"

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env)
{
    auto app = std::make_unique<Wt::WApplication>(env);

    // Set bootstrap theme see http://getbootstrap.com/
    std::shared_ptr<Wt::WBootstrapTheme> theme = std::make_shared<Wt::WBootstrapTheme>();
    theme->setVersion(Wt::BootstrapVersion::v3);
    app->setTheme(theme);

    // load approot/template.xml
    app->messageResourceBundle().use(app->appRoot() + "templates");

    // load approot/strings.xml
    // (or approot/strings_nl.xml)
    app->messageResourceBundle().use(app->appRoot() + "strings");

    // add stylesheet
    app->useStyleSheet("style.css");

    app->setTitle("Hello EULA");

    example::MainMenu* mainMenu = app->root()->addWidget(std::make_unique<example::MainMenu>());

    app->internalPathChanged().connect(mainMenu, &example::MainMenu::handlePathChange);

    return app;
}

int main(int argc, char **argv)
{
    try {
      Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);

      server.addEntryPoint(Wt::EntryPointType::Application, createApplication);

      server.run();
    } catch (Wt::WServer::Exception& e) {
      std::cerr << e.what() << std::endl;
    } catch (std::exception &e) {
      std::cerr << "exception: " << e.what() << std::endl;
    }
  }
