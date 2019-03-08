/********************************************************************************
** Form generated from reading UI file 'menu_dialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_DIALOG_H
#define UI_MENU_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_menu_dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *setting_btn;
    QPushButton *gallery_btn;
    QPushButton *back_btn;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *menu_dialog)
    {
        if (menu_dialog->objectName().isEmpty())
            menu_dialog->setObjectName(QString::fromUtf8("menu_dialog"));
        menu_dialog->resize(480, 272);
        verticalLayout_2 = new QVBoxLayout(menu_dialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_2->addItem(verticalSpacer_2);

        label = new QLabel(menu_dialog);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        font.setKerning(false);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_2->addItem(verticalSpacer_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        setting_btn = new QPushButton(menu_dialog);
        setting_btn->setObjectName(QString::fromUtf8("setting_btn"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(setting_btn->sizePolicy().hasHeightForWidth());
        setting_btn->setSizePolicy(sizePolicy);
        setting_btn->setMinimumSize(QSize(0, 60));

        horizontalLayout->addWidget(setting_btn);

        gallery_btn = new QPushButton(menu_dialog);
        gallery_btn->setObjectName(QString::fromUtf8("gallery_btn"));
        sizePolicy.setHeightForWidth(gallery_btn->sizePolicy().hasHeightForWidth());
        gallery_btn->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(gallery_btn);


        verticalLayout->addLayout(horizontalLayout);

        back_btn = new QPushButton(menu_dialog);
        back_btn->setObjectName(QString::fromUtf8("back_btn"));
        sizePolicy.setHeightForWidth(back_btn->sizePolicy().hasHeightForWidth());
        back_btn->setSizePolicy(sizePolicy);
        back_btn->setMinimumSize(QSize(0, 60));

        verticalLayout->addWidget(back_btn);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(menu_dialog);

        QMetaObject::connectSlotsByName(menu_dialog);
    } // setupUi

    void retranslateUi(QDialog *menu_dialog)
    {
        menu_dialog->setWindowTitle(QApplication::translate("menu_dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("menu_dialog", "Menu", 0, QApplication::UnicodeUTF8));
        setting_btn->setText(QApplication::translate("menu_dialog", "settings", 0, QApplication::UnicodeUTF8));
        gallery_btn->setText(QApplication::translate("menu_dialog", "gallery", 0, QApplication::UnicodeUTF8));
        back_btn->setText(QApplication::translate("menu_dialog", "back", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class menu_dialog: public Ui_menu_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_DIALOG_H
