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

    connect(ui->listWidget_objetos, &QListWidget::itemChanged, this, &MainWindow::on_listWidget_objetos_itemChanged);

    ui->canvasWidget->installEventFilter(this);
    ui->canvasWidget->setMouseTracking(true);

    ui->lineEdit_rotacao_px->setEnabled(false);
    ui->lineEdit_rotacao_py->setEnabled(false);

    int canvas_width = ui->canvasWidget->width();
    int canvas_height = ui->canvasWidget->height();
    int padding = 50;
    double w_xmin = padding;
    double w_ymin = padding;
    double w_xmax = canvas_width - padding;
    double w_ymax = canvas_height - padding;

    a_window = new WindowGrafica("Window", Ponto(w_xmin, w_ymin), Ponto(w_xmax, w_ymax));
    a_window->setVisivel(true);

    displayFile.prepend(a_window);

    transformador = new TransformadorCoordenadas();
    transformador->setViewport(w_xmin, w_ymin, w_xmax, w_ymax);

    LimitesWindow limitesIniciais = a_window->getLimites();
    ui->lineEdit_w_xmin->setText(QString::number(limitesIniciais.xmin));
    ui->lineEdit_w_ymin->setText(QString::number(limitesIniciais.ymin));
    ui->lineEdit_w_xmax->setText(QString::number(limitesIniciais.xmax));
    ui->lineEdit_w_ymax->setText(QString::number(limitesIniciais.ymax));
    ui->lineEdit_v_xmin->setText(QString::number(w_xmin));
    ui->lineEdit_v_ymin->setText(QString::number(w_ymin));
    ui->lineEdit_v_xmax->setText(QString::number(w_xmax));
    ui->lineEdit_v_ymax->setText(QString::number(w_ymax));

    clipper = new Clipping();

    atualizarListaObjetos();
}

MainWindow::~MainWindow()
{
    for(ObjetoGrafico* obj : displayFile) {
        delete obj;
    }
    displayFile.clear();
    delete transformador;
    delete clipper;
    delete ui;
}

