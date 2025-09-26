#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMouseEvent>
#include <QListWidgetItem>
#include "objetografico.h"
#include "transformador.h"
#include "windowgrafica.h"
#include "clipping.h"

enum class ModoDesenho { NENHUM, PONTO, RETA, POLIGONO };

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
    void on_pushButton_addPonto_clicked();
    void on_pushButton_excluir_clicked();
    void on_listWidget_objetos_itemChanged(QListWidgetItem *item);
    void on_pushButton_aplicar_wv_clicked();

private:
    void atualizarListaObjetos();
    void resetarModoDesenho();

    Ui::MainWindow *ui;
    QVector<ObjetoGrafico*> displayFile;
    ModoDesenho modoDesenho;
    QVector<QPoint> pontosTemporarios;
    TransformadorCoordenadas* transformador;

    WindowGrafica* a_window;
    Clipping* clipper;
};
#endif // MAINWINDOW_H
