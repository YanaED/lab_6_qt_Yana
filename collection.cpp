#include "collection.h"


Collection::Collection(QWidget* parent) : QWidget(parent)
{
    layout = new QVBoxLayout();
    this->setLayout(layout);
    add_button = new QPushButton("Add new widget");
    delete_button = new QPushButton("Delete widget");
    layout->addWidget(add_button);
    layout->addWidget(delete_button);
    add_widget(new QLabel("label_1"));
    add_widget(new QSlider(Qt::Horizontal));
    add_widget(new QScrollBar(Qt::Horizontal));
    add_widget(new QSpinBox());
    connect(add_button, SIGNAL(clicked()), this, SLOT(click_slot()));
    connect(delete_button, SIGNAL(clicked()), this, SLOT(click_slot()));
}

Collection::~Collection() {
}

void Collection::click_slot() {
    if (QObject::sender() == add_button) {
        srand(time(0));
        int rand_num = rand() % 3;
        switch (rand_num) {
        case 0:
        {
            QLabel* w1 = new QLabel("new label");
            add_widget(w1);
            break;
        }
        case 1:
        {
            QSlider* w2 = new QSlider(Qt::Horizontal);
            add_widget(w2);
            break;
        }
        case 2:
        {
            QScrollBar* w3 = new QScrollBar(Qt::Horizontal);
            add_widget(w3);
            break;
        }
        case 3:
        {
            QSpinBox* w4 = new QSpinBox();
            add_widget(w4);
            break;
        }
        default:
            break;
        }
    }
    else if (QObject::sender() == delete_button) {
        //если в списке виджетов > 1 виджета,
        //то удаляем рандомный
        if (widgets_collection.size() > 1) {
            srand(time(0));
            int rand_num = rand() % widgets_collection.size();
            remove_widget(rand_num);
        }
        //если виджетов <= 1, то удаляем 1ый
        else if (widgets_collection.size() == 1) {
            remove_widget(0);
        }
        else {
            QLabel* label = new QLabel("Nothing to delete");
            layout->addWidget(label);
        }
    }
}

void Collection::add_widget(QWidget* wid) {
    widgets_collection.push_back(wid);
    layout->addWidget(wid);
    connect_widget(wid);
}


void Collection::connect_widget(QWidget* wid) {
    QString name = wid->metaObject()->className();
    if (name == QString("QLabel")) {
        connect(this, &Collection::text_changed, static_cast<QLabel*>(wid), &QLabel::setText);
    }
    else if (name == QString("QSlider") || name == QString("QScrollBar")) {
        connect(static_cast<QAbstractSlider*>(wid), &QAbstractSlider::valueChanged, this, &Collection::get_signal);
        connect(this, &Collection::value_changed, static_cast<QAbstractSlider*>(wid), &QAbstractSlider::setValue);

    }
    else if (name == QString("QSpinBox")) {

        connect(static_cast<QSpinBox*>(wid), SIGNAL(valueChanged(int)), this, SLOT(get_signal(int)));
        connect(this, &Collection::value_changed, static_cast<QSpinBox*>(wid), &QSpinBox::setValue);
    }
    emit value_changed(data);
}

void Collection::get_signal(int value)
{
    if (data != value) {
        emit value_changed(value);
        emit text_changed(QString::number(value));
        data = value;
    }
}

void Collection::disconnect_widget(int ind) {
    QString name = widgets_collection[ind]->metaObject()->className();
    if (name == QString("QLabel")) {
        disconnect(this, &Collection::text_changed, static_cast<QLabel*>(widgets_collection[ind]), &QLabel::setText);
    }
    else if (name == QString("QSlider") || name == QString("QScrollBar")) {

        disconnect(static_cast<QAbstractSlider*>(widgets_collection[ind]), &QAbstractSlider::valueChanged, this, &Collection::get_signal);
        disconnect(this, &Collection::value_changed, static_cast<QAbstractSlider*>(widgets_collection[ind]), &QAbstractSlider::setValue);
    }
    else if (name == QString("QSpinBox")) {

        disconnect(static_cast<QSpinBox*>(widgets_collection[ind]), SIGNAL(valueChanged(int)), this, SLOT(get_signal(int)));
        disconnect(this, &Collection::value_changed, static_cast<QSpinBox*>(widgets_collection[ind]), &QSpinBox::setValue);
    }
}

void Collection::remove_widget(int num) {
    disconnect_widget(num);
    layout->removeWidget(*(widgets_collection.begin() + num));
    QWidget* w = widgets_collection[num];
    widgets_collection.erase(widgets_collection.begin() + num);
    delete w;
}