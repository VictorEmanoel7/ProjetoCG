/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *canvasWidget;
    QListWidget *listWidget_objetos;
    QLineEdit *lineEdit_sy;
    QLineEdit *lineEdit_dy;
    QLineEdit *lineEdit_sx;
    QLineEdit *lineEdit_dx;
    QLineEdit *lineEdit_angulo;
    QPushButton *pushButton_rotacionar;
    QPushButton *pushButton_escalar;
    QPushButton *pushButton_transladar;
    QPushButton *pushButton_addReta;
    QPushButton *pushButton_addPoligono;
    QPushButton *pushButton_finalizarDesenho;
    QLineEdit *lineEdit_nomeObjeto;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QCheckBox *checkBox_usarPontoEspecifico;
    QLineEdit *lineEdit_rotacao_px;
    QLineEdit *lineEdit_rotacao_py;
    QLabel *label_8;
    QLabel *label_9;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(830, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        canvasWidget = new QWidget(centralwidget);
        canvasWidget->setObjectName("canvasWidget");
        canvasWidget->setGeometry(QRect(0, 0, 461, 581));
        canvasWidget->setAutoFillBackground(false);
        listWidget_objetos = new QListWidget(centralwidget);
        listWidget_objetos->setObjectName("listWidget_objetos");
        listWidget_objetos->setGeometry(QRect(690, 40, 91, 141));
        lineEdit_sy = new QLineEdit(centralwidget);
        lineEdit_sy->setObjectName("lineEdit_sy");
        lineEdit_sy->setGeometry(QRect(740, 280, 51, 22));
        lineEdit_dy = new QLineEdit(centralwidget);
        lineEdit_dy->setObjectName("lineEdit_dy");
        lineEdit_dy->setGeometry(QRect(740, 330, 51, 22));
        lineEdit_sx = new QLineEdit(centralwidget);
        lineEdit_sx->setObjectName("lineEdit_sx");
        lineEdit_sx->setGeometry(QRect(680, 280, 51, 22));
        lineEdit_dx = new QLineEdit(centralwidget);
        lineEdit_dx->setObjectName("lineEdit_dx");
        lineEdit_dx->setGeometry(QRect(680, 330, 51, 22));
        lineEdit_angulo = new QLineEdit(centralwidget);
        lineEdit_angulo->setObjectName("lineEdit_angulo");
        lineEdit_angulo->setGeometry(QRect(680, 400, 51, 22));
        pushButton_rotacionar = new QPushButton(centralwidget);
        pushButton_rotacionar->setObjectName("pushButton_rotacionar");
        pushButton_rotacionar->setGeometry(QRect(600, 400, 75, 24));
        pushButton_escalar = new QPushButton(centralwidget);
        pushButton_escalar->setObjectName("pushButton_escalar");
        pushButton_escalar->setGeometry(QRect(600, 280, 75, 24));
        pushButton_transladar = new QPushButton(centralwidget);
        pushButton_transladar->setObjectName("pushButton_transladar");
        pushButton_transladar->setGeometry(QRect(600, 330, 75, 24));
        pushButton_addReta = new QPushButton(centralwidget);
        pushButton_addReta->setObjectName("pushButton_addReta");
        pushButton_addReta->setGeometry(QRect(470, 70, 111, 24));
        pushButton_addPoligono = new QPushButton(centralwidget);
        pushButton_addPoligono->setObjectName("pushButton_addPoligono");
        pushButton_addPoligono->setGeometry(QRect(470, 100, 111, 24));
        pushButton_finalizarDesenho = new QPushButton(centralwidget);
        pushButton_finalizarDesenho->setObjectName("pushButton_finalizarDesenho");
        pushButton_finalizarDesenho->setGeometry(QRect(470, 130, 111, 24));
        lineEdit_nomeObjeto = new QLineEdit(centralwidget);
        lineEdit_nomeObjeto->setObjectName("lineEdit_nomeObjeto");
        lineEdit_nomeObjeto->setGeometry(QRect(470, 40, 91, 22));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(470, 20, 91, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(690, 20, 91, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(680, 380, 41, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(700, 260, 21, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(760, 260, 21, 16));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(700, 310, 21, 16));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(760, 310, 21, 16));
        checkBox_usarPontoEspecifico = new QCheckBox(centralwidget);
        checkBox_usarPontoEspecifico->setObjectName("checkBox_usarPontoEspecifico");
        checkBox_usarPontoEspecifico->setGeometry(QRect(600, 440, 171, 20));
        lineEdit_rotacao_px = new QLineEdit(centralwidget);
        lineEdit_rotacao_px->setObjectName("lineEdit_rotacao_px");
        lineEdit_rotacao_px->setGeometry(QRect(610, 480, 51, 22));
        lineEdit_rotacao_py = new QLineEdit(centralwidget);
        lineEdit_rotacao_py->setObjectName("lineEdit_rotacao_py");
        lineEdit_rotacao_py->setGeometry(QRect(680, 480, 51, 22));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(630, 460, 21, 16));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(700, 460, 21, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 830, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_rotacionar->setText(QCoreApplication::translate("MainWindow", "Rotacionar", nullptr));
        pushButton_escalar->setText(QCoreApplication::translate("MainWindow", "Escalonar", nullptr));
        pushButton_transladar->setText(QCoreApplication::translate("MainWindow", "Transladar", nullptr));
        pushButton_addReta->setText(QCoreApplication::translate("MainWindow", "Adicionar Reta", nullptr));
        pushButton_addPoligono->setText(QCoreApplication::translate("MainWindow", "Adicionar Poligino", nullptr));
        pushButton_finalizarDesenho->setText(QCoreApplication::translate("MainWindow", "Finalizar Poligino", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Nome do Objeto", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Lista de Objetos", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Angulo", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        checkBox_usarPontoEspecifico->setText(QCoreApplication::translate("MainWindow", "Rotacionar Ponto Espec\303\255fico", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
