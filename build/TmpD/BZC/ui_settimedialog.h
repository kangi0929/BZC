/********************************************************************************
** Form generated from reading UI file 'settimedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTIMEDIALOG_H
#define UI_SETTIMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SetTimeDialog
{
public:
    QDateTimeEdit *dateTimeEdit;
    QPushButton *btnOk;
    QPushButton *btnCancel;

    void setupUi(QDialog *SetTimeDialog)
    {
        if (SetTimeDialog->objectName().isEmpty())
            SetTimeDialog->setObjectName("SetTimeDialog");
        SetTimeDialog->resize(242, 98);
        dateTimeEdit = new QDateTimeEdit(SetTimeDialog);
        dateTimeEdit->setObjectName("dateTimeEdit");
        dateTimeEdit->setGeometry(QRect(30, 20, 194, 26));
        btnOk = new QPushButton(SetTimeDialog);
        btnOk->setObjectName("btnOk");
        btnOk->setGeometry(QRect(30, 50, 89, 25));
        btnCancel = new QPushButton(SetTimeDialog);
        btnCancel->setObjectName("btnCancel");
        btnCancel->setGeometry(QRect(130, 50, 89, 25));

        retranslateUi(SetTimeDialog);
        QObject::connect(btnOk, &QPushButton::clicked, SetTimeDialog, qOverload<>(&QDialog::accept));
        QObject::connect(btnCancel, &QPushButton::clicked, SetTimeDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(SetTimeDialog);
    } // setupUi

    void retranslateUi(QDialog *SetTimeDialog)
    {
        SetTimeDialog->setWindowTitle(QCoreApplication::translate("SetTimeDialog", "Dialog", nullptr));
        dateTimeEdit->setDisplayFormat(QCoreApplication::translate("SetTimeDialog", "yyyy-MM-dd hh:mm:ss", nullptr));
        btnOk->setText(QCoreApplication::translate("SetTimeDialog", "\347\241\256\345\256\232", nullptr));
        btnCancel->setText(QCoreApplication::translate("SetTimeDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetTimeDialog: public Ui_SetTimeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTIMEDIALOG_H