void MainWindow::atualizarListaObjetos() {
    ui->listWidget_objetos->blockSignals(true);

    ui->listWidget_objetos->clear();
    for (int i = 0; i < displayFile.size(); ++i) {
        ObjetoGrafico* obj = displayFile[i];
        QListWidgetItem* item = new QListWidgetItem();
        QString textoItem = QString("%1 (%2)").arg(obj->getNome()).arg(tipoParaString(obj->getTipo()));
        item->setText(textoItem);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(obj->isVisivel() ? Qt::Checked : Qt::Unchecked);
        ui->listWidget_objetos->addItem(item);
    }
    ui->listWidget_objetos->blockSignals(false);
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

    LimitesWindow limites = a_window->getLimites();
    transformador->setWindow(limites.xmin, limites.ymin, limites.xmax, limites.ymax);
    Matrix T_wv = transformador->getTransformacao();

    for (const auto& objOriginal : displayFile) {
        if (objOriginal->isVisivel()) {
            ObjetoGrafico* objCopia = objOriginal->clone();

            RetaGrafica* reta = dynamic_cast<RetaGrafica*>(objCopia);
            PoligonoGrafico* poligono = dynamic_cast<PoligonoGrafico*>(objCopia);

            if (reta) {
                Ponto p1 = reta->getPontos()[0];
                Ponto p2 = reta->getPontos()[1];

                if (clipper->clipReta(p1, p2, limites)) {
                    reta->getPontos()[0] = p1;
                    reta->getPontos()[1] = p2;

                    objCopia->aplicarTransformacao(T_wv);
                    objCopia->desenhar(painter);
                }
            } else if (poligono && poligono != static_cast<ObjetoGrafico*>(a_window)) {
                QVector<Ponto>& vertices = poligono->getPontos();
                if (vertices.size() >= 2) {
                    for (int i = 0; i < vertices.size(); ++i) {
                        Ponto p1 = vertices[i];
                        Ponto p2 = vertices[(i + 1) % vertices.size()];

                        if (clipper->clipReta(p1, p2, limites)) {
                            Matrix m_p1 = p1;
                            Matrix m_p2 = p2;
                            Matrix p1_transformado = T_wv * m_p1;
                            Matrix p2_transformado = T_wv * m_p2;

                            painter.drawLine(p1_transformado.at(0,0), p1_transformado.at(1,0),
                                             p2_transformado.at(0,0), p2_transformado.at(1,0));
                        }
                    }
                }
            } else {
                objCopia->aplicarTransformacao(T_wv);
                objCopia->desenhar(painter);
            }

            delete objCopia;
        }
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

        if (modoDesenho == ModoDesenho::PONTO) {
            QString nome = ui->lineEdit_nomeObjeto->text();
            if (nome.isEmpty()) {
                nome = QString("Ponto %1").arg(displayFile.size() + 1);
            }
            Ponto p(mouseEvent->pos().x(), mouseEvent->pos().y());
            displayFile.append(new PontoGrafico(nome, p));
            atualizarListaObjetos();
            resetarModoDesenho();
            update();
            return true;
        }
        else if (modoDesenho == ModoDesenho::RETA) {
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

    double dx = ui->lineEdit_dx->text().toDouble();
    double dy = ui->lineEdit_dy->text().toDouble();

    if (index == 0) {
        Matrix matrizT_inversa = Matrix::criarMatrizTranslacao(-dx, -dy);
        for (int i = 1; i < displayFile.size(); ++i) {
            displayFile[i]->aplicarTransformacao(matrizT_inversa);
        }
    } else {
        Matrix matrizT = Matrix::criarMatrizTranslacao(dx, dy);
        displayFile[index]->aplicarTransformacao(matrizT);
    }
    update();
}

void MainWindow::on_pushButton_escalar_clicked() {
    int index = ui->listWidget_objetos->currentRow();
    if (index < 0) return;

    double sx = ui->lineEdit_sx->text().toDouble();
    double sy = ui->lineEdit_sy->text().toDouble();

    if (index == 0) {
        if (sx == 0 || sy == 0) {
            QMessageBox::warning(this, "Aviso", "Fator de escala não pode ser zero.");
            return;
        }
        Ponto centro = a_window->calcularCentro();
        Matrix T1 = Matrix::criarMatrizTranslacao(-centro.getX(), -centro.getY());
        Matrix S_inversa = Matrix::criarMatrizEscala(1.0/sx, 1.0/sy);
        Matrix T2 = Matrix::criarMatrizTranslacao(centro.getX(), centro.getY());
        Matrix matrizFinal_inversa = T2 * S_inversa * T1;

        for (int i = 1; i < displayFile.size(); ++i) {
            displayFile[i]->aplicarTransformacao(matrizFinal_inversa);
        }
    } else {
        Ponto centro = displayFile[index]->calcularCentro();
        Matrix T1 = Matrix::criarMatrizTranslacao(-centro.getX(), -centro.getY());
        Matrix S = Matrix::criarMatrizEscala(sx, sy);
        Matrix T2 = Matrix::criarMatrizTranslacao(centro.getX(), centro.getY());
        Matrix matrizFinal = T2 * S * T1;
        displayFile[index]->aplicarTransformacao(matrizFinal);
    }
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

    if (index == 0) {
        Ponto pivo = a_window->calcularCentro();
        Matrix T1 = Matrix::criarMatrizTranslacao(-pivo.getX(), -pivo.getY());
        Matrix R_inversa = Matrix::criarMatrizRotacao(-angulo);
        Matrix T2 = Matrix::criarMatrizTranslacao(pivo.getX(), pivo.getY());
        Matrix matrizFinal_inversa = T2 * R_inversa * T1;

        for (int i = 1; i < displayFile.size(); ++i) {
            displayFile[i]->aplicarTransformacao(matrizFinal_inversa);
        }
    } else {
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
    }
    update();
}

void MainWindow::on_pushButton_addPonto_clicked()
{
    modoDesenho = ModoDesenho::PONTO;
    pontosTemporarios.clear();
    ui->statusbar->showMessage("Modo 'Desenhar Ponto' ativado. Clique em 1 ponto no canvas.");
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

void MainWindow::on_pushButton_excluir_clicked()
{
    int index = ui->listWidget_objetos->currentRow();

    if (index < 0) {
        QMessageBox::warning(this, "Aviso", "Selecione um objeto para excluir.");
        return;
    }
    if (index == 0) {
        QMessageBox::warning(this, "Aviso", "Não é possível excluir a window.");
        return;
    }

    delete displayFile[index];
    displayFile.removeAt(index);
    atualizarListaObjetos();
    update();
}

void MainWindow::on_listWidget_objetos_itemChanged(QListWidgetItem *item)
{
    int index = ui->listWidget_objetos->row(item);
    if (index < 0 || index >= displayFile.size()) return;

    ObjetoGrafico* obj = displayFile[index];
    bool isChecked = (item->checkState() == Qt::Checked);
    obj->setVisivel(isChecked);

    update();
}

void MainWindow::on_pushButton_aplicar_wv_clicked()
{
    double w_xmin = ui->lineEdit_w_xmin->text().toDouble();
    double w_ymin = ui->lineEdit_w_ymin->text().toDouble();
    double w_xmax = ui->lineEdit_w_xmax->text().toDouble();
    double w_ymax = ui->lineEdit_w_ymax->text().toDouble();

    a_window->atualizarLimites(w_xmin, w_ymin, w_xmax, w_ymax);

    int v_xmin = ui->lineEdit_v_xmin->text().toInt();
    int v_ymin = ui->lineEdit_v_ymin->text().toInt();
    int v_xmax = ui->lineEdit_v_xmax->text().toInt();
    int v_ymax = ui->lineEdit_v_ymax->text().toInt();

    transformador->setViewport(v_xmin, v_ymin, v_xmax, v_ymax);

    update();
}
