#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMouseEvent>
#include "objetografico.h"

enum class ModoDesenho { NENHUM, RETA, POLIGONO };

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_pushButton_transladar_clicked();
    void on_pushButton_escalar_clicked();
    void on_pushButton_rotacionar_clicked();
    void on_pushButton_addReta_clicked();
    void on_pushButton_addPoligono_clicked();
    void on_pushButton_finalizarDesenho_clicked();
    void on_checkBox_usarPontoEspecifico_toggled(bool checked);

private:
    void popularObjetosIniciais();
    void atualizarListaObjetos();
    void resetarModoDesenho();

    Ui::MainWindow *ui;
    QVector<ObjetoGrafico*> displayFile;
    ModoDesenho modoDesenho;
    QVector<QPoint> pontosTemporarios;
};
#endif // MAINWINDOW_H
