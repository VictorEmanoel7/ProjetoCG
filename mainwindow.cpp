#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , modoDesenho(ModoDesenho::NENHUM)
{
    ui->setupUi(this);

    ui->canvasWidget->installEventFilter(this);
    ui->canvasWidget->setMouseTracking(true);

    popularObjetosIniciais();
    atualizarListaObjetos();

    ui->lineEdit_rotacao_px->setEnabled(false);
    ui->lineEdit_rotacao_py->setEnabled(false);
}

MainWindow::~MainWindow()
{
    for(ObjetoGrafico* obj : displayFile) {
        delete obj;
    }
    displayFile.clear();
    delete ui;
}

void MainWindow::popularObjetosIniciais() {
    displayFile.append(new RetaGrafica("Reta 1", Ponto(50, 50), Ponto(150, 50)));

    QVector<Ponto> verticesTriangulo;
    verticesTriangulo.append(Ponto(200, 100));
    verticesTriangulo.append(Ponto(250, 200));
    verticesTriangulo.append(Ponto(150, 200));
    displayFile.append(new PoligonoGrafico("Triangulo 1", verticesTriangulo));
}

void MainWindow::atualizarListaObjetos() {
    ui->listWidget_objetos->clear();
    for (const auto& obj : displayFile) {
        ui->listWidget_objetos->addItem(obj->getNome());
    }
}

