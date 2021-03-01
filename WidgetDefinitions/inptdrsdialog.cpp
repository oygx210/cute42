#include "WidgetHeaders/inptdrsdialog.h"
#include "MVDheaders/qt42model.h"
#include "DataHeaders/mission.h"
#include "ShareHeaders/qt42commands.h"
#include <QAbstractItemModel>
#include <QAction>
#include <QUndoStack>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QGroupBox>
#include <QDialogButtonBox>
#include <QTabWidget>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

InpTDRsDialog::InpTDRsDialog(QWidget* parent) : QDialog(parent)
{
    m_tabWidgetParent = qobject_cast<QTabWidget*>(parent);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save  |
                                       QDialogButtonBox::Apply |
                                       QDialogButtonBox::Cancel);
    m_undoStack = new QUndoStack(this);
    createWidgets();
    createActions();
    createConnections();
}

InpTDRsDialog::~InpTDRsDialog()
{

}

void InpTDRsDialog::setModel(QAbstractItemModel *model)
{
    if (model)
        m_model = static_cast<Qt42Model*>(model);
    else
        m_model = nullptr;
}

void InpTDRsDialog::setRootIndex(const QModelIndex &index)
{
    if (!index.isValid() || !index.data().canConvert<InpTDRs>())
    {
        m_index = QModelIndex();
        m_inpTDRs = InpTDRs();
        return;
    }
    m_index = index;
    m_inpTDRs = m_index.data().value<InpTDRs>();
    mapDataFromModelToWidget();
    m_buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
    m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);
}

