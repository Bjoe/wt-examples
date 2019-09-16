#ifndef EXAMPLE_USERFORMMODEL_H
#define EXAMPLE_USERFORMMODEL_H

#include <Wt/WFormModel.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WAbstractItemModel.h>
#include <Wt/WValidator.h>
#include <Wt/WString.h>
#include <memory>
#include <string>
#include <vector>

namespace example {

class UserFormModel : public Wt::WFormModel
{
public:
    // Associate each field with a unique string literal.
    static const Field FirstNameField;
    static const Field LastNameField;
    static const Field CountryField;
    static const Field CityField;
    static const Field BirthField;
    static const Field ChildrenField;
    static const Field RemarksField;

    UserFormModel();

    std::shared_ptr<Wt::WAbstractItemModel> countryModel()
    {
        return countryModel_;
    }
    int countryModelRow(const std::string& code);

    std::shared_ptr<Wt::WAbstractItemModel> cityModel()
    {
        return cityModel_;
    }
    void updateCityModel(const std::string& countryCode);

    Wt::WString userData();

    std::string countryCode (int row);

    typedef std::map<std::string, std::vector<std::string>> CityMap;
    typedef std::map<std::string, std::string> CountryMap;

private:
    static const CityMap cities;
    static const CountryMap countries;
    std::shared_ptr<Wt::WStandardItemModel> countryModel_, cityModel_;

    static const int MAX_LENGTH;
    static const int MAX_CHILDREN;

    void initializeModels();

    std::shared_ptr<Wt::WValidator> createNameValidator(const std::string& field);
    std::shared_ptr<Wt::WValidator> createCountryValidator();
    std::shared_ptr<Wt::WValidator> createCityValidator();
    std::shared_ptr<Wt::WValidator> createBirthValidator();
    std::shared_ptr<Wt::WValidator> createChildrenValidator();
};

} // namespace example

#endif // EXAMPLE_USERFORMMODEL_H
