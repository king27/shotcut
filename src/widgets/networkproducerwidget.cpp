/*
 * Copyright (c) 2012 Meltytech, LLC
 * Author: Dan Dennedy <dan@dennedy.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "networkproducerwidget.h"
#include "ui_networkproducerwidget.h"
#include "mltcontroller.h"

NetworkProducerWidget::NetworkProducerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetworkProducerWidget)
{
    ui->setupUi(this);
    ui->applyButton->hide();
    ui->preset->saveDefaultPreset(*getPreset());
    ui->preset->loadPresets();
}

NetworkProducerWidget::~NetworkProducerWidget()
{
    delete ui;
}

Mlt::Producer* NetworkProducerWidget::producer(Mlt::Profile& profile)
{
    Mlt::Producer* p = new Mlt::Producer(profile, ui->urlLineEdit->text().toUtf8().constData());
    return p;
}

Mlt::Properties* NetworkProducerWidget::getPreset() const
{
    Mlt::Properties* p = new Mlt::Properties;
    p->set("resource", ui->urlLineEdit->text().toUtf8().constData());
    return p;
}

void NetworkProducerWidget::loadPreset(Mlt::Properties& p)
{
    ui->urlLineEdit->setText(p.get("resource"));
}

void NetworkProducerWidget::on_preset_selected(void* p)
{
    Mlt::Properties* properties = (Mlt::Properties*) p;
    loadPreset(*properties);
    delete properties;
}

void NetworkProducerWidget::on_preset_saveClicked()
{
    ui->preset->savePreset(getPreset());
}

void NetworkProducerWidget::setProducer(Mlt::Producer* producer)
{
    ui->applyButton->show();
    if (producer)
        loadPreset(*producer);
}

void NetworkProducerWidget::on_applyButton_clicked()
{
    MLT.setProducer(producer(MLT.profile()));
    MLT.play();
}