void MainWindow::resetarModoDesenho() {
    modoDesenho = ModoDesenho::NENHUM;
    pontosTemporarios.clear();
    ui->statusbar->showMessage("Modo de desenho desativado.");
    update();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setClipRect(ui->canvasWidget->geometry());

    painter.setPen(QPen(Qt::green, 2));
    for (const auto& obj : displayFile) {
        obj->desenhar(painter);
    }

    if (!pontosTemporarios.isEmpty()) {
        painter.setPen(QPen(Qt::yellow, 3, Qt::DashLine));
        for(const QPoint& p : pontosTemporarios) {
            painter.drawPoint(p);
        }
        if ((modoDesenho == ModoDesenho::POLIGONO || modoDesenho == ModoDesenho::RETA) && pontosTemporarios.size() > 1) {
            for (int i = 0; i < pontosTemporarios.size() - 1; ++i) {
                painter.drawLine(pontosTemporarios[i], pontosTemporarios[i+1]);
            }
        }
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->canvasWidget && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        if (modoDesenho == ModoDesenho::RETA) {
            pontosTemporarios.append(mouseEvent->pos());
            if (pontosTemporarios.size() == 2) {
                QString nome = ui->lineEdit_nomeObjeto->text();
                if (nome.isEmpty()) {
                    nome = QString("Reta %1").arg(displayFile.size() + 1);
                }
                Ponto p1(pontosTemporarios[0].x(), pontosTemporarios[0].y());
                Ponto p2(pontosTemporarios[1].x(), pontosTemporarios[1].y());
                displayFile.append(new RetaGrafica(nome, p1, p2));

                atualizarListaObjetos();

                resetarModoDesenho();
            }
            update();
            return true;
        }
        else if (modoDesenho == ModoDesenho::POLIGONO) {
            pontosTemporarios.append(mouseEvent->pos());
            update();
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::on_pushButton_transladar_clicked() {
    int index = ui->listWidget_objetos->currentRow();
    if (index < 0) {
        QMessageBox::warning(this, "Aviso", "Selecione um objeto para transladar.");
        return;
    }

    double pX = ui->lineEdit_dx->text().toDouble();
    double pY = ui->lineEdit_dy->text().toDouble();

    Ponto centroAtual = displayFile[index]->calcularCentro();
    double cX = centroAtual.getX();
    double cY = centroAtual.getY();

    double dx = pX - cX;
    double dy = pY - cY;

    Matrix matrizT = Matrix::criarMatrizTranslacao(dx, dy);
    displayFile[index]->aplicarTransformacao(matrizT);

    update();
}

void MainWindow::on_pushButton_escalar_clicked() {
    int index = ui->listWidget_objetos->currentRow();
    if (index < 0) return;

    double sx = ui->lineEdit_sx->text().toDouble();
    double sy = ui->lineEdit_sy->text().toDouble();

    Ponto centro = displayFile[index]->calcularCentro();

    Matrix T1 = Matrix::criarMatrizTranslacao(-centro.getX(), -centro.getY());
    Matrix S = Matrix::criarMatrizEscala(sx, sy);
    Matrix T2 = Matrix::criarMatrizTranslacao(centro.getX(), centro.getY());
    Matrix matrizFinal = T2 * S * T1;

    displayFile[index]->aplicarTransformacao(matrizFinal);
    update();
}

void MainWindow::on_pushButton_rotacionar_clicked()
{
    int index = ui->listWidget_objetos->currentRow();
    if (index < 0) {
        QMessageBox::warning(this, "Aviso", "Selecione um objeto para rotacionar.");
        return;
    }

    double angulo = ui->lineEdit_angulo->text().toDouble();
    Ponto pivo;

    if (ui->checkBox_usarPontoEspecifico->isChecked()) {

        bool okPx, okPy;
        double px = ui->lineEdit_rotacao_px->text().toDouble(&okPx);
        double py = ui->lineEdit_rotacao_py->text().toDouble(&okPy);

        if (!okPx || !okPy) {
            QMessageBox::warning(this, "Erro de Entrada", "Por favor, insira coordenadas Px e Py válidas.");
            return;
        }
        pivo = Ponto(px, py);
    } else {
        pivo = displayFile[index]->calcularCentro();
    }

    Matrix T1 = Matrix::criarMatrizTranslacao(-pivo.getX(), -pivo.getY());
    Matrix R = Matrix::criarMatrizRotacao(angulo);
    Matrix T2 = Matrix::criarMatrizTranslacao(pivo.getX(), pivo.getY());
    Matrix matrizFinal = T2 * R * T1;

    displayFile[index]->aplicarTransformacao(matrizFinal);
    update();
}

void MainWindow::on_pushButton_addReta_clicked()
{
    modoDesenho = ModoDesenho::RETA;
    pontosTemporarios.clear();
    ui->statusbar->showMessage("Modo 'Desenhar Reta' ativado. Clique em 2 pontos no canvas.");
}

void MainWindow::on_pushButton_addPoligono_clicked()
{
    modoDesenho = ModoDesenho::POLIGONO;
    pontosTemporarios.clear();
    ui->statusbar->showMessage("Modo 'Desenhar Polígono' ativado. Clique nos vértices e depois em 'Finalizar'.");
}

void MainWindow::on_pushButton_finalizarDesenho_clicked()
{
    if (modoDesenho == ModoDesenho::POLIGONO && pontosTemporarios.size() >= 3) {
        QString nome = ui->lineEdit_nomeObjeto->text();
        if (nome.isEmpty()) {
            nome = QString("Poligono %1").arg(displayFile.size() + 1);
        }
        QVector<Ponto> vertices;
        for(const QPoint& qp : pontosTemporarios) {
            vertices.append(Ponto(qp.x(), qp.y()));
        }
        displayFile.append(new PoligonoGrafico(nome, vertices));

        atualizarListaObjetos();

        resetarModoDesenho();
    } else {
        QMessageBox::warning(this, "Aviso", "Para finalizar um polígono, você precisa de pelo menos 3 pontos.");
        resetarModoDesenho();
    }
}

void MainWindow::on_checkBox_usarPontoEspecifico_toggled(bool checked)
{
    ui->lineEdit_rotacao_px->setEnabled(checked);
    ui->lineEdit_rotacao_py->setEnabled(checked);

    if (checked) {
        ui->lineEdit_rotacao_px->setFocus();
    }
}
