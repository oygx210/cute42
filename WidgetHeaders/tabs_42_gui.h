#ifndef TABS_42_GUI_H
#define TABS_42_GUI_H

#include <QWidget>

class Tabs_42_GUI: public QWidget
{
    Q_OBJECT
public:
    Tabs_42_GUI(QWidget* parent = nullptr);
    virtual ~Tabs_42_GUI();
};

class Tab_Mission: public QWidget
{
    Q_OBJECT
public:
    Tab_Mission(QWidget* parent = nullptr);
    virtual ~Tab_Mission();
};

class Tab_MissionSetUp: public QWidget
{
    Q_OBJECT
public:
    Tab_MissionSetUp(QWidget* parent = nullptr);
    virtual ~Tab_MissionSetUp();
};

class Tab_MissionOutput: public QWidget
{
    Q_OBJECT
public:
    Tab_MissionOutput(QWidget* parent = nullptr);
    virtual ~Tab_MissionOutput();
};



#endif // TABS_42_GUI_H
