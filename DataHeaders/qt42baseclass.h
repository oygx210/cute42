#ifndef QT42BASECLASS_H
#define QT42BASECLASS_H

#include "ShareHeaders/qt42_sharedparameters.h"
#include "qt42abstractbaseclass.h"
#include <QString>
#include <QVariant>

class Qt42BaseClass : public Qt42AbstractBaseClass
{
public:
    Qt42BaseClass();
    virtual ~Qt42BaseClass() override;
    Qt42BaseClass(const Qt42BaseClass& QBC);
    virtual objectType type() const override {return m_type;}
    virtual QString name() const override {return m_name;}
    virtual int index() const override {return m_index;}
    virtual void setIncludedInCalculation(const bool& included = true) {m_includedInCalculation = included;}
    virtual bool includedInCalculation() const {return m_includedInCalculation;}

protected:
    virtual void changeType(const objectType& type = QT42BASECLASS) {m_type = type;}
    void changeName(const QString& name = "Qt42 Base Class"){m_name = name;}

private:
    objectType m_type = QT42BASECLASS;
    QString m_name = "Qt42 Base Class";
    int m_index = -1;
    bool m_includedInCalculation = true;
};


Q_DECLARE_METATYPE(Qt42BaseClass)
#endif // QT42BASECLASS_H
