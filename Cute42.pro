QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DataDefinitions/fieldofview.cpp \
    DataDefinitions/inp_ipc.cpp \
    DataDefinitions/inpsimenvironment.cpp \
    DataDefinitions/inpsimterms.cpp \
    DataDefinitions/mission.cpp \
    DataDefinitions/missionholder.cpp \
    DataDefinitions/orbittype.cpp \
    DataDefinitions/qt42_headers.cpp \
    DataDefinitions/qt42abstractbaseclass.cpp \
    DataDefinitions/qt42baseclass.cpp \
    DataDefinitions/qt42region.cpp \
    DataDefinitions/spacecraft.cpp \
    DataDefinitions/spacecraftcomponents.cpp \
    MVDdefinitions/qt42delegate.cpp \
    MVDdefinitions/qt42model.cpp \
    ShareDefinitions/qt42_sharedparameters.cpp \
    ShareDefinitions/qt42commands.cpp \
    WidgetDefinitions/fovdialog.cpp \
    WidgetDefinitions/graphicsdialog.cpp \
    WidgetDefinitions/inpipcdialog.cpp \
    WidgetDefinitions/inpregiondialog.cpp \
    WidgetDefinitions/inpsimtermswidgets.cpp \
    WidgetDefinitions/inptdrsdialog.cpp \
    WidgetDefinitions/lineeditor42.cpp \
    WidgetDefinitions/mainwindow_42.cpp \
    WidgetDefinitions/qt42delegatelineeditor.cpp \
    WidgetDefinitions/qt42dragwidget.cpp \
    WidgetDefinitions/referenceorbitdialog.cpp \
    WidgetDefinitions/sccomponentswidgets.cpp \
    WidgetDefinitions/spacecraftdialog.cpp \
    WidgetDefinitions/tabs_42_gui.cpp \
    WidgetDefinitions/viewlistmissions.cpp \
    main.cpp


HEADERS += \
    DataHeaders/fieldofview.h \
    DataHeaders/inp_ipc.h \
    DataHeaders/inpsimenvironment.h \
    DataHeaders/inpsimterms.h \
    DataHeaders/mission.h \
    DataHeaders/missionholder.h \
    DataHeaders/orbittype.h \
    DataHeaders/qt42_headers.h \
    DataHeaders/qt42abstractbaseclass.h \
    DataHeaders/qt42baseclass.h \
    DataHeaders/qt42region.h \
    DataHeaders/spacecraft.h \
    DataHeaders/spacecraftcomponents.h \
    MVDheaders/qt42delegate.h \
    MVDheaders/qt42model.h \
    ShareHeaders/qt42_sharedparameters.h \
    ShareHeaders/qt42commands.h \
    WidgetHeaders/fovdialog.h \
    WidgetHeaders/graphicsdialog.h \
    WidgetHeaders/inpipcdialog.h \
    WidgetHeaders/inpregiondialog.h \
    WidgetHeaders/inpsimtermswidgets.h \
    WidgetHeaders/inptdrsdialog.h \
    WidgetHeaders/lineeditor42.h \
    WidgetHeaders/mainwindow_42.h \
    WidgetHeaders/qt42delegatelineeditor.h \
    WidgetHeaders/qt42dragwidget.h \
    WidgetHeaders/referenceorbitdialog.h \
    WidgetHeaders/sccomponentswidgets.h \
    WidgetHeaders/spacecraftdialog.h \
    WidgetHeaders/tabs_42_gui.h \
    WidgetHeaders/viewlistmissions.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
