#include "userformmodel.h"

#include <Wt/WDate.h>
#include <Wt/WStandardItem.h>
#include <Wt/WLengthValidator.h>
#include <Wt/WDateValidator.h>
#include <Wt/WIntValidator.h>

namespace example {

const int UserFormModel::MAX_LENGTH = 25;
const int UserFormModel::MAX_CHILDREN = 15;

const Wt::WFormModel::Field UserFormModel::FirstNameField = "first-name";
const Wt::WFormModel::Field UserFormModel::LastNameField = "last-name";
const Wt::WFormModel::Field UserFormModel::CountryField = "country";
const Wt::WFormModel::Field UserFormModel::CityField = "city";
const Wt::WFormModel::Field UserFormModel::BirthField = "birth";
const Wt::WFormModel::Field UserFormModel::ChildrenField = "children";
const Wt::WFormModel::Field UserFormModel::RemarksField = "remarks";

const UserFormModel::CountryMap UserFormModel::countries = {
  { "BE", { "Belgium" } },
  { "NL", { "Netherlands" } },
  { "UK", { "United Kingdom" } },
  { "US", { "United States" } }
};

const UserFormModel::CityMap UserFormModel::cities = {
  { "BE", { "Antwerp", "Bruges", "Brussels", "Ghent" } },
  { "NL", { "Amsterdam", "Eindhoven", "Rotterdam", "The Hague"} },
  { "UK", { "London", "Bristol", "Oxford", "Stonehenge"} },
  { "US", { "Boston", "Chicago", "Los Angeles", "New York"} }
};

UserFormModel::UserFormModel() : Wt::WFormModel()
{
    initializeModels();

    addField(FirstNameField);
    addField(LastNameField);
    addField(CountryField);
    addField(CityField);
    addField(BirthField);
    addField(ChildrenField);
    addField(RemarksField);

    setValidator(FirstNameField, createNameValidator(FirstNameField));
    setValidator(LastNameField, createNameValidator(LastNameField));
    setValidator(CountryField, createCountryValidator());
    setValidator(CityField, createCityValidator());
    setValidator(BirthField, createBirthValidator());
    setValidator(ChildrenField, createChildrenValidator());

    // Here you could populate the model with initial data using
    // setValue() for each field.
    setValue(BirthField, Wt::WDate());
    setValue(CountryField, std::string());

}

int UserFormModel::countryModelRow(const std::string &code)
{
    for (int i = 0; i < countryModel_->rowCount(); ++i)
        if (countryCode(i) == code)
            return i;

    return -1;
}

void UserFormModel::updateCityModel(const std::string &countryCode)
{
    cityModel_->clear();

    CityMap::const_iterator i = cities.find(countryCode);

    if (i != cities.end()) {
        const std::vector<std::string>& cities = i->second;

        // The initial text shown in the city combo box should be an empty
        // string.
        cityModel_->appendRow(std::make_unique<Wt::WStandardItem>());

        for (unsigned j = 0; j < cities.size(); ++j)
            cityModel_->appendRow(std::make_unique<Wt::WStandardItem>(cities[j]));
    } else {
        cityModel_->appendRow(
                    std::make_unique<Wt::WStandardItem>("(Choose Country first)"));
    }
}

Wt::WString UserFormModel::userData()
{
    return
            Wt::asString(value(FirstNameField)) + " " +
            Wt::asString(value(LastNameField))
            + ": country code=" + Wt::asString(value(CountryField))
            + ", city=" + Wt::asString(value(CityField))
            + ", birth=" + Wt::asString(value(BirthField))
            + ", children=" + Wt::asString(value(ChildrenField))
            + ", remarks=" + Wt::asString(value(RemarksField))
            + ".";
}

std::string UserFormModel::countryCode(int row)
{
    return Wt::asString(countryModel_->data(row, 0, Wt::ItemDataRole::User)).toUTF8();
}

void UserFormModel::initializeModels()
{
    // Create a country model.
    unsigned countryModelRows = countries.size() + 1;
    const unsigned countryModelColumns = 1;
    countryModel_ =
            std::make_shared<Wt::WStandardItemModel>(countryModelRows, countryModelColumns);

    // The initial text shown in the country combo box should be an empty
    // string.
    int row = 0;
    countryModel_->setData(row, 0, std::string(" "), Wt::ItemDataRole::Display);
    countryModel_->setData(row, 0, std::string(), Wt::ItemDataRole::User);

    // For each country, update the model based on the key (corresponding
    // to the country code):
    // - set the country name for the display role,
    // - set the city names for the user role.
    row = 1;
    for (CountryMap::const_iterator i = countries.begin();
         i != countries.end(); ++i) {
        countryModel_->setData(row, 0, i->second, Wt::ItemDataRole::Display);
        countryModel_->setData(row++, 0, i->first, Wt::ItemDataRole::User);
    }

    // Create a city model.
    cityModel_ = std::make_shared<Wt::WStandardItemModel>();
    updateCityModel(std::string());
}

std::shared_ptr<Wt::WValidator> UserFormModel::createNameValidator(const std::string &field)
{
    auto v = std::make_shared<Wt::WLengthValidator>();
    v->setMandatory(true);
    v->setMinimumLength(1);
    v->setMaximumLength(MAX_LENGTH);
    return v;
}

std::shared_ptr<Wt::WValidator> UserFormModel::createCountryValidator()
{
    auto v = std::make_shared<Wt::WLengthValidator>();
    v->setMandatory(true);
    return v;
}

std::shared_ptr<Wt::WValidator> UserFormModel::createCityValidator()
{
    auto v = std::make_shared<Wt::WLengthValidator>();
    v->setMandatory(true);
    return v;

}

std::shared_ptr<Wt::WValidator> UserFormModel::createBirthValidator()
{
    auto v = std::make_shared<Wt::WDateValidator>();
    v->setBottom(Wt::WDate(1900, 1, 1));
    v->setTop(Wt::WDate::currentDate());
    v->setFormat("dd/MM/yyyy");
    v->setMandatory(true);
    return v;
}

std::shared_ptr<Wt::WValidator> UserFormModel::createChildrenValidator()
{
    auto v = std::make_shared<Wt::WIntValidator>(0, MAX_CHILDREN);
    v->setMandatory(true);
    return v;

}



} // namespace example