void InpTDRsDialog::createWidgets()
{
    QFormLayout* layoutDialog = new QFormLayout;
    labelMission = new QLabel(tr("Mission: "));
    QFont fontLabelMission("Arial", 14, QFont::Bold);
    labelMission->setFont(fontLabelMission);

    groupboxEdit = new QGroupBox(tr("Edit"));
    groupboxEdit->setAlignment(Qt::AlignCenter);
    QPalette pal;
    pal.setColor(QPalette::Window, Qt::gray);
    groupboxEdit->setAutoFillBackground(true);
    groupboxEdit->setPalette(pal);
    QHBoxLayout* layoutEdit = new QHBoxLayout;
    QVBoxLayout* layoutEditLeft = new QVBoxLayout;
    QVBoxLayout* layoutEditRight = new QVBoxLayout;

    groupboxTDRS_1 = new QGroupBox(tr("TDRS-1"));
    QHBoxLayout* layoutTDRS_1 = new QHBoxLayout;
    chkbxTDRS_1 = new QCheckBox(tr("Exists"));
    labelDesignationTDRS_1 = new QLabel(tr("Designation"));
    editDesignationTDRS_1 = new QLineEdit;
    layoutTDRS_1->addWidget(chkbxTDRS_1, 1);
    layoutTDRS_1->addWidget(labelDesignationTDRS_1,1);
    layoutTDRS_1->addWidget(editDesignationTDRS_1,2);
    groupboxTDRS_1->setLayout(layoutTDRS_1);


    groupboxTDRS_2 = new QGroupBox(tr("TDRS-2")+QString::fromUtf8("\u002A")); //"\U002A": UTF8 code of asterisk or star.
    QHBoxLayout* layoutTDRS_2 = new QHBoxLayout;
    chkbxTDRS_2 = new QCheckBox(tr("Exists"));
    labelDesignationTDRS_2 = new QLabel(tr("Designation"));
    editDesignationTDRS_2 = new QLineEdit;
    layoutTDRS_2->addWidget(chkbxTDRS_2, 1);
    layoutTDRS_2->addWidget(labelDesignationTDRS_2,1);
    layoutTDRS_2->addWidget(editDesignationTDRS_2,2);
    groupboxTDRS_2->setLayout(layoutTDRS_2);
    groupboxTDRS_2->setDisabled(true);

    groupboxTDRS_3 = new QGroupBox(tr("TDRS-3"));
    QHBoxLayout* layoutTDRS_3 = new QHBoxLayout;
    chkbxTDRS_3 = new QCheckBox(tr("Exists"));
    labelDesignationTDRS_3 = new QLabel(tr("Designation"));
    editDesignationTDRS_3 = new QLineEdit;
    layoutTDRS_3->addWidget(chkbxTDRS_3, 1);
    layoutTDRS_3->addWidget(labelDesignationTDRS_3,1);
    layoutTDRS_3->addWidget(editDesignationTDRS_3,2);
    groupboxTDRS_3->setLayout(layoutTDRS_3);

    groupboxTDRS_4 = new QGroupBox(tr("TDRS-4"));
    QHBoxLayout* layoutTDRS_4 = new QHBoxLayout;
    chkbxTDRS_4 = new QCheckBox(tr("Exists"));
    labelDesignationTDRS_4 = new QLabel(tr("Designation"));
    editDesignationTDRS_4 = new QLineEdit;
    layoutTDRS_4->addWidget(chkbxTDRS_4, 1);
    layoutTDRS_4->addWidget(labelDesignationTDRS_4,1);
    layoutTDRS_4->addWidget(editDesignationTDRS_4,2);
    groupboxTDRS_4->setLayout(layoutTDRS_4);

    groupboxTDRS_5 = new QGroupBox(tr("TDRS-5"));
    QHBoxLayout* layoutTDRS_5 = new QHBoxLayout;
    chkbxTDRS_5 = new QCheckBox(tr("Exists"));
    labelDesignationTDRS_5 = new QLabel(tr("Designation"));
    editDesignationTDRS_5 = new QLineEdit;
    layoutTDRS_5->addWidget(chkbxTDRS_5, 1);
    layoutTDRS_5->addWidget(labelDesignationTDRS_5,1);
    layoutTDRS_5->addWidget(editDesignationTDRS_5,2);
    groupboxTDRS_5->setLayout(layoutTDRS_5);

    groupboxTDRS_6 = new QGroupBox(tr("TDRS-6"));
    QHBoxLayout* layoutTDRS_6 = new QHBoxLayout;
    chkbxTDRS_6 = new QCheckBox(tr("Exists"));
    labelDesignationTDRS_6 = new QLabel(tr("Designation"));
    editDesignationTDRS_6 = new QLineEdit;
    layoutTDRS_6->addWidget(chkbxTDRS_6, 1);
    layoutTDRS_6->addWidget(labelDesignationTDRS_6,1);
    layoutTDRS_6->addWidget(editDesignationTDRS_6,2);
    groupboxTDRS_6->setLayout(layoutTDRS_6);

    groupboxTDRS_7 = new QGroupBox(tr("TDRS-7"));
    QHBoxLayout* layoutTDRS_7 = new QHBoxLayout;
    chkbxTDRS_7 = new QCheckBox(tr("Exists"));
    labelDesignationTDRS_7 = new QLabel(tr("Designation"));
    editDesignationTDRS_7 = new QLineEdit;
    layoutTDRS_7->addWidget(chkbxTDRS_7, 1);
    layoutTDRS_7->addWidget(labelDesignationTDRS_7,1);
    layoutTDRS_7->addWidget(editDesignationTDRS_7,2);
    groupboxTDRS_7->setLayout(layoutTDRS_7);

    groupboxTDRS_8 = new QGroupBox(tr("TDRS-8"));
    QHBoxLayout* layoutTDRS_8 = new QHBoxLayout;
    chkbxTDRS_8 = new QCheckBox(tr("Exists"));
    labelDesignationTDRS_8 = new QLabel(tr("Designation"));
    editDesignationTDRS_8 = new QLineEdit;
    layoutTDRS_8->addWidget(chkbxTDRS_8, 1);
    layoutTDRS_8->addWidget(labelDesignationTDRS_8,1);
    layoutTDRS_8->addWidget(editDesignationTDRS_8,2);
    groupboxTDRS_8->setLayout(layoutTDRS_8);

    groupboxTDRS_9 = new QGroupBox(tr("TDRS-9"));
    QHBoxLayout* layoutTDRS_9 = new QHBoxLayout;
    chkbxTDRS_9 = new QCheckBox(tr("Exists"));
    labelDesignationTDRS_9 = new QLabel(tr("Designation"));
    editDesignationTDRS_9 = new QLineEdit;
    layoutTDRS_9->addWidget(chkbxTDRS_9, 1);
    layoutTDRS_9->addWidget(labelDesignationTDRS_9,1);
    layoutTDRS_9->addWidget(editDesignationTDRS_9,2);
    groupboxTDRS_9->setLayout(layoutTDRS_9);

    groupboxTDRS_10 = new QGroupBox(tr("TDRS-10"));
    QHBoxLayout* layoutTDRS_10 = new QHBoxLayout;
    chkbxTDRS_10 = new QCheckBox(tr("Exists"));
    labelDesignationTDRS_10 = new QLabel(tr("Designation"));
    editDesignationTDRS_10 = new QLineEdit;
    layoutTDRS_10->addWidget(chkbxTDRS_10, 1);
    layoutTDRS_10->addWidget(labelDesignationTDRS_10,1);
    layoutTDRS_10->addWidget(editDesignationTDRS_10,2);
    groupboxTDRS_10->setLayout(layoutTDRS_10);

    labelFootnoteAsterisk = new QLabel(QString::fromUtf8("\u002A")+
                                       tr("TDRS-2 was lost along with Challenger (from \"Inp_TDRS.txt\" files in 42)"));

    layoutEditLeft->addWidget(groupboxTDRS_1,1);
    layoutEditLeft->addWidget(groupboxTDRS_2,1);
    layoutEditLeft->addWidget(groupboxTDRS_3,1);
    layoutEditLeft->addWidget(groupboxTDRS_4,1);
    layoutEditLeft->addWidget(groupboxTDRS_5,1);
    layoutEditLeft->setAlignment(Qt::AlignCenter);
    layoutEditRight->addWidget(groupboxTDRS_6,1);
    layoutEditRight->addWidget(groupboxTDRS_7,1);
    layoutEditRight->addWidget(groupboxTDRS_8,1);
    layoutEditRight->addWidget(groupboxTDRS_9,1);
    layoutEditRight->addWidget(groupboxTDRS_10,1);
    layoutEditRight->setAlignment(Qt::AlignCenter);
    layoutEdit->addLayout(layoutEditLeft,1);
    layoutEdit->addLayout(layoutEditRight,1);
    groupboxEdit->setLayout(layoutEdit);

    layoutDialog->addRow(labelMission);
    layoutDialog->addRow(groupboxEdit);
    layoutDialog->addRow(labelFootnoteAsterisk);
    layoutDialog->addRow(m_buttonBox);

    setLayout(layoutDialog);
}

