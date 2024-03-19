
#include <QObject>
#include <QApplication>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>
#include <iostream>
//
#include <QMediaPlayer>
#include <QSoundEffect>
#include <QAudioOutput>
#include <QPropertyAnimation>
#include <QTimer>


class RedButton : public QPushButton
{
Q_OBJECT

public:
    RedButton(QWidget* parrent);
    void paintEvent(QPaintEvent *e) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void keyPressEvent(QKeyEvent *e) override;

public slots:
    void setUp();
    void setDown();
private:
    QPixmap upButton;
    QPixmap downButton;
    QPixmap curState;
    bool is_down = false;
    QMediaPlayer *mediaPlayer;
    QPropertyAnimation *anim;
};

RedButton::RedButton(QWidget* parrent)
{
    setParent(parrent);
    setToolTip("Click me");
    setWindowTitle("Kick ME");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //
    QString path_of = QCoreApplication::applicationDirPath();
    std::cerr<< "relative path is " << path_of.toStdString() << std::endl;


    //
    //upButton = QPixmap("../img/up_red_button.png");
    upButton = QPixmap("../img/up.png");
    //downButton = QPixmap("../img/down_red_button.png");
    downButton = QPixmap("../img/down.png");
    curState = upButton;
    //
    setGeometry(curState.rect()); //по размеру картинки
    mediaPlayer = new QMediaPlayer(parrent);
    mediaPlayer->setSource(QUrl::fromLocalFile("/Users/alexander/CLionProjects/module38/RedButton/sound/kick.mp3"));
    QAudioOutput *audioOutput = new QAudioOutput;
    mediaPlayer->setAudioOutput(audioOutput);
    audioOutput->setVolume(100);

    anim = new QPropertyAnimation(this, "geometry");
    anim->setDuration(1000); // продолжительность анимации в миллисекундах
    anim->setStartValue(QRect(350, 200, 100, 30)); // начальное значение
    anim->setEndValue(QRect(50, 200, 50, 0)); // конечное значение

    connect(this, &QPushButton::clicked, [this]()
            {
              /*  if(is_down) {
                    setUp();
                    setWindowTitle("Kick ME");
                    mediaPlayer->play();

                }
                else {*/
                    setDown();
                    setWindowTitle("knockOUT");
                    mediaPlayer->play();
                    anim->start();
                    QTimer::singleShot(1000, this, [this](){
                        anim->stop();
                        move(700,200);
                        setUp();
                        setWindowTitle("Kick ME");
                        mediaPlayer->stop();
                    });
                //}



            }
    );

}

void RedButton::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.drawPixmap(e->rect(), this->curState); // так мы рисуем кнопку
}

QSize RedButton::sizeHint() const
{
    return QSize(200,200);
}

QSize RedButton::minimumSizeHint() const
{
    return sizeHint();
}

void RedButton::keyPressEvent(QKeyEvent *e)
{
    setDown();

}

void RedButton::setDown()
{
    curState=downButton;
    is_down=true;
    std::cout << "down"<<std::endl;
    update();
}

void RedButton::setUp()
{
    curState=upButton;
    is_down= false;
    std::cout << "up"<<std::endl;
    update();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RedButton* redButton = new RedButton(nullptr);
//    redButton->setWindowTitle("Red Button");
    redButton->setFixedSize(250,500);
    redButton->move(700,200);
    redButton->show();
    return a.exec();
}

#include <main.moc>
