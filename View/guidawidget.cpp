#include "guidawidget.h"
#include <QTextBrowser>

GuidaWidget::GuidaWidget(QWidget *parent): QWidget(parent){
    setWindowTitle("Guida");
    setWindowIcon(QIcon(":res/icons/menubar/guida.png"));
    setMinimumSize(QSize(800, 600));
    setMaximumSize(QSize(1024, 720));

    QTextBrowser *tb = new QTextBrowser;
    tb->setOpenExternalLinks(true);
    tb->setSource(QUrl("qrc:res/guida.html"));


    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(tb);
    setLayout(layout);

    // Shortcut Ctrl+H per chiudere il widget
    QShortcut* shortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_H), this);
    connect(shortcut, &QShortcut::activated, [=]{
        close();
    });
}

GuidaWidget::~GuidaWidget() = default;