void InpTDRsDialog::createActions()
{
    m_undoAction = m_undoStack->createUndoAction(this);
    m_redoAction = m_undoStack->createRedoAction(this);
}

void InpTDRsDialog::createConnections()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, [=](){mapDataFromWidgetToModel();});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::clear);
    connect(m_buttonBox, &QDialogButtonBox::accepted, m_undoStack, &QUndoStack::setClean);

    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Cancel),
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(false);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Apply),
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_buttonBox->button(QDialogButtonBox::Save),
            [=](){m_buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);});
    connect(m_buttonBox, &QDialogButtonBox::rejected, m_undoAction, &QAction::trigger);
    connect(m_undoAction, &QAction::triggered, this, [=](){mapDataFromModelToWidget();});

    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked,
            this, [=](){mapDataFromWidgetToModel();});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);});
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            [=](){m_buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);});

    connect(chkbxTDRS_1, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editDesignationTDRS_1, &QLineEdit::textChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxTDRS_2, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editDesignationTDRS_2, &QLineEdit::textChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxTDRS_3, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editDesignationTDRS_3, &QLineEdit::textChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxTDRS_4, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editDesignationTDRS_4, &QLineEdit::textChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxTDRS_5, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editDesignationTDRS_5, &QLineEdit::textChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxTDRS_6, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editDesignationTDRS_6, &QLineEdit::textChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxTDRS_7, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editDesignationTDRS_7, &QLineEdit::textChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxTDRS_8, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editDesignationTDRS_8, &QLineEdit::textChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxTDRS_9, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editDesignationTDRS_9, &QLineEdit::textChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(chkbxTDRS_10, &QCheckBox::stateChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
    connect(editDesignationTDRS_10, &QLineEdit::textChanged,
            this, [=](){m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);});
}

