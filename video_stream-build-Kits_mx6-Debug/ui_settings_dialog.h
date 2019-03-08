/********************************************************************************
** Form generated from reading UI file 'settings_dialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_DIALOG_H
#define UI_SETTINGS_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_settings_dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QComboBox *comboBox_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QGroupBox *groupBox;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_5;
    QLabel *label_3;
    QSlider *horizontalSlider_2;
    QLabel *label_4;
    QSlider *horizontalSlider_3;
    QSlider *horizontalSlider;
    QPushButton *pushButton;

    void setupUi(QDialog *settings_dialog)
    {
        if (settings_dialog->objectName().isEmpty())
            settings_dialog->setObjectName(QString::fromUtf8("settings_dialog"));
        settings_dialog->resize(480, 272);
        verticalLayout_2 = new QVBoxLayout(settings_dialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(settings_dialog);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(0, 40));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(settings_dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_2);

        comboBox = new QComboBox(settings_dialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_2->addWidget(comboBox);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_6 = new QLabel(settings_dialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_3->addWidget(label_6);

        comboBox_2 = new QComboBox(settings_dialog);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        horizontalLayout_3->addWidget(comboBox_2);


        verticalLayout_3->addLayout(horizontalLayout_3);


        horizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        checkBox = new QCheckBox(settings_dialog);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout->addWidget(checkBox);

        checkBox_2 = new QCheckBox(settings_dialog);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        verticalLayout->addWidget(checkBox_2);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        groupBox = new QGroupBox(settings_dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(0, 100));
        formLayoutWidget = new QWidget(groupBox);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(70, 20, 321, 61));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_5);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        horizontalSlider_2 = new QSlider(formLayoutWidget);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        formLayout->setWidget(1, QFormLayout::FieldRole, horizontalSlider_2);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        horizontalSlider_3 = new QSlider(formLayoutWidget);
        horizontalSlider_3->setObjectName(QString::fromUtf8("horizontalSlider_3"));
        horizontalSlider_3->setOrientation(Qt::Horizontal);

        formLayout->setWidget(2, QFormLayout::FieldRole, horizontalSlider_3);

        horizontalSlider = new QSlider(formLayoutWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(0, QFormLayout::FieldRole, horizontalSlider);


        verticalLayout_2->addWidget(groupBox);

        pushButton = new QPushButton(settings_dialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(50, 40));

        verticalLayout_2->addWidget(pushButton);


        retranslateUi(settings_dialog);

        QMetaObject::connectSlotsByName(settings_dialog);
    } // setupUi

    void retranslateUi(QDialog *settings_dialog)
    {
        settings_dialog->setWindowTitle(QApplication::translate("settings_dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("settings_dialog", "Settings", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("settings_dialog", "Recording Prefix", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("settings_dialog", "Video_", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("settings_dialog", "Recording_", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("settings_dialog", "Recording Time", 0, QApplication::UnicodeUTF8));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("settings_dialog", "10s", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("settings_dialog", "20s", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("settings_dialog", "30s", 0, QApplication::UnicodeUTF8)
        );
        checkBox->setText(QApplication::translate("settings_dialog", "Motion Detection", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("settings_dialog", "WIFI Streaming", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("settings_dialog", "Camera", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("settings_dialog", "Brightness", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("settings_dialog", "Contrast", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("settings_dialog", "Exposure", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("settings_dialog", "Set", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class settings_dialog: public Ui_settings_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_DIALOG_H
