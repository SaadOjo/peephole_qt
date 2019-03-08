/********************************************************************************
** Form generated from reading UI file 'gallery_dialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GALLERY_DIALOG_H
#define UI_GALLERY_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_gallery_dialog
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListView *listView;
    QHBoxLayout *horizontalLayout;
    QPushButton *back_btn;
    QPushButton *play_btn;

    void setupUi(QDialog *gallery_dialog)
    {
        if (gallery_dialog->objectName().isEmpty())
            gallery_dialog->setObjectName(QString::fromUtf8("gallery_dialog"));
        gallery_dialog->resize(480, 272);
        horizontalLayout_2 = new QHBoxLayout(gallery_dialog);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(gallery_dialog);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        listView = new QListView(gallery_dialog);
        listView->setObjectName(QString::fromUtf8("listView"));

        verticalLayout->addWidget(listView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        back_btn = new QPushButton(gallery_dialog);
        back_btn->setObjectName(QString::fromUtf8("back_btn"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(back_btn->sizePolicy().hasHeightForWidth());
        back_btn->setSizePolicy(sizePolicy);
        back_btn->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(back_btn);

        play_btn = new QPushButton(gallery_dialog);
        play_btn->setObjectName(QString::fromUtf8("play_btn"));
        play_btn->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(play_btn);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(gallery_dialog);

        QMetaObject::connectSlotsByName(gallery_dialog);
    } // setupUi

    void retranslateUi(QDialog *gallery_dialog)
    {
        gallery_dialog->setWindowTitle(QApplication::translate("gallery_dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("gallery_dialog", "Gallery", 0, QApplication::UnicodeUTF8));
        back_btn->setText(QApplication::translate("gallery_dialog", "back", 0, QApplication::UnicodeUTF8));
        play_btn->setText(QApplication::translate("gallery_dialog", "play", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class gallery_dialog: public Ui_gallery_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GALLERY_DIALOG_H
