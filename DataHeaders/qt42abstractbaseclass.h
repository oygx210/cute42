/* class: Qt42AbstractBaseClass
 * Purpose: for all the inheriting subclasses (Qt42BaseClass, MissionHolder, Mission,
 * SpacecraftHeader, Spacecraft, and etc..)
 * to follow specific behaviour (type(), name(), index, updateName and etc..)
 * since it will make it easier to design custom type to fit the Model/View
 * architecture.
*/

/* Note: Don't include this custom type in the QVariant() since the abstract base class
 * is not allowed.
*/


#ifndef QT42ABSTRACTBASECLASS_H
#define QT42ABSTRACTBASECLASS_H

#include "ShareHeaders/qt42_sharedparameters.h"
class Qt42AbstractBaseClass
{
public:
    Qt42AbstractBaseClass();
    Qt42AbstractBaseClass(const Qt42AbstractBaseClass& Qt42ABC);
    virtual ~Qt42AbstractBaseClass();
    virtual objectType type() const = 0;
    virtual QString name() const = 0;
    virtual int index() const = 0;
};

#endif // QT42ABSTRACTBASECLASS_H
