/********************************************************************************
** Form generated from reading UI file 'player.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYER_H
#define UI_PLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_player
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSlider *horizontalSlider_2;
    QCheckBox *checkBox;

    void setupUi(QWidget *player)
    {
        if (player->objectName().isEmpty())
            player->setObjectName(QString::fromUtf8("player"));
        player->resize(432, 269);
        verticalLayout_2 = new QVBoxLayout(player);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(player);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 194));

        verticalLayout->addWidget(widget);

        horizontalSlider = new QSlider(player);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_2 = new QPushButton(player);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        horizontalSpacer_2 = new QSpacerItem(5, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton = new QPushButton(player);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer_3 = new QSpacerItem(5, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        pushButton_3 = new QPushButton(player);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);

        horizontalSpacer = new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label = new QLabel(player);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSlider_2 = new QSlider(player);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setMinimumSize(QSize(80, 0));
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider_2);

        checkBox = new QCheckBox(player);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_2->addWidget(checkBox);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(player);

        QMetaObject::connectSlotsByName(player);
    } // setupUi

    void retranslateUi(QWidget *player)
    {
        player->setWindowTitle(QApplication::translate("player", "Form", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("player", "Play", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("player", "Pause", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("player", "Back", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("player", "Vol", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("player", "Mute", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class player: public Ui_player {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYER_H