void InpTDRsDialog::mapDataFromModelToWidget()
{
    if (!m_model)
        return;

    QModelIndex indexMission = m_index.parent();
    Mission mission = indexMission.data().value<Mission>();
    labelMission->setText(tr("Mission: ")+mission.name().trimmed());

    chkbxTDRS_1->setChecked(m_inpTDRs.TDRS1().first);
    editDesignationTDRS_1->setText(m_inpTDRs.TDRS1().second.trimmed());

    chkbxTDRS_2->setChecked(m_inpTDRs.TDRS2().first);
    editDesignationTDRS_2->setText(m_inpTDRs.TDRS2().second.trimmed());

    chkbxTDRS_3->setChecked(m_inpTDRs.TDRS3().first);
    editDesignationTDRS_3->setText(m_inpTDRs.TDRS3().second.trimmed());

    chkbxTDRS_4->setChecked(m_inpTDRs.TDRS4().first);
    editDesignationTDRS_4->setText(m_inpTDRs.TDRS4().second.trimmed());

    chkbxTDRS_5->setChecked(m_inpTDRs.TDRS5().first);
    editDesignationTDRS_5->setText(m_inpTDRs.TDRS5().second.trimmed());

    chkbxTDRS_6->setChecked(m_inpTDRs.TDRS6().first);
    editDesignationTDRS_6->setText(m_inpTDRs.TDRS6().second.trimmed());

    chkbxTDRS_7->setChecked(m_inpTDRs.TDRS7().first);
    editDesignationTDRS_7->setText(m_inpTDRs.TDRS7().second.trimmed());

    chkbxTDRS_8->setChecked(m_inpTDRs.TDRS8().first);
    editDesignationTDRS_8->setText(m_inpTDRs.TDRS8().second.trimmed());

    chkbxTDRS_9->setChecked(m_inpTDRs.TDRS9().first);
    editDesignationTDRS_9->setText(m_inpTDRs.TDRS9().second.trimmed());

    chkbxTDRS_10->setChecked(m_inpTDRs.TDRS10().first);
    editDesignationTDRS_10->setText(m_inpTDRs.TDRS10().second.trimmed());
}

void InpTDRsDialog::mapDataFromWidgetToModel()
{
    QVariant newData = QVariant();
    m_inpTDRs.edit(QPair<bool, QString>(chkbxTDRS_1->isChecked(), editDesignationTDRS_1->text().trimmed()),
                   QPair<bool, QString>(chkbxTDRS_2->isChecked(), editDesignationTDRS_2->text().trimmed()),
                   QPair<bool, QString>(chkbxTDRS_3->isChecked(), editDesignationTDRS_3->text().trimmed()),
                   QPair<bool, QString>(chkbxTDRS_4->isChecked(), editDesignationTDRS_4->text().trimmed()),
                   QPair<bool, QString>(chkbxTDRS_5->isChecked(), editDesignationTDRS_5->text().trimmed()),
                   QPair<bool, QString>(chkbxTDRS_6->isChecked(), editDesignationTDRS_6->text().trimmed()),
                   QPair<bool, QString>(chkbxTDRS_7->isChecked(), editDesignationTDRS_7->text().trimmed()),
                   QPair<bool, QString>(chkbxTDRS_8->isChecked(), editDesignationTDRS_8->text().trimmed()),
                   QPair<bool, QString>(chkbxTDRS_9->isChecked(), editDesignationTDRS_9->text().trimmed()),
                   QPair<bool, QString>(chkbxTDRS_10->isChecked(), editDesignationTDRS_10->text().trimmed()));

    newData.setValue(m_inpTDRs);
    QUndoCommand* editCommand = new EditCommand(m_model, m_index, newData);
    m_undoStack->push(editCommand);
}
