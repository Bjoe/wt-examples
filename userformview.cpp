#include "userformview.h"

#include <Wt/WPushButton.h>
#include <Wt/WTextArea.h>
#include <Wt/WSpinBox.h>
#include <Wt/WDate.h>
#include <Wt/WDateEdit.h>
#include <Wt/WComboBox.h>
#include <Wt/WLineEdit.h>
#include <Wt/WString.h>

namespace example {

UserFormView::UserFormView()
{
    model = std::make_shared<UserFormModel>();

    setTemplateText(tr("userForm-template"));
    addFunction("id", &WTemplate::Functions::id);
    addFunction("block", &WTemplate::Functions::id);

    /*
    * First Name
    */
    setFormWidget(UserFormModel::FirstNameField,
                  std::make_unique<Wt::WLineEdit>());

    /*
    * Last Name
    */
    setFormWidget(UserFormModel::LastNameField,
                  std::make_unique<Wt::WLineEdit>());

    /*
    * Country
    */
    auto countryCB = std::make_unique<Wt::WComboBox>();
    auto countryCB_ = countryCB.get();
    countryCB->setModel(model->countryModel());

    countryCB_->activated().connect([=] {
        std::string code = model->countryCode(countryCB_->currentIndex());
        model->updateCityModel(code);
    });

    setFormWidget(UserFormModel::CountryField, std::move(countryCB),
                  [=] { // updateViewValue()
        std::string code =
                Wt::asString(model->value(UserFormModel::CountryField)).toUTF8();
        int row = model->countryModelRow(code);
        countryCB_->setCurrentIndex(row);
    },

    [=] { // updateModelValue()
        std::string code = model->countryCode(countryCB_->currentIndex());
        model->setValue(UserFormModel::CountryField, code);
    });

    /*
    * City
    */
    auto cityCB = std::make_unique<Wt::WComboBox>();
    cityCB->setModel(model->cityModel());
    setFormWidget(UserFormModel::CityField, std::move(cityCB));

    /*
    * Birth Date
    */
    auto dateEdit = std::make_unique<Wt::WDateEdit>();
    auto dateEdit_ = dateEdit.get();
    setFormWidget(UserFormModel::BirthField, std::move(dateEdit),
                  [=] { // updateViewValue()
        Wt::WDate date = Wt::cpp17::any_cast<Wt::WDate>
                (model->value(UserFormModel::BirthField));
        dateEdit_->setDate(date);
    },

    [=] { // updateModelValue()
        Wt::WDate date = dateEdit_->date();
        model->setValue(UserFormModel::BirthField, date);
    });

    /*
    * Children
    */
    setFormWidget(UserFormModel::ChildrenField, std::make_unique<Wt::WSpinBox>());

    /*
    * Remarks
    */
    auto remarksTA = std::make_unique<Wt::WTextArea>();
    remarksTA->setColumns(40);
    remarksTA->setRows(5);
    setFormWidget(UserFormModel::RemarksField, std::move(remarksTA));

    /*
    * Title & Buttons
    */
    Wt::WString title = Wt::WString("Create new user");
    bindString("title", title);

    auto button = std::make_unique<Wt::WPushButton>("Save");
    auto button_ = bindWidget("submit-button", std::move(button));

    bindString("submit-info", Wt::WString());

    button_->clicked().connect(this, &UserFormView::process);

    updateView(model.get());
}

void UserFormView::process()
{
    updateModel(model.get());

    if (model->validate()) {
        // Do something with the data in the model: show it.
        bindString("submit-info",
                   Wt::WString("Saved user data for ")
                   + model->userData(), Wt::TextFormat::Plain);
        // Udate the view: Delete any validation message in the view, etc.
        updateView(model.get());
        // Set the focus on the first field in the form.
        Wt::WLineEdit *viewField =
                resolve<Wt::WLineEdit*>(UserFormModel::FirstNameField);
        viewField->setFocus(true);
    } else {
        bindEmpty("submit-info"); // Delete the previous user data.
        updateView(model.get());
    }
}

} // namespace example
