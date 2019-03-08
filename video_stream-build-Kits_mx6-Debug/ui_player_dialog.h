/********************************************************************************
** Form generated from reading UI file 'player_dialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYER_DIALOG_H
#define UI_PLAYER_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "videoplayer_pane.h"

QT_BEGIN_NAMESPACE

class Ui_player_dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    videoplayer_pane *videoplyr_pane;
    QSlider *seek_slider;
    QHBoxLayout *horizontalLayout;
    QPushButton *play_stop_btn;
    QSpacerItem *horizontalSpacer;
    QPushButton *pause_btn;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *back_btn;
    QLabel *label;
    QSlider *volume_slider;
    QCheckBox *mute_chk;

    void setupUi(QDialog *player_dialog)
    {
        if (player_dialog->objectName().isEmpty())
            player_dialog->setObjectName(QString::fromUtf8("player_dialog"));
        player_dialog->resize(486, 275);
        verticalLayout_2 = new QVBoxLayout(player_dialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        videoplyr_pane = new videoplayer_pane(player_dialog);
        videoplyr_pane->setObjectName(QString::fromUtf8("videoplyr_pane"));
        videoplyr_pane->setMinimumSize(QSize(0, 200));

        verticalLayout->addWidget(videoplyr_pane);

        seek_slider = new QSlider(player_dialog);
        seek_slider->setObjectName(QString::fromUtf8("seek_slider"));
        seek_slider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(seek_slider);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        play_stop_btn = new QPushButton(player_dialog);
        play_stop_btn->setObjectName(QString::fromUtf8("play_stop_btn"));

        horizontalLayout->addWidget(play_stop_btn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pause_btn = new QPushButton(player_dialog);
        pause_btn->setObjectName(QString::fromUtf8("pause_btn"));

        horizontalLayout->addWidget(pause_btn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        back_btn = new QPushButton(player_dialog);
        back_btn->setObjectName(QString::fromUtf8("back_btn"));

        horizontalLayout->addWidget(back_btn);

        label = new QLabel(player_dialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        volume_slider = new QSlider(player_dialog);
        volume_slider->setObjectName(QString::fromUtf8("volume_slider"));
        volume_slider->setMinimumSize(QSize(80, 0));
        volume_slider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(volume_slider);

        mute_chk = new QCheckBox(player_dialog);
        mute_chk->setObjectName(QString::fromUtf8("mute_chk"));

        horizontalLayout->addWidget(mute_chk);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(player_dialog);

        QMetaObject::connectSlotsByName(player_dialog);
    } // setupUi

    void retranslateUi(QDialog *player_dialog)
    {
        player_dialog->setWindowTitle(QApplication::translate("player_dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        play_stop_btn->setText(QApplication::translate("player_dialog", "play", 0, QApplication::UnicodeUTF8));
        pause_btn->setText(QApplication::translate("player_dialog", "pause", 0, QApplication::UnicodeUTF8));
        back_btn->setText(QApplication::translate("player_dialog", "back", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("player_dialog", "Vol", 0, QApplication::UnicodeUTF8));
        mute_chk->setText(QApplication::translate("player_dialog", "Mute", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class player_dialog: public Ui_player_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYER_DIALOG_H
